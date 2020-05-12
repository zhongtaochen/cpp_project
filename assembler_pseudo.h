#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "objectfile.h"
#include <string>
#include <fstream>

class Assembler {

public:

/**
 * Constructor: Assembler
 * Usage: Assembler assm(asm_file);
 *        Assembler assm(asm_code);
 * --------------------------------
 * @brief Create an Assembler object.
 */
    Assembler(std::ifstream &asm_file);
    Assembler(const std::string &asm_code);

/**
 * Method: output
 * Usage: assm.output(file_path);
 * ------------------------------
 * @brief Output binary machine code in text file format.
 */
    void output(const std::string &file_path);

/**
 * Method: getObjFile
 * Usage: ObjectFile obj_file = assm.getObjFile();
 * -----------------------------------------------
 * @brief Return corresponding object file.
 */
    ObjectFile getObjFile() {return obj_file;};

private:

    ObjectFile obj_file;
    std::vector<std::string> asm_lines;

/**
 * Method: handleDataSection
 * Usage: handleDataSection(asm_data_sec);
 * ---------------------------------------
 * @brief Fill data section in object file.
 */
    void handleDataSection(const std::string &asm_data_sec);

/**
 * Method: handleTextSection
 * Usage: handleTextSection(asm_text_sec);
 * ---------------------------------------
 * @brief Complete object file.
 */
    void handleTextSection(const std::string &asm_text_sec);

/**
 * Method: preprocess
 * Usage: preprocess(asm_code);
 * ----------------------------
 * @brief Construct vector `asm_lines` where each entry\n
 * represents exactly one line of assembly code and each\n
 * entry is comment-free and nonempty.
 */
    void preprocess(const std::string &asm_code);

/**
 * Method: scanLabels
 * Usage: scanLabels();
 * --------------------
 * @brief Fill in symbol table with relative address\n
 * if the label exists in context; 0 otherwise.
 */
    void scanLabels();

/**
 * Method: assembleLines
 * Usage: assembleLines();
 * -----------------------
 * @brief Fill in text segment with relative address and\n
 * instruction pairs. Fill in relocation information.
 */
    void assembleLines();

/**
 * Method: pseudoConversion
 * Usage: pseudoConversion();
 * -----------------------
 * @brief Convert pseudo instructions by real instructions.
 */

    void pseudoConversion();
};

#endif // ASSEMBLER_H
