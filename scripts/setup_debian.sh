#!/bin/bash

set -e
set -x

apt-get update -y
apt-get upgrade -y
apt-get install -y git g++ make
apt-get install -y pngcrush
apt-get install -y qt5-default qtmultimedia5-dev
