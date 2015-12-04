#include "minheap.h"


MinHeap::MinHeap(int d) {
	if (d < 2) {
		std::cout << "Sorry!" << std::endl;
	}
	tree = d;
	heap = new std::vector<string>[d+1];
	size = 0;
}


MinHeap::~MinHeap() {

}


void MinHeap::add(std:string item, int priority) {
	temp = make_pair(item, priority);
	size++;
	heap.push_back(temp);
	
	//now figure out something with priority
	trickleUp(size - 1);
}

void MinHeap::trickleUp (int pos) {
	if (pos > 0 && heap[pos].second < heap[(pos-1)/tree].second) {
		swap (heap, pos, (pos-1)/tree);
		trickleUp((pos-1)/tree);
	}
	else if (pos > 0 && heap[pos].second == heap[(pos-1)/tree].second) {
		if (heap[pos].first > heap[(pos-1)/tree].first) {
			swap (heap, pos, (pos-1)/tree);
		}
	}
}


const std:string & MinHeap::peek() const {
	if (size == 0) {
		//throw exception
	}

	return heap[0];
}



