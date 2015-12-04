BIN_DIR = bin
CXX = g++
CPPFLAGS = -Wall -g



$(BIN_DIR)/doublet: $(BIN_DIR)/hash.o $(BIN_DIR)/minheap.o $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) $(BIN_DIR)/hash.o $(BIN_DIR)/minheap.o doublet.cpp -o $(BIN_DIR)/doublet

$(BIN_DIR)/hash.o: hash.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -c hash.cpp -o $(BIN_DIR)/hash.o

$(BIN_DIR)/minheap.o: minheap.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -c minheap.cpp -o $(BIN_DIR)/minheap.o

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamps