import re

from .abs_tester import TesterInterface
from constraint.land import And
from constraint.lor import Or


class EsbmcTester(TesterInterface):
    def __init__(self):
        TesterInterface.__init__(self,"esbmc", [And,Or])

    def find_error_ids(self, output_f):
        match_objs=list(re.finditer('file .* line ([0-9]+) column .* function .*\n  assertion',output_f.read()))
        return set(map(lambda match:int(match.group(1)), match_objs))