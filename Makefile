# Necessary hacks due to school server's configuration
export LD_LIBRARY_PATH:=/usr/local/share/Qt-5.5.1/5.5/gcc_64/lib:${LD_LIBRARY_PATH}

all:
	cd src/ && $(MAKE) all

clean:
	$(RM) -r doc/* qt.conf
	cd src/ && $(MAKE) clean

doxygen:
	doxygen conf/doxygen.conf

run:
ifndef DEBUG
	# Yet another hack for our school server
	cp conf/qt.conf .
else
	$(RM) qt.conf
endif
	./hra2016 &>/dev/null &
	./hra2016-cli

pack:
	# Remove generated configuration if exists
	$(RM) -r doc/*
	# Create doc folder if it doesn't exist
	mkdir -p doc/
	# Remove archive if exists
	$(RM) xsumsa01.tar.gz
	# Create final archive
	tar pczvf xsumsa01.tar.gz \
		src/*.cpp \
		src/*.hpp \
		src/GUI.pro \
		src/Makefile \
		Makefile \
		README.txt \
		conf/*.conf \
		examples/*.sav \
		doc/
