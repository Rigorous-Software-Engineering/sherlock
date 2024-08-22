import os
import sys
import re

from tool.abs_tester import get_tester
#usage: metamorphic_checker.py <tool-name> <error-relation> <c-file1> <c-file2>


if __name__ == '__main__':
    if len(sys.argv) != 5:
        print("expected for arguments: " + str(sys.argv))
        exit(2)
    sys.path.append(os.path.dirname(sys.argv[0]) + "/..") # to enable imports from locations outside of tool_result
    tool_name = sys.argv[1]
    relation_str = sys.argv[2]
    tester = get_tester(tool_name)
    initial_lines = open(sys.argv[3]).readlines()
    transformed_lines = open(sys.argv[4]).readlines()
    initial_errors = tester.find_error_ids(open(sys.argv[3] + "_out.txt"))
    transformed_errors = tester.find_error_ids(open(sys.argv[4] + "_out.txt"))
    if relation_str == "subset":
        for initial_error_id in initial_errors:
            initial_line = initial_lines[initial_error_id - 1]
            # check if initial_line is an instrumented assertion (and not e.g. '__VERIFIER_ERROR();')
            if re.match('.*//i_code:[0-9]+', initial_line):
                # check if assertion was untouched:
                if initial_line in transformed_lines:
                    transformed_error_id = transformed_lines.index(initial_line) + 1 # use +1 to compensate for indexing in list
                    if transformed_error_id not in transformed_errors:
                        print(transformed_error_id)
                        print("metamorphic relation violated")
                        print("witness: line %d: %s" % (initial_error_id, initial_line))
                        exit(0)
        exit(17)
    elif relation_str == "equal":
        for initial_error_id in initial_errors:
            initial_assertion = initial_lines[initial_error_id - 1]
            if initial_assertion not in transformed_lines:
                print("warning metamorphic relation holds because failing assertion is modified")
                print(initial_lines[initial_error_id - 1])
                print(transformed_lines[initial_error_id - 1])
                exit(17)
        if initial_errors != transformed_errors and (len(initial_errors) > 0 or len(transformed_errors) > 0):
            print("metamorphic relation violated")
            exit(0)
        else:
            exit(17)
    else:
        print("relation " + relation_str + " not implemented")
        exit(2)

