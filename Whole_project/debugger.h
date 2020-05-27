/**
 * @file debugger.h
 * @brief <code>Debugger</code> class.
 * @details This file exports <code>Debugger</code> class, which provides interactive
 * excution toolkits for the clients and serves as the back-end of the GUI.
 */

#ifndef DEBUGGER_H
#define DEBUGGER_H

#include "executor.h"
#include "executablefile.h"
#include <cstdint>
#include <vector>
#include <set>

/**
 * @brief Provides interactive toolkits for clients, including <code>run</code> until
 * the program encounters a breakpoint, and <code>step</code> executes the next exact
 * instruction only. Subclass of <code>Executor</code>.
 */
class Debugger : Executor {

public:

/**
 * @brief Initializer for <code>Debugger</code> class.
 * @param exe_file program to be debugged.
 */
    Debugger(){};
    Debugger(ExecutableFile* exe_file);
/**
 * @brief Set the Debugger object
 * @param exe_file program to be debugged.
 */
    void debug(ExecutableFile* exe_file);
/**
 * @brief Check the number of breakpoints;
 */
    int breakpointslength();

/**
 * @brief Runs MIPS instructions stored in the text section until the program
 * encounters a breakpoint.
 * @return Address of the encoutered breakpoint, and also the address of the
 * instruction to be excuted next.
 */

    uint32_t run();

/**
 * @brief Execute only the next instruction.
 * @return Address of the instruction to be executed next.
 */

    uint32_t step();

/**
 * @brief Add the breakpoint specified by the address in the text section.
 */

    void addBreakpoint(uint32_t address);

/**
 * @brief Remove the breakpoint specified by the address in the text section.
 */

    void removeBreakpoint(uint32_t address);

/**
 * @brief Return text section information in the executable file.
 */

    std::vector<TextCell> getTextSection();

/**
 * @brief Return register files simulator.
 */

    RegisterFilesSimulator* getRegisterFilesSimulator();

private:
    ExecutableFile* exe_file;
    std::set<uint32_t> breakpoints;
};

#endif // DEBUGGER_H
