#!/bin/bash

pushd `pwd`

./fix_graphics.sh

cd ..
qmake-qt5 -config debug_and_release PrestoPalette.pro
make all -j5

popd
