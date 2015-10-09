#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <sstream>
#include <locale>
#include "webpage.h"
#include "searcheng.h"
#include "myset.h"
#include "mdpageparser.h"
#include "pageparser.h"


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
  PageParser* parser = new MDPageParser;
  string index = argv[1];
  search.add_parse_from_index_file(index, parser);



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

    //initialize all of my variables
    int i = 0;
    //int words = 0;
    bool And = false;
    bool Or = false;
    string check;
    string operation;
    MySetWebPage results;
    string added;
    //int count = 0;
    bool leave = false;

    //check if person entered a period
    if (myline[i] == '.') {
      break;
    }

    //load their words into string stream to inputted one at a time
    istringstream stream (myline);
    while(stream >> operation && leave == false) {
      for (int i = 0; i < int(operation.size()); i++) {
        if (operation[i] < 92) {
                operation[i] = operation[i] + 32;
            }
      }
      //if (And == false && Or == false) {
        //stream >> operation;
      //}

      //if they load operators
      if (operation == "and") {
        And = true;
      }
      else if (operation == "or") {
        Or = true;
      }

      //check for one word and if not one word then you back out
      if (And == false && Or == false) {
        if (!(stream >> operation)) {
          for (int i = 0; i < int(operation.size()); i++) {
            if (operation[i] < 92) {
              operation[i] = operation[i] + 32;
            }
            results = search.ONE_function(operation);
          }
          display_results(results);
        }

        else {
          cout << "Since you did not add an AND or OR to your search, we can only search for one item" << endl;
          leave = true;
          // NEED TO GET OUT OF THIS ENTIRE THING NOW
          
          }
          
      }

      //check for AND
      else if (And == true && Or == false) {
        stream >> added;
        results = search.ONE_function(added);
        while(stream >> added) {
          //stream >> added;
          
          for (int i = 0; i < int(added.size()); i++) {
            if (added[i] < 92) {
              added[i] = added[i] + 32;
            }
          }
          //tolower(added, added);
          results = search.AND_function(added, results);
          //count++;
        }
        //if (count < 1) {
          //cout << "ERROR!" << endl;
          //leave = true;
        //}
        //else {
        display_results(results);
      //}
      }

      //check for OR
      else if (And == false && Or == true) {
        stream >> operation;
        results = search.ONE_function(operation);
        while(stream >> added) {
          //stream >> added;

          for (int i = 0; i < int(added.size()); i++) {
            if (added[i] < 92) {
              added[i] = added[i] + 32;
            }
          }
          results = search.OR_function(added, results);
          //count++;
        }
        //if (count < 1) {
          //cout << "ERROR!" << endl;
          //leave = true;
        //}
        //else {
        display_results(results);
      //}
      }

    }

    



  }
  delete parser;
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
