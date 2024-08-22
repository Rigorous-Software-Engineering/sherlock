from .abs_tester import TesterInterface
from constraint.land import And
from constraint.lor import Or
import re

def __extract_loc_identifier__(re_s):
    id_with_tail = re_s.split(" ")[2]
    return int(id_with_tail[:len(id_with_tail)-1])

class CpaTester(TesterInterface):
    def __init__(self):
        TesterInterface.__init__(self,"cpa", [And,Or])

    # re_s has form '<id>:'

    def find_error_ids(self, output_f):
        ids_with_prefix = re.findall('in line [0-9]*:',output_f.read())
        return list(map(__extract_loc_identifier__, ids_with_prefix))