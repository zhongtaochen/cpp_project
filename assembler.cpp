#include "assembler.h"
#include "lineassembler.h"
#include "utils.h"
#include <string>
#include <stdlib.h>
#include <sstream>
#include <iostream>
using namespace std;

const map<string, Format_Pseudo> Pseudo_Bin =
{   {"mul",    {RDEST, RSRC1,   SRC2}},
    {"abs",    {RDEST, RSRC1,   NONE}},
    {"div",    {RDEST, RSRC1,   SRC2}},
//    {"divu",   {RDEST, RSRC1,   SRC2}},
//    {"mulo",   {RDEST, RSRC1,   SRC2}},
    {"mulous", {RDEST, RSRC1,   SRC2}},
//    {"neg",    {RDEST, RSRC1,   NONE}},
//    {"negu",   {RDEST, RSRC1,   NONE}},
    {"not",    {RDEST, RSRC1,   NONE}},
    {"rem",    {RDEST, RSRC1,   RSRC2}},
    {"remu",   {RDEST, RSRC1,   RSRC2}},
//    {"rol",    {RDEST, RSRC1,   RSRC2}},
//    {"ror",    {RDEST, RSRC1,   RSRC2}},
    {"li",     {RDEST, IMM,     NONE}},
//    {"seq",    {RDEST, RSRC1,   RSRC2}},
//    {"sge",    {RDEST, RSRC1,   RSRC2}},
//    {"sgeu",   {RDEST, RSRC1,   RSRC2}},
//    {"sgt",    {RDEST, RSRC1,   RSRC2}},
//    {"sgtu",   {RDEST, RSRC1,   RSRC2}},
//    {"sle",    {RDEST, RSRC1,   RSRC2}},
//    {"sleu",   {RDEST, RSRC1,   RSRC2}},
//    {"sne",    {RDEST, RSRC1,   RSRC2}},
    {"b",      {LABEL, NONE,    NONE}},
    {"beqz",   {RSRC1, LABEL,   NONE}},
    {"bge",    {RSRC1, RSRC2,   LABEL}},
//    {"bgeu",   {RSRC1, RSRC2,   LABEL}},
    {"bgt",    {RSRC1, SRC2,    LABEL}},
    {"bgtu",   {RSRC1, SRC2,    LABEL}},
    {"ble",    {RSRC1, SRC2,    LABEL}},
//    {"bleu",   {RSRC1, SRC2,    LABEL}},
    {"blt",    {RSRC1, RSRC2,   LABEL}},
//    {"bltu",   {RSRC1, RSRC2,   LABEL}},
//    {"bnez",   {RSRC1, LABEL,   NONE}},
    {"la",     {RDEST, ADDRESS, NONE}},
//    {"ld",     {RDEST, ADDRESS, NONE}},
//    {"ulh",    {RDEST, ADDRESS, NONE}},
//    {"ulhu",   {RDEST, ADDRESS, NONE}},
//    {"ulw",    {RDEST, ADDRESS, NONE}},
//    {"sd",     {RSRC1, ADDRESS, NONE}},
//    {"ush",    {RSRC1, ADDRESS, NONE}},
//    {"usw",    {RSRC1, ADDRESS, NONE}},
    {"move",   {RDEST, RSRC1,   NONE}},
//    {"mfc1.d", {RDEST, FRSRC1,  NONE}},
//    {"l.d",    {FDEST, ADDRESS, NONE}},
//    {"l.s",    {FDEST, ADDRESS, NONE}},
//    {"s.d",    {FDEST, ADDRESS, NONE}},
//    {"s.s",    {FDEST, ADDRESS, NONE}},
    {"beq",    {RDEST, RSRC1,   SRC2}},
    {"clear",  {RDEST, NONE,    NONE}},
    {"bal",    {RDEST, NONE,    NONE}},
    {"bne",    {RDEST, RSRC1,   SRC2}},
    {"jalr",   {RDEST, NONE,    NONE}},
    {"nop",    {NONE,  NONE,    NONE}}
};

Assembler::Assembler(ifstream &asm_file):Assembler(fileToString(asm_file)){}

Assembler::Assembler(const string &asm_code) {
    string::size_type data_pos = asm_code.find(".data");
    string::size_type text_pos = asm_code.find(".text");
    if (text_pos == asm_code.npos) {
        handleTextSection(asm_code);
    }
    if (data_pos != asm_code.npos) {
        string asm_data_sec = asm_code.substr(data_pos + 5, text_pos - data_pos - 5);
        handleDataSection(asm_data_sec);
        asm_lines.clear();
        string asm_text_sec = asm_code.substr(text_pos + 5);
        handleTextSection(asm_text_sec);
    }
}

void Assembler::handleDataSection(const string &asm_data_sec) {
    preprocess(asm_data_sec);
    for (string line : asm_lines) {
//        cout << intToHexString(obj_file.data_size) << endl;
        vector<string> tokens = split(line, "[ \t]+");
        string type = tokens.at(1);
        if (type == ".asciiz") {
            string str = line.substr(line.find("\"")+1, line.rfind("\"")-line.find("\"")-1);
            str = str + "\0";
            unsigned int word = 0;
            unsigned int i = 0;
            for (; i < str.size(); i++) {
                char ch = str.at(i);
                word |= (ch << ((3 - (i % 4)) << 3));
                if (i % 4 == 3) {
                    obj_file.data_segment.push_back({obj_file.data_size, intToBinaryString(word)});
                    obj_file.data_size += 4;
                    word = 0;
                }
            }
            if (str.size() % 4 != 0) {
                obj_file.data_segment.push_back({obj_file.data_size, intToBinaryString(word)});
                obj_file.data_size += 4;
            }
        } else if (type == ".word") {
            string data = line.substr(line.find(".word")+5);
            trim(data);
            vector<string> elements = split(data, "[ \t,]+");
            for (string element : elements) {
                obj_file.data_segment.push_back({obj_file.data_size, intToBinaryString(stoi(element))});
                obj_file.data_size += 4;
            }
        }
    }
}

void Assembler::handleTextSection(const string &asm_text_sec) {
    preprocess(asm_text_sec);
    obj_file.text_size = asm_lines.size() << 2;
    scanLabels();
    pseudoConversion();
    assembleLines();
}

void Assembler::preprocess(const string &asm_code) {
    stringstream sstrm(asm_code);
    string asm_line;
    while (getline(sstrm, asm_line)) {
        clearComment(asm_line);
        trim(asm_line);
        if (!isEmptyLine(asm_line)) {
            asm_lines.push_back(asm_line);
        }
    }
}

void Assembler::scanLabels() {
    string asm_line, label, remain;
    for (unsigned int i = 0; i < asm_lines.size(); i++) {
        asm_line = asm_lines.at(i);
        string::size_type pos = asm_line.find(":");
        if (pos != asm_line.npos) { // colon exists
            label = asm_line.substr(0, pos);
            remain = asm_line.substr(pos + 1);
            obj_file.symbol_table.insert({label, i << 2});
            if (isEmptyLine(remain)) {
                asm_lines.erase(asm_lines.begin() + i);
                i--;
            } else {
                trim(remain);
                asm_lines.at(i) = remain;
            }
        }
    }
}

void Assembler::pseudoConversion(){
    string asm_line;
    for (unsigned int i = 0; i < asm_lines.size(); i++) {
        asm_line = asm_lines.at(i);
        vector<string> tokens = split(asm_line, "[ \t,]+");
        string instruction = tokens.at(0);
        Format_Pseudo format = Pseudo_Bin.at(instruction);
        vector<vector<string>> new_instructions;
        if (instruction == "mul"){
            new_instructions.push_back({"mult", tokens[2], tokens[3]});
            new_instructions.push_back({"mflo", tokens[1]});
            asm_lines = insertConverted(asm_lines, i, new_instructions);
        } else if (instruction == "div" && format.op3 != NONE){
            new_instructions.push_back({"div", tokens[2], tokens[3]});
            new_instructions.push_back({"mflo", tokens[1]});
            asm_lines = insertConverted(asm_lines, i, new_instructions);
        } else if (instruction == "rem"){
            new_instructions.push_back({"div", tokens[2], tokens[3]});
            new_instructions.push_back({"mfhi", tokens[1]});
            asm_lines = insertConverted(asm_lines, i, new_instructions);
        } else if (instruction == "move"){
            new_instructions.push_back({"or", tokens[1], tokens[2], "$zero"});
            asm_lines = insertConverted(asm_lines, i, new_instructions);
        } else if (instruction == "clear"){
            new_instructions.push_back({"or", tokens[1], "$zero", "$zero"});
            asm_lines = insertConverted(asm_lines, i, new_instructions);
        } else if (instruction == "li"){
            string C_hi = intToBinaryString(stoi(tokens[2])).substr(0,16);
            string C_lo = intToBinaryString(stoi(tokens[2])).substr(16,16);
            new_instructions.push_back({"lui", tokens[1], C_hi});
            new_instructions.push_back({"ori", tokens[1], tokens[1], C_lo});
            asm_lines = insertConverted(asm_lines, i, new_instructions);
        } else if (instruction == "la"){
            string A_hi = intToBinaryString(stoi(tokens[2])).substr(0,16);
            string A_lo = intToBinaryString(stoi(tokens[2])).substr(16,16);
            new_instructions.push_back({"lui", tokens[1], A_hi});
            new_instructions.push_back({"ori", tokens[1], tokens[1], A_lo});
            asm_lines = insertConverted(asm_lines, i, new_instructions);
        } else if (instruction == "b"){
            new_instructions.push_back({"beq", "$zero", "$zero", tokens[1]});
            asm_lines = insertConverted(asm_lines, i, new_instructions);
        } else if (instruction == "bal"){
            new_instructions.push_back({"bgezal", "$zero", tokens[1]});
            asm_lines = insertConverted(asm_lines, i, new_instructions);
        } else if (instruction == "bgt"){
            new_instructions.push_back({"slt", "$at", tokens[2], tokens[1]});
            new_instructions.push_back({"bne", "$at", "$zero", tokens[3]});
            asm_lines = insertConverted(asm_lines, i, new_instructions);
        } else if (instruction == "blt"){
            new_instructions.push_back({"slt", "$at", tokens[1], tokens[2]});
            new_instructions.push_back({"bne", "$at", "$zero", tokens[3]});
            asm_lines = insertConverted(asm_lines, i, new_instructions);
        } else if (instruction == "bge"){
            new_instructions.push_back({"slt", "$at", tokens[1], tokens[2]});
            new_instructions.push_back({"beq", "$at", "$zero", tokens[3]});
            asm_lines = insertConverted(asm_lines, i, new_instructions);
        } else if (instruction == "ble"){
            new_instructions.push_back({"slt", "$at", tokens[2], tokens[1]});
            new_instructions.push_back({"beq", "$at", "$zero", tokens[3]});
            asm_lines = insertConverted(asm_lines, i, new_instructions);
        } else if (instruction == "bgtu"){
            new_instructions.push_back({"sltu", "$at", tokens[2], tokens[1]});
            new_instructions.push_back({"bne", "$at", "$zero", tokens[3]});
            asm_lines = insertConverted(asm_lines, i, new_instructions);
        } else if (instruction == "beqz"){
            new_instructions.push_back({"beq", tokens[1], "$zero", tokens[2]});
            asm_lines = insertConverted(asm_lines, i, new_instructions);
        } else if (instruction == "beq" && tokens[2].find("$") == tokens[2].npos){
            new_instructions.push_back({"ori", "$at", "$zero", tokens[2]});
            new_instructions.push_back({"beq", tokens[1], "$at", tokens[3]});
            asm_lines = insertConverted(asm_lines, i, new_instructions);
        } else if (instruction == "bne"){
            new_instructions.push_back({"ori", "$at", "$zero", tokens[2]});
            new_instructions.push_back({"bne", tokens[1], "$at", tokens[3]});
            asm_lines = insertConverted(asm_lines, i, new_instructions);
        } else if (instruction == "jalr"){
            new_instructions.push_back({"jalr", tokens[1], "$ra"});
            asm_lines = insertConverted(asm_lines, i, new_instructions);
        } else if (instruction == "not"){
            new_instructions.push_back({"nor", tokens[1], tokens[2], "$zero"});
            asm_lines = insertConverted(asm_lines, i, new_instructions);
        } else if (instruction == "nop"){
            new_instructions.push_back({"sll", "$zero", "$zero", "0"});
            asm_lines = insertConverted(asm_lines, i, new_instructions);
        } else if (instruction == "abs"){
            new_instructions.push_back({"sra", "$at", tokens[2], "31"});
            new_instructions.push_back({"xor", tokens[1], tokens[2], "$at"});
            new_instructions.push_back({"subu", tokens[1], tokens[1], "$at"});
            asm_lines = insertConverted(asm_lines, i, new_instructions);
        } else if (instruction == "mulou"){
            new_instructions.push_back({"multu", tokens[2], tokens[3]});
            new_instructions.push_back({"mflo", tokens[1]});
            asm_lines = insertConverted(asm_lines, i, new_instructions);
        } else if (instruction == "remu"){
            new_instructions.push_back({"divu", tokens[2], tokens[3]});
            new_instructions.push_back({"mfhi", tokens[1]});
            asm_lines = insertConverted(asm_lines, i, new_instructions);
        }
    }

//    for (unsigned int i = 0; i < asm_lines.size(); i++){
//        asm_line = asm_lines.at(i);
////        cout << asm_line;
//        vector<string> tokens = split(asm_line, "[ \t,]+");
//        for (unsigned int j = 0; j < tokens.size(); j++){
//            cout << tokens[j] << endl;
//            cout << j << endl;
//        }
//    }
}


void Assembler::assembleLines() {
    for (unsigned int i = 0; i < asm_lines.size(); i++) {
        obj_file.text_segment.push_back({i << 2, asm_lines.at(i)});
        LineAssembler line_assm(obj_file, i << 2);
        obj_file = line_assm.assemble();
    }
}

void Assembler::output(const string &file_path) {
    string mc_code = "";
    for (unsigned int i = 0; i < obj_file.text_segment.size(); i++) {
        mc_code += obj_file.text_segment.at(i).data + "\n";
    }
    writeFile(file_path, mc_code);
}
