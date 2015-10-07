#include "myset.h"
#include "webpage.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

WebPage::WebPage() {}

WebPage::WebPage(std::string filename) {
	title = filename;
}

WebPage::~WebPage() {

}

void WebPage::filename(std::string fname) {
	title = fname;
}

std::string WebPage::filename() const {
	return title;
}

void WebPage::all_words(const MySetString& words) {
	unique.set_union(words);
}

MySetString WebPage::all_words() const {
	return unique;
}

void WebPage::add_incoming_link(WebPage* wp) {
	inlink.insert(wp);
}

MySetWebPage WebPage::incoming_links() const {
	return inlink;
}

void WebPage::add_outgoing_link(WebPage* wp) {
	outlink.insert(wp);
}

MySetWebPage WebPage::outgoing_links() const {
	return outlink;
}

std::ostream & operator<<(std::ostream & os, const WebPage & page) {
	string parse;
	string web;
	//string submit;
	ifstream text;
	text.open(page.filename().c_str());
	while(!text.eof()) {
		getline(text, parse);
		bool open = false;
		//page >> parse;
		int size = parse.size();
		for (int i = 0; i < size; i++) {
			if (parse[i] == '(') {
				open = true;
			}


			else if (parse[i] == ')') {
				open = false;

			}

			else if (open == false) {
				os << parse[i];
			}
		}
	}
	text.close();
	return os;
}