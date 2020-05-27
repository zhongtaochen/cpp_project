/**
 * @file debugger_test.cpp
 * @brief Unit tests for <code>Debugger</code> class.
 */

#include "debugger.h"
#include <assert.h>
#include <iostream>

/**
 * @brief Simple unit tests for <code>Debugger</code> class.
 * @details For the convenience of testing, the <code>execute</code>
 * method in <code>Executor</code> class is adpated to only printing.
 * Notice that the <code>machine_code</code> and <code>instruction</code>
 * are also adapted for unit tests.
 */
void testDebugger(){
    /** Initialize Executable File */
    ExecutableFile exe_file;
    exe_file.text_size = 24;
    exe_file.text_segment = {
        {0x00400000, 0x00400000, "Breakpoint 0x00400000"},
        {0x00400004, 0x00400004, "Breakpoint 0x00400004"},
        {0x00400008, 0x00400008, "Breakpoint 0x00400008"},
        {0x0040000c, 0x0040000c, "Breakpoint 0x0040000c"},
        {0x00400010, 0x00400010, "Breakpoint 0x00400010"},
        {0x00400014, 0x00400014, "Breakpoint 0x00400014"}
    };
    exe_file.data_size = 8;
    exe_file.data_segment = {
        {0x00500000, 0x00001010},
        {0x00500004, 0x00001010}
    };

    /** Core Methods */
    Debugger debugger(&exe_file);
    debugger.addBreakpoint(0x00400000);
    debugger.addBreakpoint(0x00400008);
    assert(debugger.run() == 0x00400000);
    std::cout << "Expected:\n\n" << std::endl;
    assert(debugger.run() == 0x00400008);
    std::cout << "Expected:\n0x00400000\n0x00400004\n" << std::endl;
    assert(debugger.step() == 0x0040000c);
    std::cout << "Expected:\n0x00400008\n" << std::endl;
    debugger.addBreakpoint(0x00400010);
    debugger.addBreakpoint(0x00400014);
    debugger.removeBreakpoint(0x00400010);
    assert(debugger.run() == 0x00400014);
    std::cout << "Expected:\n0x0040000c\n0x00400010\n" << std::endl;

    Debugger debugger2(&exe_file);
    debugger2.addBreakpoint(0x00400008);
    assert(debugger2.run() == 0x00400008);
    std::cout << "Expected:\n0x00400000\n0x00400004\n" << std::endl;
}
