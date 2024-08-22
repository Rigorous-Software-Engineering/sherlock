import re

def live_variables_of(c_file):
    lvars_list = []  # lvars_list[i] contains live variables at line number i + 1
    stack = []
    for loc in c_file.readlines():
        block_is_well_defined = (stack != [])  # loc is in a function and ...
        for char in loc:
            if char == '{':
                block_is_well_defined = False
                stack.append([])
            elif char == '}':
                block_is_well_defined = False
                stack.pop()
        if block_is_well_defined:
            new_lvar = get_var_name(loc)
            if new_lvar is not None:
                stack[len(stack) - 1].append(new_lvar)
            current_lvars = collect_lvars(stack)
        else:
            current_lvars = set()
        lvars_list.append(current_lvars)
    assert stack == []
    c_file.seek(0)  # set back file pointer for instrumentation pass
    return lvars_list


def collect_lvars(stack):
    lvars = set()
    for block_lvars in stack:
        lvars.update(block_lvars)
    return lvars


# returns the name of a variable which can be (more or less safely) parsed from a LOC or None if no variable name
# could be parsed
def get_var_name(line):
    # this pattern matches any line defining the identifier on the LHS of an assignment followed by '=',
    # followed by some other character c which is different from '='
    line=line.strip()
    match_res_primitive = re.search("(^| )([_a-zA-Z][_a-zA-Z0-9]*) *=[^=]", line)
    match_res_array = re.search("(^)([_a-zA-Z][_a-zA-Z0-9]* *(\[.*\])+) *=[^=]", line)
    match = match_res_primitive or match_res_array
    if match is not None:
        return match.group(2)
