#ifndef LOADER_H
#define LOADER_H

#include "executablefile.h"
#include "memory_simulator.h"
#include "registers_simulator.h"

class Loader {
public:

/**
 * Constructor: Loader
 * Usage: Loader loader(exe_file);
 * -------------------------------
 * @brief Initialize Loader object and generate memory and register file.
 */
    Loader(ExecutableFile exe_file);

/**
 * Method: getMemorySimulator
 * Usage: Memory_Simulator mem_sim = loader.getMemorySimulator();
 * --------------------------------------------------------------
 * @brief Return corresponding memory simulator.
 */
    Memory_Simulator getMemorySimulator() {return mem_sim;};

/**
 * Method: getRegistersSimulator
 * Usage: Registers_Simulator regs_sim = loader.getRegistersSimulator();
 * ---------------------------------------------------------------------
 * @brief Return corresponding registers simulator.
 */
    Registers_Simulator getRegistersSimulator() {return regs_sim;};

private:

    Memory_Simulator mem_sim;
    Registers_Simulator regs_sim;

};

#endif // LOADER_H
