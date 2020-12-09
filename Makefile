include Makefile.common

all: libs tests

.PHONY: libs tests

libs:
	cd Charap; make

tests:
	cd tests; make
