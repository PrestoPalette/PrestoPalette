#! /bin/bash

export QT_SELECT=qt5
qmake --version

git clone https://github.com/PrestoPalette/PrestoPalette
cd PrestoPalette
cd scripts
./build_linux-debug.sh

# sudo docker build -t PrestoPalette .
# sudo docker run PrestoPalette
# sudo docker run -t -i PrestoPalette /bin/bash
