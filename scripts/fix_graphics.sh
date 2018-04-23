#!/bin/bash

pushd `pwd`

cd $(dirname $(realpath -s "$BASH_SOURCE"))

cd ../graphics

find . -maxdepth 1 -type f -iname '*.png' -exec pngcrush -ow -rem allb -reduce {} \;

popd
