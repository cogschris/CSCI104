#include "minheap.h"
#include <iostream>
#include <algorithm>


MinHeap::MinHeap(int d) {
	if (d < 2) {
		std::cout << "Sorry!" << std::endl;
	}
	tree = d;
	//heap = new std::vector<std::string>[d+1];
	size = 0;
}


MinHeap::~MinHeap() {

}


void MinHeap::add(std::string item, int priority) {
	temp = make_pair(item, priority);
	size++;
	heap.push_back(temp);
	track.add(make_pair(item, size-1));
	//now figure out something with priority
	trickleUp(size - 1);
}

void MinHeap::trickleUp (int pos) {
	if (pos > 0 && heap[pos].second < heap[(pos-1)/tree].second) {
		swap (pos, (pos-1)/tree);
		track.update(std::make_pair(heap[(pos-1)/tree].first, (pos-1)/tree));
		track.update(std::make_pair(heap[pos].first, (pos-1)/tree));
		trickleUp((pos-1)/tree);
	}
	else if (pos > 0 && heap[pos].second == heap[(pos-1)/tree].second) {
		if (heap[pos].first > heap[(pos-1)/tree].first) {
			swap (pos, (pos-1)/tree);
			track.update(std::make_pair(heap[(pos-1)/tree].first, (pos-1)/tree));
			track.update(std::make_pair(heap[pos].first, (pos-1)/tree));
		}
	}
}


const std::string & MinHeap::peek() const {
	if (size == 0) {
		//throw exception
	}

	return heap[0].first;
}

 void MinHeap::remove() {
 	swap (0, size-1);
 	heap.pop_back(); 
	size --; 
	trickleDown (0);
 }

 void MinHeap::trickleDown(int pos) {
 	if (tree*pos + 1 < size) {
 		int compare = heap[pos].second;
 		for (int i = 1; i <= tree; i++) {
 			if (compare > heap[pos*tree + i].second) {
 				compare = heap[pos*tree + i].second;
 			}
 			else if (compare == heap[pos*tree+i].second) {
 				if (heap[pos].first > heap[pos*tree + i].first ) {
 					compare = heap[pos*tree + i].second;
 				}
 			}
 		}
 		if (heap[compare].second < heap[pos].second) {
			swap (compare, pos);
			track.update(std::make_pair(heap[compare].first, (compare)/tree));
			track.update(std::make_pair(heap[pos].first, (pos)/tree));
			trickleDown (compare);
		}
		

 	}
 }

 void MinHeap::swap(int init, int place) {
 	std::pair<std::string, int> tempo = heap[init];
 	heap[init] = heap[place];
 	heap[place] = tempo;
 }

 void MinHeap::update(std::string item, int priority) {
 	int found = 0;
 	found = track.find(item);
 	if (heap[found].second > priority) {
 		heap[found].second = priority;
 		trickleUp(found);
 	}
 }

 bool MinHeap::isEmpty() {
 	return size == 0;
 }

