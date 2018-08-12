#!/bin/bash

pushd `pwd`

cd $(dirname $(readlink -f -s "$BASH_SOURCE"))

export PATH=/usr/local/opt/qt5/bin:$PATH

cd ..
rm -rf build
mkdir build
cd build

cmake -G "Unix Makefiles" .. -DCMAKE_INSTALL_PREFIX=../install -DCMAKE_BUILD_TYPE=Release \
&& make -j 7 \
&& cpack -G "TGZ"

popd
