#include "main_window.h"
#include <QApplication>

using namespace std;

int main(int argc, char* argv[])
{
	if (argc < 1) {
		cout << "Enter index file location" << endl;
		return 1;
	}
	
	QApplication app(argc, argv);

	MainWindow mainWindow (argv[1]);

	mainWindow.show();

	return app.exec();
}