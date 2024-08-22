#!/bin/sh
# need to define that in case this script is not called from tool_tester.sh
PROJ_DIR=$(dirname "$0")/../..
export PROJ_DIR

. $PROJ_DIR/tools/common.sh

run_ultimate(){
   $executable_path $static_opts $random_opts --file $1 > $2
  cat $2
}

random_opts=$(set_analyzer_opts 'ultimate')
static_opts="--architecture 64bit  --spec $PROJ_DIR/tools/ultimate/unreach-call.prp --procedureinliner.inline.calls.to.implemented.procedures ALWAYS --procedureinliner.ignore.calls.to.procedures.called.more.than.once NEVER --traceabstraction.stop.after.first.violation.was.found false --rcfgbuilder.add.additional.assume.for.each.assert false --full-output"
executable_path="$HOME/UAutomizer-linux/Ultimate.py"

echo $executable_path $static_opts $random_opts
run_ultimate $f $out_f

if [ "$(grep -zPc 'Result:\n(TRUE|FALSE)' $out_f)" -ne 1 ]; then
  echo "execution did not terminate successfully"
  exit 124
fi