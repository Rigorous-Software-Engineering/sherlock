import os

def get_tester(tool_name):
    if tool_name == "klee":
        from .klee import KleeTester
        return KleeTester()
    elif tool_name == "cbmc":
        from .cbmc import CbmcTester
        return CbmcTester()
    elif tool_name == "clam":
        from .clam import ClamTester
        return ClamTester()
    elif tool_name == "cpa":
        from .cpa import CpaTester
        return CpaTester()
    elif tool_name == "esbmc":
        from .esbmc import EsbmcTester
        return EsbmcTester()
    elif tool_name == "ultimate":
        from .ultimate import UltimateTester
        return UltimateTester()
    elif tool_name == "mopsa":
        from .mopsa import MopsaTester
        return MopsaTester()
    elif tool_name == "symbiotic":
        from .symbiotic import SymbioticTester
        return SymbioticTester()
    else:
        raise NotImplementedError("tool %s is not supported" % tool_name)

class TesterInterface:
    def __init__(self, tool_name, supported_forms, assert_fnc_name="assert", assume_fnc_name="__VERIFIER_assume"):
        self.tool_name = tool_name
        self.tool_seed = None
        self.tool_options=None
        self.waiting_time = 30
        self.assert_fnc_name = assert_fnc_name
        self.assume_fnc_name = assume_fnc_name
        self.supported_forms = supported_forms
        self.bench_dir = None
        self.bench_name = None

    def find_error_ids(self,output_f):
        pass

    def get_tester_path(self):
        proj_path=os.environ['PROJ_DIR'] + os.sep
        tool_dir_path=proj_path+"tools"+os.sep+self.tool_name+os.sep
        return tool_dir_path + "tester.sh"