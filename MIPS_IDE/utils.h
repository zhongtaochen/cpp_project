#ifndef UTILS_H
#define UTILS_H

#include <fstream>
#include <string>
#include <vector>

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


#endif // UTILS_H
