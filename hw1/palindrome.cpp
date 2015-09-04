#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

void makePalindromeHelper(ostream& ofile, char* options, int len, int size, string pal);


void makePalindromes(ostream& ofile, char* options, int size) {
	int terms = strlen(options);
	string temp;
	for (int i = 0; i < terms; i++) {
		temp = options[i];
		makePalindromeHelper(ofile, options, terms, size, temp);
		temp = temp + options[i];
		makePalindromeHelper(ofile, options, terms, size, temp);
	}
	//makePalindromes(ofile, options, --size);

}

void makePalindromeHelper(ostream& ofile, char* options, int len, int size, string pal) {
	string temp;
	ofile << pal << endl;
	if (pal.length() < size - 1) {
		for (int i = 0; i < len; i++) {
			temp = options[i] + pal + options[i];
			makePalindromeHelper(ofile, options, len, size, temp); 
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
