#!/bin/bash

build_dir=$PWD/../build
output_dir=$PWD/../bin
source_dir=$PWD/

mkdir -p $build_dir
mkdir -p $output_dir

cd $build_dir
cmake $source_dir
make

cd $source_dir