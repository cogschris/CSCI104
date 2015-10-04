#include "myset.h"
#include "webpage.h"

MySetString::MySetString() : std::set<std::string>() {}

MySetString MySetString::set_intersection(const MySetString& other) {
	std::set<std::string>::iterator it;
	std::set<std::string>::iterator check;
	std::temp<std::string>;

	for (it = other.begin(); it != other.end(); ++it) {
		for (check = this.begin(); check != this.end(); ++check) {
			if (check == it) {
				temp.insert(it);
			}
		}
	}

	return temp;
}

MySetString MySetString::set_union(const MySetString& other) {
	std::set<std::string>::iterator it;
	std::set<std::string>::iterator check;
	std::temp<std::string>;

	for (it = other.begin(); it != other.end(); ++it) {
		temp.insert(it);
	}

	for (it = this.begin(); it != this.end(); ++it) {
		bool che = false;
		for (check = temp.being(); check != temp.end(); ++check) {
			if (it == check) {
				che = true;
			}
		}
		if (che = false) {
			temp.insert(it);
		}
	}

	return temp;
}

MySetWebPage::MySetWebPage() : std::set<WebPage*>() {}

MySetWebPage MySetWebPage::set_intersection(const MySetWebPage& other) {
	std::set<WebPage*>::iterator it;
	std::set<WebPage*>::iterator check;
	std::temp<WebPage*>;

	for (it = other.begin(); it != other.end(); ++it) {
		for (check = this.begin(); check != this.end(); ++check) {
			if (check == it) {
				temp.insert(it);
			}
		}
	}
}

MySetWebPage MySetWebPage::set_union(const MySetWebPage& other) {

	std::set<WebPage*>::iterator it;
	std::set<WebPage*>::iterator check;
	std::temp<WebPage*>;

	for (it = other.begin(); it != other.end(); ++it) {
		temp.insert(it);
	}

	for (it = this.begin(); it != this.end(); ++it) {
		bool che = false;
		for (check = temp.being(); check != temp.end(); ++check) {
			if (it == check) {
				che = true;
			}
		}
		if (che = false) {
			temp.insert(it);
		}
	}

	return temp;
}
