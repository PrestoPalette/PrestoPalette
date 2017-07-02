#!/bin/bash

pushd `pwd`

export PATH=/usr/local/opt/qt5/bin:$PATH

cd ..
rm -rf build
mkdir build
cd build

cmake -G "Unix Makefiles" .. -DCMAKE_INSTALL_PREFIX=../install -DCMAKE_BUILD_TYPE=Release
make -j 7 && ctest && make install && cpack -G "Bundle"

popd
