#ifndef MSORT_H
#define MSORT_H


#include <vector>
#include 


class MSort {
 public: 
 	template <class T, class Comparator>
  	void mergeSort (vector<T> myArray, Comparator comp);
  	void merge(vector<T> myArray, int b, int e, int m);
  };


void MSort::mergeSort(vector<T> myArray, Comparator comp, int b, int e) {
	if (b < e) {
		int m = floor((1 + e)/2); 
		mergeSort(myArray, 1, m);
		mergeSort(myArray, m+1, e);
		Merge(myArray, comp, 1, r, m);
	}
}

void MSort::merge(std::vector<T> myArray, Comparator comp, int l, int r, int m) {
	vector<T> temp;
	int i = l, j = m+1, k = 0;
	while (i <= m || j <= r) {
		if (i <= m && (j > r || myArray[i] <= myArray[j])) {
		
			temp.push_back(myArray[i]); i ++; k ++; 
		}
		else { 
			temp.push_back(myArray[i]); j ++; k ++; 
		}
		
	}
	for (k = 0; k < r+1-l; k ++) {
		myArray[k+l] = temp[k];
	
	}

}









/*
	int size = myArray.size();
	vector<T> lower;
	vector<T> upper;

	for (int i = 0; i < size/2; i++) {
		lower[i] = myArray[i];
	}
	for (int i = size; i < size; i++) {
		lower[i] = myArray[i];
	}
}*/