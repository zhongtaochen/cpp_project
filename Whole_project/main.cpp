#include <QApplication>
#include "mainwindow.h"
using namespace std;

int main(int argc, char* argv[]) {
	Q_INIT_RESOURCE(application);
	QApplication app(argc, argv);

	MainWindow mainWin;
	mainWin.resize(1000, 600);
	mainWin.show();
	return app.exec();
}
