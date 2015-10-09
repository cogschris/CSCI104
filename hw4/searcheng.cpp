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
		add_parse_page(file, parser);
		
	}
	index.close();
}

void SearchEng::add_parse_page(string filename, PageParser* parser) {
	//create the new things
	MySetString allwords;
	MySetString alllinks;
	WebPage* add = new WebPage(filename);
	//add.(filename);


	parser -> parse(filename, allwords, alllinks);
	//go through and check if the webpage and word exist
	//if they dont, add them in
	//if they do then just update the set
	std::set<string>::iterator it;
	for (it = allwords.begin(); it != allwords.end(); ++it) {
		if (check.count(*it) == 0) {
			MySetWebPage New;
			New.insert(add);
			check.insert(make_pair(*it, New));
		}

		else {
			MySetWebPage update;
			update = (check.find(*it)->second); 
			update.insert(add);
			check[*it] = update;
		}
	}
	final.insert(add);
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