#!/bin/bash

pushd `pwd`

./fix_graphics.sh

cd ..
rm -rf build
mkdir build
cd build

cmake -G "Unix Makefiles" .. -DCMAKE_INSTALL_PREFIX=../install -DCMAKE_BUILD_TYPE=Debug
make -j 7 && ctest && make install && cpack -G "TGZ"

popd
