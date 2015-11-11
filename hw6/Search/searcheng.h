#ifndef SEARCHENG_H
#define SEARCHENG_H

#include <map>
#include <vector>
#include <string>
#include <set>
#include "webpage.h"
#include "myset.h"
#include "pageparser.h"

class SearchEng {
 public:
  SearchEng();
  ~SearchEng();
  void add_parse_from_index_file(std::string index_file, PageParser* parser);
  void add_parse_page(std::string filename, PageParser* parser, WebPage* web);
  MySetWebPage OR_function(std::string word, MySetWebPage compare);
  MySetWebPage AND_function(std::string word, MySetWebPage compare);
  MySetWebPage ONE_function(std::string word);
  int num_WebPages();
  MySetWebPage get_total();


  /**** Add other desired member functions here *****/


 private:
  /**** Add other desired data members here *****/
 //	std::map<string, *WebPage> files;
 	std::map<std::string, MySetWebPage> check;
 	MySetWebPage final;
 	int number;
};

#endif
