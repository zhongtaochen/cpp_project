#ifndef LINEASSEMBLER_H
#define LINEASSEMBLER_H

#include "objectfile.h"
#include <map>
#include <string>
#include <vector>

enum OperandType {NONE, RD, RS, RT, SA, IMM, IMM_RS, LABEL};
struct Format {OperandType op1; OperandType op2; OperandType op3; int id;};

class LineAssembler {
public:

/** Bins are implemented in file line_assembler_data.cpp */

    const static std::map<std::string, Format> R_BIN;
    const static std::map<std::string, Format> I_BIN;
    const static std::map<std::string, Format> J_BIN;
    const static std::vector<std::string> REG_BIN;
    const static std::vector<std::string> Pseudo_Bin;

/**
 * Constructor: LineAssembler
 * Usage: Line_Assembler line_assm(obj_file, address);
 * ---------------------------------------------------
 * @brief Initializes a LineAssembler object.
 */

    LineAssembler(ObjectFile obj_file, unsigned int address);

/**
 * Method: assemble
 * Usage: string machine_code = line_assm.assemble();
 * --------------------------------------------------
 * @brief Returns machine code for valid line of Assembly code.
 */

    virtual ObjectFile assemble();

protected:

    std::string asm_line;
    ObjectFile obj_file;
    unsigned int address;

/**
 * Constructor: LineAssembler
 * ---------------------------
 * @brief Void default constructor.
 */
    LineAssembler(){};

/**
 * Method: handleOperand
 * Usage: handleOperand(op_type, op);
 * ----------------------------------
 * @brief Void method. Overriden in subclasses.
 */
    virtual void handleOperand(OperandType op_type, const std::string &op){};

/**
 * Method: getOperandInt
 * Usage: int op = getOperandInt(op_type, operand);
 * ------------------------------------------------
 * @return Integer representation of a operand.
 */

    int getOperandInt(OperandType op_type, const std::string &operand);

private:

/**
 * Method: getRegInt
 * Usage: int reg = getRegInt(reg);
 * --------------------------------
 * @return Integer representation of a register.
 */

    int getRegInt(const std::string &reg);

};

class R_LineAssembler : LineAssembler {
public:

/**
 * Constructor: R_LineAssembler
 * Usage: R_LineAssembler r_line_assm(asm_line);
 * ----------------------------------------------
 * @brief Construct a R_LineAssembler object.\n
 *        Initialize all private characteristic attributes.
 */

    R_LineAssembler(std::string asm_line, ObjectFile obj_file, unsigned int address);

    ObjectFile assemble() override;

private:

    int rd, rs, rt, sa, fn;

    void handleOperand(OperandType op_type, const std::string &op) override;
};

class I_LineAssembler : LineAssembler {
public:

/**
 * Constructor: I_LineAssembler
 * Usage: I_LineAssembler i_line_assm(asm_line, pc, label_bin);
 * -------------------------------------------------------------
 * @brief Construct an I_LineAssembler object.\n
 *        Initialize all private characteristic attributes.
 */

    I_LineAssembler(std::string asm_line, ObjectFile obj_file, unsigned int address);

    ObjectFile assemble() override;

private:

    int op, rs, rt, imm;

    void handleOperand(OperandType op_type, const std::string &op) override;

};

class J_LineAssembler : LineAssembler {
public:

/**
 * Constructor: J_LineAssembler
 * Usage: J_LineAssembler j_line_assm(asm_line, label_bin);
 * ---------------------------------------------------------
 * @brief Construct a J_LineAssembler object.\n
 *        Initialize all private characteristic attributes.
 */

    J_LineAssembler(std::string asm_line, ObjectFile obj_file, unsigned int address);

    ObjectFile assemble() override;

private:

    int op, target;

    void handleOperand(OperandType op_type, const std::string &op) override;
};

class Pseudo_LineAssembler : LineAssembler {
public:
//啥都没写呢还
    //lineassembler_data.cpp 也没写哦
    Pseudo_LineAssembler(std::string asm_line, ObjectFile obj_file, unsigned int address);

private:
};

#endif // LINEASSEMBLER_H
