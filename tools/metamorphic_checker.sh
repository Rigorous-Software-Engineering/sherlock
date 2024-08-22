#!/bin/bash

PROJ_DIR=$(dirname "$0")/..
export PROJ_DIR

# usage: ./metamorphic_checker.sh <tool-name> <directory>
# <directory> needs to contain the files "initial.c" and one of "weaken.c", "strengthen.c", "weaken-invariant.c", ...

set_params(){
  if [ -f "$bug_dir/$1.c" ]; then
    transformed_f="$bug_dir/$1.c"
    relation=$2
  fi
}

set_params_strengthen(){
if [ -f "$bug_dir/$1.c" ]; then
  relation="subset"
  # exchange initial and transformed file
  transformed_f=$initial_f
  initial_f="$bug_dir/$1.c"
fi
}

analyzer_options_arg="-o "
while getopts "s:o:" o; do
  case "${o}" in
    s)
      seed_arg="-s $OPTARG";;
    o)
      analyzer_options_arg="-o $OPTARG";;
    *)
      usage
      ;;
  esac
done
shift $((OPTIND-1))
tool_name=$1
bug_dir=$2

if ! [ -d $bug_dir ]; then
  echo "error $bug_dir is not a directory"
  exit 124
fi
initial_f="$bug_dir/initial.c"
set_params "weaken" "subset"
set_params "weaken-invariant" "equal"
set_params "weaken-assume" "subset"
set_params_strengthen "strengthen"
set_params_strengthen "strengthen-assume"
set_params_strengthen "add-assume"
set_params_strengthen "add-assert"

if ! [ -f "$initial_f" ]; then
  echo "error initial file $initial_f does not exist"
  exit 124
fi
if ! [ -f "$transformed_f" ]; then
  echo "error transformed file $transformed_f does not exist"
  exit 124
fi

echo $seed_arg $analyzer_options_arg $initial_f
if ! sh $PROJ_DIR/tools/"$tool_name"/tester.sh $seed_arg "$analyzer_options_arg" $initial_f; then
  exit 124 # not interesting because of analyzer error
fi
if ! sh $PROJ_DIR/tools/"$tool_name"/tester.sh $seed_arg "$analyzer_options_arg" $transformed_f; then
  exit 124
fi
python3 $PROJ_DIR/main/tool_result/metamorphic_checker.py $tool_name $relation $initial_f $transformed_f
ex_code=$?
# exiting with exit code from python script
if [ $ex_code -eq 0 ]; then
  mkdir -p $PROJ_DIR/bug_files
  mkdir -p $PROJ_DIR/bug_files/0
  cp -r $PROJ_DIR/output_files/ $PROJ_DIR/bug_files/0
fi
exit $ex_code