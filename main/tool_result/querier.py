import os
import signal
import subprocess
import time

from transform.state import State

class ToolException(Exception):
    pass

class Querier:

    C_HEADER = """#include <assert.h>
    extern void __VERIFIER_assume(int cond);
    """

    def __init__(self, seed_f, tester):
        self.seed_f = seed_f
        self.tester = tester
        self.__reset_out_info__()

    def __reset_out_info__(self):
        self.curr_out_line_nr = self.C_HEADER.count('\n')
        self.assertion_loc_dict = dict()


    #sets variables curr_out_line_nr and assertions_loc_dict
    def write_state(self, output_f, seed_f, state: State):
        self.__reset_out_info__()
        output_f.write(self.C_HEADER)
        seed_f.seek(0)
        code_lines = seed_f.readlines()
        for line_nr in range(0,len(code_lines)):
            # write code from seed file
            output_f.write(code_lines[line_nr])
            self.curr_out_line_nr += 1

            # write code from instrumentation
            assertions_str = self.__get_instrumentation__(state.assertions_dict[line_nr],True)
            assumptions_str = self.__get_instrumentation__(state.assumptions_dict[line_nr], False)
            instrumentation_str = assertions_str + assumptions_str
            output_f.write(instrumentation_str)


    def __get_instrumentation__(self, instrumentation:list, is_assert):
        lines = ""
        if is_assert:
            instr_string= self.tester.assert_fnc_name
        else:
            instr_string = self.tester.assume_fnc_name
        instr_string+="(%s);"
        for constraint in instrumentation:
            lines+= instr_string % constraint
            lines+= " //i_code:"  + str(hash(constraint)) + "\n"
            self.curr_out_line_nr += 1
            if is_assert:
                # save which constraint is on which LOC in the output file
                self.assertion_loc_dict.update({self.curr_out_line_nr : constraint})
        return lines

    def set_failing_assertions_for(self, state: State):
        # generate the test file from the state
        output_files_path=os.environ['PROJ_DIR'] + os.sep + "output_files" + os.sep
        test_f_name = "test%d.c" % state.id
        test_f = open(output_files_path + test_f_name, "w")
        self.write_state(test_f, self.seed_f, state)
        test_f.close()
        time_before = time.time()
        # invoke the tool on the test file
        args = [self.tester.get_tester_path()]
        if self.tester.tool_options is None:
            # specify tool seed if no analyzers were set explicitly
            args.extend(["-s", str(self.tester.tool_seed)])
        else:
            args.extend(["-o", self.tester.tool_options])
        args.append(test_f.name)
        p = subprocess.Popen(args, stderr=subprocess.DEVNULL, stdout=subprocess.DEVNULL,
                             start_new_session=True)
        try:
            print("waiting %d seconds:" % self.tester.waiting_time)
            ex_code = p.wait(timeout=self.tester.waiting_time)
            if ex_code != 0:
                print("tool invocation failed with exit code %d" % ex_code)
                return -1
        except subprocess.TimeoutExpired:
            os.killpg(os.getpgid(p.pid), signal.SIGTERM)
            print("timeout encountered")
            return -1
        time_after = time.time()
        # traverse the output of the tool and return the assertions that failed
        out_f = open(output_files_path + test_f_name + "_out.txt",'r')
        err_ids = self.tester.find_error_ids(out_f)
        print("error ids are: " + str(err_ids))
        out_f.close()
        # transform the error ids to the 'constraint' objects stored in the state
        result = set()
        for err_id in err_ids:
            # check that the assertion which the tool reported as falling was actually added to the code by instrumentation
            if err_id in self.assertion_loc_dict:
                result.add(self.assertion_loc_dict[err_id])
            else:
                print("error id %d not found in state" % err_id)
        state.set_failing_assertions(result)
        return time_after - time_before