#ifndef LINKER_H
#define LINKER_H

#include "objectfile.h"
#include "executablefile.h"
#include <vector>
#include "utils.h"
using namespace std;

class Linker {

public:

/**
 * Constructor: Linker
 * Usage: Linker linker(obj_file_list);
 * ------------------------------------
 * @brief Initilize Linker object and generate executable file.
 */
    Linker(std::vector<ObjectFile> obj_file_list);

/**
 * Method: getExecutableFile
 * Usage: ExecutableFile exe_file = linker.getExecutableFile();
 * ------------------------------------------------------------
 * @brief Return corresponding executable file.
 */
    ExecutableFile getExecutableFile() {return exe_file;};

private:

    ExecutableFile exe_file;

};

//这里不需要text.size
Linker::Linker(vector<ObjectFile> obj_file_list) {
    if (obj_file_list.size() >= 1) {
        map<string, unsigned int> symbol_table;
        for (ObjectFile obj_file : obj_file_list) {
//            static const unsigned int __text_addr = 0x00400000;
//            static const unsigned int __data_addr = 0x00500000;
            unsigned int curr_text_addr = exe_file.text_size + ExecutableFile::__text_addr;
            unsigned int curr_data_addr = exe_file.data_size + ExecutableFile::__data_addr;
            //            struct segment_cell {unsigned int address; std::string data;};
            for (ObjectFile::segment_cell cell : obj_file.text_segment) {
                unsigned int absolute_addr = cell.address + curr_text_addr;
                exe_file.text_segment.push_back({absolute_addr, cell.data});
                exe_file.text_size += 4;
            }
            for (ObjectFile::segment_cell cell : obj_file.data_segment) {
                unsigned int absolute_addr = cell.address + curr_data_addr;
                exe_file.data_segment.push_back({absolute_addr, cell.data});
                exe_file.data_size += 4;
            }
            for (auto const & pair: obj_file.symbol_table) {
                symbol_table[pair.first] = pair.second + curr_text_addr;
            }

            //struct segment_cell {unsigned int address; std::string data;};
            //std::vector<segment_cell> text_segment;

            //struct relocation_cell {unsigned int address; std::string instuction; std::string dependency;};
            for (ObjectFile::relocation_cell reloc : obj_file.relocation_info) {
                if (reloc.instuction == "j" || reloc.instuction == "jal") { // J-type
                    ExecutableFile::segment_cell cell = exe_file.text_segment.at(reloc.address >> 2);
                    // data cell.refers to  instructions like lw$a0,...
                    string mc_code  = cell.data;
                    int mc_code_int = stoi(mc_code, 0, 2);
                    mc_code_int &= 0xfc000000;
                    mc_code_int |= ((symbol_table.at(reloc.dependency) &= ~0xf0000000) >> 2);

                    // 这里不能at.(reloca.dependency) 如果不只一个文件

                    exe_file.text_segment.at(reloc.address >> 2).data = intToBinaryString(mc_code_int);
                }
            }
        }
    }
}

#endif // LINKER_H





