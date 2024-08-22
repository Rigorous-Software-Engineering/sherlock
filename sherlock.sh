#!/usr/bin/env sh
usage() { echo "Usage: $0 -t <tool_name> [-s <seed>] [-o <analyzer_options>] [-b <budget>] [-w <seconds>] [-c] [-1] [<test-path>]" 1>&2; }

csv_header="directory,file,Seed,pool size,prev id,transformation type,id,#failing assertions,#assertions,#assumptions,analyzer time,elapsed time,transformation chain,transformation accept,PASS/FAIL"

empty_output_files(){
  rm -rf /tmp/esbmc*
  rm -rf $PROJ_DIR/output_files/*
}

get_new_seed(){
  awk -v sd="$1" 'BEGIN { srand(sd); print int( rand()*10000000 ) }'
}

get_random_value_for(){
  len=$(jq ".$1 | length" $json_f)
  idx=$(echo "$len*$seed_now/10000000" | bc)
  rand_val=$(jq ".$1[$idx]" $json_f)
  echo $rand_val
}

set_random_test_args(){
  json_f=$1
  seed_now=$(get_new_seed $seed)
  rand_instrumenter_args=""
  seed_now=$(get_new_seed $seed_now)
  if $(get_random_value_for 'symbolic_constraints_only'); then # in this case we expect a boolean value in the json
     rand_instrumenter_args="${rand_instrumenter_args} -y"
  fi
  seed_now=$(get_new_seed $seed_now)
  if $(get_random_value_for 'always_instrument'); then
    rand_instrumenter_args="${rand_instrumenter_args} -i"
  fi
  seed_now=$(get_new_seed $seed_now)
  if [ -z $waiting_time ]; then
    waiting_time=$(get_random_value_for 'waiting_time')
  fi
}

test_file(){
  input_f=$1
  if ! [ -e $input_f ]; then
    printf "Warning: Input file %s does not exist\n" $input_f
    return
  fi

  json_path="$PROJ_DIR/tools/$tool_name/tester_options.json"
  if ! [ -f $json_path ]; then
    echo "tool $tool_name is not supported, use cbmc, clam, cpa, esbmc, klee, mopsa, symbiotic or ultimate"
    usage
    exit 1
  fi
  set_random_test_args $json_path

  printf "\n******************************************************************************************\n"
  echo "$input_f"
  printf "seed=%d\n" $seed
  # Two initial transformations:
  # 1. Remove comments (gcc -dD -E) to simplify processing of input file (detect loops,...)
  # 2. Undefine some common type/function qualifiers as pycparser library can't handle type/function qualifiers
  (cat $PROJ_DIR/preprocessing/macros_undefine_qualifiers.c;
   cat $PROJ_DIR/preprocessing/ultimate.c
   cat $PROJ_DIR/preprocessing/goblint.c
   cat $PROJ_DIR/preprocessing/cbmc.c
   cat $input_f) | gcc -fpreprocessed -dD -E -P - > $orig_f

  # $analyzer_options must be last argument!
  python3 "$PROJ_DIR/main/tester.py" -w $waiting_time -s $seed $ttl_arg $budget_arg $continue_testing_arg $rand_instrumenter_args -t $tool_name "$analyzer_options" $input_f
}

PROJ_DIR=$(dirname "$0")
export PROJ_DIR

orig_f="$PROJ_DIR/output_files/orig.c" # to store the input file with some preprocessing (comments,...)
bug_dir="$PROJ_DIR/bug_files"
mkdir -p $PROJ_DIR/output_files
mkdir -p $bug_dir

# process variables from command line
one_iteration_only=false
continue_testing_arg="" # set to -c if we should continue testing same seed file after finding a bug

while getopts "s:o:l:b:t:w:1ch" o; do
  case "${o}" in
    s)
      seed=$OPTARG;;
    o)
      analyzer_options="-o $OPTARG";;
    l)
      ttl_arg="-l $OPTARG";;
    b)
      budget_arg="-b $OPTARG";;
    w)
      waiting_time=$OPTARG;;
    t)
      tool_name=$OPTARG;;
    1)
      one_iteration_only=true;;
    c)
      continue_testing_arg="-c";;
    h)
      usage;
      cat $PROJ_DIR/help_msg.txt;
      exit 0;;
    *)
      usage;
      exit 1;;
  esac
done
shift $((OPTIND-1))

if [ -z "$tool_name" ]; then
    echo "required option is -t"
    usage
    exit 1
fi

if ! [ -f $PROJ_DIR/out.csv ]; then
    printf '%s' "$csv_header" > $PROJ_DIR/out.csv
fi
empty_output_files

# set test path if none was provided
test_path=$1
if [ $tool_name = 'clam' ]; then
  if [ -z $test_path ]; then
    test_path="$PROJ_DIR/testfiles/svcomp20"
  fi
fi
if [ -z $test_path ]; then
  test_path="$PROJ_DIR/testfiles/testcomp22"
fi

# set an initial seed if none was provided
if [ -z "$seed" ]; then
  seed=$(od -An -N3 -i /dev/urandom | awk '{printf $1 % 10000000 + 1}')
fi

if [ -d $test_path ]; then
  # if the input file is a directory test all c-files in it in an infinite loop (except -1) is given
  while true; do
    printf "starting with seed %d\n" $seed
    for input_f in $(find "$test_path" -name '*.c' | shuf); do
      test_file $input_f
      empty_output_files
      seed=$(get_new_seed $seed)
    done
    echo "all files tested"
    if $one_iteration_only; then
      break
    fi
  done
else
  # if the input file is a regular file, test only this file
  test_file $test_path
  ex_code=$?
fi
echo "testing done"
exit $ex_code