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
* Method: resolveLab
* Usage: resolveLable(obj_file);
* -----------------------
* @brief Resolve local PC-relative labels.\n
* and resolveLables will call function resolveAddresAsm and removeFromReloInfo
*/
    void resolveLables(ObjectFile &obj_file);


/**
* Method: resolveAddressAsm
* Usage: resolveAddressAsm(Taddress, PC_address, text_seg );
* -----------------------
* @brief Resolve local PC-relative address that should be resolved in assembler.\n
* Taddress represents the destination address.
*/
    void resolveAddressAsm(const std::string Taddress, const std::string PC_address, ObjectFile::segment_cell &text_seg );



/**
* Method: removeFromReloInfo
* Usage: removeFromReloInfo(obj_file);
* -----------------------
* @brief Remove the redundent reloca info 这里要remove 是因为 有些信息不该被linker处理，但是放在了reloca info 里.\n
*/
     void removeFromReloInfo(ObjectFile &obj_file);


};

#endif // ASSEMBLER_H
