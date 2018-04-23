#!/bin/bash

pushd `pwd`

cd $(dirname $(realpath -s "$BASH_SOURCE"))

./fix_graphics.sh

cd ..
qmake -config debug_and_release PrestoPalette.pro
make all

popd
