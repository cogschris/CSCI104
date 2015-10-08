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

}

void SearchEng::add_parse_from_index_file(string index_file, PageParser* parser) {

	string file;
	ifstream index;
	index.open(index_file.c_str());

	while (index >> file) {
		

		add_parse_page(file, parser);
		
	}
	index.close();
}

void SearchEng::add_parse_page(string filename, PageParser* parser) {

	MySetString allwords;
	MySetString alllinks;
	WebPage* add = new WebPage(filename);
	//add.(filename);


	parser -> parse(filename, allwords, alllinks);

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

}

MySetWebPage SearchEng::OR_function(std::string word, MySetWebPage compare) {
	MySetWebPage temp;
	
	temp = (check.find(word)->second);
	temp = compare.set_union(temp);
	return temp;

}

MySetWebPage SearchEng::AND_function(std::string word, MySetWebPage compare) {
	MySetWebPage temp;
	
	temp = (check[word]);
	temp = compare.set_intersection(temp);
	//cout << temp << endl;
	return temp;

}

MySetWebPage SearchEng::ONE_function(std::string word) {
	MySetWebPage temp;
	temp = (check[word]);

	return temp;
}