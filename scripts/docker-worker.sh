#! /bin/bash

pushd `pwd`

./build_linux-debug.sh
./build_linux-release.sh

popd
