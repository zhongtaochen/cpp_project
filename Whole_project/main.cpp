#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include "assembler.h"
#include "linker.h"
#include "loader.h"
#include "simulator.h"
#include "utils.h"
#include "debugger.h"
#include <iostream>
using namespace std;
#include "finddialog.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(application);
    QApplication app(argc, argv);

    //QCoreApplication app(argc, argv);
    MainWindow mainWin;
    mainWin.resize(1000, 600);
    mainWin.show();
    return app.exec();
}

//int main(int argc, char *argv[]){
//    Q_INIT_RESOURCE(application);
//    QApplication app(argc, argv);
//    MainWindow mainWin;
//    mainWin.resize(1000, 600);
//    return 0;
//}
