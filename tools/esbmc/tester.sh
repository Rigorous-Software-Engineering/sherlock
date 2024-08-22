#!/bin/sh
# need to define that in case this script is not called from tool_tester.sh
PROJ_DIR=$(dirname "$0")/../..
export PROJ_DIR

. $PROJ_DIR/tools/common.sh


run_esbmc(){
$tool_binary $static_opts $random_opts $1 > $2 2>&1
}

random_opts=$(set_analyzer_opts 'esbmc')
static_opts="--multi-property"
tool_binary="/home/ESBMC_Project/release/bin/esbmc"

echo $tool_binary $static_opts $random_opts

run_esbmc $f $out_f
cat $out_f
if [ "$(grep -c 'VERIFICATION SUCCESSFUL\|VERIFICATION FAILED' $out_f)" -eq 0 ]; then
  echo "esbmc aborted"
  exit 124
fi