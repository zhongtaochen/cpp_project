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
 * @brief Constructor for <code>Loader</code> class.
 * @param exe_file program to be loaded.
 */

    Loader(ExecutableFile* exe_file);

/**
 * @brief Returns loaded memory simulator.
 */

    MemorySimulator* getMemorySimulator();

/**
 * @brief Returns initilized register files simulator.
 */

    RegisterFilesSimulator* getRegisterFilesSimulator();

private:
    MemorySimulator* mem;
    RegisterFilesSimulator* reg;
};

#endif // LOADER_H
