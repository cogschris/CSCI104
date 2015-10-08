BIN_DIR = bin
CXX = g++
CPPFLAGS = -Wall -g


$(BIN_DIR)/search: search.cpp $(BIN_DIR)/webpage.o $(BIN_DIR)/searcheng.o $(BIN_DIR)/myset.o $(BIN_DIR)/mdpageparser.o $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) $(BIN_DIR)/webpage.o $(BIN_DIR)/searcheng.o $(BIN_DIR)/myset.o $(BIN_DIR)/mdpageparser.o search.cpp -o $(BIN_DIR)/search

$(BIN_DIR)/myset.o: myset.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -c myset.cpp -o $(BIN_DIR)/myset.o

$(BIN_DIR)/mdpageparser.o: mdpageparser.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -c mdpageparser.cpp -o $(BIN_DIR)/mdpageparser.o

$(BIN_DIR)/webpage.o: webpage.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -c webpage.cpp -o $(BIN_DIR)/webpage.o

$(BIN_DIR)/searcheng.o: searcheng.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -c searcheng.cpp -o $(BIN_DIR)/searcheng.o

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamps


	