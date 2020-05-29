/**
 * @file assembler.h
 * @brief <code>Assembler</code> class.
 * @details This file exports <code>Assembler</code> class, which processes assembly
 * code and outputs an <code>ObjectFile</code>.
 */

#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "objectfile.h"
#include <string>
#include <fstream>

/**
 * @brief Assembles assembly code and outputs an <code>ObjectFile</code>.
 */
class Assembler {

public:

/**
 * @brief Intializer for <code>Assembler</code> class.
 */

    Assembler(){};
    Assembler(std::ifstream &asm_file);
    Assembler(const std::string &asm_code);

/**
 * @brief Assemble assembly code.
 */

     void assemble(std::ifstream &asm_file);
     void assemble(const std::string &asm_code);

/**
 * @brief Return assembled object file.
 */

    ObjectFile getObjFile() {return obj_file;};

private:

    ObjectFile obj_file;
    std::vector<std::string> asm_lines;
    

/**
 * @brief Fill data section and part of symbol table in object file.
 */

    void handleDataSection(const std::string &asm_data_sec);

/**
 * @brief Fill text section, part of relocation information, and
 * part of relocation information in object file.
 */

    void handleTextSection(const std::string &asm_text_sec);

/**
 * @brief Construct vector <code>asm_lines</code> where each entry
 * represents exactly one line of assembly code and each
 * entry is comment-free and nonempty.
 */

    void preprocess(const std::string &asm_code);

/**
 * @brief Fill symbol table with relative address for labels in
 * text section.
 */

    void scanLabels();
 
/**
 * @brief Convert pseudo instructions to real instructions.
 * @param i relative instruction index in <code>asm_lines</code>
 */

    void pseudoConversion(std::string asm_line, int i);

};


#endif // ASSEMBLER_H
