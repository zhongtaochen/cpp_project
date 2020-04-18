/**
 * @file objectfile.h
 * @brief <code>ObjectFile</code> class, <code>TextCell</code> struct,
 * <code>DataCell</code> struct, <code>RelocationCell</code> struct.
 * @details This file exports an <code>ObjectFile</code> class and several
 * neccessary structs. The design adapts from the descriptions in Patterson
 * and Henessy's book section 2.12.
 */

#ifndef OBJECTFILE_H
#define OBJECTFILE_H

#include <cstdint>
#include <string>
#include <vector>
#include <map>

/**
 * @brief Basic unit for text segment in both <code>ObjectFile</code> and
 * <code>ExecutableFile</code> class.
 */
struct TextCell{
    uint32_t address;
    uint32_t machine_code;
    std::string instruction;
};

/**
 * @brief Basic unit for data segment in both <code>ObjectFile</code> and
 * <code>ExecutableFile</code> class.
 */
struct DataCell{
    uint32_t address;
    uint32_t data;
};

/**
 * @brief Basic unit for relocation information both <code>ObjectFile</code>.
 */
struct RelocationCell{
    uint32_t address;
    std::string instruciton_type;
    std::string dependency;
};

/**
 * @brief Output of designed <code>Assembler</code> in this project.
 * Records neccessary information for further linking and debugging.
 */
class ObjectFile {

public:

/**
 * @brief Void initilizer for the <code>ObjectFile</code> class.
 * All attributes are public.
 */
    ObjectFile(){};

    std::string name;
    unsigned int text_size;
    unsigned int data_size;
    std::vector<TextCell> text_segment;
    std::vector<DataCell> data_segment;
    std::vector<RelocationCell> relocation_information;
    std::map<std::string, std::string> symbol_table;

};

#endif // OBJECTFILE_H
