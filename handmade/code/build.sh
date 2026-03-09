#!/bin/bash
set -e

mkdir -p ../../build
pushd ../../build
clang ../handmade/code/sdl_handmade.cpp -o handmadehero -g $(sdl2-config --cflags --libs) -lm
popd
