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
        }
        unsigned int start_text_locat = 0;
        for (ObjectFile obj_file : obj_file_list) {
            for (ObjectFile::relocation_cell reloc : obj_file.relocation_info) {
                ExecutableFile::segment_cell cell = exe_file.text_segment.at((start_text_locat+reloc.address)>> 2);
                string mc_code  = cell.data;
                int mc_code_int = stoi(mc_code, 0, 2);
                if (reloc.instuction == "j" || reloc.instuction == "jal") { // J-type
                    mc_code_int &= 0xfc000000;
                    mc_code_int |= ((symbol_table.at(reloc.dependency) &= ~0xf0000000) >> 2);
                }
                if(reloc.instuction == "lb"||"lbu"||"lhu"||"lw"||"lwcl"||"sb"||"sh"){
                    mc_code_int &= 0xfc1f0000;
                    mc_code_int |= 0x03e0000; // set rs to $gp
                    //static const unsigned int __data_addr = 0x00500000;
                    string addrs_diff = intToHexString(symbol_table.at(reloc.dependency)-exe_file.__data_addr);//offset w.r.t $gp
                    unsigned int addrs_diff_int  = std::stoul(addrs_diff,nullptr,16);
                    mc_code_int |= 0x0000ffff&addrs_diff_int;

                }
                exe_file.text_segment.at((start_text_locat+reloc.address) >> 2).data = intToBinaryString(mc_code_int);
            }
            start_text_locat+=obj_file.text_size;
        }
    }
}

#endif // LINKER_H





