#!/bin/bash

analyzer_opts=""
export PROJ_DIR=/home/sherlock
. $PROJ_DIR/creduce/interesting.sh
check_interesting "clam"

