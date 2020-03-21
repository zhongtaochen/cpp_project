#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "memory_simulator.h"
#include "registers_simulator.h"

class Simulator {
public:

/**
 * Constructor: Simulator
 * Usage: Simulator sim(mem_sim, regs_sim);
 * --------------------------------------------------
 * @brief Initialize Simulator object.
 */
    Simulator(Memory_Simulator mem_sim, Registers_Simulator regs_sim);

    Memory_Simulator getMemorySimulator() {return mem_sim;};
    Registers_Simulator getRegistersSimulator() {return regs_sim;};

private:

    unsigned int pc = Memory_Simulator::__start_addr;
    Memory_Simulator mem_sim;
    Registers_Simulator regs_sim;
    int exit_status = 0;

/**
 * Method: execute
 * Usage: execute(instruction);
 * ----------------------------
 * @brief Execute binary code instruction.
 */
    void execute(const std::string &instruction);

/**
 * Method: executeR
 * Usage: executeR(instruction);
 * -----------------------------
 * @brief Execute R-type binary code instruction.
 */
    void executeR(const std::string &instruction);

/**
 * Method: executeI
 * Usage: executeI(instruction);
 * -----------------------------
 * @brief Execute I-type binary code instruction.
 */
    void executeI(const std::string &instruction);

/**
 * Method: executeJ
 * Usage: executeJ(instruction);
 * -----------------------------
 * @brief Execute J-type binary code instruction.
 */
    void executeJ(const std::string &instruction);
};

#endif // SIMULATOR_H
