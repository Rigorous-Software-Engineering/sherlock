#!/bin/sh
# need to define that in case this script is not called from tool_tester.sh
PROJ_DIR=$(dirname "$0")/../..
export PROJ_DIR

. $PROJ_DIR/tools/common.sh

random_opts=$(set_analyzer_opts 'cbmc')

echo cbmc $random_opts
cbmc $random_opts $f > $out_f
cat $out_f

if [ "$(grep -c ' Results:' $out_f)" -ne 1 ]; then
  echo "execution did not terminate successfully"
  exit 1
fi
