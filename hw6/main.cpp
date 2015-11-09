#include "main_window.h"
#include <QApplication>
#include <fstream>
#include <iostream>
#include <string>
#include "crawler.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc == 2) {
		Crawler crawl(argv[1]);
	}
	else {
		Crawler crawl("config.txt")
	}
	
	QApplication app(argc, argv);

	MainWindow mainWindow (crawl.out());

	mainWindow.show();

	return app.exec();
}