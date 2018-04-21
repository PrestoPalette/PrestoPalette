[![Build Status](https://travis-ci.org/PrestoPalette/PrestoPalette.svg?branch=master)](https://travis-ci.org/PrestoPalette/PrestoPalette) 
[![Build Status](https://ci.appveyor.com/api/projects/status/github/prestopalette/prestopalette?svg=true&passingText=AppVeyor)](https://ci.appveyor.com/project/dagostinelli/prestopalette) 


# PrestoPalette

**A tool for artists to create harmonious color palettes in seconds**

<img src="https://raw.githubusercontent.com/PrestoPalette/PrestoPalette-Packaging/master/screenshots/1.png"/>

Building
--------

**(Easiest) Use QT Creator**

```
1. git clone https://github.com/PrestoPalette/PrestoPalette
2. Launch QT Creator
3. Open the PrestoPalette directory with QT Creator
4. Build and Run 
```
NOTE: PrestoPalette is a CMake QT project.

**Cross-Compile for Windows from Linux using MinGW**

```
git clone https://github.com/PrestoPalette/PrestoPalette
cd PrestoPalette
cd scripts
./build_mingw64-release.sh
cd ../build
ls *.exe
```

**Build Release RPM (Fedora / RedHat / CentOS)**

```
git clone https://github.com/PrestoPalette/PrestoPalette
cd PrestoPalette
cd scripts
./build_linux-release.sh
cd ../build
cpack -G "RPM"
sudo rpm -i PrestoPalette*.rpm
```

**Debug Build for Development (Linux)**

```
git clone https://github.com/PrestoPalette/PrestoPalette
cd PrestoPalette
cd scripts
./build_linux-debug.sh
cd ../build
./prestopalette
```

**Building with CMake Manually**

```
git clone https://github.com/PrestoPalette/PrestoPalette
cd PrestoPalette
mkdir build
cd build
cmake ..
make && make install
```

**Mac OSX**

This is untested, however the steps should be the same as Linux.  Be sure to have at least version 3.0 of cmake installed

```
git clone https://github.com/PrestoPalette/PrestoPalette
cd PrestoPalette
mkdir build
cd build
cmake ..
make
```
