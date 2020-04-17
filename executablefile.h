#ifndef EXECUTABLEFILE_H
#define EXECUTABLEFILE_H

#include <string>
#include <vector>

class ExecutableFile {
public:

    static const unsigned int __text_addr = 0x00400000;
    static const unsigned int __data_addr = 0x00500000;

/**
 * Constructor: ExecutableFile
 * Usage: ExecutableFile exe_file;
 * -------------------------------
 * @brief Void initializer for class ExecutableFile.
 */
    ExecutableFile() {};

    unsigned int text_size = 0;
    unsigned int data_size = 0;

    struct segment_cell {unsigned int address; std::string data;};
    std::vector<segment_cell> text_segment;
    std::vector<segment_cell> data_segment;

};

#endif // EXECUTABLEFILE_H
