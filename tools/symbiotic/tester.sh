#!/bin/sh
# need to define that in case this script is not called from tool_tester.sh
PROJ_DIR=$(dirname "$0")/../..
export PROJ_DIR

. $PROJ_DIR/tools/common.sh

run_symbiotic(){
  $executable_path $random_opts $1 1> $2
  cat $2
}

random_opts=$(set_analyzer_opts 'symbiotic')
executable_path="$HOME/symbiotic/bin/symbiotic"

echo $executable_path $random_opts
run_symbiotic $f $out_f

if [ "$(grep -Ec 'RESULT: (true|false)' $out_f)" -ne 1 ]; then
  echo "execution did not terminate successfully"
  exit 124
fi