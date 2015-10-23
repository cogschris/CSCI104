#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QListWidget>
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
	MainWindow(std::string name);
	~MainWindow();
private slots:
	
	void displayresults();
	void displayresultsincoming();
	void displayresultsoutgoing();
	void functions();
	//void and_function();
	//void or_function();
	//void single_function();

private:

	// // UI

	// Layouts
	QHBoxLayout* overallLayout;
	QVBoxLayout* display;
	QVBoxLayout* formLayout;
	QHBoxLayout* sorting;
	QListWidget* filelist;
	// Displayed quote
	QLabel* Input_text;
	QRadioButton* AND_button;
	QRadioButton* OR_button;
	QRadioButton* SINGLE_button;
	QPushButton* search_button;

	QPushButton* filename;
	QPushButton* num_in;
	QPushButton* num_out;
	//QPushButton* refresh_button;

	QLineEdit* search_text;


	SearchEng searching;

	MySetWebPage results;
	
	//QLabel* pokemonNameDisplay;

	// List of quotes
	//QListWidget* pokemonListWidget;
};