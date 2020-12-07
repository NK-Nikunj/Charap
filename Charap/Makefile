include ../Makefile.common

all: libs

libs: libcharap.a

.PHONY: distclean clean

libcharap.a: array_t.o
	$(CHARMC) ${LD_OPTS} -o $@ $< -I$(BASE_DIR); rm array_t.o

array_t.o: ${BASE_DIR}/frontend/array_t.C Charap.hpp
	cd backend; $(CHARMC) array_t.ci;
	$(CHARMC) -c ${OPTS} $< -I$(BASE_DIR)

distclean: clean
	rm libcharap.a

clean:
	cd backend; rm *.decl.h *.def.h