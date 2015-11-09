

#include <set>
#include <string>
#include "webpage.h"

#ifndef MYSET_H
#define MYSET_H

// avoid circular reference
template<class T>
class WebPage;

template<class T>
class MySetString : public std::set<T>
{
public:
  MySetString();
  MySetString<T> set_intersection(const MySetString& other);
  MySetString<T> set_union(const MySetString& other);
};

template<class T>
class MySetWebPage : public std::set<T>
{
public:
  MySetWebPage();
  MySetWebPage<T> set_intersection(const MySetWebPage& other);
  MySetWebPage<T> set_union(const MySetWebPage& other);
};

#endif






template<class T>
MySetString<T>::MySetString() {}

template<class T>
MySetString<T> MySetString<T>::set_intersection(const MySetString& other) {
	typename std::set<T>::iterator it;
	//std::set<std::string>::iterator check;
	MySetString temp;
	//check to make sure it exists in the other one and then add to set
	for (it = *(other.begin()); it != *(other.end()); ++it) {
		//std::cout << *it << std::endl;
		if(this -> find(*it) != this -> end()) {
				temp.insert(*it);

			}
		}
	
	return temp;

}

template<class T>
MySetString<T> MySetString<T>::set_union(const MySetString& other) {
	typename std::set<T>::iterator it;
	typename std::set<T>::iterator check;
	MySetString temp;
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

template<class T>
MySetWebPage<T>::MySetWebPage() : std::set<T>() {}

template<class T>
MySetWebPage<T> MySetWebPage<T>::set_intersection(const MySetWebPage& other) {
	typename std::set<T>::iterator it;
	//std::set<WebPage*>::iterator check;
	MySetWebPage<T> temp;
	//same as above intersection for webpages
	for (it = other.begin(); it != other.end(); ++it) {
		//std::cout << *it << std::endl;
		if(this -> find(*it) != this -> end()) {
				temp.insert(*it);

			}
		}
	
	return temp;
}

template<class T>
MySetWebPage<T> MySetWebPage<T>::set_union(const MySetWebPage& other) {
	//exact same thing as above
	typename std::set<T>::iterator it;
	typename std::set<T>::iterator check;
	MySetWebPage<T> temp;

	for (it = other.begin(); it != other.end(); ++it) {
		temp.insert(*it);
	}

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