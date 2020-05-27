#include "executor.h"
#include "simulator.h"
#include <assert.h>
#include <iostream>

void TestExecutor::testExecutor() {
    Executor executor;
    executor.mem = new MemorySimulator();
    executor.reg = new RegisterFilesSimulator();

    /** R-TYPE ADD */
    executor.pc = MemorySimulator::__start_address;
    uint32_t instruction = 0b00000010000100011001000000100000;
    executor.reg->writeReg(16, 10);
    executor.reg->writeReg(17, 20);
    executor.mem->writeWord(0x00400000, instruction);
    assert(executor.execute(instruction) == 0x00400004);
    assert(executor.reg->readReg(18) == 10+20);

    /** R-TYPE DIVU */
    executor.pc = MemorySimulator::__start_address;
    instruction = 0b00000010000100011001000000011011;
    executor.reg->writeReg(16, 10);
    executor.reg->writeReg(17, 20);
    executor.mem->writeWord(0x00400000, instruction);
    assert(executor.execute(instruction) == 0x00400004);
    assert(executor.reg->readReg(32) == 10%20);
    assert(executor.reg->readReg(33) == 10/20);

    /** R-TYPE MULTU */
    executor.pc = MemorySimulator::__start_address;
    instruction = 0b00000010000100011001000000011001;
    executor.reg->writeReg(16, 10);
    executor.reg->writeReg(17, 20);
    executor.mem->writeWord(0x00400000, instruction);
    assert(executor.execute(instruction) == 0x00400004);
    assert(executor.reg->readReg(32) == 0);
    assert(executor.reg->readReg(33) == 10*20);

    /** I-TYPE ADDI */
    executor.pc = MemorySimulator::__start_address;
    instruction = 0b00100010000100011111111111111111;
    executor.reg->writeReg(16, 10);
    executor.mem->writeWord(0x00400000, instruction);
    assert(executor.execute(instruction) == 0x00400004);
    assert(executor.reg->readReg(17) == 9);

    /** R-TYPE TEQ */
    executor.pc = MemorySimulator::__start_address;
    instruction = 0b00000010000100011001000000110100;
    executor.reg->writeReg(16, 20);
    executor.reg->writeReg(17, 20);
    executor.mem->writeWord(0x00400000, instruction);
    executor.execute(instruction);

    std::cout << "Executor tests passed." << std::endl;
}
