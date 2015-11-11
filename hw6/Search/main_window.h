#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>
#include <QPlainTextEdit>
#include <QRadioButton>
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

#include <string>
#include <vector>

class MainWindow : public QWidget
{
	Q_OBJECT
public:
	MainWindow(std::string name, std::map<std::string, std::string> maps);
	~MainWindow();
	std::map<std::string, std::string> items;
	double epsilon;
	int steps;
private slots:
	
	void displayresults();
	void displayresultsfilename();
	void displayresultsincoming();
	void displayresultsoutgoing();
	void functions();
	void showpage(QListWidgetItem*);
	void hidepage();
	void closeapp();
	void populate(WebPage*);
	void sortalph();
	void sortinc();
	void sortout();
	void error();
	void hideerror();
	//void and_function();
	//void or_function();
	//void single_function();


	void initializepagerank(std::vector<WebPage*> rank);
	void iteratepagerank(std::vector<WebPage*> rank);


private:

	// // UI

	// Layouts
	QHBoxLayout* overallLayout;
	QVBoxLayout* display;
	QVBoxLayout* formLayout;
	//QHBoxLayout* sorting;
	QListWidget* filelist;
	// Displayed quote
	QLabel* Input_text;
	QLabel* label;
	QRadioButton* AND_button;
	QRadioButton* OR_button;
	QRadioButton* SINGLE_button;
	QPushButton* search_button;
	QPushButton* exiting;
	QPushButton* pagerank_button;
	QPushButton* filename;
	QPushButton* num_in;
	QPushButton* num_out;
	//QPushButton* refresh_button;

	QLineEdit* search_text;
	QHBoxLayout* labels;
	QLabel* newin;
	QLabel* newout;
	QPushButton* filename2;
	QPushButton* num_in2;
	QPushButton* num_out2;



	SearchEng searching;

	MySetWebPage results;
	MySetWebPage secondin;
	MySetWebPage secondout;

	std::vector<WebPage*> showlist;

	std::vector<WebPage*> showinlist;
	std::vector<WebPage*> showoutlist;


	QWidget* otherwin;
	QVBoxLayout* otherlayout;
	QLabel* title;
	QTextEdit* webpagestuff;
	QHBoxLayout* outin;
	QListWidget* in;
	QListWidget* out;
	QPushButton* exitnew;


	QWidget* errorwin;
	QVBoxLayout* errorlayout;
	QLabel* errormessage;
	QPushButton* exiterror;


	int iteratorcounter;
	std::map<WebPage*, double> pagerank;
	MySetWebPage allwebs;

	
	//QLabel* pokemonNameDisplay;

	// List of quotes
	//QListWidget* pokemonListWidget;
};