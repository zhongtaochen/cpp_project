/**
 * @file excutor.cpp
 * @brief <code>Executor</code> class implementation.
 */

#include "executor.h"
#include "simulator.h"
#include <iostream>
#include <iomanip>
#include "fstream"

void trap(uint32_t pc, std::string msg);

uint32_t Executor::execute(uint32_t instruction) {
//    std::cout << std::hex << instruction << std::endl;
    pc += 4;

    uint32_t opcode = instruction >> 26;
    uint32_t rs = (instruction >> 21) & 0x1f;
    uint32_t rt = (instruction >> 16) & 0x1f;
    uint32_t rd = (instruction >> 11) & 0x1f;
    uint32_t sa = (instruction >> 6) & 0x1f;
    uint32_t fn = instruction & 0x3f;

    uint16_t imm = instruction;
    uint32_t imm_zero = imm; // zero-extension
    int32_t imm_sign = (int16_t) imm; // sign-extension
    uint32_t branch = pc + (imm_sign << 2);
    uint32_t offset = (*reg)[rs] + imm_sign;

    uint32_t target = (pc & 0xf0000000) | ((instruction & 0x3ffffff) << 2);

    if (opcode == 0b000000) { // R-Type

        if (fn == 0b100000) { // add
            (*reg)[rd] = (*reg)[rs] + (*reg)[rt];
        } else if (fn == 0b100001) { // addu
            (*reg)[rd] = (*reg)[rs] + (*reg)[rt];
        } else if (fn == 0b100100) { // and
            (*reg)[rd] = (*reg)[rs] & (*reg)[rt];
        } else if (fn == 0b011010) { // div
            (*reg)[32] = ((int32_t)(*reg)[rs]) % ((int32_t)(*reg)[rt]); // HI
            (*reg)[33] = ((int32_t)(*reg)[rs]) / ((int32_t)(*reg)[rt]); // LO
        } else if (fn == 0b011011) { // divu
            (*reg)[32] = ((uint32_t)(*reg)[rs]) % ((uint32_t)(*reg)[rt]); // HI
            (*reg)[33] = ((uint32_t)(*reg)[rs]) / ((uint32_t)(*reg)[rt]); // LO
        } else if (fn == 0b001001) { // jalr
            (*reg)[rd] = pc;
            pc = (*reg)[rs];
        } else if (fn == 0b001000) { // jr
            pc = (*reg)[rs];
        } else if (fn == 0b010000) { // mfhi
            (*reg)[rd] = (*reg)[32];
        } else if (fn == 0b010010) { // mflo
            (*reg)[rd] = (*reg)[33];
        } else if (fn == 0b011000) { // mult
            int64_t product = ((int32_t)(*reg)[rs]) * ((int32_t)(*reg)[rt]);
            (*reg)[32] = product >> 32; // HI
            (*reg)[33] = product; // LO
        } else if (fn == 0b011001) { // multu
            uint64_t product = ((uint32_t)(*reg)[rs]) * ((uint32_t)(*reg)[rt]);
            (*reg)[32] = product >> 32; // HI
            (*reg)[33] = product; // LO
        } else if (fn == 0b010001) { // mthi
            (*reg)[32] = (*reg)[rs];
        } else if (fn == 0b010011) { // mtlo
            (*reg)[33] = (*reg)[rs];
        } else if (fn == 0b100111) { // nor
            (*reg)[rd] = ~((*reg)[rs] | (*reg)[rt]);
        } else if (fn == 0b100101) { // or
            (*reg)[rd] = (*reg)[rs] | (*reg)[rt];
        } else if (fn == 0b000000) { // sll
            (*reg)[rd] = (*reg)[rt] << sa;
        } else if (fn == 0b000100) { // sllv
            (*reg)[rd] = (*reg)[rt] << (*reg)[rs];
        } else if (fn == 0b101010) { // slt
            (*reg)[rd] = ((int32_t)(*reg)[rs] < (int32_t)(*reg)[rt]) ? 1 : 0;
        } else if (fn == 0b101011) { // sltu
            (*reg)[rd] = ((uint32_t)(*reg)[rs] < (uint32_t)(*reg)[rt]) ? 1 : 0;
        } else if (fn == 0b000011) { // sra
            (*reg)[rd] = (int32_t)(*reg)[rt] >> sa;
        } else if (fn == 0b000111) { // srav
            (*reg)[rd] = (int32_t)(*reg)[rt] >> (*reg)[rs];
        } else if (fn == 0b000010) { // srl
            (*reg)[rd] = (uint32_t)(*reg)[rt] >> sa;
        } else if (fn == 0b000110) { // srlv
            (*reg)[rd] = (uint32_t)(*reg)[rt] >> (*reg)[rs];
        } else if (fn == 0b100010) { // sub
            (*reg)[rd] = (*reg)[rs] - (*reg)[rt];
        } else if (fn == 0b100011) { // subu
            (*reg)[rd] = (*reg)[rs] - (*reg)[rt];
        } else if (fn == 0b001100) { // syscall
            syscall();
        } else if (fn == 0b110100) { // teq
            if ((*reg)[rs] == (*reg)[rt]) trap(pc-4, "Trap if equal.");
        } else if (fn == 0b110110) { // tne
            if ((*reg)[rs] != (*reg)[rt]) trap(pc-4, "Trap if not equal.");
        } else if (fn == 0b110000) { // tge
            if ((int32_t)(*reg)[rs] >= (int32_t)(*reg)[rt]) trap(pc-4, "Trap if greater equal.");
        } else if (fn == 0b110001) { // tgeu
            if ((uint32_t)(*reg)[rs] >= (uint32_t)(*reg)[rt])
                trap(pc-4, "Unsigned trap if greater equal.");
        } else if (fn == 0b110010) { // tlt
            if ((int32_t)(*reg)[rs] < (int32_t)(*reg)[rt]) trap(pc-4, "Trap if less.");
        } else if (fn == 0b110011) { // tltu
            if ((uint32_t)(*reg)[rs] < (uint32_t)(*reg)[rt])
                trap(pc-4, "Unsigned trap if less.");
        } else if (fn == 0b100110) { // xor
            (*reg)[rd] = (*reg)[rs] ^ (*reg)[rt];
        }
    } else if (opcode == 0b001000) { // addi
        (*reg)[rt] = (*reg)[rs] + imm_sign;
    } else if (opcode == 0b001001) { // addiu
        (*reg)[rt] = (*reg)[rs] + imm_sign;
    } else if (opcode == 0b001100) { // andi
        (*reg)[rt] = (*reg)[rs] & imm_zero;
    } else if (opcode == 0b000100) { // beq
        if ((*reg)[rs] == (*reg)[rt]) pc = branch;
    } else if (opcode == 0b000001 && rt == 0b00001) { // bgez
        if ((int32_t)(*reg)[rs] >= 0) pc = branch;
    } else if (opcode == 0b000001 && rt == 0b10001) { // bgezal
        if ((int32_t)(*reg)[rs] >= 0) {
            (*reg)[31] = pc; // $ra register
            pc = branch;
        }
    } else if (opcode == 0b000111 && rt == 0b00000) { // bgtz
        if ((int32_t)(*reg)[rs] > 0) pc = branch;
    } else if (opcode == 0b000110 && rt == 0b00000) { // blez
        if ((int32_t)(*reg)[rs] <= 0) pc = branch;
    } else if (opcode == 0b000001 && rt == 0b10000) { // bltzal
        if ((int32_t)(*reg)[rs] < 0) {
            (*reg)[31] = pc; // $ra register
            pc = branch;
        }
    } else if (opcode == 0b000001 && rt == 0b00000) { // bltz
        if ((int32_t)(*reg)[rs] < 0) pc = branch;
    } else if (opcode == 0b000101) { // bne
        if ((*reg)[rs] != (*reg)[rt]) pc = branch;
    } else if (opcode == 0b100000) { // lb
        (*reg)[rt] = (int8_t) mem->readByte(offset);
    } else if (opcode == 0b100100) { // lbu
        (*reg)[rt] = (uint8_t) mem->readByte(offset);
    } else if (opcode == 0b100001) { // lh
        (*reg)[rt] = (int16_t) mem->readHalfWord(offset);
    } else if (opcode == 0b100101) { // lhu
        (*reg)[rt] = (uint16_t) mem->readHalfWord(offset);
    } else if (opcode == 0b001111) { // lui
        (*reg)[rt] = imm_zero << 16;
    } else if (opcode == 0b100011) { // lw
        (*reg)[rt] = mem->readWord(offset);
    } else if (opcode == 0b000010) { // j
        pc = target;
    } else if (opcode == 0b000011) { // jal
        (*reg)[31] = pc; // $ra register
        pc = target;
    } else if (opcode == 0b001101) { // ori
        (*reg)[rt] = (*reg)[rs] | imm_zero;
    } else if (opcode == 0b101000) { // sb
        mem->writeByte(offset, (*reg)[rt]);
    } else if (opcode == 0b101001) { // sh
        mem->writeHalfWord(offset, (*reg)[rt]);
    } else if (opcode == 0b001010) { // slti
        (*reg)[rt] = ((int32_t)(*reg)[rs] < (int32_t)(imm_sign)) ? 1 : 0;
    } else if (opcode == 0b001011) { // sltiu
        (*reg)[rt] = ((uint32_t)(*reg)[rs] < (uint32_t)(imm_sign)) ? 1 : 0;
    } else if (opcode == 0b101011) { // sw
        mem->writeWord(offset, (*reg)[rt]);
    } else if (opcode == 0b000001 && rt == 0b01100) { // teqi
        if ((int32_t)(*reg)[rs] == imm_sign) trap(pc-4, "Trap if equal immediate.");
    } else if (opcode == 0b000001 && rt == 0b01110) { // tnei
        if ((int32_t)(*reg)[rs] != imm_sign) trap(pc-4, "Trap if not equal immediate.");
    } else if (opcode == 0b000001 && rt == 0b01000) { // tgei
        if ((int32_t)(*reg)[rs] >= imm_sign) trap(pc-4, "Trap if greater equal immediate.");
    } else if (opcode == 0b000001 && rt == 0b01001) { // tgeiu
        if ((uint32_t)(*reg)[rs] >= ((uint32_t)imm_sign))
            trap(pc-4, "Unsigned trap if greater equal immediate.");
    } else if (opcode == 0b000001 && rt == 0b01010) { // tlti
        if ((int32_t)(*reg)[rs] < imm_sign) trap(pc-4, "Trap if less immediate.");
    } else if (opcode == 0b000001 && rt == 0b01011) { // tltiu
        if ((uint32_t)(*reg)[rs] < ((uint32_t)imm_sign))
            trap(pc-4, "Unsigned trap if less immediate.");
    } else if (opcode == 0b001110) { // xori
        (*reg)[rt] = (*reg)[rs] ^ imm_zero;
    }

    return pc;
};

void Executor::syscall() {
    if ((*reg)[2] == 1) { // print_int
        std::cout << (int)(*reg)[4] << std::endl;
    } else if ((*reg)[2] == 4) { // print_string
        uint32_t address = (*reg)[4];
        char curr_char = mem->readByte(address);
        while (curr_char) {
            std::cout << curr_char;
            curr_char = mem->readByte(++address);
        }
        std::cout << std::endl;
    } else if ((*reg)[2] == 5) { // read_int
        int32_t in;
        std::cin >> in;
        reg->writeReg(2, in);
    } else if ((*reg)[2] == 8) { // read_string
        uint32_t address = (*reg)[4];
        uint32_t length = (*reg)[5];
        char curr_char;
        for (uint32_t i = 0; i < length; i++) {
            std::cin >> curr_char;
            mem->writeByte(address+i, curr_char);
        }
    } else if ((*reg)[2] == 9) { // sbrk
        uint32_t amount = (*reg)[4];
        (*reg)[29] = (*reg)[29] - amount;
        (*reg)[2] = (*reg)[29];
    } else if ((*reg)[2] == 10) { // exit
        exit(0);
    } else if ((*reg)[2] == 11) { // print_char
        std::cout << (char) (*reg)[4] << std::endl;
    } else if ((*reg)[2] == 12) { // read_char
        char in;
        std::cin >> in;
        reg->writeReg(2, in);
    } else if ((*reg)[2] == 13) { // open
        uint32_t address = (*reg)[4];
        char curr_char = mem->readByte(address);
        std::string file_name = "";
        while (curr_char) {
            file_name += curr_char;
            curr_char = mem->readByte(++address);
        }
        files_record.push_back(file_name);
        (*reg)[4] = files_record.size()-1;
    } else if ((*reg)[2] == 14) { // read
        std::string file_name = files_record.at((*reg)[4]);
        uint32_t address = (*reg)[5];
        uint32_t length = (*reg)[6];
        std::ifstream infile;
        infile.open(file_name);
        char curr_char;
        uint32_t num_chars_read = 0;
        for (;num_chars_read < length; num_chars_read++) {
             infile.read(&curr_char, 1);
             mem->writeByte(address+num_chars_read, curr_char);
        }
        (*reg)[4] = num_chars_read;
    } else if ((*reg)[2] == 15) { // write
        std::string file_name = files_record.at((*reg)[4]);
        uint32_t address = (*reg)[5];
        uint32_t length = (*reg)[6];
        std::ofstream outfile;
        outfile.open(file_name);
        char curr_char;
        uint32_t num_chars_written = 0;
        for (;num_chars_written < length; num_chars_written++) {
            curr_char = mem->readByte(address+num_chars_written);
            outfile << (char) curr_char;
        }
        (*reg)[4] = num_chars_written;
    } else if ((*reg)[2] == 16) { // close
        // do nothing
    } else if ((*reg)[2] == 17) {
        exit(0); // return $a0 is ommitted
    }
}

/**
 * @brief Trap exception. Print address of the exception and detailed information.
 * Furthermore, the program will be aborted.
 */
void trap(uint32_t pc, std::string msg) {
    std::cout << "Address: 0x" << std::setw(8) << std::setfill('0')
              << std::hex << pc << std::endl;
    std::cout << msg << std::endl;
    exit(1);
}
