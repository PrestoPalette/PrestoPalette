#!/bin/bash

set -e
set -x

pushd `pwd`

cd $(dirname $(realpath -s "$BASH_SOURCE"))

./fix_graphics.sh

cd ..
qmake-qt5 -config debug_and_release PrestoPalette.pro
make all

popd
