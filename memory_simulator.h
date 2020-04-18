#ifndef MEMORY_SIMULATOR_H
#define MEMORY_SIMULATOR_H

#include <string>
#include <vector>

class Memory_Simulator {
public:
/**
 * Constructor: Memory_Simulator
 * Usage: Memory_Simulator mem_sim(num_of_bytes);
 * ----------------------------------------------
 * @brief Initialize a new simulated memory block of certain size.
 */

    Memory_Simulator(unsigned int num_of_bytes);

/**
 * Method: readByte
 * Usage: string data = mem_sim.readByte(address);
 * -----------------------------------------------
 * @brief Read single-byte data from given address.
 */

    std::string readByte(unsigned int address);

/**
 * Method: writeByte
 * Usage: mem_sim.writeByte(address, data);
 * ----------------------------------------
 * @brief Write single-byte data to given address.
 */

    void writeByte(unsigned int address, std::string data);

/**
 * Method: readHalfWord
 * Usage: string data = mem_sim.readHalfWord(address);
 * ---------------------------------------------------
 * @brief Read two-consecutive-byte data from given address.
 */

    std::string readHalfWord(unsigned int address);

/**
 * Method: writeHalfWord
 * Usage: mem_sim.writeByte(address, data);
 * ----------------------------------------
 * @brief Write two-consecutive-byte data to given address.
 */

    void writeHalfWord(unsigned int address, std::string data);

/**
 * Method: readWord
 * Usage: string data = mem_sim.readWord(address);
 * ------------------------------------------------
 * @brief Read four-consecutive-byte data from given address.
 */

    std::string readWord(unsigned int address);

/**
 * Method: writeWord
 * Usage: mem_sim.writeWord(address, data);
 * ----------------------------------------
 * @brief Write four-consecutive-byte data to given address.
 */

    void writeWord(unsigned int address, std::string data);

/**
 * Method: getEndAddress
 * Usage: unsigned int end_addr = getEndAddress();
 * -----------------------------------------------
 * @brief Return end address.
 */

    unsigned int getEndAddress() {return __end_addr;};

/**
 * Method: display
 * Usage: mem_sim.display();
 * -------------------------
 * @brief Display data in memory block for debug use.
 */

    void display();

    static const unsigned int __start_addr = 0x00400000;

private:

    unsigned int num_of_bytes;
    std::vector<std::string> memory_block;
    unsigned int __end_addr;

    unsigned int toIndex(unsigned int address);
};

#endif // MEMORY_SIMULATOR_H
