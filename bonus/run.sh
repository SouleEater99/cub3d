#!/bin/bash

if [ $# -ne 1 ]; then
    
    echo "USAGE: <./run.sh map_path>"
    exit 1
fi

echo "$1"

make run MAP=$1
make fclean
# make clean