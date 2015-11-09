

#include <vector>
#include <iostream>
#include <cmath>   

//using namespace std;



template <class T, class Comparator>
void mergeSort(std::vector<T> & myArray, Comparator comp) {
	mergehelper(myArray, comp, 0, myArray.size()-1);
}

template <class T, class Comparator>
void mergehelper(std::vector<T> & myArray, Comparator comp, int b, int e) {
	if (b < e) {

		int m = floor((b + e)/2); 
		mergehelper(myArray, comp, b, m);
		mergehelper(myArray, comp, m+1, e);
		merge(myArray, comp, b, e, m);
	}
}

template <class T, class Comparator>
void merge(std::vector<T> & myArray, Comparator comp, int l, int r, int m) {
	//cout << myArray.size() << endl;
	std::vector<T> temp(r +1 - l);
	int i = l, j = m+1, k = 0; //cout << l << " " << r << " " << m << endl;
	while (i <= m || j <= r) {
		//cout << myArray[i] << endl;
		//cout << i << " " << j << endl;

		if (i <= m && ((j > r) || comp(myArray[i], myArray[j]))) {
		
			temp[k] = myArray[i]; i++; k++; 
			//cout << "see me!" << endl;
		}
		else { 
			temp[k] = myArray[j]; j++; k++;
			//cout << "see me!" << endl; 
		}
		
	}
	//cout << "hi superstar" << endl;
	for (k = 0; k < r+1-l; k++) {
		//cout << temp[k]->filename() << endl;
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