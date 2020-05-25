#include "assembler.h"
#include "linker.h"
#include "loader.h"
#include "simulator.h"
#include "utils.h"

#include <iostream>
using namespace std;
int main() {
    //std::ifstream file = readFile("C:\\Users\\quyah\\Desktop\\cpp_project\\New Folder\\cpp_project\\simple_test_files\\testla1.asm");
    //std::ifstream file1 = readFile("C:\\Users\\quyah\\Desktop\\cpp_project\\New Folder\\cpp_project\\simple_test_files\\testla2.asm");
    //Assembler assm(file);
    //Assembler assm1(file1);
    ////std::vector<ObjectFile> obj_file_list = {assm.getObjFile(),assm1.getObjFile()};
    //std::vector<ObjectFile> obj_file_list = {assm.getObjFile()};
    //std::vector<ObjectFile> obj_file_list1 = { assm1.getObjFile() };
    //Linker linker(obj_file_list);
    //Linker linker2(obj_file_list1);
    //for (int i = 0; i <linker.getExecutableFile().text_segment.size(); i++) {
    //    if (linker.getExecutableFile().text_segment.at(i).address != linker2.getExecutableFile().text_segment.at(i).address) {
    //        cout << "address at " << i << endl;
    //    }
    //    if (linker.getExecutableFile().text_segment.at(i).machine_code != linker2.getExecutableFile().text_segment.at(i).machine_code) {
    //        cout << "machine code at " << i << endl;
    //    }
    //    if (linker.getExecutableFile().text_segment.at(i).instruction != linker2.getExecutableFile().text_segment.at(i).instruction) {
    //        cout << "instruction code at " << i << endl;
    //        
    //    }
    //}
    //cout << "1" << endl;
    std::ifstream file = readFile("C:\\Users\\quyah\\Desktop\\cpp_project\\New Folder\\cpp_project\\simple_test_files\\mini_grader.asm");
    Assembler assm(file);
    std::vector<ObjectFile> obj_file_list = { assm.getObjFile()}; 
    Linker linker(obj_file_list);
    ExecutableFile exe_file =  linker.getExecutableFile();
    Loader loader(&exe_file);
    Simulator simulator(loader.getMemorySimulator(), loader.getRegisterFilesSimulator());
    simulator.run();
    return 0;
}
