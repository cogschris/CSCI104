/*
Author: Chris Cognetta
email: ccognett@usc.edu

The function is designed to take a linked list and separate it based on the value of the pivot chosen.
It simply just changes the pointers and attaches them to the new lists.

*/

#include <iostream>
#include <cstdlib>
#include <stdexcept>
using namespace std;


struct Node {
    int value;
    Node *next;
};

void split (Node*& in, Node*& smaller, Node*& larger, int pivot);


void split (Node*& in, Node*& smaller, Node*& larger, int pivot) {
	
	//as long as we arent loaing a null
	if (in == NULL) {
		return;
	}
		//if the value is smaller
		if (in -> value <= pivot) {
			if (smaller == NULL) {
				smaller = in;
				smaller -> next = NULL;
			}
			else {
				smaller -> next = in; //load the value as the next
				smaller = smaller -> next; //move forward
				in = in -> next; //move forward
				smaller -> next= NULL; //delete the pointer to the rest of the list
			}
		}
		//just follows the same premise
		else if (in -> value > pivot) {
			if (larger == NULL) {
				larger = in;
				larger -> next = NULL;
			}
			else {
				larger -> next = in;
				larger = larger -> next;
				
				in = in -> next;
				larger -> next = NULL;
			}
		}
			
		
			split(in, smaller, larger, pivot); //run the recursion again
		
}
/* This was just my test code

int main() {

	Node *start = new Node;
	start -> value = 0;
	Node *place = start;
	for (int i = 1; i < 10; i++) {
		Node *add = new Node;
		add -> value = i;
		start -> next = add;
		start = start -> next;
	}

	Node *startsmall = new Node;
	startsmall -> value = 0;
	Node *startlarge = new Node;
	startlarge -> value = 10;
	//startsmall   = NULL;
	Node *temps = startsmall;
	//startlarge = NULL;
	Node *templ = startlarge;

	split(place, temps, templ, 5);

	cout << "Small Values:" << endl;
	while (startsmall != NULL) {
		cout << startsmall -> value << " ";
		Node *temp = startsmall->next;
    	delete startsmall;
    	startsmall = temp;
		//startsmall = startsmall -> next;
	}

	cout << endl << "Large Values:" << endl;
	while (startlarge != NULL) {
		cout << startlarge -> value << " ";
		Node *temp = startlarge->next;
    	delete startlarge;
    	startlarge = temp;
		//startlarge = startlarge -> next;
	}

	cout << endl;
	return 1;
}
*/
