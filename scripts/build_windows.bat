@ECHO OFF

PUSHD "%~dp0"

cd ..

qmake.exe -config debug_and_release PrestoPalette.pro
nmake all
windeployqt.exe build\debug\PrestoPalette.exe
windeployqt.exe build\release\PrestoPalette.exe
iscc PrestoPalette.iss "/DCustomBinaryLocation=build\release"
iscc PrestoPalette.iss "/DCustomBinaryLocation=build\debug" "/DConfiguration=Debug"

POPD
