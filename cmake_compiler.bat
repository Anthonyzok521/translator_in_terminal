@echo off

set "build=build"

if not exist "%build%" (
  mkdir build
)

cd build

cmake .. -DCMAKE_TOOLCHAIN_FILE="%VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake" -DCMAKE_BUILD_TYPE=Release

if %errorlevel% == 0 (
  cmake --build . --config Release
  if %errorlevel% == 0 (
    echo Compilation completed successfully.
  ) else (
    echo Error during compilation.
  )
) else (
  echo Error during configuration with CMake.
)

cd ..