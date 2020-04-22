/**
 * @file executor.h
 * @brief <code>Executor</code> class.
 * @details This file exports <code>Executor</code> class, which acts as
 * an interface for <code>Simulator</code> class and <code>Debugger</code> class.
 */

#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <cstdint>

class MemorySimulator;
class RegisterFilesSimulator;
class TestExecutor;

/**
 * @brief Abstract the behavior of executing of MIPS instructions.
 * @details <code>Simulator</code> class and <code>Debugger</code> class
 * inheritates <code>Executor</code> interface.
 */
class Executor {

public:

    friend TestExecutor;

/**
 * @brief Excutes MIPS instruction.
 * @return address of the instruction to be excuted next.
 */

    uint32_t execute(uint32_t instruction);

protected:
/**
 * @brief Protected void constructor for <code>Executor</code> class.
 * @details Prohibit initialization by clients.
 */
    Executor(){};

    MemorySimulator* mem;
    RegisterFilesSimulator* reg;
    uint32_t pc;
};


/**
 * @brief Encapsulates unit tests for <code>Executor</code> class.
 * Friend class of <code>Executor</code> class.
 */
class TestExecutor {

public:

/**
 * @brief Void constructor for <code>TestExecutor</code> class.
 */

    TestExecutor(){};

/**
 * @brief Unit tests for <code>Executor</code> class.
 */

    void testExecutor();
};

#endif // EXECUTOR_H
