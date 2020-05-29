/**
 * @file simulator_test.cpp
 * @brief Unit tests for <code>MemorySimulator</code> class, <code>RegisterFilesSimulator</code> class,
 * and <code>Simulator</code> class.
 */

#include "simulator.h"
#include <assert.h>

/**
* @brief Simple unit tests for <code>MemorySimulator</code> class.
* @details Cover all core methods and special handling for out-of-bound situation.
* Implementation passed all unit tests.
*/
void testMemorySimulator() {
	MemorySimulator mem(8);

	/** Core Methods */
	mem.writeByte(0x00400000, 0b10101010);
	mem.writeByte(0x00400001, 0b01010101);
	mem.writeHalfWord(0x00400002, 0b1000000110000001);
	mem.writeWord(0x00400004, 0b00000001100000011000000110000000);

	assert(mem.readByte(0x00400002) == 0b10000001);
	assert(mem.readHalfWord(0x00400001) == 0b0101010110000001);
	assert(mem.readWord(0x00400000) == 0b10101010010101011000000110000001);
	assert(mem.readWord(0x00400004) == 0b00000001100000011000000110000000);
	assert(mem.getEndAddress() == 0x00400007);

	/** Out-of-bound Situation */
//    mem.writeByte(0x00400008, 0b10101010);
//    uint8_t data = mem.readByte(0x00400008);
}

/**
 * @brief Simple unit tests for <code>RegisterFilesSimulator</code> class.
 * @details Cover setup, all core methods and special handling for out-of-bound situation.
 * Implementation passed all unit tests.
 */
void testRegisterFilesSimulator() {
	RegisterFilesSimulator reg;

	/** Check Zeros Setup */
	assert(reg[0] == 0x00000000);

	/** Core Methods */
	reg.writeReg(1, 0x31415926);
	assert(reg.readReg(1) == 0x31415926);
	reg[1] = 0x27182818;
	assert(reg[1] == 0x27182818);
	assert(reg.readReg(1) == 0x27182818);

	/** Out-of-bound Situation */
//    reg[34] = 0x00000000;
}

/**
 * @brief Simple unit tests for <code>Simulator</code> class.
 * @details Cover core methods. Implementation passed the tests.
 */
void testSimulator() {
	MemorySimulator mem(8);
	RegisterFilesSimulator reg;
	Simulator sim(&mem, &reg);
	sim.run();
}
