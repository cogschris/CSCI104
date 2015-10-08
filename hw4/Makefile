BIN_DIR = bin
CXX = g++
CPPFLAGS = -Wall -g


search: search.cpp webpage.o searcheng.o myset.o mdpageparser.o 
	$(CXX) $(CPPFLAGS) webpage.o searcheng.o myset.o mdpageparser.o search.cpp -o search

myset.o: myset.cpp 
	$(CXX) $(CPPFLAGS) -c myset.cpp -o myset.o

mdpageparser.o: mdpageparser.cpp pageparser.h
	$(CXX) $(CPPFLAGS) -c mdpageparser.cpp -o mdpageparser.o

webpage.o: webpage.cpp 
	$(CXX) $(CPPFLAGS) -c webpage.cpp -o webpage.o

searcheng.o: searcheng.cpp 
	$(CXX) $(CPPFLAGS) -c searcheng.cpp -o searcheng.o

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamps


