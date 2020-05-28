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
#include <QTextStream>




//int main(int argc, char *argv[])
//{


//    Q_INIT_RESOURCE(application);
//    QApplication app(argc, argv);


//    MainWindow mainWin;
//    mainWin.resize(1000, 600);
//    mainWin.show();
//    return app.exec();
//    return 0;

//}








//#include <QApplication>
//#include <QTextStream>
//#include <QDebug>

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    QTextStream out(stdout);//显示数据
//    QTextStream in(stdin);//获取数据
//    out<<"input"<<endl;
//    QString str;

//    in>>str;


//    out << str << endl;

//    return a.exec();
//}

int main(){
    std::ifstream file = readFile("C:\\Users\\quyah\\Desktop\\cpp_project\\New Folder\\cpp_project\\simple_test_files\\fibonacci.asm");
    Assembler assm;
    assm.assemble(file);
    std::vector<ObjectFile> obj_file_list = { assm.getObjFile()};
    Linker linker;
    linker.link(obj_file_list);
    ExecutableFile exe_file =  linker.getExecutableFile();
    Loader loader;
    loader.load(&exe_file);
    Simulator simulator(loader.getMemorySimulator(), loader.getRegisterFilesSimulator());
    simulator.run();
    return 0;
}

