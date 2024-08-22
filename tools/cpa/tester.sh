#!/bin/sh

# need to define that in case this script is not called from tool_tester.sh
PROJ_DIR=$(dirname "$0")/../..
export PROJ_DIR

. $PROJ_DIR/tools/common.sh

string_in_output(){
  if [ "$(grep -c "$1" "$2")" -gt 0 ]; then
    return 0
  else
    return 1
  fi
}

static_opts="-preprocess -predicateAnalysis -setprop analysis.stopAfterError=false -benchmark -heap 2000M"
random_opts=$(set_analyzer_opts 'cpa')

echo cpa.sh $static_opts $random_opts

~/CPAchecker-2.2-unix/scripts/cpa.sh $static_opts $random_opts $f > $out_f 2>&1

if string_in_output 'Exception in' $out_f; then
  printf "CPA crashed on benchmark %s\n" $f
  exit 1
elif ! string_in_output 'Verification result: FALSE\|Verification result: TRUE' $out_f; then
  echo "no verification result produced by CPAchecker"
  exit 2
fi

cat $out_f