#ifndef CRAWLER
#define CRAWLER

#include "crawler.h"
#include "mdpageparser.h"
#include <sstream>
#include <fstream>
#include "searcheng.h"
#include <iostream>
#include "webpage.h"
#include "myset.h"

class Crawler {
 public:
  Crawler(std::string input);
  ~Crawler();
  std::string out();
  void build_index(WebPage* web);

 

 private:
 	MySetWebPage<T> alpha;
 	std::string output;
 	std::string file;
 	std::string out;









#endif