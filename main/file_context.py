import re

import pycparser
import pycparser_fake_libc
from pycparser import parse_file

from analysis.live_variables import live_variables_of
from analysis import type_extractor, param_live_variables

# makes sure to add instrumentation only at beginning of a block or after a statement
def __can_instrument_after__(loc):
    stripped_line = loc.strip()
    # notice that the following check automatically excludes (multi-line) macro function as these have a tailing '\'
    return stripped_line.endswith(';') or stripped_line.endswith('{')

def __is_branch_instruction__(loc):
    return re.search('(if|while|for|switch) *(\(.*\))',loc) is not None

def __is_main_declaration__(loc):
    return re.search('int *main *\(.*\)',loc) is not None

class FileContext:
    def __init__(self, file, always_instrument):
        try:
            cpp_arg_list = ["-I" + pycparser_fake_libc.directory]
            ast = parse_file(file.name, use_cpp=True, cpp_args=cpp_arg_list)
        except pycparser.plyparser.ParseError as pe:
            print("parse error when trying to extract types from input file: " + str(pe))
            exit(1)
        te = type_extractor.TypeExtractor(ast)
        lvars_list = live_variables_of(file)
        param_live_variables.add_param_lvars(ast, lvars_list) # modifies 'lvars_list'

        # find symbolic and concrete variables
        symbolic_vars_list=[]
        concrete_vars_list=[]
        for lvars in lvars_list:
            # retain all numeric variables which were not introduced during instrumentation
            usable_lvars = list(filter(lambda v : not v.startswith("bnd_cnt_") and te.is_numeric(v), lvars))
            symbolic_vars = list(filter(lambda v: te.is_symbolic(v), usable_lvars))
            concrete_vars = list(filter(lambda v: not te.is_symbolic(v), usable_lvars))
            symbolic_vars_list.append(symbolic_vars)
            concrete_vars_list.append(concrete_vars)
        self.lvars_partition = symbolic_vars_list,concrete_vars_list

        self.always_instrument = always_instrument
        self.code_constants = te.get_constants()
        self.file = file

    # gets all line numbers that have a lvar,
    # in case is_symbolic there needs to be additionally at least one symbolic var
    def get_instrumentable_line_nrs(self, is_symbolic):
        res = []
        symbolic_vars_list, concrete_vars_list = self.lvars_partition
        self.file.seek(0)
        lines = self.file.readlines()
        assert len(lines) == len(symbolic_vars_list)
        if is_symbolic:
            reference_list = symbolic_vars_list
        else:
            reference_list = [s_vars + c_vars for s_vars, c_vars in zip(symbolic_vars_list, concrete_vars_list)]
        allow_instrumentation = self.always_instrument
        for line_nr in range(0,len(lines)):
            if __is_branch_instruction__(lines[line_nr]):
                allow_instrumentation = True
            elif __is_main_declaration__(lines[line_nr]):
                allow_instrumentation = self.always_instrument # reset once you reach declaration of main
            if allow_instrumentation and reference_list[line_nr] and __can_instrument_after__(lines[line_nr]):
                res.append(line_nr)
        return res