FROM fedora:26

WORKDIR /workdir
ADD . /workdir

RUN dnf install -y \
	cmake \
	git \
	qtcreator \
	qt5-devel \
	pngcrush

WORKDIR /workdir
CMD ["bash", "cd scripts && ./docker-worker.sh"]
