@ECHO OFF

PUSHD "%~dp0"

cd ..

REM RELEASE MODE
rmdir /s /q build
qmake.exe -config release PrestoPalette.pro
nmake
windeployqt.exe build\release\PrestoPalette.exe
iscc PrestoPalette.iss "/DCustomBinaryLocation=build\release"
nmake clean

REM DEBUG MODE
rmdir /s /q build
qmake.exe -config debug PrestoPalette.pro
nmake
windeployqt.exe build\debug\PrestoPalette.exe
iscc PrestoPalette.iss "/DCustomBinaryLocation=build\debug" "/DConfiguration=Debug"
nmake clean

POPD
