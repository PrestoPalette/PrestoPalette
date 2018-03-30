@ECHO OFF

PUSHD "%~dp0"

cd ..

qmake.exe -config release PrestoPalette.pro
nmake
windeployqt.exe build\release\PrestoPalette.exe
cp PrestoPalette.iss build\release
cp icon.bmp build\release
iscc build\release\PrestoPalette.iss

POPD
