import re

from .abs_tester import TesterInterface
from constraint.land import And
from constraint.lor import Or

class MopsaTester(TesterInterface):
    def __init__(self):
        TesterInterface.__init__(self,"mopsa", [And,Or], assert_fnc_name="_mopsa_assert",
                                 assume_fnc_name="_mopsa_assume")

    def find_error_ids(self, output_f):
        match_objs=list(re.finditer('.c:([0-9]+).*Assertion failure',output_f.read()))
        return set(map(lambda match:int(match.group(1)), match_objs))