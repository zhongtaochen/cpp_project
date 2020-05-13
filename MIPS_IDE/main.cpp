#include "assembler.h"
#include "linker.h"
#include "loader.h"
#include "simulator.h"
#include "utils.h"
#include "iostream"
#include "vector"
using namespace std;

int main() {
    ifstream file1 = readFile("C:\\Users\\quyah\\Desktop\\cpp_project\\New Folder\\cpp_project\\simple_test_files\\mini_grader.asm");
    Assembler assm1(file1);
    ObjectFile obj = assm1.getObjFile();
    vector<ObjectFile> obl{ assm1.getObjFile() };
    Linker linker(obl);
    Loader loader(&(linker.getExecutableFile()));
    Simulator sim(loader.getMemorySimulator(),loader.getRegisterFilesSimulator());

}