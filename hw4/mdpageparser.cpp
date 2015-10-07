#include "pageparser.h"
#include "mdpageparser.h"
#include "myset.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

MDPageParser::~MDPageParser() {

}

void MDPageParser::parse(string filename, MySetString& allWords, MySetString& allLinks) {

	ifstream text;
	text.open(filename.c_str());

	string load;

	while (!text.eof()) {
		getline(text, load);
		int size = load.size();
		bool specialpunc = false;
		string enter;
		bool front = false;
		bool back = false;
		bool check = false;

		for (int i = 0; i < size; i++) {
			//if its alpha, then pass into new string
			if (isalpha(load[i])) {
				if (load[i] < 91) {
					load[i] = load[i] + 32;
				}
				enter = enter + load[i];

				if (check == true) {
					check = false;
					front = false;
					back = false;
				}
			}


			//if it is an ( then end everything and start over with the new link
			//also start initialize the bool so that its true to pass through "."
			else if (load[i] == '(' && front == true && back == true) {
				check = false;
				front = false;
				back = false;
				allWords.insert(enter);
				string enter;
				specialpunc = true;
			}

			else if (!isalpha(load[i]) && specialpunc == true) {
				enter = enter + load[i];
			}

			else if (load[i] == ')') {
				allLinks.insert(enter);
				string enter;
				specialpunc = false;
			}

			//if it is not an alpha or a space, and the punctuation is false, then end
			//and start over

			else if (!isalpha(load[i]) && specialpunc == false) {
				if (check == true) {
					check = false;
					front = false;
					back = false;
				}
				if(load[i] == '[') {
					front = true;
				}
				if (load[i] == ']' && front == true) {
					back = true;
					check = true;
				}
				allWords.insert(enter);
				string enter;
			}
		}
	}
}