#include "main_window.h"
#include <map>
#include <vector>
#include <string>
#include "webpage.h"
#include "myset.h"
#include "pageparser.h"
#include "mdpageparser.h"
#include "searcheng.h"
#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <algorithm>
#include "msort.h"

using namespace std;


//basic structs based on alphabet, outgoing and incoming
struct pageranking {
    bool operator()(WebPage* lhs, WebPage* rhs) 
    { 
      return lhs->get_pagerank() >= rhs->get_pagerank(); 
    }
  };

struct OutgoingComp {
    bool operator()(WebPage* lhs, WebPage* rhs) 
    { 
      return lhs->outgoing() <= rhs->outgoing(); 
    }
  };

struct IncomingComp {
    bool operator()(WebPage* lhs, WebPage* rhs) 
    { 
      return (lhs->incoming()) <= (rhs->incoming()); 
    }
  };

struct Alphabet {
    bool operator()(WebPage* lhs, WebPage* rhs) 
    { 
    	return (lhs->filename()) <= (rhs->filename());
    }
  };

MainWindow::MainWindow(string name, std::map<string, string> maps)
{
	items = maps;
	//constructing the qt with like EVERYTHING ITS SO MUCH
	PageParser* parser = new MDPageParser;
	epsilon = atof(items["RESTART_PROBABILITY"].c_str());
	steps = atoi(items["STEP_NUMBER"].c_str());
	
	searching.add_parse_from_index_file(name, parser);

	setWindowTitle("Chris' Google");

	overallLayout = new QHBoxLayout();

	display = new QVBoxLayout();
	overallLayout->addLayout(display);

	label = new QLabel("Results (filename / incoming links / outgoing links) :");
	display->addWidget(label);

	filelist = new QListWidget();
	connect(filelist, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(showpage(QListWidgetItem*)));
	display->addWidget(filelist);

	pagerank_button = new QPushButton("Sort by PageRank");
	connect(pagerank_button, SIGNAL(clicked()), this, SLOT(displayresults()));
	display->addWidget(pagerank_button);

	filename = new QPushButton("Sort by filename");
	connect(filename, SIGNAL(clicked()), this, SLOT(displayresultsfilename()));
	display->addWidget(filename);

	num_in = new QPushButton("Sort by number of incoming links");
	connect(num_in, SIGNAL(clicked()), this, SLOT(displayresultsincoming()));
	display->addWidget(num_in);

	num_out = new QPushButton("Sort by number of outgoing links");
	connect(num_out, SIGNAL(clicked()), this, SLOT(displayresultsoutgoing()));
	display->addWidget(num_out);

	formLayout = new QVBoxLayout();
	overallLayout->addLayout(formLayout);

	Input_text = new QLabel("Please enter search term(s):");
	formLayout->addWidget(Input_text);

	search_text = new QLineEdit();
	
	formLayout->addWidget(search_text);

	AND_button = new QRadioButton("AND", this);
	formLayout->addWidget(AND_button);

	OR_button = new QRadioButton("OR", this);
	formLayout->addWidget(OR_button);

	SINGLE_button = new QRadioButton("SINGLE", this);
	formLayout->addWidget(SINGLE_button);
	SINGLE_button->setChecked(true);

	search_button = new QPushButton("Search");
	connect(search_button, SIGNAL(clicked()), this, SLOT(functions()));
	connect(search_text, SIGNAL(returnPressed()), this, SLOT(functions()));
	formLayout->addWidget(search_button);

	exiting = new QPushButton("Exit Application");
	connect(exiting, SIGNAL(clicked()), this, SLOT(closeapp()));
	formLayout->addWidget(exiting);
	
	setLayout(overallLayout);

	//otherwindow stuff now
	otherlayout = new QVBoxLayout();
	otherwin = new QWidget;

	webpagestuff = new QTextEdit();
	webpagestuff->setReadOnly(true);
	otherlayout->addWidget(webpagestuff);

	title = new QLabel("Remember, data is organized as follows: filename / number of incoming links / number of outgoing links");
	otherlayout->addWidget(title);


	labels = new QHBoxLayout();
	otherlayout->addLayout(labels);


	newin = new QLabel("Incoming Links:");
	labels->addWidget(newin);

	newout = new QLabel("Outgoing Links:");
	labels->addWidget(newout);

	outin = new QHBoxLayout();
	otherlayout->addLayout(outin);

	in = new QListWidget();
	connect(in, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(showpage(QListWidgetItem*)));
	outin->addWidget(in);

	out = new QListWidget();
	connect(out, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(showpage(QListWidgetItem*)));
	outin->addWidget(out);

	filename2 = new QPushButton("Sort by filename");
	connect(filename2, SIGNAL(clicked()), this, SLOT(sortalph()));
	otherlayout->addWidget(filename2);

	num_in2 = new QPushButton("Sort by incoming links");
	connect(num_in2, SIGNAL(clicked()), this, SLOT(sortinc()));
	otherlayout->addWidget(num_in2);

	num_out2 = new QPushButton("Sort by outgoing links");
	connect(num_out2, SIGNAL(clicked()), this, SLOT(sortout()));
	otherlayout->addWidget(num_out2);

	exitnew = new QPushButton("Exit");
	connect(exitnew, SIGNAL(clicked()), this, SLOT(hidepage()));
	otherlayout->addWidget(exitnew);

	otherwin->setLayout(otherlayout);

	//error window
	errorlayout = new QVBoxLayout();
	errorwin = new QWidget();

	errormessage = new QLabel("Sorry, you used the program incorrectly. Please re-read the instructions before continuing to use the program. Have a nice day! :)");
	errorlayout->addWidget(errormessage);

	exiterror = new QPushButton("Back to searching!");
	connect(exiterror, SIGNAL(clicked()), this, SLOT(hideerror()));
	errorlayout->addWidget(exiterror);

	errorwin->setLayout(errorlayout);

	iteratorcounter = 0;

	
	allwebs = searching.get_total();

}

MainWindow::~MainWindow() {
	//never really allocated stuff so dont need it
}

void MainWindow::displayresults() {
	//always want to clear before loading stuff in
	
	
	filelist->clear();
	std::set<WebPage*>::iterator it;
	showlist.clear();
	pageranking comp;
	//push webpages into vectors
	MySetWebPage temp;
	MySetWebPage push;
	temp = results;
	push = results;

	for (it = temp.begin(); it != temp.end(); ++it) {
		std::set<WebPage*>::iterator it2;
		MySetWebPage inc;
		inc = (*it)->incoming_links();
		if ((*it)->incoming() > 0) {
			for (it2 = inc.begin(); it2 != inc.end(); ++it2) {
				push.insert(*it2);
			}
		}
		//cout << "hi" << endl;
		MySetWebPage outc;
		outc = (*it)->outgoing_links();
		if ((*it)->outgoing() > 0) {

			for (it2 = outc.begin(); it2 != outc.end(); ++it2) {
				//cout << (*it2)->filename() << endl;
				push.insert(*it2);
				
				
			}
			inc.clear();
			outc.clear();
			
		}
		
	}
	for (it = push.begin(); it != push.end(); ++it) {
		
			showlist.push_back(*it);
	}
	
	initializepagerank(showlist);
	int alphsize = showlist.size();
	
	//MERGESORT!!!
	mergeSort(showlist, comp);
	//write out everything
	for (int i = 0; i < alphsize; i++) {	
		
		QString temp;

		
		temp += QString::fromStdString((showlist[i])->filename());
		temp += "  In: ";
		
		temp += QString::number((showlist[i])->incoming());
		temp += "  Out: ";
		
		temp += QString::number((showlist[i])->outgoing());
		temp += "  PR: ";

		temp += QString::number((showlist[i])->get_pagerank());
		
		filelist->addItem(temp);
		
	}
}

void MainWindow::displayresultsfilename() {
	//always want to clear before loading stuff in
	filelist->clear();
	std::set<WebPage*>::iterator it;
	showlist.clear();
	Alphabet comp;
	MySetWebPage temp;
	MySetWebPage push;
	temp = results;
	push = results;
	//push webpages into vectors
	
	for (it = temp.begin(); it != temp.end(); ++it) {
		std::set<WebPage*>::iterator it2;
		MySetWebPage inc;
		inc = (*it)->incoming_links();
		if ((*it)->incoming() > 0) {
			for (it2 = inc.begin(); it2 != inc.end(); ++it2) {
				push.insert(*it2);
			}
		}
		
		MySetWebPage outc;
		outc = (*it)->outgoing_links();
		if ((*it)->outgoing() > 0) {

			for (it2 = outc.begin(); it2 != outc.end(); ++it2) {
				
				push.insert(*it2);
				
				
			}
			inc.clear();
			outc.clear();
			
		}
		
	}

	for (it = push.begin(); it != push.end(); ++it) {
		
			showlist.push_back(*it);
	}
	int alphsize = showlist.size();
	
	//MERGESORT!!!
	mergeSort(showlist, comp);
	//write out everything
	for (int i = 0; i < alphsize; i++) {	
		
		QString temp;

		
		temp += QString::fromStdString((showlist[i])->filename());
		temp += "  In: ";
		
		temp += QString::number((showlist[i])->incoming());
		temp += "  Out: ";
		
		temp += QString::number((showlist[i])->outgoing());
		temp += "  PR: ";

		temp += QString::number((showlist[i])->get_pagerank());
		
		filelist->addItem(temp);
		
	}
}

//basically same thing as above except for different comparator
void MainWindow::displayresultsincoming() {
	filelist->clear();
	std::set<WebPage*>::iterator it;
	showlist.clear();
	IncomingComp comp;
	MySetWebPage temp;
	MySetWebPage push;
	temp = results;
	push = results;
	for (it = temp.begin(); it != temp.end(); ++it) {
		std::set<WebPage*>::iterator it2;
		MySetWebPage inc;
		inc = (*it)->incoming_links();
		if ((*it)->incoming() > 0) {
			for (it2 = inc.begin(); it2 != inc.end(); ++it2) {
				push.insert(*it2);
			}
		}
		
		MySetWebPage outc;
		outc = (*it)->outgoing_links();
		if ((*it)->outgoing() > 0) {

			for (it2 = outc.begin(); it2 != outc.end(); ++it2) {
				
				push.insert(*it2);
				
				
			}
			inc.clear();
			outc.clear();
			
		}
		
	}
	for (it = push.begin(); it != push.end(); ++it) {
		
			showlist.push_back(*it);
	}

	int incsize = showlist.size();
	//cout << alphsize << endl;
	mergeSort(showlist, comp);
	
	for (int i = 0; i < incsize; i++) {	

		QString temp;

		//temp += "\"";
		temp += QString::fromStdString((showlist[i])->filename());
		temp += "  In: ";
		
		temp += QString::number((showlist[i])->incoming());
		temp += "  Out: ";
		
		temp += QString::number((showlist[i])->outgoing());
		temp += "  PR: ";

		temp += QString::number((showlist[i])->get_pagerank());
		
		filelist->addItem(temp);
	}
}
//yep same thing as above
void MainWindow::displayresultsoutgoing() {
	filelist->clear();
	std::set<WebPage*>::iterator it;
	showlist.clear();
	OutgoingComp comp;
	MySetWebPage temp;
	MySetWebPage push;
	temp = results;
	push = results;
	for (it = temp.begin(); it != temp.end(); ++it) {
		std::set<WebPage*>::iterator it2;
		MySetWebPage inc;
		inc = (*it)->incoming_links();
		if ((*it)->incoming() > 0) {
			for (it2 = inc.begin(); it2 != inc.end(); ++it2) {
				push.insert(*it2);
			}
		}
		//cout << "hi" << endl;
		MySetWebPage outc;
		outc = (*it)->outgoing_links();
		if ((*it)->outgoing() > 0) {
//cout << (*it)->outgoing() << endl;
//cout<< (*it)->filename() << endl;
			for (it2 = outc.begin(); it2 != outc.end(); ++it2) {
				//cout << (*it2)->filename() << endl;
				push.insert(*it2);
				
				
			}
			inc.clear();
			outc.clear();
			//cout << "done " << endl;
		}
		//cout << "what is this?? " << endl;
	}
	for (it = push.begin(); it != push.end(); ++it) {
		
			showlist.push_back(*it);
	}
	int outsize = showlist.size();
	//cout << alphsize << endl;
	mergeSort(showlist, comp);
	
	for (int i = 0; i < outsize; i++) {	

		QString temp;

		//temp += "\"";
		temp += QString::fromStdString((showlist[i])->filename());
		temp += "  In: ";
		
		temp += QString::number((showlist[i])->incoming());
		temp += "  Out: ";
		
		temp += QString::number((showlist[i])->outgoing());
		temp += "  PR: ";

		temp += QString::number((showlist[i])->get_pagerank());
		
		filelist->addItem(temp);
	}
}
//just a way to close the app
void MainWindow::closeapp() {
	otherwin->hide();
	close();
}
//this is how i run through the different functions
void MainWindow::functions() {
	
	//if something is checked then run whatever
	if (AND_button->isChecked()) {
		
		if (search_text->text().isEmpty()) {
			
			return;
		}
		string temp;
		temp = search_text->text().toStdString();
		istringstream stream (temp);
		search_text->setText("");
		string loading;
		stream >> loading;
		for (int i = 0; i < int(loading.size()); i++) {
            if (loading[i] < 92) {
              loading[i] = loading[i] + 32;
            }
          }
         //initializedand then run the stuff
		results = searching.ONE_function(loading);

		while (stream >> loading) {
			for (int i = 0; i < int(loading.size()); i++) {
	            if (loading[i] < 92) {
	              loading[i] = loading[i] + 32;
	            }
          	}

          	results = searching.AND_function(loading, results);
		}

	}
//same as above
	else if (OR_button->isChecked()) {
		//OR_button->setChecked(false);
		if (search_text->text().isEmpty()) {
			
			return;
		}
		string temp;
		temp = search_text->text().toStdString();
		istringstream stream (temp);
		search_text->setText("");
		string loading;
		stream >> loading;
		for (int i = 0; i < int(loading.size()); i++) {
            if (loading[i] < 92) {
              loading[i] = loading[i] + 32;
            }
          }
		results = searching.ONE_function(loading);

		while (stream >> loading) {
			for (int i = 0; i < int(loading.size()); i++) {
	            if (loading[i] < 92) {
	              loading[i] = loading[i] + 32;
	            }
          	}

          	results = searching.OR_function(loading, results);
		}

	}
//same thing as above for single
	else if (SINGLE_button->isChecked()) {
		//SINGLE_button->setChecked(false);
		if (search_text->text().isEmpty()) {
			
			return;
		}
		string temp;
		temp = search_text->text().toStdString();
		istringstream stream (temp);
		search_text->setText("");
		string loading;
		stream >> loading;
		for (int i = 0; i < int(loading.size()); i++) {
            if (loading[i] < 92) {
              loading[i] = loading[i] + 32;
            }
          }
        if (stream >> loading) {
        	error();
        	return;
        }
		results = searching.ONE_function(loading);
	}

	displayresults();
}
//to call the new webpage
void MainWindow::showpage(QListWidgetItem* translate) {
	
	//basically getthe webpage and then do stuff from there
	string test;
	QString str = translate->text();
	istringstream stream (str.toStdString());
	stream >> test;
	for (int i = 0; i < int(showlist.size()); i++) {
		if (showlist[i]->filename() == test) {
			secondin = showlist[i] -> incoming_links();
			secondout = showlist[i] -> outgoing_links();
			//cout << showlist[i] -> outgoing() << endl;
			populate(showlist[i]);
		}
	}


	otherwin->show();
}

void MainWindow::hidepage() {
	otherwin->hide();
}

void MainWindow::error() {
	errorwin->show();
}

void MainWindow::hideerror() {
	errorwin->hide();
}
//called by function above to fill stuff on the new window
void MainWindow::populate(WebPage* web) {
	otherwin->setWindowTitle(QString::fromStdString(web->filename()));
	//ostream propugation(NULL); 
	stringstream propugation;
	propugation << *web;
	string str="";
	str =  propugation.str();
	webpagestuff->setText(QString::fromStdString(str));
	sortalph();
}

void MainWindow::sortalph() {

	showinlist.clear(); showoutlist.clear();
	in->clear(); out->clear();

	std::set<WebPage*>::iterator it;
	//just search through and get webpages and sort them
	Alphabet comp;
	for (it = secondin.begin(); it != secondin.end(); ++it) {
		
		showinlist.push_back(*it);
	}

	for (it = secondout.begin(); it != secondout.end(); ++it) {
		
		showoutlist.push_back(*it);
		//cout << (*it)->incoming() << " " << (*it)->outgoing() << endl;
	}



	//cout << alphsize << endl;
	mergeSort(showinlist, comp);
	mergeSort(showoutlist, comp);

	int outinsize = showinlist.size();
	int outoutsize = showoutlist.size();
//have to do tiwce because two differenct lists
	for (int i = 0; i < outinsize; i++) {	

		QString temp;

		//temp += "\"";
		temp += QString::fromStdString((showinlist[i])->filename());
		temp += "  In: ";
		temp += QString::number((showinlist[i])->incoming());
		temp += "  Out: ";
		temp += QString::number((showinlist[i])->outgoing());
		//temp += "\"";
		in->addItem(temp);
	}

	for (int i = 0; i < outoutsize; i++) {	

		QString temp;

		//temp += "\"";
		temp += QString::fromStdString((showoutlist[i])->filename());
		temp += "  In: ";
		temp += QString::number((showoutlist[i])->incoming());
		//std::cout << (showoutlist[i])->incoming() << std::endl;
		temp += "  Out: ";
		temp += QString::number((showoutlist[i])->outgoing());
		//cout << (showoutlist[i])->outgoing() << endl;
		//temp += "\"";
		out->addItem(temp);
	}
	
	
}
//same
void MainWindow::sortinc() {

	showinlist.clear(); showoutlist.clear();
	in->clear(); out->clear();

	std::set<WebPage*>::iterator it;
	
	IncomingComp comp;
	for (it = secondin.begin(); it != secondin.end(); ++it) {
		
		showinlist.push_back(*it);
	}

	for (it = secondout.begin(); it != secondout.end(); ++it) {
		
		showoutlist.push_back(*it);
		//cout << (*it)->incoming() << " " << (*it)->outgoing() << endl;
	}



	//cout << alphsize << endl;
	mergeSort(showinlist, comp);
	mergeSort(showoutlist, comp);

	int outinsize = showinlist.size();
	int outoutsize = showoutlist.size();

	for (int i = 0; i < outinsize; i++) {	

		QString temp;

		//temp += "\"";
		temp += QString::fromStdString((showinlist[i])->filename());
		temp += "  In: ";
		temp += QString::number((showinlist[i])->incoming());
		temp += "  Out: ";
		temp += QString::number((showinlist[i])->outgoing());
		//temp += "\"";
		in->addItem(temp);
	}

	for (int i = 0; i < outoutsize; i++) {	

		QString temp;

		//temp += "\"";
		temp += QString::fromStdString((showoutlist[i])->filename());
		temp += "  In: ";
		temp += QString::number((showoutlist[i])->incoming());
		//std::cout << (showoutlist[i])->incoming() << std::endl;
		temp += "  Out: ";
		temp += QString::number((showoutlist[i])->outgoing());
		//cout << (showoutlist[i])->outgoing() << endl;
		//temp += "\"";
		out->addItem(temp);
	}
	
	
}
//same
void MainWindow::sortout() {

	showinlist.clear(); showoutlist.clear();
	in->clear(); out->clear();

	std::set<WebPage*>::iterator it;
	
	OutgoingComp comp;
	for (it = secondin.begin(); it != secondin.end(); ++it) {
		
		showinlist.push_back(*it);
	}

	for (it = secondout.begin(); it != secondout.end(); ++it) {
		
		showoutlist.push_back(*it);
		//cout << (*it)->incoming() << " " << (*it)->outgoing() << endl;
	}



	//cout << alphsize << endl;
	mergeSort(showinlist, comp);
	mergeSort(showoutlist, comp);

	int outinsize = showinlist.size();
	int outoutsize = showoutlist.size();

	for (int i = 0; i < outinsize; i++) {	

		QString temp;

		//temp += "\"";
		temp += QString::fromStdString((showinlist[i])->filename());
		temp += "  In: ";
		temp += QString::number((showinlist[i])->incoming());
		temp += "  Out: ";
		temp += QString::number((showinlist[i])->outgoing());
		//temp += "\"";
		in->addItem(temp);
	}

	for (int i = 0; i < outoutsize; i++) {	

		QString temp;

		//temp += "\"";
		temp += QString::fromStdString((showoutlist[i])->filename());
		temp += "  In: ";
		temp += QString::number((showoutlist[i])->incoming());
		//std::cout << (showoutlist[i])->incoming() << std::endl;
		temp += "  Out: ";
		temp += QString::number((showoutlist[i])->outgoing());
		//cout << (showoutlist[i])->outgoing() << endl;
		//temp += "\"";
		out->addItem(temp);
	}
	
	
}

void MainWindow::initializepagerank(std::vector<WebPage*> rank) {
	
	std::vector<WebPage*>::iterator it;
	//double number;
	for (it = rank.begin(); it != rank.end(); ++it) {
		(*it)->set_pagerank(double(1)/(searching.num_WebPages()));
		//cout << (*it)->get_pagerank() << endl;
		bool found = false;
		MySetWebPage temp = (*it)->outgoing_links();

		std::set<WebPage*>::iterator it2;
		for (it2 = temp.begin(); it2 != temp.end(); ++it2) {
			if ((*it2)->filename() == (*it)->filename()){
				found = true;
				
			}
		}
		if (found != true) {
			(*it)->set_found(true);
			//(*it)->set_out((*it)->outgoing() + 1);
		}
	}

	iteratorcounter = 0;
	iteratepagerank(rank);

}

void MainWindow::iteratepagerank(std::vector<WebPage*> rank) {
	
	iteratorcounter++;
	std::vector<WebPage*> temp;
	temp = rank;
	std::vector<WebPage*>::iterator it;
	std::vector<WebPage*>::iterator it2;
	std::set<WebPage*>::iterator it3;
	std::vector<WebPage*>::iterator it4;
	//cout << epsilon << " " << steps << endl;
	for (it = temp.begin(); it != temp.end(); ++it) {
		/*cout <<(*it)->filename() << endl;
		std::set<WebPage*> tempIn = (*it)->incoming_links();
		for (it3 = tempIn.begin(); it3 != tempIn.end(); ++it3){
			cout <<"\t" <<(*it3)->filename()<<" incoming" <<endl;
		}
		cout << "starting printing f outgoin" <<endl;
		std::set<WebPage*> temp = (*it)->outgoing_links();
		for (it3 = temp.begin(); it3 != temp.end(); ++it3){
			cout <<"\t" <<(*it3)->filename() <<" outgoing" <<endl;
		}*/
			double sum = 0;
		if ((*it)->get_found() == true) {
			sum = (*it)->get_pagerank()/(double((*it)->outgoing()+1.0));
		}
		else {
			sum = (*it)->get_pagerank()/(double((*it)->outgoing()));
		}
		//double sum = (*it)->get_pagerank()/(double((*it)->outgoing()));
		MySetWebPage inc = (*it)->incoming_links();
		
		//cout << (*it)->incoming_links().filename() << "  " << (*it)->outgoing_links().filename() << endl;
		if ((*it)->incoming() != 0) {
			for (it3 = inc.begin(); it3 != inc.end(); ++it3) {
				//if ((*it)->filename() != (*it2)->filename()) {

				for (it4 = rank.begin(); it4 != rank.end(); ++it4) {
					if ((*it4)->filename() == (*it3)->filename()) {
						if((*it)->filename() != (*it3)->filename()) {
						
							if ((*it3)->get_found() == true) {
								sum += ((*it3)->get_pagerank())/(double((*it3)->outgoing()+1.0));
						
							}
							else {
								sum += ((*it3)->get_pagerank())/(double((*it3)->outgoing()));
							}
						}
					}
				}
			}
		}
		//MySetWebPage outc = (*it)->outgoing_links();
		for (it2 = rank.begin(); it2 != rank.end(); ++it2) {
			if ((*it)->filename() == (*it2)->filename()) {
				
				(*it2)->set_pagerank((epsilon/double(rank.size()))+(double((1.0-epsilon)*sum)));
			//cout << (*it2)->get_pagerank() << " end" << endl;
			}
		}
		//cout << sum << "    " << (double((*it)->outgoing()) + double(1)) << endl;
		//cout << (*it)->filename() << endl;
		//cout << (*it)->get_pagerank() << " end" << endl;
		//cout << (*it)->get_pagerank() << endl;

	}
	//cout << "hi blooo" << endl;
	if (iteratorcounter <= steps) {
		iteratepagerank(rank);
	}
	
}