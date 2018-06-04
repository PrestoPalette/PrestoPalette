[![Build Status](https://travis-ci.org/PrestoPalette/PrestoPalette.svg?branch=master)](https://travis-ci.org/PrestoPalette/PrestoPalette) 
[![Build Status](https://ci.appveyor.com/api/projects/status/github/prestopalette/prestopalette?svg=true&passingText=AppVeyor)](https://ci.appveyor.com/project/dagostinelli/prestopalette) 


# PrestoPalette

**A tool for artists to create harmonious color palettes in seconds**

<img src="https://raw.githubusercontent.com/PrestoPalette/PrestoPalette-Packaging/master/screenshots/1.png"/>

Downloading and Installing
--------------------------
<a href="https://github.com/PrestoPalette/PrestoPalette/releases">For latest version, click here</a>

Building for Development
------------------------

**(Easiest) Use Qt Creator**

```
1. git clone https://github.com/PrestoPalette/PrestoPalette
2. Launch Qt Creator
3. Open the PrestoPalette directory with Qt Creator
4. Build and Run 
```

**Fedora (Red Hat Enterprise / CentOS)**

```
git clone https://github.com/PrestoPalette/PrestoPalette
cd PrestoPalette
cd scripts
./setup_fedora.sh
./build_fedora.sh
```

**Ubuntu**

```
git clone https://github.com/PrestoPalette/PrestoPalette
cd PrestoPalette
cd scripts
./setup_ubuntu.sh
./build_qmake.sh
```

**macOS**

```
   brew update > /dev/null
&& brew install qt5 > /dev/null
&& brew install pngcrush > /dev/null
&& export PATH=/usr/local/opt/qt5/bin/:$PATH

git clone https://github.com/PrestoPalette/PrestoPalette
cd PrestoPalette
cd scripts
./build_osx.sh
```

How to Package
--------------

<a href="https://github.com/PrestoPalette/PrestoPalette-Packaging">For packaging directions, click here</a>
