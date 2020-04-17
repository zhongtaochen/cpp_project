#include "linker.h"
#include "utils.h"
using namespace std;

Linker::Linker(vector<ObjectFile> obj_file_list) {
    if (obj_file_list.size() == 1) {
        map<string, unsigned int> symbol_table;
        for (ObjectFile obj_file : obj_file_list) {
            unsigned int curr_text_addr = exe_file.text_size + ExecutableFile::__text_addr;
            unsigned int curr_data_addr = exe_file.data_size + ExecutableFile::__data_addr;
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
            for (ObjectFile::relocation_cell reloc : obj_file.relocation_info) {
                if (reloc.instuction == "j" || reloc.instuction == "jal") { // J-type
                    ExecutableFile::segment_cell cell = exe_file.text_segment.at(reloc.address >> 2);
                    string mc_code  = cell.data;
                    int mc_code_int = stoi(mc_code, 0, 2);
                    //mc_code_int is the binary representing instructions,
                    mc_code_int &= 0xfc000000;
                    mc_code_int |= ((symbol_table.at(reloc.dependency) &= ~0xf0000000) >> 2);
                    exe_file.text_segment.at(reloc.address >> 2).data = intToBinaryString(mc_code_int);
                }
            }
        }
    }
}
