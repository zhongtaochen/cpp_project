/**
 * @file simulator.h
 * @brief <code>Simulator</code> class, <code>MemorySimulator</code> class,
 * <code>RegisterFilesSimulator</code> class.
 * @details This file exports an <code>Simulator</code> class simulating processing MIPS
 * instructions, with <code>MemorySimulator</code> class simulating the behaviors of memory
 * block and <code>RegisterFilesSimulator</code> simulating the behaviors of register files.
 */

#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <cstdint>
#include "executor.h"




 /**
  * @brief Simulate behaviors of memory.
  * @details Encapsulate an <code>uint8_t</code> array, wherein each element
  * simulates one-byte data in the memory. Big-edian machine assumed.
  */
class MemorySimulator {

public:

	/** Start address of simulated memory.*/
	static const uint32_t __start_address = 0x00400000;

	/**
	 * @brief Initializer for <code>MemorySimulator</code> class.
	 * @param num_of_bytes Predefined size of simulated memory. 10MB as default.
	 */

	MemorySimulator(unsigned int num_of_bytes = 0x00a00000);

	/**
	 * @brief Destructor for <code>MemorySimulator</code> class. Invoked implicitly usually.
	 */

	~MemorySimulator();

	/**
	 * @brief Write single-byte data to to given address.
	 * @warning Abort if <code>address</code> is out of bound.
	 */

	void writeByte(uint32_t address, uint8_t byte_data);

	/**
	 * @brief Write two-consecutive-byte data to to given address.
	 * @warning Abort if <code>address</code> is out of bound.
	 */

	void writeHalfWord(uint32_t address, uint16_t half_word_data);

	/**
	 * @brief Write four-consecutive-byte data to to given address.
	 * @warning Abort if <code>address</code> is out of bound.
	 */

	void writeWord(uint32_t address, uint32_t word_data);

	/**
	 * @brief Read single-byte data to to given address.
	 * @warning Abort if <code>address</code> is out of bound.
	 * @warning Unsigned extension if return value is int type.
	 */

	uint8_t readByte(uint32_t address);

	/**
	 * @brief Read two-consecutive-byte data to to given address.
	 * @warning Abort if <code>address</code> is out of bound.
	 * @warning Unsigned extension if return value is int type.
	 */

	uint16_t readHalfWord(uint32_t address);

	/**
	 * @brief Read four-consecutive-byte data to to given address.
	 * @warning Abort if <code>address</code> is out of bound.
	 * @warning Unsigned extension if return value is int type.
	 */

	uint32_t readWord(uint32_t address);

	/**
	 * @brief Return the end address of the simulated memory.
	 */

	uint32_t getEndAddress();

private:

	uint8_t* mem_arr;
	uint32_t __end_address;

	/**
	 * @brief Calculate corrresponding simulated block index given <code>address</code>.
	 * @warning Abort if <code>address</code> is out of bound.
	 */

	unsigned int toIndex(uint32_t address);

};

/**
 * @brief Simulates behaviors of register files.
 * @details 32 general registers and special registers HI and LO with id 32 and 33.
 */
class RegisterFilesSimulator {

public:

	/**
	 * @brief Initializer for <code>RegisterFileSimulator</code> class.
	 * Set zero value for each register in default.
	 */

	RegisterFilesSimulator();

	/**
	 * @brief Write four-byte data to given register.
	 * @warning Abort if <code>id</code> is out of bound.
	 */

	void writeReg(unsigned int id, uint32_t data);

	/**
	 * @brief Read four-byte data to given register.
	 * @warning Abort if <code>id</code> is out of bound.
	 */

	uint32_t readReg(unsigned int id);

	/**
	 * @brief Overloads <code>[]</code> operator to access specific register file.
	 * @warning Abort if <code>id</code> is out of bound.
	 */

	uint32_t& operator[](unsigned int id);

private:
	uint32_t register_files[34];

	/**
	 * @brief Check given <code>id</code> is valid or not.
	 * @warning Abort if <code>id</code> is out of bound.
	 */

	void checkValid(unsigned int id);
};


/**
 * @brief Simulate behaviors of the processor. Subclass of <code>Executor</code>.
 */
class Simulator : Executor {

public:

	/**
	 * @brief Initializer for <code>Simulator</code> class.
	 * @param mem Memory simulator to be loaded.
	 * @param reg Register files simulator to be loaded.
	 */

	Simulator() {};
	Simulator(MemorySimulator* mem, RegisterFilesSimulator* reg);
	/**
	 * @brief Set the Simulator Object
	 * @param mem Memory simulator to be loaded.
	 * @param reg Register files simulator to be loaded.
	 */
	void simulate(MemorySimulator* mem, RegisterFilesSimulator* reg);


	/**
	 * @brief Run MIPS instructions stored in the text section until the program exits.
	 * @details Text section in the memory starts from the <code>__start_address</code>
	 * defined in <code>MemorySimulator</code> class.
	 */

	void run();
};

#endif // SIMULATOR_H
