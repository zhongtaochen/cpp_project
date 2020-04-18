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
 *  //handleglobal 应该是不支持的
 * ---------------------------------------
 * @brief Fill data section in object file.
 */
    void handleDataSection(const std::string &asm_data_sec);
// 需要call split 成token  token 第一位是 var_name, 第二位是 type 第三位是 var_value
// 根据token第二位 分别call handleWord handleByte handleSpace handleASCII
//  handlehalfword handlekdata handlektext handlealign
// 把 var_name 和 addrss of this variable 存储在symbol table里
// 这个function 之后应按需要 改动 ，现在只是曲这样想的
// 但这样子写 其实没有做到 词法分析？？ 和 czt之前写的没有什么区别


/**
* Method: handle_word()
* Usage: handle_word(line);
* ---------------------------------------
* @brief Handle ".word" and write word in dataseg of objFile.
* Note that when you save word, the starting address should be divisible by 4.
* 看这个Note and refer to https://stackoverflow.com/questions/19608845/understanding-assembly-mips-align-and-memory-addressing
*/
    void handle_word(std::string line);

/**
* Method: handle_byte()
* Usage: handle_byte(line);
* --------------------------------------
* @brief Handle ".byte" and write byte in dataseg of objFile.
*/
    void handle_byte(std::string line);
/**
* Method: handle_halfword()
* Usage: handle_halfword(line);
* --------------------------------------
* @brief Handle ".half" and write halfword in dataseg of objFile.
*/

    void handle_halfword(std::string line);

/**
* Method: handle_space()
* Usage: handle_space(line);
* --------------------------------------
* @brief Handle ".space" and save empty space in dataseg of objFile.
*/

    void handle_space(std::string line);


/**
* Method: handle_align()
* Usage: handle_align(line);
* --------------------------------------
* @brief Handle ".align n" by chaing the data_size, so the the next variable will\n
* be saved at the starting address which is divisible by 2^n
*/

     void handle_align(std::string line);



/**
* Method: handleTextSection
* Usage: handleTextSection(asm_text_sec);
* ---------------------------------------
* @brief Complete object file.
*/

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
