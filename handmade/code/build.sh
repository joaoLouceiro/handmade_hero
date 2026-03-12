#!/bin/bash
set -e

mkdir -p ../../build
pushd ../../build
clang -DHANDMADE_SDL=1 ../handmade/code/unity_build.cpp -o handmadehero -g $(sdl2-config --cflags --libs) -lm
popd
