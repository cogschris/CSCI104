/*
Author: Chris Cognetta
email: ccognett@usc.edu

this is just to test my llistint.cpp
*/
#include "llistint.h"
#include <iostream>

using namespace std;

int main() {
	LListInt * list = new LListInt();

	list -> insert(0, 14);
	list -> insert(1, 12);
	list -> insert(0, 35);

	cout << "The value at 0 is " << list -> get(0) <<endl;
	cout << "And the value at 1 is " << list -> get(1) << endl;

	list -> remove(0);
	cout << "The value at 0 is now " << list -> get(0) << endl;
	cout << "And the size of the list is " << list -> size() << endl;

	list -> set(0, 120);
	cout << "The value at 0 has now changed to " << list -> get(0) << endl;

	if (list -> empty() == true) {
		cout << "The list is empty" << endl;
	}
	else {
		cout << "Hold up, the list still has items in it!" << endl;
	}

	list -> clear();
	if (list -> empty() == true) {
		cout << "Yep, the list is empty, the size is " << list -> size() << endl;
	}
	else {
		cout << "Nope, there is " << list -> size() << " items remaining" << endl;
	}

	list -> insert(4, 14);

	if (list -> empty() == true) {
		cout << "Hey, you can't add something to the 4th entry if there are 0 entries!" << endl;
	}
	else {
		cout << "Oops my code is definetely broken if you are reading this" << endl;
	}
	


	return 0;
}