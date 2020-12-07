include ../Makefile.common

TEST_DIR=$(BASE_DIR)/../tests
LIBS_DIR=$(BASE_DIR)

all: test_vector

.PHONY: test_vector

test_vector: $(TEST_DIR)/test_vector.C $(TEST_DIR)/test_vector.ci
	$(CHARMC) -E test_vector.ci; $(CHARMC) $< -L$(LIBS_DIR) -lcharap -I$(BASE_DIR) -I$(BASE_DIR)/backend -o $@
