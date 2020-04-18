#include "assembler.h"
#include "lineassembler.h"
#include "utils.h"
#include <sstream>
#include <iostream>
using namespace std;

Assembler::Assembler(ifstream &asm_file):Assembler(fileToString(asm_file)){}

Assembler::Assembler(const string &asm_code) {
    string::size_type data_pos = asm_code.find(".data");
    string::size_type text_pos = asm_code.find(".text");
    //  ????????
    if (text_pos != asm_code.npos) {
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
