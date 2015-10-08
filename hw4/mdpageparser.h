#ifndef MD_PARSER_H
#define MD_PARSER_H

#include <string>
#include "myset.h"
#include "pageparser.h"

/**
 * Base class for parsers (for some specific
 *  format such as MD or HTML)
 */

class MDPageParser : public PageParser {
 public:
  ~MDPageParser();

  /** 
   * Parses a file and returns all unique words according
   *  to some parser rules and all hyperlinks based 
   *  on the format the parser is designed to implement
   */
  void parse(std::string filename,
		     MySetString& allWords,
		     MySetString& allLinks);
};

#endif