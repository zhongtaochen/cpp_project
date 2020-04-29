#include "lineassembler.h"
#include "utils.h"
#include <algorithm>
#include <iterator>
using namespace std;

LineAssembler::LineAssembler(ObjectFile obj_file, unsigned int address) {
    this->asm_line = obj_file.text_segment.at(address >> 2).data;
    this->obj_file = obj_file;
    this->address = address;
}

ObjectFile LineAssembler::assemble() {
    vector<string> tokens = split(asm_line, "[ \t,]+");
    string instruction = tokens.at(0);
    if (R_BIN.count(instruction)) {
        R_LineAssembler r_line_assm(asm_line, obj_file, address);
        return r_line_assm.assemble();
    } else if (I_BIN.count(instruction)) {
        I_LineAssembler i_line_assm(asm_line, obj_file, address);
        return i_line_assm.assemble();
    } else if (J_BIN.count(instruction)) {
        J_LineAssembler j_line_assm(asm_line, obj_file, address);
        return j_line_assm.assemble();
    }
    return ObjectFile();
}

int LineAssembler::getOperandInt(OperandType op_type, const string &operand) {
    switch (op_type) {
        case RD: case RS: case RT: return getRegInt(operand);
        case SA: case IMM: return stoi(operand);
        case LABEL:
            if (obj_file.symbol_table.count(operand)) {
                return obj_file.symbol_table.at(operand);
            } else {
                vector<string> tokens; string instruction;
                tokens = split(asm_line, "[ \t,]+");
                instruction = tokens.at(0);
                obj_file.relocation_info.push_back({address, instruction, operand});
                return 0;
            }
        default: return -1;
    }
}

int LineAssembler::getRegInt(const string &reg) {
    auto it = find(REG_BIN.begin(), REG_BIN.end(), reg);
    return distance(REG_BIN.begin(), it);
}
