#!/bin/sh
# need to define that in case this script is not called from tool_tester.sh
PROJ_DIR=$(dirname "$0")/../..
export PROJ_DIR

. $PROJ_DIR/tools/common.sh

klee_aborted_abnormally(){
  klee_output_file=$1
  # match either "KLEE: HaltTimer invoked" or "KLEE: halting execution" in the messages:
  # Both show halt because of abnormal error or timeout
  # Large allocs do not emit any of the other messages (even tough they concretize symbolic size)
  forbidden_regex='KLEE: halt\|KLEE: watchdog exiting\|Large alloc:.*bytes\|KLEE: WARNING: killing [0-9]* states\|KLEE:.*concretiz.*'
  if [ "$(grep -c 'KLEE: done:' $klee_output_file)" -lt 1 ]; then
    return 0
  elif [ "$(grep -ci "$forbidden_regex" $klee_output_file)" -gt 0 ]; then
    return 0
  else
    return 1
  fi
}

# to set a different timeout than 30s, modify klee_static_opts
klee_static_opts="--silent-klee-assume --exit-on-error-type=Model --write-no-tests --max-memory-inhibit=0 --max-time=30s"
random_opts=$(set_analyzer_opts 'klee')
clang_static_opts="-fbracket-depth=512 -emit-llvm -c -g -S -Wno-everything"
linking_files="--override=$PROJ_DIR/tools/klee/instruments.ll"

ll_f=$f'_compiled.ll'
if ! clang $clang_optional_arg $clang_static_opts "$f" -o "$ll_f"; then
  echo "compile error"; exit 3;
fi
linked_f=$f'_linked.ll'
llvm-link -S $linking_files "$ll_f" -o "$linked_f"

# WARNING: Works only as long as KLEE prints it's own info to stderr and the program under test only prints to stdout
echo klee $klee_static_opts $random_opts # print args
klee $klee_static_opts $random_opts "$linked_f" 2> $out_f
cat $out_f

if klee_aborted_abnormally $out_f ; then
    echo "klee aborted"
    exit 124
fi