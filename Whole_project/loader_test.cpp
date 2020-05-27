/**
 * @file loader_test.cpp
 * @brief Unit tests for <code>Loader</code> class.
 */

#include "loader.h"
#include <assert.h>

/**
 * @brief Simple unit tests for <code>Loader</code> class.
 * @details Cover all core methods. Implementation passed all unit tests.
 */
void testLoader(){
    /** Initialize Executable File */
    ExecutableFile exe_file;
    exe_file.text_size = 8;
    exe_file.text_segment = {
        {0x00400000, 0x00000000, "nop"},
        {0x00400004, 0x00000000, "nop"}
    };
    exe_file.data_size = 8;
    exe_file.data_segment = {
        {0x00500000, 0x00001010},
        {0x00500004, 0x00001010}
    };

    /** Core Methods */
    Loader loader(&exe_file);
    MemorySimulator* mem = loader.getMemorySimulator();
    RegisterFilesSimulator* reg = loader.getRegisterFilesSimulator();
    assert(mem->readWord(0x00400000) == 0x00000000);
    assert(mem->readByte(0x00500003) == 0x10);
    assert((*reg)[28] == 0x00500000);
    assert(reg->readReg(29) == mem->getEndAddress());
}
