CXX = g++
CPPFLAGS = -g -Wall
BIN_DIR = exe

all: alisttest
	./$(BIN_DIR)/lab3


$(BIN_DIR)/alisttest: alistint.o $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) $(BIN_DIR)/alistint.o $(BIN_DIR)/alisttest.o -o $(BIN_DIR)/alisttest

$(BIN_DIR)/alisttest.o: alisttest.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -c alisttest.cpp -o $(BIN_DIR)/alisttest.o 

$(BIN_DIR)/alistint.o: alistint.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -c alistint.cpp -o $(BIN_DIR)/alistint.o 

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp
