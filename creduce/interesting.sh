#!/bin/bash

# need to set $assume_fnc_name and $assert_fnc_name
reapply_transformations(){
  # files to be written in this pass:
  while IFS= read -r line; do
    if [[ $line =~ "//i_code" ]]; then
      # find the (first) line number (initial_start_f and transformed_start_f)
      line_nr=$(grep -Fn "$line" $initial_start_f | awk -F':' '{print $1}')
      if ! [[ $line_nr =~ ^[0-9]+$ ]]; then
          echo line nr $line_nr of $line is invalid
          exit 3
      fi
      # now find the weakened assumption in the file transformed_start.c
      transformed_instrumentation=$(sed -n "$line_nr p" < $transformed_start_f)
      if [ -z "$transformed_instrumentation" ]; then
        exit 4
      fi

      echo $transformed_instrumentation >> "$curr_transformed_f"
    else
      echo "$line" >> "$curr_transformed_f"
    fi
    # copy to $curr_initial_f
    echo "$line" >> $curr_initial_f
  done < initial.c # use initial.c from tmp directory!
}

check_interesting(){
  tool_name=$1
  rm -rf $PROJ_DIR/output_files/*
  mkdir -p $PROJ_DIR/output_files
  initial_start_f=$PROJ_DIR/bug_files/1/initial.c
  transformed_f_name=$(ls -I initial.c $PROJ_DIR/bug_files/1)
  transformed_start_f=$PROJ_DIR/bug_files/1/$transformed_f_name
  curr_initial_f="$PROJ_DIR/output_files/initial.c"
  curr_transformed_f="$PROJ_DIR/output_files/$transformed_f_name"
  reapply_transformations
  $PROJ_DIR/tools/metamorphic_checker.sh -o "$analyzer_opts" $tool_name $PROJ_DIR/output_files
}
