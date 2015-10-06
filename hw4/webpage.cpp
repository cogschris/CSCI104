#include "myset.h"
#include <fstream>


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

MySetWebpage WebPage::incoming_links() const {
	return inlink;
}

void WebPage::add_outgoing_link(WebPage* wp) {
	outlink.insert(wp);
}

MySetWebpage WebPage::outgoing_links() const {
	return outlink;
}

std::ostream & operator<<(std::ostream & os, const WebPage & page) {
	std::string parse;
	std::string web;
	std::string submit;
	ofstream text;
	text.open(title)
	while(!text.eof()) {
		getline(parse, text);
		std::bool open = false;
		//page >> parse;
		std::int size = parse.size();
		for (std::int i = 0; i < size; i++) {
			if (parse[i] = '(') {
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
	return submit;
}