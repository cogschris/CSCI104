CC       = g++
CPPFLAGS = -g -Wall
BIN_DIR  = bin
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread




$(BIN_DIR)/alisttest: alisttest.cpp $(BIN_DIR)/alistint.o $(BIN_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) alisttest.cpp $(BIN_DIR)/alistint.o $(GTEST_LL) -o $(BIN_DIR)/alisttest

$(BIN_DIR)/alisttest: problem5.cpp $(BIN_DIR)/alistint.o $(BIN_DIR)/stackint.o $(BIN_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) problem5.cpp $(BIN_DIR)/alistint.o $(BIN_DIR)/stackint.o -o $(BIN_DIR)/problem5

$(BIN_DIR)/alistint.o: alistint.o $(BIN_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) -c alistint.cpp -o $(BIN_DIR)/alistint.o

$(BIN_DIR)/alistint.o: alistint.o $(BIN_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) -c alistint.cpp -o $(BIN_DIR)/alistint.o

$(BIN_DIR)/stackint.o: stackint.o $(BIN_DIR)/.dirstamp
	$(CC) $(CPPFLAGS) -c stackint.cpp -o $(BIN_DIR)/stackint.o

.PHONY: clean

clean:
	rm -rf $(BIN_DIR)

alisttest: $(BIN_DIR)/alisttest
	-@$(BIN_DIR)/alisttest
	-@echo "--- All Tested!---"

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamps