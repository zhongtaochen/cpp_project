#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <string>
#include <vector>
#include <QStringList>
#include <objectfile.h>
/**
 * @brief convert vector text_segment to a QString
 */

QStringList textseg_to_Qstring(std::vector<TextCell> text_seg);

/**
 * @brief Return file content as string.
 */
std::string fileToString(const std::ifstream &file);

/**
 * @brief File stream specified by given file path.
 */
std::ifstream readFile(const std::string &filepath);

/**
 * @brief Write content to file.
 * @warning Any original file content will be lost.
 */
void writeFile(const std::string &filepath, const std::string &content);

/**
 * @brief Clear comment at the end of line of assembly code.
 */
void clearComment(std::string &asm_line);

/**
 * @brief Clear blank characters in the front and the end.
 */
void trim(std::string &s);

/**
 * @brief Check if line consisting of only blank characters.
 */
bool isEmptyLine(const std::string &line);

/**
 * @brief A vector of strings splitted by the given delimiter.
 * e.g. split("main:	add $s0, $s1, $s2	#r instructions", ":")
 *      returns {"main", "	add $s0, $s1, $s2	#r instructions"}.
 */
std::vector<std::string> split(const std::string &s, const std::string &delim);

/**
 * @brief Return hexadecimal string representing the integer.
 */
std::string intToHexString(unsigned int num);

/**
 * @brief A 32-digit string containing 0 and 1 which represents the integer.
 * e.g. intToBinaryString(31) returns "00000000000000000000000000011111".
 */
std::string intToBinaryString(int machine_code_int);


/**
 * Function: combineString
 * Usage: string strv = combineString(str)
 * -----------------------------------------
 * @brief Given a vector of strings, combine it element-wise
 * with a space in between. For example, combine vector {"a
 * , "b", "c"} into "a b c".
 */
std::string combineString(std::vector<std::string> str);

/**
 * Function: insertConverted
 * Usage: vector<string> str_vec = insertConverted(str_vec, i, vec_str_vec);
 * -----------------------------------------
 * @brief Given a vector of strings "str_vec", modify it by
 * replacing its i-th element with a vector of string vectors,
 * for example, replacing "b" by "b0" and "b1" so that {"a", "b", "c"}
 * turns out to be {"a", "b0", "b1", "c"}.
 */
 void insertConverted(std::vector<std::string> &str_vec, unsigned int pos,
    std::vector<std::vector<std::string>> vec_str_vec);

 void convertInstruction(std::string &instruction, std::string var_name, unsigned int address);

#endif // UTILS_H
