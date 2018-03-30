@ECHO OFF

PUSHD "%~dp0"

cd ..

qmake.exe -config release PrestoPalette.pro
nmake
windeployqt.exe build\release\PrestoPalette.exe
iscc PrestoPalette.iss

POPD
