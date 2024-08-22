from .abs_tester import TesterInterface
from constraint.land import And

class ClamTester(TesterInterface):
    def __init__(self):
        TesterInterface.__init__(self,"clam",[And], assert_fnc_name="__CRAB_assert")


    def find_error_ids(self, output_f):
        assertion_ids=set()
        for line in output_f:
            if "Result" in line and "FAIL" in line:
                items=line.split(" ")
                assertion_ids.add(int(items[4].split("=")[1]))
        return assertion_ids