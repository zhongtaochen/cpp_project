/**
 * @file debugger.cpp
 * @brief <code>Debugger</code> class implementation.
 */

#include "debugger.h"
#include "loader.h"

Debugger::Debugger(ExecutableFile* exe_file) {
    debug(exe_file);
}

void Debugger::debug(ExecutableFile* exe_file){
    this->exe_file = exe_file;
    Loader loader(exe_file);
    this->mem = loader.getMemorySimulator();
    this->reg = loader.getRegisterFilesSimulator();
    this->pc = MemorySimulator::__start_address;
};
int Debugger::breakpointslength(){
    return breakpoints.size();
}

uint32_t Debugger::run() {
    static bool firstrun = true;
    if (firstrun) {
        firstrun = false;
        if (breakpoints.count(pc) == 1) return pc;
    }
    while (true) {
        execute(mem->readWord(pc));
        if (breakpoints.count(pc) == 1) break;
    }
    return pc;
}

uint32_t Debugger::step() {
    return execute(mem->readWord(pc));
}

void Debugger::addBreakpoint(uint32_t address) {
    breakpoints.insert(address);
}

void Debugger::removeBreakpoint(uint32_t address) {
    auto search = breakpoints.find(address);
    if (search != breakpoints.end()) breakpoints.erase(search);
}

std::vector<TextCell> Debugger::getTextSection() {
    return exe_file->text_segment;
}

RegisterFilesSimulator* Debugger::getRegisterFilesSimulator() {
    return reg;
}
