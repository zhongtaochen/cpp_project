#include "assembler.h"
#include "linker.h"
#include "loader.h"
#include "simulator.h"
#include "utils.h"
using namespace std;
#include <iostream>

int main() {

    ifstream file = readFile("C:\\Users\\quyah\\Desktop\\MIPS_Simulator\\testfile.asm");
//    ifstream file = readFile("C:\\Users\\quyah\\Desktop\\MIPS_Simulator\\my_t1.asm");

    //    ifstream file = readFile("C:\\Users\\40455\\Desktop\\FOCUS\\ARCHITECTURE\\HW2\\simple test files\\4.asm");
    Assembler assm(file);
////    assm.output("C:\\Users\\40455\\Desktop\\FOCUS\\ARCHITECTURE\\HW2\\output.txt");
    Linker linker({assm.getObjFile()});
    ExecutableFile outputfile = linker.getExecutableFile();
    string filename = "exeoutput.txt";
//    ofstream outfile(filename.c_str());
//    ExeAsTxt(outfile,outputfile);
//    outfile.close();

//    Loader loader(linker.getExecutableFile());
//    ExecutableFile exe_file = linker.getExecutableFile();
//    Simulator sim(loader.getMemorySimulator(), loader.getRegistersSimulator());

}

//int main(){
//    unsigned int a = 0xff1;
//    unsigned int b = 0xfc0;
//    string answer = intToHexString(a-b);
//    unsigned int x = std::stoul(answer,nullptr,16);
//    cout<<answer<<endl;
//    cout<<x<<endl;
//}

