/**
 * @file lineassembler_j.cpp
 * @brief <code>J_LineAssembler</code> class implementation.
 */

#include "lineassembler.h"
#include "utils.h"
using namespace std;

/* Implementation notes:
 * Here follows the format of J-TYPE instruction.
 * < J-type >
 *  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
 * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 * |    op(6bits)    |                            target(26bits)                                   |
 * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 */

ObjectFile J_LineAssembler::assemble() {
	uint32_t machine_code_int = 0;
	machine_code_int |= (op << 26);
	machine_code_int |= target;
	obj_file.text_segment.at(address >> 2).machine_code = machine_code_int;
	return obj_file;
}

/**
 * @details All J-type instructions involve absolute address.
 * No operand handling. Immediately fill the relocation information.
 */
J_LineAssembler::J_LineAssembler(string asm_line, ObjectFile obj_file, uint32_t address) {
	this->asm_line = asm_line;
	this->obj_file = obj_file;
	this->address = address;

	vector<string> tokens = split(asm_line, "[ \t,]+");
	string instruction = tokens.at(0);
	Format format = J_BIN.at(instruction);
	op = format.id; target = 0;

	this->obj_file.relocation_information.push_back({ address, instruction, tokens.at(1) });
}

void J_LineAssembler::handleOperand(OperandType op_type, const std::string& op) {};
