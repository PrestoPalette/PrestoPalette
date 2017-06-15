#!/bin/bash

pushd `pwd`

cd ../graphics

find . -maxdepth 1 -type f -iname '*.png' -exec pngcrush -ow -rem allb -reduce {} \;

popd
