#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "objectfile.h"
#include <string>
#include <fstream>
//enum PseudoOperandType {IMM_Pseudo,NONE_Pseudo,LABEL, RDEST, RSRC1, RSRC2, SRC2, ADDRESS, FRSRC1, FDEST };
//struct Format_Pseudo { PseudoOperandType op1; PseudoOperandType op2; PseudoOperandType op3; };

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
    //const static std::map<std::string, Format_Pseudo> Pseudo_Bin;

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
 
    /**
 * Method: pseudoConversion
 * Usage: pseudoConversion();
 * -----------------------
 * @brief Convert pseudo instruction to real instructions.
 */

    void pseudoConversion(std::string asm_line, int i);

};


#endif // ASSEMBLER_H
