#include "memory_simulator.h"
#include "utils.h"
#include <iostream>
using namespace std;

Memory_Simulator::Memory_Simulator(unsigned int num_of_bytes) : memory_block(num_of_bytes, "00000000") {
    this->num_of_bytes = num_of_bytes;
    this->__end_addr = __start_addr + num_of_bytes - 1;
}

string Memory_Simulator::readByte(unsigned int address) {
    return memory_block.at(toIndex(address));
}

void Memory_Simulator::writeByte(unsigned int address, string data) {
    if (!isBinaryString(data, 8)) error("Invalid sigle-byte data.");
    memory_block.at(toIndex(address)) = data;
}

string Memory_Simulator::readHalfWord(unsigned int address) {
    return readByte(address) + readByte(address + 1);
}

void Memory_Simulator::writeHalfWord(unsigned int address, string data) {
    if (!isBinaryString(data, 16)) error("Invalid two-byte data.");
    writeByte(address, data.substr(0, 8));
    writeByte(address+1, data.substr(8, 8));
}

string Memory_Simulator::readWord(unsigned int address) {
    return readHalfWord(address) + readHalfWord(address + 2);
}

void Memory_Simulator::writeWord(unsigned int address, string data) {
    if (!isBinaryString(data, 32)) error("Invalid four-byte data.");
    writeHalfWord(address, data.substr(0, 16));
    writeHalfWord(address+2, data.substr(16, 16));
}

void Memory_Simulator::display() {
    for (unsigned address = __start_addr; address <= __end_addr; address++) {
        if (address % 4 == 0) cout << endl << intToHexString(address);
        cout << " " << readByte(address);
    }
    cout << endl;
}

unsigned int Memory_Simulator::toIndex(unsigned int address) {
    if ((address < __start_addr) || (address > __end_addr))
        error("Memory address out of bounds.");
    return address - __start_addr;
}
