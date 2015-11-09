#include "crawler.h"
#include "mdpageparser.h"
#include <sstream>
#include <fstream>
#include "searcheng.h"
#include <iostream>
#include "webpage.h"
#include "myset.h"

Crawler(std::string input) {

	istringstring line (input);
	std::string temp;
	
	PageParser* parser = new MDPageParser;

	while (line>>temp) {
		if(temp == "INDEX_FILE") {
			line >> file;
			line >> file;
		}
		else if(temp == "OUTPUT_FILE") {
			line >> out;
			line >> out;
		}
	
	}

	output = out;
	ifstream index(file);
	ofstream alllinks(out)

	while (index >> file) {




		
		//parse each page
		WebPage* add = new WebPage(file);
		if (alpha.find(add) != end()) {
				alpha.insert(add);
		}

		build_index(add);
	}
		/*
		//alpha.insert(add);
		parser.parse(add, add.incoming_links(), add.outgoing_links());
		std::set<WebPage*>::iterator it;
		for(it = add.incoming_links().begin(); it != add.incoming_links().endl(); ++it) {
			if (alpha.find(it) != end()) {
				alpha.insert(*it);
			}
		}
		for(it = add.outgoing_links().begin(); it != add.outgoing_links().endl(); ++it) {
			if (alpha.find(it) != end()) {
				alpha.insert(*it);
			}
		}
	}

	std::set<WebPage*>::iterator it;
	//std::set<WebPage*>::iterator it2;
	for (it = alpha.begin(); it != alpha.end(); ++it) {
		alllinks << *it.filename() << endl;
	}

	index.close();
	alllinks.close();*/

}

~Crawler() {

}

std::string Crawler::file() {
	return out;
}


void Crawler::build_index(WebPage* web) {

	MDPageParser parsing;
	SearchEng searching;
	searching.add_parse_page(web.filename(), parsing, web);
	std::set<WebPage*>::iterator it;
	for (it = web.incoming_links().begin(); it != web.incoming_links().end(); ++it) {
		if (alpha.find(*it) != alpha.end()) {
				alpha.insert(*it);
		}

		build_index(*it);
	}
	for (it = web.outgoing_links().begin(); it != web.outgoing_links().end(); ++it) {
		if (alpha.find(*it) != alpha.end()) {
				alpha.insert(*it);
		}

		build_index(*it);
	}


}