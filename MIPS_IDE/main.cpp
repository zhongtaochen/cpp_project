#include "assembler.h"
#include "linker.h"
#include "loader.h"
#include "simulator.h"
#include "utils.h"

int main() {
    std::ifstream file = readFile("C:\\Users\\40455\\Desktop\\simple_test_files\\fibonacci.asm");
    Assembler assm(file);
    assm.output("C:\\Users\\40455\\Desktop\\simple_test_files\\tmp.txt");
    std::vector<ObjectFile> obj_file_list = {assm.getObjFile()};
    Linker linker(obj_file_list);
    ExecutableFile exe_file =  linker.getExecutableFile();
    Loader loader(&exe_file);
    Simulator simulator(loader.getMemorySimulator(), loader.getRegisterFilesSimulator());
    simulator.run();
    return 0;
}
