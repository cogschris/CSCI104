#include "main_window.h"
#include <QApplication>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <set>
//#include "crawler.h"

using namespace std;



void build_index(std::vector<string> links, string output);
void parse(string filename, std::set<string> &allLinks, std::vector<string> &outie);


std::map<string, string> crawl(string input, std::map<string, string> &items) {
	
	/*istringstream line (input);
	string temp;
	string file;
	string output;
	
	

	while (line>>temp) {
		if(temp == "INDEX_FILE") {
			line >> file;
			line >> file;
		}
		else if(temp == "OUTPUT_FILE") {
			line >> output;
			line >> output;
		}
	
	}*/

	ifstream starter;
	starter.open(input.c_str());

	while (!starter.eof()) {
		bool invalid = false;

		string temp;
		getline(starter, temp);
		string parameter;
		string value;
		bool useful = false;

		for(int i = 0; i < int(temp.size()); i++) {
			if (temp[i] == '#') {
				invalid = true;
				if (invalid == false && useful == true && !value.empty()) {
					useful = false;
					items[parameter] = value;
					
					parameter.clear();
					value.clear();
				}
			}

			else if (temp[i] == ' ') {
				if (invalid == false && useful == true && !value.empty()) {
					useful = false;
					items[parameter] = value;
					parameter.clear();
					value.clear();
				}
			}

			else if (temp[i] == '=') {
				useful = true;
			}

			else if((isalpha(temp[i]) && useful == true) || ((temp[i] >= 48) && (temp[i] <= 57) && useful == true) || ((temp[i] == '/' || temp[i] == '.') && useful == true)) {
				value += temp[i];
				
			}
			else if((isalpha(temp[i]) && useful == false) || (((temp[i] == '_' || temp[i] == '/' || temp[i] == '.') && isalpha(temp[i+1]) && useful == false))) {
				parameter += temp[i];
			}


		}
		if (invalid == false && useful == true && !value.empty()) {
					useful = false;
					
					items.insert(std::make_pair(parameter, value));
					
					parameter.clear();
					value.clear();
				}
	}

	//output = out;''
	string file;
	string check;
	check = items["INDEX_FILE"];
	
	string final;
	final = items["OUTPUT_FILE"];
	//cout << final << endl;
	ifstream index;
	index.open(check.c_str());
	ofstream alllinks;
	alllinks.open(final.c_str());
	
	//ofstream alllinks(output);
	std::set<string> links;
	std::vector<string> outie;

//alllinks << "file" << endl;
	while (index >> file) {

		if (links.find(file) == links.end()) {
			links.insert(file);
			outie.push_back(file);
			//cout << file << endl;
			//alllinks << file << "\n";
			// alllinks.write(file.c_str(),file.size());
			//cout << "got here" << endl;
			parse(file, links, outie);


		}
		
	}
	build_index(outie, final);
	alllinks.close();
	index.close();
	return items;
	
}


void build_index(std::vector<string> links, string output) {
	ofstream alllinks;
	alllinks.open(output.c_str());
	
	
	std::vector<string>::iterator it;
	
	for (it = links.begin(); it != links.end(); ++it) {
		alllinks << *it << "\n";
		
	}
	
	alllinks.close();

}

void parse(string filename, std::set<string> &allLinks, std::vector<string> &outie) {
	//ofstream alllinks;
	//alllinks.open(output.c_str());
	//alllinks << filename << "\n";
	ifstream text;
	text.open(filename.c_str());

	string load;

	while (getline(text, load)) {
		
		int size = int(load.size());
		bool specialpunc = false;
		string enter;
		bool front = false;
		bool back = false;
		bool check = false;

		for (int i = 0; i < size; i++) {
			//if its alpha, then pass into new string
			if (isalpha(load[i])) {
				if (load[i] < 91 && specialpunc == false) {
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
				//allWords.insert(enter);
				
				string enter;
				specialpunc = true;
			}

			

			else if (load[i] == ')') {
				//std::set<string>::iterator it;
				if (allLinks.find(enter) == allLinks.end()) {
					allLinks.insert(enter);
					outie.push_back(enter);
					parse(enter, allLinks, outie);
				}

				//parse(enter, allLinks);
				enter.clear();
				string enter;
				specialpunc = false;
				check = false;
				front = false;
				back = false;
			}

			else if (!(isalpha(load[i])) && specialpunc == true) {
				enter = enter + load[i];
			}

			//if it is not an alpha or a space, and the punctuation is false, then end
			//and start over

			else if (!(isalpha(load[i])) && specialpunc == false) {
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
				//allWords.insert(enter);
				
				enter.clear();
				string enter;
			}
		}
	}
	//alllinks.close();
}

int main (int argc, char* argv[]) {
	
	string config;
	if (argc >= 2) {
		config = argv[2];
		crawl(config);
	}

	else {
		config = "config.txt";
		
		crawl(config);
		
	}

	return 0;
}