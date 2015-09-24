/*
NOTE:
I made up my own values for each symbol
True values: -1
False Values: -2
"(" : -3

*/
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

	
	string temp;
	string number;
	int parencounter = 0;
	//int numcounter = 0;
	bool failed = false;
	int size = 0;
	int negative = 0;
	bool failworld = false;

	while (!input.eof()) {
		getline(input, temp);
		size = temp.size();
		StackInt eval;
		failed = false;
		failworld = false;
		parencounter = 0;
		number.clear();

		for (int i = 0; i < size; i++) {

			if (failed == true || failworld == true) {
				break;
			}

			if ((temp[i] == '(') || (temp[i] == '&') || (temp[i] == '|') || (temp[i] == '~') || (temp[i] == ' ')) {

				if (number[0] != '\0') {

					if (key.find(number) != key.end()) {

						if (key[number] == true) {

							if (negative == 1) {
								eval.pop();
								eval.push(-2);
							}
							else if(negative == 0) {
								eval.push(-1);
							}
						}

						else if (key[number] == false) {
							if (negative == 1) {
								eval.pop();
								eval.push(-1);
							}
							else if (negative == 0) {
								eval.push(-2);
							}
						}
						negative = 0;
					}

					else {

						failworld = true;
						break;
					}
					number.clear();
					//numcounter = 0;
				}

				if (temp[i] == '(') {
					eval.push(-3);
					parencounter++;
					negative = 0;
				}

				if (temp[i] == '&') {
					eval.push(-4);
					negative = 0;
				}

				if (temp[i] == '|') {
					eval.push(-5);
					negative = 0;
				}

				if (temp[i] == '~') {
					eval.push(-6);
					negative = 1;
				}

			}

			else if ((temp[i] == '0') || (temp[i] == '1') || (temp[i] == '2') || (temp[i] == '3') || (temp[i] == '4') || (temp[i] == '5') || (temp[i] == '6' || (temp[i] == '7') || (temp[i] == '8') || (temp[i] == '9'))) {
				
				number += temp[i];
				//numcounter++;
			}

			else if (temp[i] == ')') {
				parencounter--;
				if (number[0] != '\0') {

					if (key.find(number) != key.end()) {

						if (key[number] == true) {

							eval.push(-1);
						}

						else if (key[number] == false) {

							eval.push(-2);
						}
					}
					else {
						failworld = true;
						break;
					}
					number.clear();
					//numcounter = 0;
				}
				int andcheck = 0;
				int orcheck = 0;
				while (eval.top() != (-3)) {

					if (eval.empty() == true) {
						failed = true;
						break;
					}

					int first = eval.top();
					eval.pop();
					if (eval.top() == (-3)) {
						eval.pop();
						eval.push(first);
						break;
					}
					int symbol = eval.top();
					if (symbol == -4) {
						andcheck = 1;
					}
					if (symbol == -5) {
						orcheck = 1;
					}
					eval.pop();

					int second = eval.top();

						
					
					if (symbol != (-6)) {
						if ((first <= -3) || (second <= -4)) {
							//cout << "Malformed" << endl;
							failed = true;
						}
						eval.pop();

						if (andcheck == 1 && orcheck == 1) {
							failed = true;
						}

						if (symbol == -4) {
							if (first == -1 && second == -1) {
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
					}

					else if (symbol == (-6)) {
						if (first == -1) {
							eval.push(-2);
						}
						else if (first == -2) {
							eval.push(-1);
						}
					}

					
				}

				if (failed == true) {
					break;
				}
			}
		}

		if (failed == false) {
			while (eval.empty() == false) {
				if (number[0] != '\0') {

					if (key.find(number) != key.end()) {

						if (key[number] == true) {

							if (negative == 1) {
								eval.pop();
								eval.push(-2);
							}
							else if(negative == 0) {
								eval.push(-1);
							}
						}

						else if (key[number] == false) {
							if (negative == 1) {
								eval.pop();
								eval.push(-1);
							}
							else if (negative == 0) {
								eval.push(-2);
							}
						}
						negative = 0;
					}

					else {

						failworld = true;
						break;
					}
					number.clear();
					//numcounter = 0;
				}
				int first = eval.top();
				eval.pop();
				int symbol = eval.top();
				eval.pop();
				int second = eval.top();

				if ((first <= -3) ) {
					//cout << "Malformed" << endl;
					failed = true;
				}
						
				if (symbol != (-6)) {
					
					eval.pop();
					if (symbol == -4) {
							if (first == -1 && second == -1) {
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
				}

				else if (symbol == (-6)) {
					if (first == -1) {
						eval.push(-2);
					}
					else if (first == -2) {
						eval.push(-1);
					}
				}
			}
		}

		if (failworld == true) {
			cout << "Unknown variable" << endl;
		}
		else if (failed == true || parencounter > 0) {
			cout << "Malformed" << endl;
		}

		
		else if ((eval.top() == -1) && (failed != true)) {
			cout << "True" << endl;
		}
		else if ((eval.top() == -2) && (failed != true)) {
			cout << "False" << endl;
		}

		

	}
	input.close();
	return 0;
}