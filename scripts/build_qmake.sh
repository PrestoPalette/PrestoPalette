#!/bin/bash

set -e
set -x

pushd `pwd`

cd $(dirname $(realpath -s "$BASH_SOURCE"))

./fix_graphics.sh

cd ..
qmake -config debug_and_release PrestoPalette.pro
make all -j4

popd
