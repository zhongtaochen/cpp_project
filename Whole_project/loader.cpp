/**
 * @file loader.cpp
 * @brief <code>Loader</code> class implementation.
 */

#include "loader.h"
Loader::Loader(ExecutableFile* exe_file) {
	load(exe_file);
}

void Loader::load(ExecutableFile* exe_file) {
	mem = new MemorySimulator;
	for (TextCell text_cell : exe_file->text_segment) {
		mem->writeWord(text_cell.address, text_cell.machine_code);
	}
	for (DataCell data_cell : exe_file->data_segment) {
		mem->writeWord(data_cell.address, data_cell.data);
	}

	reg = new RegisterFilesSimulator;
	//    reg->writeReg(28, exe_file->data_segment.at(0).address); // $gp
	reg->writeReg(28, 0x00500000);
	reg->writeReg(29, mem->getEndAddress()); // $fp
}

MemorySimulator* Loader::getMemorySimulator() {
	return mem;
}

RegisterFilesSimulator* Loader::getRegisterFilesSimulator() {
	return reg;
}
