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
 * @brief Convert pseudo instructions by real instructions.
 */

    void pseudoConversion();

};

//const std::map<std::string, Format_Pseudo> Assembler::Pseudo_Bin =
//{ {"mul",    {RDEST, RSRC1,   SRC2}},
//    {"abs",    {RDEST, RSRC1,   NONE}},
//    {"div",    {RDEST, RSRC1,   SRC2}},
//    //    {"divu",   {RDEST, RSRC1,   SRC2}},
//    //    {"mulo",   {RDEST, RSRC1,   SRC2}},
//        {"mulous", {RDEST, RSRC1,   SRC2}},
//    //    {"neg",    {RDEST, RSRC1,   NONE}},
//    //    {"negu",   {RDEST, RSRC1,   NONE}},
//        {"not",    {RDEST, RSRC1,   NONE}},
//        {"rem",    {RDEST, RSRC1,   RSRC2}},
//        {"remu",   {RDEST, RSRC1,   RSRC2}},
//    //    {"rol",    {RDEST, RSRC1,   RSRC2}},
//    //    {"ror",    {RDEST, RSRC1,   RSRC2}},
//        {"li",     {RDEST, IMM_Pseudo,     NONE}},
//    //    {"seq",    {RDEST, RSRC1,   RSRC2}},
//    //    {"sge",    {RDEST, RSRC1,   RSRC2}},
//    //    {"sgeu",   {RDEST, RSRC1,   RSRC2}},
//    //    {"sgt",    {RDEST, RSRC1,   RSRC2}},
//    //    {"sgtu",   {RDEST, RSRC1,   RSRC2}},
//    //    {"sle",    {RDEST, RSRC1,   RSRC2}},
//    //    {"sleu",   {RDEST, RSRC1,   RSRC2}},
//    //    {"sne",    {RDEST, RSRC1,   RSRC2}},
//        {"b",      {LABEL, NONE,    NONE}},
//        {"beqz",   {RSRC1, LABEL,   NONE}},
//        {"bge",    {RSRC1, RSRC2,   LABEL}},
//    //    {"bgeu",   {RSRC1, RSRC2,   LABEL}},
//        {"bgt",    {RSRC1, SRC2,    LABEL}},
//        {"bgtu",   {RSRC1, SRC2,    LABEL}},
//        {"ble",    {RSRC1, SRC2,    LABEL}},
//    //    {"bleu",   {RSRC1, SRC2,    LABEL}},
//        {"blt",    {RSRC1, RSRC2,   LABEL}},
//    //    {"bltu",   {RSRC1, RSRC2,   LABEL}},
//    //    {"bnez",   {RSRC1, LABEL,   NONE}},
//        {"la",     {RDEST, ADDRESS, NONE}},
//    //    {"ld",     {RDEST, ADDRESS, NONE}},
//    //    {"ulh",    {RDEST, ADDRESS, NONE}},
//    //    {"ulhu",   {RDEST, ADDRESS, NONE}},
//    //    {"ulw",    {RDEST, ADDRESS, NONE}},
//    //    {"sd",     {RSRC1, ADDRESS, NONE}},
//    //    {"ush",    {RSRC1, ADDRESS, NONE}},
//    //    {"usw",    {RSRC1, ADDRESS, NONE}},
//        {"move",   {RDEST, RSRC1,   NONE}},
//    //    {"mfc1.d", {RDEST, FRSRC1,  NONE}},
//    //    {"l.d",    {FDEST, ADDRESS, NONE}},
//    //    {"l.s",    {FDEST, ADDRESS, NONE}},
//    //    {"s.d",    {FDEST, ADDRESS, NONE}},
//    //    {"s.s",    {FDEST, ADDRESS, NONE}},
//        {"beq",    {RDEST, RSRC1,   SRC2}},
//        {"clear",  {RDEST, NONE,    NONE}},
//        {"bal",    {RDEST, NONE,    NONE}},
//        {"bne",    {RDEST, RSRC1,   SRC2}},
//        {"jalr",   {RDEST, NONE,    NONE}},
//        {"nop",    {NONE,  NONE,    NONE}}
//
//};

#endif // ASSEMBLER_H
