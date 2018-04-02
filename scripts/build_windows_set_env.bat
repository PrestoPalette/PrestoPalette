@ECHO OFF

PUSHD "%~dp0"

cd ..

set QTDIR=c:\Qt\5.10.1\msvc2017_64
set PATH=%QTDIR%\bin;%PATH%;
set PATH=C:\Program Files (x86)\Inno Setup 5;%PATH%;

POPD
