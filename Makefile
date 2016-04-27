# Necessary hack due to school server's configuration
export LD_LIBRARY_PATH := /usr/local/share/Qt-5.5.1/5.5/gcc_64/lib:${LD_LIBRARY_PATH}

all:
	cd src/ && $(MAKE) all

clean:
	$(RM) docs/*
	cd src/ && $(MAKE) clean

run:
	./hra2016
