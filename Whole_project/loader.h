/**
 * @file loader.h
 * @brief <code>Loader</code> class.
 * @details This file exports <code>Loader</code> class.
 */

#ifndef LOADER_H
#define LOADER_H

#include "executablefile.h"
#include "simulator.h"

/**
 * @brief Abstract the behaviors of loading the program and variables into
 * the simulated memory, and initilizing the register files.
 */
class Loader {

public:

/**
 * @brief Initializer for <code>Loader</code> class.
 */

    Loader(){};
    Loader(ExecutableFile* exe_file);

/**
 * @brief Load exe_file program
 * @param exe_file program to be loaded.
 */

    void load(ExecutableFile* exe_file);

/**
 * @brief Return loaded memory simulator.
 */

    MemorySimulator* getMemorySimulator();

/**
 * @brief Return initilized register files simulator.
 */

    RegisterFilesSimulator* getRegisterFilesSimulator();

private:
    MemorySimulator* mem;
    RegisterFilesSimulator* reg;
};

#endif // LOADER_H
