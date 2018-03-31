#!/bin/bash

pushd `pwd`

./fix_graphics.sh

cd ..
rm -rf build

qmake-qt5 -config debug_and_release PrestoPalette.pro
make all -j5

popd
