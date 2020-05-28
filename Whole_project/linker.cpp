#include "linker.h"
#include "utils.h"
#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;

Linker::Linker(vector<ObjectFile>& obj_file_list) {
	link(obj_file_list);
}

void Linker::link(std::vector<ObjectFile>& obj_file_list) {
	exe_file.text_size = 0;
	exe_file.data_size = 0;
	if (obj_file_list.size() >= 1) {
		map<string, unsigned int> symbol_table;
		for (ObjectFile obj_file : obj_file_list) {
			uint32_t curr_text_addr = exe_file.text_size + 0x00400000;
			uint32_t curr_data_addr = exe_file.data_size + 0x00500000;
			for (TextCell cell : obj_file.text_segment) {
				unsigned int absolute_addr = cell.address + curr_text_addr;
				exe_file.text_segment.push_back({ absolute_addr, cell.machine_code,cell.instruction });
			}
			for (auto const& pair : obj_file.symbol_table) {
				if (pair.first.find("*") != string::npos) {
					symbol_table[pair.first.substr(1)] = pair.second + curr_data_addr;
				}
				else {
					symbol_table[pair.first] = pair.second + curr_text_addr;
				}

			}
			for (DataCell cell : obj_file.data_segment) {
				unsigned int absolute_addr = cell.address + curr_data_addr;
				exe_file.data_segment.push_back({ absolute_addr, cell.data });
			}
			exe_file.text_size += obj_file.text_size;
			exe_file.data_size += obj_file.data_size;

		}
		unsigned int start_text_locat = 0;
		string i_type[] = { "0","lb","lbu","lhu","lw","lwcl","sb","sh","bgez","bgtz","blez","bltz","bgezal","bltzal" };
		for (ObjectFile obj_file : obj_file_list) {
			if (!obj_file.relocation_information.empty()) {
				for (RelocationCell reloc : obj_file.relocation_information) {
					int sum = start_text_locat + reloc.address;
					TextCell cell = exe_file.text_segment.at(sum >> 2);
					uint32_t mc_code_int = cell.machine_code;
					if (reloc.instruction_type == "lui") {
						/*cout << intToBinaryString(mc_code_int) << endl;
						std::cout << intToBinaryString(symbol_table.at(reloc.dependency)) << endl;
						std::cout << intToBinaryString(symbol_table.at(reloc.dependency) >> 16) << endl;*/
						mc_code_int |= ((symbol_table.at(reloc.dependency) >> 16));
						//std::cout << intToBinaryString(mc_code_int) << endl;
						//cout << "1" << endl;
						convertInstruction(exe_file.text_segment.at(sum >> 2).instruction, reloc.dependency, (symbol_table.at(reloc.dependency) >> 16));
					}
					else if (reloc.instruction_type == "ori") {
						//cout << intToBinaryString(mc_code_int) << endl;
						//std::cout << intToBinaryString(symbol_table.at(reloc.dependency)) << endl;
						//std::cout << intToBinaryString((symbol_table.at(reloc.dependency) & 0x0000ffff)) << endl;
						mc_code_int |= ((symbol_table.at(reloc.dependency) & 0x0000ffff));
						convertInstruction(exe_file.text_segment.at(sum >> 2).instruction, reloc.dependency, (symbol_table.at(reloc.dependency) & 0x0000ffff));
						//cout << intToBinaryString(mc_code_int) << endl;
						//cout << "1" << endl;
					}
					else if (reloc.instruction_type == "j" || reloc.instruction_type == "jal") { // J-type
						mc_code_int &= 0xfc000000;
						mc_code_int |= ((symbol_table.at(reloc.dependency) & (~0xf0000000))) >> 2;

					}
					else if (i_type->find(reloc.instruction_type)) { // i-type                  
						mc_code_int &= 0xffff0000;
						//static const unsigned int __data_addr = 0x00500000;                 
//                        string addrs_diff = intToHexString(symbol_table.at(reloc.dependency)- 0x00500000);//offset w.r.t $gp
//                        unsigned int addrs_diff_int  = std::stoul(addrs_diff,nullptr,16);
						uint32_t addrs_diff_int = symbol_table.at(reloc.dependency) - 0x00500000;
						mc_code_int |= 0x0000ffff & addrs_diff_int;
					}
					exe_file.text_segment.at(sum >> 2).machine_code = mc_code_int;
				}
			}
			start_text_locat += (obj_file.text_size);
		}
	}

}



