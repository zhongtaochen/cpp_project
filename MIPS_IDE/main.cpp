#include "assembler.h"
#include "linker.h"
#include "loader.h"
#include "simulator.h"
#include "utils.h"
int main() {
    std::ifstream file = readFile("C:\\Users\\quyah\\Desktop\\cpp_project\\New Folder\\cpp_project\\simple_test_files\\mini_grader.asm");
    std::ifstream file1 = readFile("C:\\Users\\quyah\\Desktop\\cpp_project\\New Folder\\cpp_project\\simple_test_files\\testlinker.asm");
    Assembler assm(file);
    Assembler assm1(file1);
    std::vector<ObjectFile> obj_file_list = {assm.getObjFile(),assm1.getObjFile()};
    Linker linker(obj_file_list);
    ExecutableFile exe_file =  linker.getExecutableFile();
    Loader loader(&exe_file);
    Simulator simulator(loader.getMemorySimulator(), loader.getRegisterFilesSimulator());
    simulator.run();
    return 0;
}
