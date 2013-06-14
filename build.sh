#!/bin/bash

# build.sh [board-name] [compile | burn]
#
# compile is the default option for 2nd argument

if [[ -z "$1" ]]
then
	echo "board-name missing, try 'head ./build.sh'"
	exit 1
fi

export PROGNAME=diy-vt100
export SRC_DIR=$PWD
export HW_DIR=$PWD/board/$1
export BUILD_DIR=$PWD/build
export INCLUDE_DIR=$SRC_DIR/include

cd $HW_DIR
make $2
