#include "registers_simulator.h"
#include "utils.h"
using namespace std;

Registers_Simulator::Registers_Simulator() {
    for (unsigned int reg = 0; reg < 32; reg++) {
        this->regs.insert({REG(reg), "00000000000000000000000000000000"});
    }
}

string Registers_Simulator::readReg(unsigned int number) {
    return regs.at(REG(number));
}

void Registers_Simulator::writeReg(unsigned int number, string data) {
    if (!isBinaryString(data, 32)) error("Invalid fout-byte data.");
    regs.at(REG(number)) = data;
}
