/*
Author: Chris Cognetta
email: ccognett@usc.edu

This code is stores all the words in a text file in a set and then allows the user to search
through the set to find if words exist.

*/

#include <iostream>
#include <cstring>
#include <set>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
	//make my set
	set<string> words;

	//open my file
	ifstream myfile;
	myfile.open(argv[1]);

	string temp;

	//load everything in the set
	while (!myfile.eof()) {
		myfile >> temp;
		
		//change everything to lowercase
		for(int i = 0; temp[i] != '\0'; i++) {
			if (temp[i] > 64 && temp[i] < 91) {
				temp[i] += 32;
			}
		}

		words.insert(temp);
	}

	
	//prompt user for word to seach
	string test;
	cout << "Please enter a string to verify if it exists in the set" << endl;

	
	//using getline to check if they just hit enter instead
	while (getline(cin, test)) {
		if (test == "") {
			break;
		}

		//change the test to lowercase
		for(int i = 0; test[i] != '\0'; i++) {
			if (test[i] > 64 && test[i] < 91) {
				test[i] += 32;
			}
		}
		/*for (int i = 0; i < size; i++) {

		}*/

		//then do the verifying
		if(words.count(test) > 0) {
			cout << "in the file" << endl;
		}
		else {
			cout << "not in the file" << endl;
		}
		//prompt for new string
		cout << "Please enter another string" << endl;
		//cin >> test;

	}

	//close the file
	myfile.close();
	return 0;
}