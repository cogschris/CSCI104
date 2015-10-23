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
#include "msort.h"

using namespace std;

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

MainWindow::MainWindow(string name)
{
	
	PageParser* parser = new MDPageParser;
	
	searching.add_parse_from_index_file(name, parser);

	setWindowTitle("Chris' Google");

	overallLayout = new QHBoxLayout();

	display = new QVBoxLayout();
	overallLayout->addLayout(display);

	filelist = new QListWidget();
	display->addWidget(filelist);

	sorting = new QHBoxLayout();
	display->addLayout(sorting);

	//refresh_button = new QPushButton("Refresh/Reload");
	///display->addWidget(refresh_button);

	filename = new QPushButton("Sort by filename");
	connect(filename, SIGNAL(clicked()), this, SLOT(displayresults()));
	sorting->addWidget(filename);

	num_in = new QPushButton("Sort by number of incoming links");
	connect(num_in, SIGNAL(clicked()), this, SLOT(displayresultsincoming()));
	sorting->addWidget(num_in);

	num_out = new QPushButton("Sort by number of outgoing links");
	connect(num_out, SIGNAL(clicked()), this, SLOT(displayresultsoutgoing()));
	sorting->addWidget(num_out);

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
	formLayout->addWidget(search_button);

	setLayout(overallLayout);
}

MainWindow::~MainWindow() {

}

void MainWindow::displayresults() {
	
	filelist->clear();
	std::set<WebPage*>::iterator it;
	vector<WebPage*> alph;
	Alphabet comp;
	for (it = results.begin(); it != results.end(); ++it) {
		
		alph.push_back(*it);
		cout << (*it)->filename() << endl;
	}

	int alphsize = alph.size();
	//cout << alphsize << endl;
	
	mergeSort(alph, comp, 0, alphsize-1);
	cout << "done" << endl;
	for (int i = 0; i < alphsize; i++) {	
		//cout << "fuck" << endl;
		QString temp;

		//temp += "\"";
		//cout << i << endl;
		cout << alph[i]->filename() << endl;
		temp += QString::fromStdString((alph[i])->filename());
		temp += "  ";
		//cout << "damn" << endl;
		temp += QString::number((alph[i])->incoming());
		temp += "  ";
		//cout << "okay" << endl;
		temp += QString::number((alph[i])->outgoing());
		//temp += "\"";
		filelist->addItem(temp);
		//cout << "shit" << endl;
	}
}

void MainWindow::displayresultsincoming() {
	filelist->clear();
	std::set<WebPage*>::iterator it;
	vector<WebPage*> inc;
	IncomingComp comp;
	for (it = results.begin(); it != results.end(); ++it) {
		
		inc.push_back(*it);
	}

	int incsize = inc.size();
	//cout << alphsize << endl;
	mergeSort(inc, comp, 0, incsize-1);
	
	for (int i = 0; i < incsize; i++) {	

		QString temp;

		//temp += "\"";
		temp += QString::fromStdString((inc[i])->filename());
		temp += "  ";
		temp += QString::number((inc[i])->incoming());
		temp += "  ";
		temp += QString::number((inc[i])->outgoing());
		//temp += "\"";
		filelist->addItem(temp);
	}
}

void MainWindow::displayresultsoutgoing() {
	filelist->clear();
	std::set<WebPage*>::iterator it;
	vector<WebPage*> out;
	OutgoingComp comp;
	for (it = results.begin(); it != results.end(); ++it) {
		
		out.push_back(*it);
	}

	int outsize = out.size();
	//cout << alphsize << endl;
	mergeSort(out, comp, 0, outsize-1);
	
	for (int i = 0; i < outsize; i++) {	

		QString temp;

		//temp += "\"";
		temp += QString::fromStdString((out[i])->filename());
		temp += "  ";
		temp += QString::number((out[i])->incoming());
		temp += "  ";
		temp += QString::number((out[i])->outgoing());
		//temp += "\"";
		filelist->addItem(temp);
	}
}


void MainWindow::functions() {
	

	if (AND_button->isChecked()) {
		//AND_button->setChecked(false);
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

          	results = searching.AND_function(loading, results);
		}

	}

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
		results = searching.ONE_function(loading);
	}

	displayresults();
}