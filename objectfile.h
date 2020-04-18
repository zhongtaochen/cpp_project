#ifndef OBJECTFILE_H
#define OBJECTFILE_H

#include <fstream>
#include <string>
#include <vector>
#include <map>

class ObjectFile {

public:

/**
 * Constructor: ObjectFile
 * Usage: ObjectFile obj_file;
 * ---------------------------
 * @brief Void initializer for class ObjectFile.
 */
    ObjectFile() {};

    std::string name;
    unsigned int text_size = 0;
    unsigned int data_size = 0;

    struct segment_cell {unsigned int address; std::string data;};
    std::vector<segment_cell> text_segment;
    std::vector<segment_cell> data_segment;

    struct relocation_cell {unsigned int address; std::string instuction; std::string dependency;};
    std::vector<relocation_cell> relocation_info;

    std::map<std::string, unsigned int> symbol_table;

};

#endif // OBJECTFILE_H

