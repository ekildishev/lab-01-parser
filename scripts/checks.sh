  
#!/bin/sh
set -e

files=`find . -name "*.cpp" | grep -v "./tools/*"`
filter=-build/c++11,-runtime/references,-whitespace/braces,-whitespace/indent,-whitespace/comments,-build/include_order
echo $files | xargs cpplint --filter=$filter

export CTEST_OUTPUT_ON_FAILURE=true
# address sanitizer
#CMAKE_LINKER_OPTS="-DCMAKE_EXE_LINKER='-fuse-ld=gold'"
CMAKE_CONFIG_OPTS="-DHUNTER_CONFIGURATION_TYPES=Debug -DCMAKE_BUILD_TYPE=Debug"
CMAKE_TOOLCHAIN_OPTS="-DCMAKE_TOOLCHAIN_FILE='`pwd`/tools/polly/sanitize-address-cxx17-pic.cmake'"
CMAKE_OPTS="$CMAKE_LINKER_OPTS $CMAKE_CONFIG_OPTS $CMAKE_TOOLCHAIN_OPTS"
cmake -H. -B_builds/sanitize-address-cxx17 $CMAKE_OPTS
cmake --build _builds/sanitize-address-cxx17