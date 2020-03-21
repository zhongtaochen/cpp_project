#include "assembler.h"
#include "linker.h"
#include "loader.h"
#include "simulator.h"
#include "utils.h"
using namespace std;

int main(int argc, char *argv[]) {
//    ifstream file = readFile("C:\\Users\\40455\\Desktop\\FOCUS\\ARCHITECTURE\\HW2\\mini_grader(2).asm");
    ifstream file = readFile("C:\\Users\\40455\\Desktop\\FOCUS\\ARCHITECTURE\\HW2\\simple test files\\4.asm");
    Assembler assm(file);
//    assm.output("C:\\Users\\40455\\Desktop\\FOCUS\\ARCHITECTURE\\HW2\\output.txt");
    Linker linker({assm.getObjFile()});
    Loader loader(linker.getExecutableFile());
//    ExecutableFile exe_file = linker.getExecutableFile();
    Simulator sim(loader.getMemorySimulator(), loader.getRegistersSimulator());
}
