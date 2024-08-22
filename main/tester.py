import os
import sys
import time
from getopt import getopt
import random

from file_context import FileContext
from constraint.constraint_builder import ConstraintBuilder
from tool_result.tool.abs_tester import get_tester
from tool_result.querier import Querier
from transform.state import initial_state
from transform.strengthening_transformation import StrengtheningTransformationExpectation
from transform.weakening_transformation import WeakeningTransformationExpectation
from transform.weaken_invariant_transformation import WeakenInvariantTransformationExpectation

from cov import coverage


# describes allowed operators for 'AND' and OR
constraint_builder = None
tester= None
csv_file = open(os.environ['PROJ_DIR'] + os.sep + "out.csv",'a')
pool_map = dict()
ITERATIONS_WITHOUT_MOD=100

def usage():
    print("usage: %s <c-file-path> -s <seed> -t <tool> [-b <loop_bound>] [-S <analyzer_seed>] [-l <ttl>] [-w <seconds>] [-c] [-y] [-i] " % sys.argv[0])
    exit(1)

def write_bug_files(initial_s, querier, transformation_name, transformed_state_id):
    bug_base_dir = os.environ['PROJ_DIR'] + os.sep + "bug_files" + os.sep
    bug_dirs = os.listdir(bug_base_dir) # the files shall be named '1', '2', ...
    new_idx = 1
    if bug_dirs:
        last_idx = max(map(int,bug_dirs))
        new_idx = last_idx + 1
    os.mkdir(bug_base_dir + str(new_idx))
    dst_dir = bug_base_dir + str(new_idx)
    querier.write_state(open(dst_dir + os.sep + "initial.c", 'w'),querier.seed_f, initial_s)
    output_dir = os.environ['PROJ_DIR'] + os.sep + "output_files" + os.sep
    os.system("cp %s %s" % (output_dir + "test%d.c" % transformed_state_id, dst_dir + os.sep + transformation_name + ".c"))

def do_iterative_testing(instrumentable_lines, transformations, querier):
    start_time = time.time()
    no_mod_cnt = 0
    i = 0
    while not budget_exceeded(i, no_mod_cnt):
        i+=1
        no_mod_cnt+=1
        state = random.choice(list(pool_map.values()))
        state.ttl-=1
        # determine which transformations are applicable for a random LOC
        reference_loc_nr = random.choice(instrumentable_lines) #  the LOC nr that determines the type of transformation
        transformation = random.choice(list(filter(lambda t : t.can_be_applied_for(state, reference_loc_nr), transformations)))
        new_state, ex_time =  transformation.transform(state, querier, instrumentable_lines, reference_loc_nr)
        csv_file.write("%s,%s,%d,%d,%d,%s,%d," % (tester.bench_dir, tester.bench_name, seed, len(pool_map), state.id,
                                                  transformation.name, new_state.id))
        # check if execution set the 'failing_assertions' correctly == execution was successful
        if new_state is None or new_state.get_failing_assertions() is None:  #or :
            csv_file.write("?,?,?,?,%f,,REJECT,ERR\n" % (time.time() - start_time))
        else:
            print("%d assertions failing in new state " % len(new_state.get_failing_assertions()))
            csv_file.write("%d,%d,%d,%f,%f,\"%s\"," % (len(new_state.get_failing_assertions()),
                                                       len(new_state.get_all_assertions()), len(new_state.get_all_assumptions()),
                                                       ex_time, (time.time() - start_time), str(new_state.single_transformations_lst)))
            failure_witnesses = transformation.get_expectation_failure_witnesses()
            if failure_witnesses: # there are witnesses for failure
                csv_file.write(",FAIL\n")
                print("found a bug")
                print("we got %d witnesses: %s " % (len(failure_witnesses), str(list(map(str, failure_witnesses)))))
                print("chain of transformations: " + str(new_state.transformations_lst))
                # copy files to bug_files
                write_bug_files(state, querier, transformation.name, new_state.id)
                if not continue_testing:
                    print("stopping for this seed file")
                    exit(2)
            else: # there are no failure-witnesses
                cov_str = coverage.get_coverage_str(new_state)
                if cov_str in pool_map:
                    covered_state = pool_map[cov_str]
                    if covered_state.ttl <= 0:
                        csv_file.write("REPLACE,PASS\n")
                        pool_map[cov_str] = new_state
                        print("replacing old state by new state")
                    else:
                        csv_file.write("REJECT,PASS\n")
                        print("rejecting new state")
                else:
                    pool_map[cov_str] = new_state
                    csv_file.write("ACCEPT,PASS,\n")
                    print("accepting new state")
                    no_mod_cnt=0
        # empty output files
        os.system("rm -rf " + os.environ['PROJ_DIR'] + os.sep + "output_files" + os.sep + "*")
        csv_file.flush()

def test(f_ctx, max_ttl):
    init_state = initial_state(len(f_ctx.lvars_partition[0]), max_ttl)
    querier=Querier(f_ctx.file, tester)
    init_state.set_failing_assertions(set())
    pool_map[coverage.get_coverage_str(init_state)] = init_state
    csv_file.write("\n%s,%s,%d,0,0,init,,0,0,0,0,0,[]," % (tester.bench_dir, tester.bench_name, tester.tool_seed))
    instrumentable_lines = f_ctx.get_instrumentable_line_nrs(symbolic_constraints_only)
    if instrumentable_lines:
        csv_file.write("ACCEPT\n")
        transformations = [WeakeningTransformationExpectation(f_ctx),
                           StrengtheningTransformationExpectation(f_ctx,constraint_builder),
                           WeakenInvariantTransformationExpectation(f_ctx)]
        do_iterative_testing(instrumentable_lines, transformations, querier)
    else:
        print("no instrumentable lines, returning")
        csv_file.write("ERROR\n")


def main(max_ttl):
    output_fs_path = os.path.dirname(os.path.dirname(__file__)) + "/output_files" # parent directory path of current file
    orig_f_path = output_fs_path + "/orig.c"
    with open(orig_f_path, 'r') as orig_f:
        f_ctx = FileContext(orig_f, always_instrument)
        test(f_ctx, max_ttl)


if __name__ == "__main__":
    if len(sys.argv) < 1:
        print("not enough arguments provided")
        usage()
    seed=random.randrange(10000000) # may be overwritten by option -s
    waiting_time = 30 # may be overwritten by option -w
    symbolic_constraints_only = False
    budget_exceeded = lambda i, no_mod_c : False # default: never abort
    tool_seed = None
    continue_testing=False
    always_instrument = False # whether to instrument before seeing any branching instruction (if, while, ...)
    ttl = float("inf") # infinite ttl as standard value
    tool_options = None
    opts, args = getopt(sys.argv[1:], "b:s:o:l:yt:iw:c")
    for o, a in opts:
        if o == "-b":
            iterations = a
            budget_exceeded = lambda i, no_mod_c: i >= int(iterations) or no_mod_c >= ITERATIONS_WITHOUT_MOD
        elif o == "-s":
            seed = int(a)
        elif o == "-o":
            tool_options=a
        elif o == "-l":
            ttl = int(a)
        elif o == "-y":
            symbolic_constraints_only = True
        elif o == "-i":
            always_instrument = True
        elif o == "-t":
            tester=get_tester(a)
        elif o == "-w":
            waiting_time=int(a)
        elif o == "-c":
            continue_testing=True
        else:
            print("unexpected option: " + o)
            usage()
    if tester is None:
        print("required options are: -t")
        usage()
    random.seed(seed)
    tester.tool_options = tool_options # can be None
    tester.tool_seed = seed
    bench_path = sys.argv[len(sys.argv) -1]
    tester.bench_dir = os.path.dirname(bench_path)
    tester.bench_name = os.path.basename(bench_path)
    tester.waiting_time = waiting_time
    constraint_builder = ConstraintBuilder(symbolic_constraints_only, tester.supported_forms)
    main(ttl)
    csv_file.close()
