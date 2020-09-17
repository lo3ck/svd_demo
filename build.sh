#!/bin/bash
build_dir=$PWD/../build
output_dir=$PWD/../bin
source_dir=$PWD/

if [ "$1"x = "make"x ]; then
    

    mkdir -p $build_dir
    mkdir -p $output_dir

    cd $build_dir
    cmake $source_dir
    make

    cd $source_dir
    exit
fi


if [ "$1"x = "run"x ]; then
    cd $build_dir
    make
    cd $output_dir
    time ./eigen_demo
    exit
fi

