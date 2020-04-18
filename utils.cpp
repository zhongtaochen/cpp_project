#include "utils.h"
#include <sstream>
#include <iostream>
#include <regex>
#include <iomanip>
using namespace std;

string fileToString(ifstream &file) {
    stringstream buffer;
    buffer << file.rdbuf();
    cout<<buffer.get();
    return buffer.str();
}

ifstream readFile(const string &filepath) {
    ifstream file(filepath);
    if (!file) cout << "No such file exists." << endl;
    return file;
}

void writeFile(const string &filepath, const string &content) {
    ofstream file(filepath);
    if (!file) {cout << "No such directory exists." << endl; return;}
    file.clear();
    file << content;
    file.close();
}

void clearComment(string &asm_line) {
    asm_line = regex_replace(asm_line, regex("#(.)*"), "");
}

void trim(string &s) {
    if (s.empty()) return;
    s.erase(0, s.find_first_not_of(" \f\r\t\v"));
    s.erase(s.find_last_not_of("  \f\r\t\v") + 1);
}

bool isEmptyLine(const std::string &line) {
    return regex_match(line, regex("[ \f\n\r\t\v]*"));
}

vector<string> split(const string &s, const string &delim) {
    regex re(delim);
    vector<string> tokens(sregex_token_iterator(s.begin(), s.end(), re, -1), sregex_token_iterator());
    return tokens;
}

string intToBinaryString(int machine_code_int) {
    return bitset<32>(machine_code_int).to_string();
}

string intToHexString(unsigned int num) {
    stringstream sstrm;
    sstrm << "0x"
         << std::setfill ('0') << std::setw(sizeof(unsigned int)*2)
         << std::hex << num;
    return sstrm.str();
}

void error(string msg) {
    cerr << msg << endl;
    exit(EXIT_FAILURE);
}

bool isBinaryString(string str, unsigned int digits) {
    return str.length() == digits && regex_match(str, regex("^[01]+$"));
}

unsigned long binaryStringToInt(const string &str) {
    bitset<32> bs(str);
    return bs.to_ulong();
}

using namespace std;
//不要看这个func  这个瞎写 来testlinker的， 结果没用到
void ExeAsTxt(std::ofstream & of, ExecutableFile exefile){
    of<<"textsize:"<<exefile.text_size<<endl;
    of<<"datasize:"<<exefile.data_size<<endl;
    of<<"textseg"<<endl;
    for (ExecutableFile::segment_cell cell : exefile.text_segment) {
        of<<cell.address<<"   "<<cell.data<<endl;
    }
    of<<"dataseg"<<endl;
    for (ExecutableFile::segment_cell cell : exefile.data_segment) {
        of<<cell.address<<"   "<<cell.data<<endl;
    }
}
