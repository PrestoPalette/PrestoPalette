FROM fedora:26

# Set the working directory to /app
WORKDIR /app

# Copy the current directory contents into the container at /app
ADD . /app

RUN dnf install -y \
	cmake \
	git \
	qtcreator \
	qt5-devel \
	pngcrush

CMD ["bash", "/app/app/build.sh"]
