#!/bin/sh

# need to define that in case this script is not called from tool_tester.sh
PROJ_DIR=$(dirname "$0")/../..
export PROJ_DIR

. $PROJ_DIR/tools/common.sh

random_opts=$(set_analyzer_opts 'clam')

clam.py --crab-check=assert -g $random_opts $f > $out_f
if [ "$(wc -l < $out_f)" -le 4 ]; then # check if clam produced more than just header lines
  echo "clam aborted";
  exit 124;
elif [ "$(grep -c 'ANALYSIS RESULTS' $out_f)" -eq 0 ]; then
  echo "clam error or abort"; tail $out_f;
  exit 3
fi

cat $out_f