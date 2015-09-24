#include <iostream>
#include <fstream>
#include <map>
#include <cstdlib>
#include <string> 
#include <stdio.h>
#include <string.h>
#include "stackint.h"

using namespace std;

int main(int argc, char* argv[]) {

	if (argc < 2) {
		cout << "Please enter 2 files" << endl;
		return 1;
	}

	map <string, bool> key;
	//map<string, string> iterator it;

	ifstream guide;
	guide.open(argv[2]);
	//string term1;
	//string term2;

	string varKey;
	char value;
	while (guide >> varKey >> value) {
		key.insert(make_pair(varKey, (value == 'T')));
	}

	

	guide.close();

	ifstream input;
	input.open(argv[1]);

	StackInt eval;
	string temp;
	string number;
	int pushin;
	int num = 0;
	int size = 0;
	int counter = 1;

	while (!input.eof()) {
		getline(input, temp);
		size = temp.size();


		for (int i = 0; i < size; i++) {
			
			if (temp[i] == '(') {
				if (number[0] != '\0') {
					//it = key.find(number);
					if (key[number] == true) {
						pushin = -1;
					}
					else {
						pushin = -2;
					}

					size = 0;
					number.clear();
					eval.push(pushin);
				}
				//cout << "here" << endl;
				eval.push(-3);
			}

			else if (temp[i] == '&') {
				if (number[0] != '\0') {
					//it = key.find(number);
					if (key[number] == true) {
						pushin = -1;
					}
					else {
						pushin = -2;
					}
					size = 0;
					number.clear();
					eval.push(pushin);
				}
				eval.push(-4);
			}

			else if (temp[i] == '|') {
				if (number[0] != '\0') {
					//it = key.find(number);
					if (key[number] == true) {
						pushin = -1;
					}
					else {
						pushin = -2;
					}
					size = 0;
					number.clear();
					eval.push(pushin);
				}
				eval.push(-5);
			}

			else if (temp[i] == '~') {
				if (number[0] != '\0') {
					//it = key.find(number);
					if (key[number] == true) {
						pushin = -1;
					}
					else {
						pushin = -2;
					}
					size = 0;
					number.clear();
					eval.push(pushin);
				}
				eval.push(-6);
			}

			else if ((temp[i] == '0') || (temp[i] == '1') || (temp[i] == '2') || (temp[i] == '3') || (temp[i] == '4') || (temp[i] == '5') || (temp[i] == '6' || (temp[i] == '7') || (temp[i] == '8') || (temp[i] == '9'))) {
				number[num] = temp[i];
				num++;

			}

			else if (temp[i] == ')') {
				if (number[0] != '\0') {
					//it = key.find(number);
					if (key[number] == true) {
						pushin = -1;
					}
					else {
						pushin = -2;
					}
					size = 0;
					number.clear();
					eval.push(pushin);
				}

				while (eval.top() != '(') {
					int first = eval.top();
					eval.pop();
					int symbol = eval.top();
					eval.pop();
					int second;
					if (symbol != -6) {
						second = eval.top();
						eval.pop();
					}

					//int end = eval.top();
					//eval.pop();

					if (symbol == -4) {
						if (first == second) {
							eval.push(-1);
						}
						else {
							eval.push(-2);
						}
					}
					else if (symbol == -5) {
						if ((first == -1) || (second == -1)) {
							eval.push(-1);
						}
						else {
							eval.push(-2);
						}
					}

					else if (symbol == -6) {
						if (first == -1) {
							eval.push(-2);
						}
						else {
							eval.push(-1);
						}
					}

				}

			}

		}

		if (eval.empty() != 0) {
			cout << counter << " Malformed" << endl;
		}

		else if (eval.top() == -1) {
			cout << counter << " True" << endl;
		}

		else if (eval.top() == -2) {
			cout << counter << " False" << endl;
		}
		counter++;

	}
	input.close();
	return 0;
}