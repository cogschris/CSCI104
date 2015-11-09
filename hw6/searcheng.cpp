#include <map>
#include <vector>
#include <string>
#include "webpage.h"
#include "myset.h"
#include "pageparser.h"
#include "searcheng.h"
#include <string>
#include <iostream>
#include <fstream>
#include <set>

using namespace std;

SearchEng::SearchEng() {
	number = 0;
}

SearchEng::~SearchEng() {
	std::set<WebPage*>::iterator it;
	for (it = final.begin(); it != final.end(); ++it) {
		delete *it;
	}
}

void SearchEng::add_parse_from_index_file(string index_file, PageParser* parser) {
	//load the file
	string file;
	ifstream index;
	index.open(index_file.c_str());

	while (index >> file) {
		
		//parse each page
		WebPage* add = new WebPage(file);
		final.insert(add);
		number++;
		
	}

	std::set<WebPage*>::iterator it;
	for (it = final.begin(); it != final.end(); ++it) {
		add_parse_page((*it)->filename(), parser, *it);
	}

	index.close();
}

void SearchEng::add_parse_page(string filename, PageParser* parser, WebPage* web) {
	//create the new things
	MySetString allwords;
	MySetString alllinks;
	
	//add.(filename);


	parser -> parse(filename, allwords, alllinks);
	//go through and check if the webpage and word exist
	//if they dont, add them in
	//if they do then just update the set
	std::set<string>::iterator it;
	for (it = allwords.begin(); it != allwords.end(); ++it) {
		if (check.count(*it) == 0) {
			MySetWebPage New;
			New.insert(web);
			check.insert(make_pair(*it, New));
		}

		else {
			MySetWebPage update;
			update = (check.find(*it)->second); 
			update.insert(web);
			check[*it] = update;
		}
	}

	for (it = alllinks.begin(); it != alllinks.end(); ++it) {
		/*WebPage* add = new WebPage(*it);
		std::set<WebPage*>::iterator it2;
		for (it2 = final.begin(); it2 != final.end(); ++it2) {
			if (*it2 == add->filename()) {
				(web)->add_outgoing_link(*it2);
			}
		web->add_outgoing_link(add);*/
		std::set<WebPage*>::iterator it2;
		for (it2 = final.begin(); it2 != final.end(); ++it2) {
			if (*it == (*it2)->filename()) {
				(*it2)->add_incoming_link(web);
				web->add_outgoing_link(*it2);
			}
		}
	}
	//final.insert(web);
}

MySetWebPage SearchEng::OR_function(std::string word, MySetWebPage compare) {
	//bascially take the webpage and check to make sure the word exists
	//on another page and if it does add it to the set 
	MySetWebPage temp;
	if (check.find(word) != check.end()) {
		temp = (check.find(word)->second);
		temp = compare.set_union(temp);
		return temp;
	}
	
	return compare;

}

MySetWebPage SearchEng::AND_function(std::string word, MySetWebPage compare) {
	MySetWebPage temp;
	//this time check to make sure the same word exists on both pages
	temp = (check[word]);
	temp = compare.set_intersection(temp);
	//cout << temp << endl;
	return temp;

}

MySetWebPage SearchEng::ONE_function(std::string word) {
	//just return one to the set
	MySetWebPage temp;
	temp = (check[word]);

	return temp;
}

int SearchEng::num_WebPages() {
	return number;
}