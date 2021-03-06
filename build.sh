#!/bin/bash

# build.sh [port] [compile | burn]
#
# compile is the default option for 2nd argument

if [[ -z "$1" ]]
then
	echo "port missing, try 'head ./build.sh'"
	exit 1
fi

export PROGNAME=diy-vt100
export SRC_DIR=$PWD
export PORT_DIR=$PWD/port/$1
export BUILD_DIR=$PWD/build
export INCLUDE_DIR=$SRC_DIR/include

cd $PORT_DIR
make $2
