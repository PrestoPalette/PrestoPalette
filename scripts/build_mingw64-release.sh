#!/bin/bash

pushd `pwd`

./fix_graphics.sh

cd ..
rm -rf build
mkdir build
cd build

mingw64-cmake -G "Unix Makefiles" .. -DCMAKE_INSTALL_PREFIX=../install -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=/usr/share/mingw/toolchain-mingw64.cmake
make -j 7 && ctest && make install && cpack -G "TGZ" && cpack -G "NSIS64" && exiftool PrestoPalette.exe 

# to make sure the icon is present run this:
# wrestool -x -n MAINICON PrestoPalette.exe 
# wrestool -l PrestoPalette.exe 

# to manually compile the .rc file:
# windres application.rc -O coff -o application.res

popd
