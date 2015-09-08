#include <iostream>

using namespace std;


void split (Node*& in, Node*& smaller, Node*& larger, int pivot);

struct Node {
    int value;
    Node *next;
};


void split (Node*& in, Node*& smaller, Node*& larger, int pivot) {
	//basicaly mkae it so i verify the value of the pivot 
	//against the value of the pivot and then make it the next
	//of the node smaller of larger and and then make smaller
	//the new one then open the file to the new list and BAM DONE
}

