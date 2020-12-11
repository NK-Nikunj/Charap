include ../../Makefile.common

TEST_DIR=$(BASE_DIR)/../tests
LIBS_DIR=$(BASE_DIR)

all: vector

vector: vector.C vector.ci
	$(CHARMC) -E vector.ci
	$(CHARMC) $< -L$(LIBS_DIR) -lcharap -I$(BASE_DIR) -I$(BASE_DIR)/backend -o $@ ${OPTS}
