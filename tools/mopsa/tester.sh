#!/bin/sh
# need to define that in case this script is not called from tool_tester.sh
PROJ_DIR=$(dirname "$0")/../..
export PROJ_DIR

. $PROJ_DIR/tools/common.sh


random_opts=$(set_analyzer_opts 'mopsa')
static_opts="-no-color"
tool_binary="$HOME/mopsa-analyzer/bin/mopsa"

echo $tool_binary $static_opts $random_opts

$tool_binary $static_opts $random_opts $f > $out_f

cat $out_f
if [ "$(grep -c 'Analysis terminated successfully' $out_f)" -ne 1 ]; then
  echo "mopsa aborted"
  exit 124
fi