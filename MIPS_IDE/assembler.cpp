#include "assembler.h"
#include "lineassembler.h"
#include "sstream"
#include "utils.h"
using namespace std;

Assembler::Assembler(const ifstream &asm_file) :
    Assembler(fileToString(asm_file)) {}

Assembler::Assembler(const string &asm_code) {
    string::size_type data_pos = asm_code.find(".data");
    string::size_type text_pos = asm_code.find(".text");
    if (data_pos != asm_code.npos) { // ".data" exists implies ".text" exists
        string asm_data_sec = asm_code.substr(data_pos+5, text_pos-data_pos-5);
        handleDataSection(asm_data_sec);
        asm_lines.clear();

        string asm_text_sec = asm_code.substr(text_pos+5);
        handleTextSection(asm_text_sec);
    } else { // if data section does not exist, no ".text" remark exists
        handleTextSection(asm_code);
    }
//    handleTextSection(asm_code);
}

void Assembler::handleDataSection(const string& asm_data_sec) {
    preprocess(asm_data_sec);
    for (string line : asm_lines) {
        //        cout << intToHexString(obj_file.data_size) << endl;
        vector<string> tokens = split(line, "[ \t]+");
        string type = tokens.at(1);
        string data_name = line.substr(0, line.find(":"));
        obj_file.symbol_table.insert({ "*" + data_name,obj_file.data_size });

        if (type == ".asciiz" || type == ".ascii") {
            string str = line.substr(line.find("\"") + 1, line.rfind("\"") - line.find("\"") - 1);
            if (type == ".asciiz") {
                str = str + "\0";
            }
            unsigned int word = 0;
            for (unsigned int i = 0; i < str.size(); i++) {
                char ch = str.at(i);
                word |= (ch << ((3 - (i % 4)) << 3));
                if (i % 4 == 3) {
                    obj_file.data_segment.push_back({ obj_file.data_size, word});
                    obj_file.data_size += 4;
                    word = 0;
                }
            }
            if (str.size() % 4 != 0) {
                obj_file.data_segment.push_back({ obj_file.data_size, word });
                obj_file.data_size += 4;
            }
        }
        else if (type == ".word") {
            string data = line.substr(line.find(".word") + 5);
            trim(data);
            vector<string> elements = split(data, "[ \t,]+");
            for (string element : elements) {
                uint32_t data = stoi(element);
                obj_file.data_segment.push_back({ obj_file.data_size, data });
                obj_file.data_size += 4;
            }
        }
        else if (type == ".half") {
            string data = line.substr(line.find(".half") + 5);
            trim(data);
            vector<string> elements = split(data, "[ \t,]+");
            int i = 0;
            uint32_t word = 0;
            for (string element : elements) {
                if (i % 2 == 1) {
                    unsigned int data = stoi(element);
                    word |= data;
                    obj_file.data_segment.push_back({ obj_file.data_size, word});
                    obj_file.data_size += 4;
                    word = 0;
                }else {
                    unsigned int data = stoi(element);
                    word |= (data << 16);
                }
                i += 1;
            }
            if (elements.size() % 2 != 0) {
                obj_file.data_segment.push_back({ obj_file.data_size, word});
                obj_file.data_size += 4;
            }
        }
        else if (type == ".byte") {
            string data = line.substr(line.find(".byte") + 5);
            trim(data);
            vector<string> elements = split(data, "[ \t,]+");
            int i = 0;
            uint32_t word = 0;
            for (string element : elements) {
                unsigned int data = stoi(element);
                if (stoi(element) < 0) {
                    data &= 0x000000ff;
                }
                if (i % 4 == 0) {word |= data << 24;
                }else if (i % 4 == 1) {word |= data << 16;
                }else if (i % 4 == 2) {word |= data << 8;
                }else{
                    obj_file.data_segment.push_back({ obj_file.data_size, word});
                    obj_file.data_size += 4;
                    word = 0;
                }
                i += 1;
            }
            if (elements.size() % 4 != 0) {
                obj_file.data_segment.push_back({ obj_file.data_size, word});
                obj_file.data_size += 4;
            }

        }
        else if (type == ".space") {
            string data = line.substr(line.find(".space") + 6);
            trim(data);
            for (int i = 0; i < stoi(data); i++) {
                obj_file.data_segment.push_back({ obj_file.data_size, 00000000000000000000000000000000 });
                obj_file.data_size += 4;
            }
        }
    }
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
        if (pos != asm_line.npos) { // colon exists, label exists
            label = asm_line.substr(0, pos);
            remain = asm_line.substr(pos+1); // skip colon
            obj_file.symbol_table.insert({ label, i<<2 });
            if (isEmptyLine(remain)) {
                asm_lines.erase(asm_lines.begin()+i);
                i--;
            }
            else {
                trim(remain);
                asm_lines.at(i) = remain;
            }
        }
    }
}

void Assembler::handleTextSection(const string &asm_text_sec) {
    preprocess(asm_text_sec);
    obj_file.text_size = asm_lines.size() << 2;
    scanLabels();
    for (unsigned int i = 0; i < asm_lines.size(); i++) {
        obj_file.text_segment.push_back({ i << 2, 0, asm_lines.at(i) });
        LineAssembler line_assm(obj_file, i << 2);
        obj_file = line_assm.assemble();
    }
}

void Assembler::output(const string& file_path) {
    string mc_code = "";
    for (unsigned int i = 0; i < obj_file.text_segment.size(); i++) {
        mc_code += intToBinaryString(obj_file.text_segment.at(i).machine_code) + "\n";
    }
    writeFile(file_path, mc_code);
}
