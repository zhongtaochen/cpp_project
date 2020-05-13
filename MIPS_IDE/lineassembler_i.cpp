#include "lineassembler.h"
#include "utils.h"
#include <iostream>
using namespace std;

/* Implementation notes:
 * Here follows the format of I-TYPE instruction.
 * < I-type >
 *  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
 * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 * |    op(6bits)    |   rs(5bits)  |   rt(5bits)  |                 imm(16bits)                   |
 * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 */

ObjectFile I_LineAssembler::assemble() {
    int machine_code_int = 0;
    machine_code_int |= (op << 26);
    machine_code_int |= (rs << 21);
    machine_code_int |= (rt << 16);
    machine_code_int |= (imm & 0xFFFF); // NEGATIVE CASE
    obj_file.text_segment.at(address >> 2).machine_code = machine_code_int;
    return obj_file;
}

I_LineAssembler::I_LineAssembler(string asm_line, ObjectFile obj_file, unsigned int address) {
    this->asm_line = asm_line;
    this->obj_file = obj_file;
    this->address = address;
    //这里的address是 4 8 12 这样

    rs = 0; rt = 0; imm = 0;
    vector<string> tokens = split(asm_line, "[ \t,]+");
    string instruction = tokens.at(0);
    Format format = I_BIN.at(instruction);
    op = format.id;
    if (format.op1) handleOperand(format.op1, tokens.at(1));
    if (format.op2) handleOperand(format.op2, tokens.at(2));
    if (format.op3) handleOperand(format.op3, tokens.at(3));

    /* Special cases */
    if (instruction == "bgez")   rt = 0x1;
    if (instruction == "bgezal") rt = 0x11;
    if (instruction == "bltzal") rt = 0x10;
    if (instruction == "teqi")   rt = 0xc;
    if (instruction == "tnei")   rt = 0xe;
    if (instruction == "tgei")   rt = 0x8;
    if (instruction == "tgeiu")  rt = 0x9;
    if (instruction == "tlti")   rt = 0xa;
    if (instruction == "tltiu")  rt = 0xb;
}

void I_LineAssembler::handleOperand(OperandType op_type, const string &operand) {
    string::size_type left, right;
    switch (op_type) {
        case RS: rs = getOperandInt(op_type, operand); break;
        case RT: rt = getOperandInt(op_type, operand); break;
        case IMM: imm = getOperandInt(op_type, operand); break;
        //这里被曲改掉了-1
        case LABEL: imm = (getOperandInt(op_type, operand) - address) >> 2; break;
        case IMM_RS:
            left = operand.find("(");
            right = operand.find(")");
            //这里的if是曲加上的， 因为operand 可能是个label需要被linker处理，需读取dataseg的数据
            if(left == right){ //cannot find
                imm = 0;
                rs = 0;
                vector<string> tokens; string instruction;
                tokens = split(asm_line, "[ \t,]+");
                instruction = tokens.at(0);
                obj_file.relocation_information.push_back({address, instruction, operand});

            }else{
                imm = getOperandInt(IMM, operand.substr(0, left));
                rs = getOperandInt(RS, operand.substr(left+1, right-left-1));
            }

            break;
        default: break;
    }
}
