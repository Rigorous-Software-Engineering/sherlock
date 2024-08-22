import re

from .abs_tester import TesterInterface
from constraint.land import And
from constraint.lor import Or

class KleeTester(TesterInterface):
    def __init__(self):
        TesterInterface.__init__(self,"klee", [And,Or])

    def find_error_ids(self, output_f):
        match_objs=list(re.finditer('KLEE: ERROR: .*\.c:([0-9]+): ASSERTION FAIL:',output_f.read()))
        return set(map(lambda match:int(match.group(1)), match_objs))