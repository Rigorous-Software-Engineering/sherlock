import re

from .abs_tester import TesterInterface
from constraint.land import And
from constraint.lor import Or

class UltimateTester(TesterInterface):
    def __init__(self):
        TesterInterface.__init__(self,"ultimate", [And,Or], assert_fnc_name="__ULTIMATE_assert")

    def find_error_ids(self, output_f):
        ids_as_strings=re.findall('\[L([0-9]+)\] *CALL.*_assert\(.*\)\n.*COND TRUE',output_f.read())
        return list(map(lambda s:int(s), ids_as_strings))