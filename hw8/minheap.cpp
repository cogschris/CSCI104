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
	track.add(make_pair(item, size-1));
	//now figure out something with priority
	trickleUp(size - 1);
}

void MinHeap::trickleUp (int pos) {
	if (pos > 0 && heap[pos].second < heap[(pos-1)/tree].second) {
		swap (heap, pos, (pos-1)/tree);
		track.update(heap[(pos-1)/tree].first, pos-1)/tree);
		track.update(heap[pos].first, pos-1)/tree);
		trickleUp((pos-1)/tree);
	}
	else if (pos > 0 && heap[pos].second == heap[(pos-1)/tree].second) {
		if (heap[pos].first > heap[(pos-1)/tree].first) {
			swap (heap, pos, (pos-1)/tree);
			track.update(heap[(pos-1)/tree].first, pos-1)/tree);
			track.update(heap[pos].first, pos-1)/tree);
		}
	}
}


const std:string & MinHeap::peek() const {
	if (size == 0) {
		//throw exception
	}

	return heap[0];
}

 void MinHeap::remove() {
 	swap (heap, 0, size-1);
 	heap.pop_back(); 
	size --; 
	trickleDown (0);
 }

 void MinHeap::trickleDown(int pos) {
 	if (tree*pos + 1 < size) {
 		int compare = heap[size-1].second;
 		for (int i = 1; i <= tree; i++) {
 			if (compare > heap[pos + 1].second) {
 				compare = heap[pos + 1].second;
 			}
 		}
 		if (heap[compare].second < heap[pos].second) {
			swap (heap, compare, pos);
			track.update(heap[(pos-1)/tree].first, pos-1)/tree);
			track.update(heap[pos].first, pos-1)/tree);
			trickleDown (compare);
		}

 	}
 }

 void MinHeap::update(std::string item, int priority) {
 	int found = 0;
 	found = track.find(item);
 	if (heap[item].second > priority) {
 		heap[item].second = priority;
 		trickleDown(item);
 	}
 }

 bool MinHeap::isEmpty() {
 	return size == 0;
 }

