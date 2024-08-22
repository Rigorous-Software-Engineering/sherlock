#!/bin/sh

usage() { echo "Usage: $0 [-s <seed> | -o <analyzer_options>]" 1>&2; exit 1; }

# to be called from tools/.. scripts (with tool name as $1)
set_analyzer_opts(){
  if [ -n "$options" ]; then
    echo $options
  elif [ -n "$seed" ]; then
    python3 $PROJ_DIR/tools/print_opts.py $PROJ_DIR/tools/$1/tool_options.json -s $seed # outputs random options
  else
    python3 $PROJ_DIR/tools/print_opts.py $PROJ_DIR/tools/$1/tool_options.json -s 1
  fi
}

while getopts "I:s:o:" o; do
  case "${o}" in
    s) # the seed is used for choosing (random) parameters for the tool
      seed=$OPTARG;;
    o) # alternatively specify the parameters explicitly
      options=$OPTARG;;
    *)
      usage
      ;;
  esac
done
shift $((OPTIND-1))

export f=$1
export out_f=$1"_out.txt"
