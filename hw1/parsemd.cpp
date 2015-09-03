#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

int main(int argc, char* argv[]) {

	ifstream links;
	links.open(argv[1]);
	ofstream write;
	write.open(argv[2]);


	string phrase;
	
	//write << phrase << endl;
	
	string temp;
	while (!links.eof()) {
		links >> phrase;
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

		else if ((phrase[0] > 47 && phrase[0] < 58) || (phrase[0] > 65 && phrase[0] < 91) || (phrase[0] > 96 && phrase[0] < 123)) {
			for (int i = 0; phrase[i] != '\0'; i++) {
				if ((phrase[i] > 65 && phrase[i] < 91) || (phrase[i] > 96 && phrase[i] < 123)) {
					write << phrase[i];
				}
			}
			write << endl;
		}
	
	}

	links.close();
	write.close();
	return 0;
	
}