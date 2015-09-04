/*
Author: Chris Cognetta
email: ccognett@usc.edu

This program takes in a large text file and analyzes each word. The program then
will take appropriate action and print the answers in another text file
*/


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

int main(int argc, char* argv[]) {

	if(argc < 2) {
		cout << "Please make sure to include the input and output text files" << endl;
		return 1;
	}

	//loading the files
	ifstream links;
	links.open(argv[1]);
	ofstream write;
	write.open(argv[2]);


	string phrase;
	
	//write << phrase << endl;
	
	string temp;
	while (!links.eof()) {
		//loading each word
		links >> phrase;

		//basically if the file has a bracket then search for a '('
		if (phrase[0] == '[') {
			int i = 0;
			int paren = 0;
			int link_present = 0;
			while (phrase[i] != '\0') {
				if (phrase[i] == '(') {
					paren = i;
					link_present = 1;
				}
				i++;
			}
			if (link_present == 1) {
				write << "LINK (";
				for (int j = paren + 1; phrase[j] != ')'; j++) {
					write << phrase[j];
				}
				write << ", ";
				for (int j = 1; phrase[j] != ']'; j++) {
					write << phrase[j];
				}
				write << ")" << endl;
			}

			//otherwise just ignore the brackets
			else {
				int final = 0;
				for (int j = 1; phrase[j] != '\0' && phrase[j] != ']'; j++) {
					write << phrase[j];
					final++;
				}
				write << endl;
				if (phrase[final + 1] == ']' && phrase[final + 2] != '\0') {
					for (int j = final + 2; phrase[j] != '\0'; j++) {
						write << phrase[j];
					}
					write << endl;
				}
			}	
		}

		//if '(' then make sure to say it twice
		else if (phrase[0] == '(') {
			int final = 0;
			write << "LINK (";
			for (int i = 1; phrase[i] != ')'; i++) {
				write << phrase[i];
				final++;
			}
			write << ", ";
			for (int i = 1; phrase[i] != ')'; i++) {
				write << phrase[i]; 
			}
			write << ")" << endl;
			
			if (phrase[final + 1] == ')' && phrase[final + 2] != '\0') {
					for (int j = final + 2; phrase[j] != '\0'; j++) {
						write << phrase[j];
					}
					write << endl;
				}
		}
		// for normal words
		else if ((phrase[0] > 47 && phrase[0] < 58) || (phrase[0] > 65 && phrase[0] < 91) || (phrase[0] > 96 && phrase[0] < 123)) {
			for (int i = 0; phrase[i] != '\0'; i++) {
				//this extra if statement to not include numbers
				if ((phrase[i] > 65 && phrase[i] < 91) || (phrase[i] > 96 && phrase[i] < 123)) {
					write << phrase[i];
				}
			}
			write << endl;
		}
	
	}

	//deallocate
	links.close();
	write.close();
	return 0;
	
}