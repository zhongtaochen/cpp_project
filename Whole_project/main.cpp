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

//    ExecutableFile exe_file;
//    exe_file.text_size = 24;
//    exe_file.text_segment = {
//        {0x00400000, 0x00400000, "Breakpoint 0x00400000"},
//        {0x00400004, 0x00400004, "Breakpoint 0x00400004"},
//        {0x00400008, 0x00400008, "Breakpoint 0x00400008"},
//        {0x0040000c, 0x0040000c, "Breakpoint 0x0040000c"},
//        {0x00400010, 0x00400010, "Breakpoint 0x00400010"},
//        {0x00400014, 0x00400014, "Breakpoint 0x00400014"}
//    };
//    exe_file.data_size = 8;
//    exe_file.data_segment = {
//        {0x00500000, 0x00001010},
//        {0x00500004, 0x00001010}
//    };

//    /** Core Methods */
//    Debugger debugger(&exe_file);
//    debugger.addBreakpoint(0x00400000);
//    debugger.addBreakpoint(0x00400008);
//    assert(debugger.run() == 0x00400000);
//    std::cout << "Expected:\n\n" << std::endl;
//    assert(debugger.run() == 0x00400008);
//    std::cout << "Expected:\n0x00400000\n0x00400004\n" << std::endl;
//    assert(debugger.step() == 0x0040000c);
//    std::cout << "Expected:\n0x00400008\n" << std::endl;
//    debugger.addBreakpoint(0x00400010);
//    debugger.addBreakpoint(0x00400014);
////    debugger.removeBreakpoint(0x00400010);
//    assert(debugger.run() == 0x00400010);
//    std::cout << "Expected:\n0x0040000c\n0x00400010\n" << std::endl;
//    std::cout<<"keyyi"<<endl;

//    Debugger debugger2(&exe_file);
//    debugger2.addBreakpoint(0x00400008);
//    assert(debugger2.run() == 0x00400008);
//    std::cout << "Expected:\n0x00400000\n0x00400004\n" << std::endl;
//    return 0;

}

//int main(int argc, char *argv[]){
//    Q_INIT_RESOURCE(application);
//    QApplication app(argc, argv);
//    MainWindow mainWin;
//    mainWin.resize(1000, 600);
//    return 0;
//}
