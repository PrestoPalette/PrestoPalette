[![Build Status](https://travis-ci.org/PrestoPalette/PrestoPalette.svg?branch=master)](https://travis-ci.org/PrestoPalette/PrestoPalette) 
[![Build Status](https://ci.appveyor.com/api/projects/status/github/prestopalette/prestopalette?svg=true&passingText=AppVeyor)](https://ci.appveyor.com/project/dagostinelli/prestopalette) 


# PrestoPalette

**A tool for artists to create harmonious color palettes in seconds**

![](https://raw.githubusercontent.com/PrestoPalette/PrestoPalette-Packaging/master/screenshots/1.png)

Install (easy way)
-------

- <a href="https://github.com/PrestoPalette/PrestoPalette/releases">Windows</a>
- Mac - Help us by becoming a packager for Mac OSX (the app already builds for Mac) (See Package Maintainers section below)
- Linux Fedora - `sudo dnf install prestopalette`
- Linux RedHat / CentOS - Install EPEL, then `sudo yum install prestopalette`
- Linux Other - You may fetch the source and compile it yourself. See below.

Install (hard way - compile it yourself)
-----------------------

There are mulitple ways to do this.  

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

**Qt Creator**

```
1. git clone https://github.com/PrestoPalette/PrestoPalette
2. Launch Qt Creator
3. Open the PrestoPalette directory with Qt Creator
4. Build and Run 
```

How to Help
-----------

**Package Maintainers**

We are looking for package maintainers.  Head over to [PrestoPalette-Packaging](https://github.com/PrestoPalette/PrestoPalette-Packaging) and help us out!

**Features**

Send us a Pull Request or file an issue to start the conversation.
