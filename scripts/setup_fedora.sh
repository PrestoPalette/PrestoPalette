#!/bin/bash

set -e
set -x

dnf install -y \
	clang \
	git \
	qt5-devel \
	pngcrush
