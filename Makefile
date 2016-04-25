all:
	cd src/ && $(MAKE) all

clean:
	$(RM) docs/*
	cd src/ && $(MAKE) clean
