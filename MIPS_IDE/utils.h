#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <fstream>

/**
 * Function: fileToString
 * Usage: string str = fileToString(file);
 * ---------------------------------------
 * @brief Return file content as string.
 */
std::string fileToString(std::ifstream &file);

/**
 * Function: readFile
 * Usage: fstream file = readFile(filepath);
 * ----------------------------------------
 * @return File stream specified by given file path.
 */
std::ifstream readFile(const std::string &filepath);

/**
 * Function: writeFile
 * Usage: writeFile(filepath, content);
 * ------------------------------------
 * @brief Write content to file.
 * @warning Any original file content will be lost.
 */
void writeFile(const std::string &filepath, const std::string &content);

/**
 * Function: clearComment
 * Usage: clearComment(asm_line);
 * ------------------------------
 * @brief Clear comment at the end of line of assembly code.
 */
void clearComment(std::string &asm_line);

/**
 * Function: trim
 * Usage: trim(s);
 * ---------------
 * @brief Clear blank characters in the front and the end.
 */
void trim(std::string &s);

/**
 * Function: isEmptyLine
 * Usage: if (isEmptyLine(line)) ...
 * ---------------------------------
 * Check if line consisting of only blank characters.
 */
bool isEmptyLine(const std::string &line);

/**
 * Function: split
 * Usage: vector<string> tokens = split(s, delim);
 * -----------------------------------------------
 * @return A vector of strings splitted by the given delimiter.
 * e.g. split("main:	add $s0, $s1, $s2	#r instructions", ":")
 *      returns {"main", "	add $s0, $s1, $s2	#r instructions"}.
 */
std::vector<std::string> split(const std::string &s, const std::string &delim);

/**
 * Function: intToBinaryString
 * Usage: string machine_code = intToBinaryString(machine_code_int);
 * -----------------------------------------------------------------
 * @return A 32-digit string containing 0 and 1 which represents the integer.
 * e.g. intToBinaryString(31) returns "00000000000000000000000000011111".
 */
std::string intToBinaryString(int machine_code_int);

/**
 * Function: intToHexString
 * Usage: string hex = intToHexString(num);
 * ----------------------------------------
 * @brief Return hexadecimal string representing the integer.
 */
std::string intToHexString(unsigned int num);

/**
 * Function: error
 * Usage: error(msg);
 * ------------------
 * @brief Print out error message and exit the program.
 */
void error(std::string msg);

/**
 * Function: isBinaryString
 * Usage: if (isBinaryString(str, digits)) ...
 * -------------------------------------------
 * @brief Check if the given string is a binary string with specified digits.
 */
bool isBinaryString(std::string str, unsigned int digits);

/**
 * Function: binaryStringToInt
 * Usage: int strv = binaryStringToInt(str);
 * -----------------------------------------
 * @brief Return corresponding integer for binary string.
 */
unsigned long binaryStringToInt(const std::string &str);

#endif // UTILS_H
