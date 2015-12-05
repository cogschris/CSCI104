#include "hash.h"
#include <string>
#include <cmath>
#include <iostream>
#include <stdexcept>


HashTable::HashTable() {
	size = 31;
	orig = 31;
	table = new std::vector< std::pair<std::string, int> >*[size];
	for(int i = 0; i < size; i++) {
		table[i] = new std::vector<std::pair<std::string, int> >;
	}
	count = 0;
}

HashTable::~HashTable() {

}

void HashTable::add(std::pair<std::string, int> new_item) {
	std::string checking = new_item.first;
	int temp_size = checking.size();
	long long int modding = 0;

	for (int i = 0; i < temp_size; i++) {
		if (checking[i] < 94) {
			checking[i] += 32;
		}
		modding += (checking[i]-97) * pow(29, temp_size-1-i);
	}
	int key = modding%size;
	for (int i = 0; i < int(table[key]->size()); i++) {
		if (new_item.first == (*table[key])[i].first) {
			 
			throw std::invalid_argument("///Just Invalid///");
			
		}
	}

	
	int temp = key;
	int start = 0;
	bool insert = false;
	while (temp <= size && insert == false) {
		
		if (count/size <= 1) {
			for (int i = 0; i < int(table[key]->size()); i++) {
				if (new_item.first == (*table[key])[i].first) {
					throw std::invalid_argument("///Just Invalid///");
					
				}
			}	
			table[temp]->push_back(new_item);
			count++;
			insert = true;
		}
		start++;
		temp = start*orig + key;
	}
	//std::cout << "fucking hell crap shit   " << std:: endl;
	if (insert == false) {
		resize();
		//temp = (start+1)*size + key;
		//std::cout << temp << "   " << size << std::endl;
		table[temp]->push_back(new_item);
		count++;
			insert = true;
	}
}

const int& HashTable::find(std::string key) const {
	
	int key_size = key.size();
	long long int modding = 0;

	for (int i = 0; i < key_size; i++) {
		if (key[i] < 94) {
			key[i] += 32;
		}
		modding += (key[i]-97) * pow(29, key_size-1-i);
	}

	int search = modding%orig;
	
	int multiply = 0;
	while (search <= orig) {

		for (int i = 0; i < int(table[search]->size()); i++) {
			if (key == (*table[search])[i].first) {
				return (*table[search])[i].second;
			}
		}
		multiply++;
		search = orig*multiply + search;

	}
	throw std::invalid_argument("///Just Invalid///");
	//return 0;
}

void HashTable::remove (std::string key) {
	int key_size = key.size();
	long long int modding = 0;

	for (int i = 0; i < key_size; i++) {
		if (key[i] < 94) {
			key[i] += 32;
		}
		modding += (key[i]-97) * pow(29, key_size-1-i);
	}
	int search = modding%size;

	int multiply = 0;
	bool leave = false;
	while (search <= orig && leave == false) {

		for (int i = 0; i < int(table[search]->size()); i++) {
			if (key == (*table[search])[i].first) {
				table[search]->erase(table[search]->begin() + i);
				leave = true;
			}
		}
		multiply++;
		search = orig*multiply + search;

	}
}

void HashTable::update (std::pair<std::string, int> new_value) {
	std::string key = new_value.first;
	int key_size = int(key.size());
	long long int modding = 0;

	for (int i = 0; i < key_size; i++) {
		//if (key[i] < 94) {
		//	key[i] += 32;
		//}
		modding += (key[i]-97) * pow(29, key_size-1-i);
	}
	int search = modding%size;

	int multiply = 0;
	bool leave = false;
	//std::cout << new_value.first << "  updated yay  " << new_value.second << std::endl;
	while (search <= orig && leave == false) {

		for (int i = 0; i < int(table[search]->size()); i++) {
			if (key == (*table[search])[i].first) {
				(*table[search])[i] = new_value;
				leave = true;
			}
		}
		multiply++;
		search = orig*multiply + search;

	}
}

void HashTable::resize() {
	//std::cout << "fucking resize" << std::endl;
	std::vector< std::pair<std::string, int> >  *temp;
	//std::cout << size << std::endl;
	temp = new std::vector< std::pair<std::string, int> >[size];
	for(int i = 0; i < size; i++) {
		temp[i] = *table[i];
	}
	for(int i = 0; i < size; i++) {
		delete table[i];
	}
	delete [] table;	


	table = new std::vector< std::pair<std::string, int> >*[size*2 + 1];
	for(int i = 0; i < size; i++) {
		table[i] = &temp[i];
	}
	for(int i = size; i < size*2 + 1; i++) {
		table[i] = new std::vector<std::pair<std::string, int> >;
	}
	//std::cout << size << std::endl;
	//for(int i = 0; i < size; i++) {
	//	delete temp[i];
	//}
	
	//delete [] temp;
	size = size*2 + 1;
}