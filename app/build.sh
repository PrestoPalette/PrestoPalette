#! /bin/bash

export QT_SELECT=qt5
qmake --version

git clone https://github.com/PrestoPalette/PrestoPalette
cd PrestoPalette
cd scripts
./build_linux-debug.sh

# sudo docker build -t build_bot .
# sudo docker run build_bot
# sudo docker run -t -i build_bot /bin/bash
