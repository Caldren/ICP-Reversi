# Necessary hacks due to school server's configuration
export LD_LIBRARY_PATH:=/usr/local/share/Qt-5.5.1/5.5/gcc_64/lib:${LD_LIBRARY_PATH}

all:
	cd src/ && $(MAKE) all

clean:
	$(RM) -r doc/*
	cd src/ && $(MAKE) clean

doxygen:
	doxygen conf/doxygen.conf

run:
	./hra2016
