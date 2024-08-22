import re

from .abs_tester import TesterInterface
from constraint.land import And
from constraint.lor import Or

def __extract_loc_identifier__(re_s):
    return int(re_s.split(" ")[1])

class SymbioticTester(TesterInterface):
    def __init__(self):
        TesterInterface.__init__(self,"symbiotic", [And,Or])

    def find_error_ids(self, output_f):
        ids_with_junk=re.findall('\nLine: .*',output_f.read())
        return list(map(__extract_loc_identifier__, ids_with_junk))