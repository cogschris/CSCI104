#include "myset.h"
#include "webpage.h"

MySetString::MySetString() : std::set<std::string>() {}

MySetString MySetString::set_intersection(const MySetString& other) {
	std::set<std::string>::iterator it;
	//std::set<std::string>::iterator check;
	MySetString temp;
	//check to make sure it exists in the other one and then add to set
	for (it = other.begin(); it != other.end(); ++it) {
		//std::cout << *it << std::endl;
		if(this -> find(*it) != this -> end()) {
				temp.insert(*it);

			}
		}
	
	return temp;

}

MySetString MySetString::set_union(const MySetString& other) {
	std::set<std::string>::iterator it;
	std::set<std::string>::iterator check;
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

MySetWebPage::MySetWebPage() : std::set<WebPage*>() {}

MySetWebPage MySetWebPage::set_intersection(const MySetWebPage& other) {
	std::set<WebPage*>::iterator it;
	//std::set<WebPage*>::iterator check;
	MySetWebPage temp;
	//same as above intersection for webpages
	for (it = other.begin(); it != other.end(); ++it) {
		//std::cout << *it << std::endl;
		if(this -> find(*it) != this -> end()) {
				temp.insert(*it);

			}
		}
	
	return temp;
}

MySetWebPage MySetWebPage::set_union(const MySetWebPage& other) {
	//exact same thing as above
	std::set<WebPage*>::iterator it;
	std::set<WebPage*>::iterator check;
	MySetWebPage temp;

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
