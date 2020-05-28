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




int main(int argc, char *argv[])
{


    Q_INIT_RESOURCE(application);
    QApplication app(argc, argv);


    MainWindow mainWin;
    mainWin.resize(1000, 600);
    mainWin.show();
    return app.exec();
    return 0;

}


//int main(){
//    std::ifstream file = readFile("C:\\Users\\quyah\\Desktop\\cpp_project\\New Folder\\cpp_project\\simple_test_files\\testmultiple_files1.asm");
//    std::ifstream file2 = readFile("C:\\Users\\quyah\\Desktop\\cpp_project\\New Folder\\cpp_project\\simple_test_files\\testmultiple_files2.asm");

//    Assembler assm;
//    Assembler assm2;
//    assm.assemble(file);
//    assm2.assemble(file2);

//    std::vector<ObjectFile> obj_file_list = { assm.getObjFile(),assm2.getObjFile()};
//    Linker linker;
//    linker.link(obj_file_list);
//    ExecutableFile exe_file =  linker.getExecutableFile();
//    Loader loader;
//    loader.load(&exe_file);
//    Simulator simulator(loader.getMemorySimulator(), loader.getRegisterFilesSimulator());
//    simulator.run();
//    return 0;
//}

