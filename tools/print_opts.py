import json
import random
import sys
from getopt import getopt

def usage():
    print("usage: %s <json-file> -s <seed>" % sys.argv[0])
    exit(1)

def print_random_options(opt_dict):
    for opt_entry in opt_dict:
        key_str = ""
        if opt_entry["name"] != "":
            key_str = opt_entry["name"] + "="
        print_str = key_str + random.choice(opt_entry["possible_values"])
        print(print_str, end=' ')

if __name__ == '__main__':
    if len(sys.argv) < 2:
        usage()
    opts, args = getopt(sys.argv[2:], "s:")
    seed = None
    for o, a in opts:
        if o == "-s":
            seed = int(a)
        else:
            usage()
    if seed is None:
        usage()
    f = open(sys.argv[1])
    data = json.load(f)
    random.seed(seed)
    print_random_options(data)
    f.close()