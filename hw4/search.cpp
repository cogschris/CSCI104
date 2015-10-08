#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <sstream>

#include "webpage.h"
#include "searcheng.h"

using namespace std;

void display_results(set<WebPage*>& results);

int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "usage: ./search index_file...Please provide an index file" << endl;
    return 1;
  }

  /****************   Add code to ***************************/
  /* Initialize your search engine and parse all the pages */
  SearchEng search;
  MDPageParser parser;
  search.add_parse_from_index_file(string(argv[1]), *parser);



  string myline;
  bool done = false;
  while( !done ){
    cout << "\n++++++++++++++++++++" << endl;
    cout << "Enter search terms: " << endl;
    getline(cin, myline);
    cout << "++++++++++++++++++++\n" << endl;

    /* Add your code here and feel free to modify    */
    /*  what is above but don't change the display.  */
    /* Call display_results() with the set of pages  */
    /*  that match the search. It will display the   */
    /*  matching results to the screen for you.      */


    int i = 0;
    int words = 0;
    bool And = false;
    bool Or = false;
    string check;
    string operation;
    MySetWebPage results;
    string added;

    bool leave = false;
    if (myline[i] == '.') {
      break;
    }
    istringstream stream (myline);
    while(!stream.empty() && leave == false) {

      if (And == false && Or == false) {
        stream >> operator;
      }

      if (operation == "AND") {
        And = true;
      }
      else if (operation == "OR") {
        Or = true;
      }


      if (And == false && Or == false) {
        if (!stream.empty()) {
          cout << "Since you did not add an AND or OR to your search, we can only search
          for one item" << endl;
          leave = true;
          // NEED TO GET OUT OF THIS ENTIRE THING NOW
        }

        else {
          operation = tolower(operation);
          results = search.ONE_function(operation);
          display_results(results);
          leave = true;

        }
      }

      else if (And == true && Or == false) {
        results = search.ONE_function(operation);
        while(!stream.empty()) {
          stream >> added;
          results = search.AND_function(added, results);
        }

      }

      else if (And == false && Or == true) {
        results = search.OR_function(operation);
        while(!stream.empty()) {
          stream >> added;
          results = search.OR_function(added, results);
        }

      }
    }

    display_results(results);



    }
  }
  return 0;
}

void display_results(set<WebPage*>& results)
{
  int hits = results.size();
  cout << hits << " hits." << endl;
  cout << "=====" << endl;
  int i=0;
  for(set<WebPage*>::iterator it = results.begin();
      it != results.end();
      ++it)
    {
      cout << (*it)->filename() << endl;
      cout << "+---+" << endl;
      cout << (**it) << "\n" << endl;
      i++;
    }
  
}
