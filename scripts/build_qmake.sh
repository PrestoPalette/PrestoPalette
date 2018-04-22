#!/bin/bash

pushd `pwd`

./fix_graphics.sh

cd ..
qmake -config debug_and_release PrestoPalette.pro
make all

popd
