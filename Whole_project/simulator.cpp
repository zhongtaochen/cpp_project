/**
 * @file simulator.cpp
 * @brief <code>MemorySimulator</code> class, <code>RegisterFilesSimulator</code> class,
 * <code>Simulator</code> class implementation.
 */

#include "simulator.h"
#include <iostream>

MemorySimulator::MemorySimulator(unsigned int num_of_bytes) {
    this->mem_arr = new uint8_t[num_of_bytes];
    this->__end_address = __start_address + num_of_bytes - 1;
}

MemorySimulator::~MemorySimulator() {
    delete[] mem_arr;
}

void MemorySimulator::writeByte(uint32_t address, uint8_t byte_data) {
    mem_arr[toIndex(address)] = byte_data;
}

void MemorySimulator::writeHalfWord(uint32_t address, uint16_t half_word_data) {
    writeByte(address+1, half_word_data);
    writeByte(address, half_word_data>>8);
}

void MemorySimulator::writeWord(uint32_t address, uint32_t word_data) {
    writeHalfWord(address+2, word_data);
    writeHalfWord(address, word_data>>16);
}

uint8_t MemorySimulator::readByte(uint32_t address) {
    return mem_arr[toIndex(address)];
}

uint16_t MemorySimulator::readHalfWord(uint32_t address) {
    return (readByte(address)<<8) | readByte(address+1);
}

uint32_t MemorySimulator::readWord(uint32_t address) {
    return (readHalfWord(address)<<16) | readHalfWord(address+2);
}

uint32_t MemorySimulator::getEndAddress() {
    return __end_address;
}

unsigned int MemorySimulator::toIndex(uint32_t address) {
    if (address < __start_address || address > __end_address) {
        std::cerr << "Memory address out of bound. Abort." << std::endl;
        exit(0);
    }
    return address - __start_address;
}

RegisterFilesSimulator::RegisterFilesSimulator() {
    for (unsigned int id = 0; id < 34; id++) {
        register_files[id] = 0x00000000;
    }
}

void RegisterFilesSimulator::writeReg(unsigned int id, uint32_t data) {
    checkValid(id);
    register_files[id] = data;
}

uint32_t RegisterFilesSimulator::readReg(unsigned int id) {
    checkValid(id);
    return register_files[id];
}

uint32_t& RegisterFilesSimulator::operator[](unsigned int id) {
    checkValid(id);
    return register_files[id];
}

void RegisterFilesSimulator::checkValid(unsigned int id) {
    if (id >= 34) {
        std::cerr << "Register files id out of bound. Abort." << std::endl;
        exit(0);
    }
}

Simulator::Simulator(MemorySimulator* mem, RegisterFilesSimulator* reg) {
    simulate(mem,reg);
};
void Simulator::simulate(MemorySimulator *mem, RegisterFilesSimulator *reg){
    this->mem = mem;
    this->reg = reg;
    this->pc = MemorySimulator::__start_address;
}

void Simulator::run() {
    while (true) {
        execute(mem->readWord(pc));
    }
};
