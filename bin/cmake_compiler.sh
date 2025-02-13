#!/bin/bash

build="build"

if [! -d "$build" ]; then
  mkdir "$build"
fi

cd "$build"

cmake .. -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" -DCMAKE_BUILD_TYPE=Release

if [ $? -eq 0 ]; then
  cmake --build. --config Release
  if [ $? -eq 0 ]; then
    echo "Compilation completed successfully."
  else
    echo "Error during compilation."
  fi
else
  echo "Error during configuration with CMake."
fi

cd..