#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "objectfile.h"
#include <string>
#include <fstream>

class Assembler {

public:

/**
 * @brief Create an <code>Assembler</code> object.
 */

    Assembler(const std::ifstream &asm_file);
    Assembler(const std::string &asm_code);

/**
 * @brief Output binary machine code in text file format.
 */

    void output(const std::string &file_path);

/**
 * @brief Return corresponding object file.
 */

    ObjectFile getObjFile() {return obj_file;};

private:

    ObjectFile obj_file;
    std::vector<std::string> asm_lines;

/**
 * @brief Fill data section in object file.
 */

    void handleDataSection(const std::string &asm_data_sec);

/**
 * @brief Complete object file.
 */

    void handleTextSection(const std::string &asm_text_sec);

/**
 * @brief Construct vector <code>asm_lines</code> where each entry
 * represents exactly one line of assembly code and each
 * entry is comment-free and nonempty.
 */

    void preprocess(const std::string &asm_code);

/**
 * @brief Fill symbol table with relative address
 * if the label exists in the text section.
 */

    void scanLabels();

};

#endif // ASSEMBLER_H
