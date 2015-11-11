#include "myset.h"
#include "webpage.h"
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

WebPage::WebPage() {}

WebPage::WebPage(std::string filename) {
	title = filename;
	inlinks = 0;
	outlinks = 0;
	pagerank = 1;
	found = false;
}

WebPage::~WebPage() {

}

void WebPage::set_pagerank(double n) {
	pagerank = n;
}

double WebPage::get_pagerank() {
	return pagerank;
}

void WebPage::filename(std::string fname) {
	title = fname;
}

std::string WebPage::filename() const {
	return title;
}

int WebPage::incoming() {
	return inlinks;
}

int WebPage::outgoing() {
	return outlinks;
}

void WebPage::set_out(int n) {
	outlinks = n;
}

void WebPage::set_found(bool n) {
	found = n;
}

bool WebPage::get_found() {
	return found;
}

void WebPage::all_words(const MySetString& words) {
	unique = words;
}

MySetString WebPage::all_words() const {
	return unique;
}

void WebPage::add_incoming_link(WebPage* wp) {
	inlink.insert(wp);
	inlinks++;
}

MySetWebPage WebPage::incoming_links() const {
	return inlink;
}

void WebPage::add_outgoing_link(WebPage* wp) {
	outlink.insert(wp);
	outlinks++;
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
