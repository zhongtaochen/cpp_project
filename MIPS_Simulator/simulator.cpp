#include "simulator.h"
#include "utils.h"
#include <iostream>
using namespace std;

Simulator::Simulator(Memory_Simulator mem_sim, Registers_Simulator regs_sim) :
    mem_sim(mem_sim), regs_sim(regs_sim){
    while (!exit_status) {
//        cout << intToHexString(pc) << endl;
//        if (pc == 0x004000a0) {
//            cout << "debug" << endl;
//        }
        string instruction = mem_sim.readWord(pc);
        execute(instruction);
        pc += 4;
    }
}

void Simulator::execute(const string &instruction) {
    string op_code = instruction.substr(0, 6);
    if (op_code == "000000") executeR(instruction);
    else if (op_code == "000010" || op_code == "000011") executeJ(instruction);
    else executeI(instruction);
}

void Simulator::executeR(const string &instruction) {
    unsigned int rs = binaryStringToInt(instruction.substr(6, 5));
    unsigned int rt = binaryStringToInt(instruction.substr(11, 5));
    unsigned int rd = binaryStringToInt(instruction.substr(16, 5));
    unsigned int sa = binaryStringToInt(instruction.substr(21, 5));
    string fn = instruction.substr(26, 6);
    if (fn == "001100") { // syscall
        int v0v = binaryStringToInt(regs_sim.readReg(2));
        if (v0v == 1) {
            cout << binaryStringToInt(regs_sim.readReg(4));
        } else if (v0v == 4) {
            unsigned int address = binaryStringToInt(regs_sim.readReg(4));
            char curr_char = binaryStringToInt(mem_sim.readByte(address));
            while (curr_char) {
                curr_char = binaryStringToInt(mem_sim.readByte(address++));
                cout << curr_char;
            }
        } else if (v0v == 5) {
            int in;
            cin >> in;
            regs_sim.writeReg(2, intToBinaryString(in));
        } else if (v0v == 8) {

        } else if (v0v == 9) {
            uint32_t a0v = binaryStringToInt(regs_sim.readReg(4));
            uint32_t spv = binaryStringToInt(regs_sim.readReg(29));
            regs_sim.writeReg(29, intToBinaryString(spv-a0v));
            regs_sim.writeReg(2, regs_sim.readReg(29));
        } else if (v0v == 10) {
            exit_status = 1;
        } else if (v0v == 11) {
            cout << (char) binaryStringToInt(regs_sim.readReg(4));
        } else if (v0v == 12) {
            char in;
            cin >> in;
            regs_sim.writeReg(2, intToBinaryString(in));
        }
    } else if (fn == "100000") { // add
        int rsv = binaryStringToInt(regs_sim.readReg(rs));
        int rtv = binaryStringToInt(regs_sim.readReg(rt));
        regs_sim.writeReg(rd, intToBinaryString(rsv+rtv));
    } else if (fn == "100010") { // sub
        int rsv = binaryStringToInt(regs_sim.readReg(rs));
        int rtv = binaryStringToInt(regs_sim.readReg(rt));
        regs_sim.writeReg(rd, intToBinaryString(rsv-rtv));
    } else if (fn == "001000") { // jr
        pc = binaryStringToInt(regs_sim.readReg(31));
        pc -= 4;
    }
}

void Simulator::executeI(const std::string &instruction) {
    unsigned int rs = binaryStringToInt(instruction.substr(6, 5));
    unsigned int rt = binaryStringToInt(instruction.substr(11, 5));
    string op = instruction.substr(0, 6);
    if (op == "001000") { // addi
        int16_t imm = binaryStringToInt(instruction.substr(16));
        int32_t extended_imm = imm;
        int rsv = binaryStringToInt(regs_sim.readReg(rs));
        regs_sim.writeReg(rt, intToBinaryString(rsv+extended_imm));
    } else if (op == "000101") { // bne
        if (regs_sim.readReg(rs) != regs_sim.readReg(rt)) {
            int16_t imm = binaryStringToInt(instruction.substr(16));
            int32_t extended_imm = imm;
            extended_imm = extended_imm << 2;
            pc = pc + extended_imm;
        }
    } else if (op == "100011") { // lw
        int16_t imm = binaryStringToInt(instruction.substr(16));
        int32_t extended_imm = imm;
        uint32_t address = binaryStringToInt(regs_sim.readReg(rs));
        address += extended_imm << 2;
        regs_sim.writeReg(rt, mem_sim.readWord(address));
    } else if (op == "101011") { // sw
        int16_t imm = binaryStringToInt(instruction.substr(16));
        int32_t extended_imm = imm;
        uint32_t address = binaryStringToInt(regs_sim.readReg(rs));
        address += extended_imm << 2;
        mem_sim.writeWord(address, regs_sim.readReg(rt));
    } else if (op == "001111") { // lui
        uint16_t imm = binaryStringToInt(instruction.substr(16));
        uint32_t imm_extended = imm;
        imm_extended = imm_extended << 16;
        regs_sim.writeReg(rt, intToBinaryString(imm_extended));
    } else if (op == "001101") { // ori
        uint16_t imm = binaryStringToInt(instruction.substr(16));
        uint32_t imm_extended = imm;
        uint32_t rsv = binaryStringToInt(regs_sim.readReg(rs));
        uint32_t rtv = rsv | imm_extended;
        regs_sim.writeReg(rt, intToBinaryString(rtv));
    } else if (op == "000100") { // beq
        if (regs_sim.readReg(rs) == regs_sim.readReg(rt)) {
            int16_t imm = binaryStringToInt(instruction.substr(16));
            int32_t extended_imm = imm;
            extended_imm = extended_imm << 2;
            pc = pc + extended_imm;
        }
    }
}

void Simulator::executeJ(const std::string &instruction) {
     string op = instruction.substr(0, 6);
     if (op == "000011") regs_sim.writeReg(31, intToBinaryString(pc+4));  // jal
     // j & jal
     pc &= 0xf0000000;
     uint32_t target = binaryStringToInt(instruction.substr(6));
     pc |= (target << 2);
     pc -= 4;
}
