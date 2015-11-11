

#include <set>
#include <string>
//#include "webpage.h"

#ifndef MYSET_H
#define MYSET_H

// avoid circular reference

class WebPage;

template<class T>
class MySet : public std::set<T>
{
public:
  MySet();
  MySet<T> set_intersection(const MySet<T>& other);
  MySet<T> set_union(const MySet<T>& other);
  
};










template<class T>
MySet<T>::MySet() {}

template<class T>
MySet<T> MySet<T>::set_intersection(const MySet<T>& other) {
	typename std::set<T>::iterator it;
	//std::set<std::string>::iterator check;
	MySet<T> temp;
	//check to make sure it exists in the other one and then add to set
	for (it = (other.begin()); it != (other.end()); ++it) {
		//std::cout << *it << std::endl;
		if(this -> find(*it) != this -> end()) {
				temp.insert(*it);

			}
		}
	
	return temp;

}

template<class T>
MySet<T> MySet<T>::set_union(const MySet<T>& other) {
	typename std::set<T>::iterator it;
	typename std::set<T>::iterator check;
	MySet<T> temp;
	//add everything already to the set
	for (it = other.begin(); it != other.end(); ++it) {
		temp.insert(*it);
	}
	//if there are the same thing just push it in once
	for (it = this->begin(); it != this->end(); ++it) {
		bool che = false;
		for (check = temp.begin(); check != temp.end(); ++check) {
			if (it == check) {
				che = true;
			}
		}
		if (che == false) {
			temp.insert(*it);
		}
	}

	return temp;
}


typedef MySet<std::string> MySetString;
typedef MySet<WebPage*> MySetWebPage;
#endif