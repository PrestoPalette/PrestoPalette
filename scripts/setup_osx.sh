#!/bin/bash

set -e
set -x

brew update
brew install qt5
brew install pngcrush
export PATH=/usr/local/opt/qt5/bin/:$PATH
