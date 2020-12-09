include ../Makefile.common

all: libs

libs: libcharap.a

.PHONY: distclean clean

libcharap.a: operators.o
	$(CHARMC) ${LD_OPTS} -o $@ $< -I$(BASE_DIR); rm operators.o

operators.o: ${BASE_DIR}/frontend/operators.C Charap.hpp
	cd backend; $(CHARMC) operators.ci;
	$(CHARMC) -c ${OPTS} $< -I$(BASE_DIR)

distclean: clean
	rm libcharap.a

clean:
	cd backend; rm *.decl.h *.def.h