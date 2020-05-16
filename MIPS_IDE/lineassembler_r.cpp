#include "lineassembler.h"
#include "utils.h"
using namespace std;

/* Implementation notes:
 * Here follows the format of R-TYPE instruction.
 * < R-type >
 *  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10  9  8  7  6  5  4  3  2  1  0
 * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 * |    op(6bits)    |   rs(5bits)  |   rt(5bits)  |   rd(5bits)  |   sa(5bits)  |     fn(6bits)   |
 * +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
 */

ObjectFile R_LineAssembler::assemble() {
    uint32_t machine_code_int = 0;
    machine_code_int |= (rs << 21);
    machine_code_int |= (rt << 16);
    machine_code_int |= (rd << 11);
    machine_code_int |= (sa << 6);
    machine_code_int |= fn;
    obj_file.text_segment.at(address >> 2).machine_code = machine_code_int;
    return obj_file;
}

R_LineAssembler::R_LineAssembler(string asm_line, ObjectFile obj_file, unsigned int address) {
    this->asm_line = asm_line;
    this->obj_file = obj_file;
    this->address = address;

    rs = 0; rt = 0; rd = 0; sa = 0; // DEFAULT
    vector<string> tokens = split(asm_line, "[ \t,]+");
    string instruction = tokens.at(0);
    Format format = R_BIN.at(instruction);
    if (format.op1) handleOperand(format.op1, tokens.at(1));
    if (format.op2) handleOperand(format.op2, tokens.at(2));
    if (format.op3) handleOperand(format.op3, tokens.at(3));
    fn = format.id;
}

void R_LineAssembler::handleOperand(OperandType op_type, const string &operand) {
    switch (op_type) {
        case NONE: break;
        case RS: rs = getOperandInt(op_type, operand); break;
        case RD: rd = getOperandInt(op_type, operand); break;
        case RT: rt = getOperandInt(op_type, operand); break;
        case SA: sa = getOperandInt(op_type, operand); break;
        default: break;
    }
}
