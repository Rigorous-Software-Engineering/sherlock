import re
import sys


def __is_instrumentation_line__(loc):
    return re.match('.*//i_code:[0-9]+',loc) is not None


# usage: equalizer.py initial.c strengthen.c
if __name__ == '__main__':
    lines_initial = open(sys.argv[1]).readlines()
    lines_transformed = open(sys.argv[2]).readlines()

    for line_nr in range(0, len(lines_transformed)):
        if __is_instrumentation_line__(lines_transformed[line_nr]) != __is_instrumentation_line__(lines_initial[line_nr]):
            lines_initial.insert(line_nr, "//\n")

    with open(sys.argv[1], 'w') as initial_f:
        initial_f.writelines(lines_initial)
