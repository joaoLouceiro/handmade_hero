#!/bin/bash
set -e

mkdir -p ../../build
pushd ../../build
bear -o ../compile_commands.json -- \
  clang++ \
  ../handmade/code/unity_build.cpp -o handmadehero \
  $(sdl2-config --cflags --libs) \
  -g \
  -lm \
  -DHANDMADE_SDL=1 \
  -DHANDMADE_SLOW=1 \
  -DHANDMADE_INTERNAL=1 \
  -Wall \
  -Wextra \
  -pedantic \
  -Werror \
  -Wno-unused-variable \
  -Wno-unused-parameter \
  -Wno-writable-strings \
  -Wno-pragma-once-outside-header \
  -Wno-undefined-internal \
  -Wno-missing-field-initializers \
  -Wno-gnu-anonymous-struct \
  -Wno-nested-anon-types \
  -Wno-unused-function \
  -fno-exceptions \
  -fno-rtti
popd
