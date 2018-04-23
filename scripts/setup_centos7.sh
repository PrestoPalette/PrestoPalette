#!/bin/bash

set -e
set -x

yum install -y epel-release
yum install -y tar gcc-c++ make 
yum install -y qt5-qtbase-devel qt5-qtmultimedia-devel desktop-file-utils rpm_build rpmdevtools libappstream-glib pngcrush

