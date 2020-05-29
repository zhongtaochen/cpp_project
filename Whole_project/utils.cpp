/**
 * @file utils.cpp
 * @brief This file implements utils.h.
 */

#include "utils.h"
#include "assembler.h"
#include <iostream>
#include <sstream>
#include <regex>
#include <iomanip>
#include <bitset>
using namespace std;

QStringList textseg_to_Qstring(std::vector<TextCell> text_seg) {
	QStringList resultlist;
	for (auto const& pair : text_seg) {
		QString instrctn = QString::fromStdString(pair.instruction);
		QString addr = QString::fromStdString(intToBinaryString(pair.address));
		resultlist.append(QString("%1 %2").arg(addr, instrctn));
	}
	return resultlist;
}

string fileToString(const ifstream& file) {
	stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

ifstream readFile(const string& filepath) {
	ifstream file(filepath);
	if (!file) cout << "No such file exists." << endl;
	return file;
}

void writeFile(const string& filepath, const string& content) {
	ofstream file(filepath);
	if (!file) { cout << "No such directory exists." << endl; return; }
	file.clear();
	file << content;
	file.close();
}

void clearComment(string& asm_line) {
	asm_line = regex_replace(asm_line, regex("#(.)*"), "");
}

void trim(string& s) {
	if (s.empty()) return;
	s.erase(0, s.find_first_not_of(" \f\r\t\v"));
	s.erase(s.find_last_not_of("  \f\r\t\v") + 1);
}

bool isEmptyLine(const std::string& line) {
	return regex_match(line, regex("[ \f\n\r\t\v]*"));
}

vector<string> split(const string& s, const string& delim) {
	regex re(delim);
	vector<string> tokens(sregex_token_iterator(s.begin(), s.end(), re, -1), sregex_token_iterator());
	return tokens;
}

string intToHexString(unsigned int num) {
	stringstream sstrm;
	sstrm << "0x"
		<< std::setfill('0') << std::setw(sizeof(unsigned int) * 2)
		<< std::hex << num;
	return sstrm.str();
}

string intToBinaryString(int machine_code_int) {
	return bitset<32>(machine_code_int).to_string();
}

string combineString(vector<string> str) {
	string combined = str[0] + " ";
	for (unsigned int i = 1; i < str.size() - 1; i++) {
		combined += str[i];
		combined += ", ";
	}
	combined += str[str.size() - 1];
	return combined;
}

void insertConverted(vector<string>& str_vec, unsigned int pos,
	vector<vector<string>> vec_str_vec) {
	if (vec_str_vec.size() == 0) {
		return;
	}
	if (!vec_str_vec[0].empty()) {
		string temp_1 = combineString(vec_str_vec[0]);
		str_vec[pos] = temp_1;
	}
	for (unsigned int i = 1; i < vec_str_vec.size(); i++) {
		if (!vec_str_vec[i].empty()) {
			string temp = combineString(vec_str_vec[i]);
			str_vec.insert(str_vec.begin() + pos + i, temp);
		}
	}
}

void convertInstruction(string& instruction, string var_name, unsigned int address) {
	int var_pos = instruction.find(var_name);
	stringstream sstrm;
	sstrm << std::dec << address;
	instruction = instruction.substr(0, var_pos) + sstrm.str();
}
