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
	string load;

	//load everything in the set
	while (!myfile.eof()) {
		getline(myfile, temp);
		cout << temp << endl;
		load.clear();
		//int j = 0;
		//change everything to lowercase
		for(size_t i = 0; i <= temp.size(); i++) {
			if (isalpha(temp[i])) {
						//cout << temp[i] << endl;

				if ((int)temp[i] > 64 && (int)temp[i] < 91) {
					temp[i] = temp[i] + 32;
					load = load + temp[i];
				}
				else {
					load = load + temp[i];
				}
				//cout << load << endl;
				//j++;
			}

			else {
				//j = 0;
				//cout << load[0] << endl;
				words.insert(load);
				load.clear();

			}

		
		}
		//words.insert(load);
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