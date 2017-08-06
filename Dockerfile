FROM ubuntu:xenial

# Set the working directory to /app
WORKDIR /app

# Copy the current directory contents into the container at /app
ADD . /app

RUN apt-get update && apt-get install -y \
	cmake \
	apt-utils \
	git \
	software-properties-common \
	&& add-apt-repository --yes ppa:beineri/opt-qt58-xenial \
	apt-get update && apt-get install -y \
	qt5-qmake \
	qtbase5-dev \
	libqt5xmlpatterns5-dev \
	pngcrush \
	build-essential \
	qtmultimedia5-dev 
	&& rm -rf /var/lib/apt/lists/*

CMD ["bash", "/app/app/build.sh"]
