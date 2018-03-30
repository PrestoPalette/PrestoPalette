#!/bin/bash

pushd `pwd`

./fix_graphics.sh

cd ..
rm -rf build

#qmake-qt5 -config debug PrestoPalette.pro
mingw64-qmake-qt5 -config release PrestoPalette.pro
make -j5

popd
