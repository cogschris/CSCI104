/*
Skeleton code provided by CS104
Author: Chris Cognetta
email: ccognett@usc.edu

This program is designed to take an input of letters and a certain size and then make as many
palindrome combinations as possible.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

void makePalindromeHelper(ostream& ofile, char* options, int len, int size, string pal);


void makePalindromes(ostream& ofile, char* options, int size) {
	int terms = strlen(options); //get the amount of terms to work with
	string temp; //temporary string to hold semicombined terms
	for (int i = 0; i < terms; i++) {
		temp = options[i];
		makePalindromeHelper(ofile, options, terms, size, temp);
		//so call palindrome helper on one letter to make all the odd number palindromes

		temp = temp + options[i];
		makePalindromeHelper(ofile, options, terms, size, temp);
		//call palindrome helper on two letters to make all the even sets
	}
	//makePalindromes(ofile, options, --size);

}

void makePalindromeHelper(ostream& ofile, char* options, int len, int size, string pal) {
	string temp;
	ofile << pal << endl;
	//print out the string already, which is already symmetrical

	if (pal.length() < size - 1) {
		for (int i = 0; i < len; i++) {
			temp = options[i] + pal + options[i];
			//bascially follow xPx and add two of the same letters to the string

			makePalindromeHelper(ofile, options, len, size, temp); 
			//call it again on a bigger palindrome
		}
	}

}


int main(int argc, char* argv[])
{
  if(argc < 4){
    cerr << "Please provide an output file, a string of characters, and the max length" << endl;
    return 1;
  }

  ofstream ofile(argv[1]);
  int len = atoi(argv[3]);
  makePalindromes(ofile, argv[2], len);
  ofile.close();
  return 0;
}
