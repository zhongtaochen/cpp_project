/**
 * @file lineassembler.h
 * @brief <code>LineAssembler</code> class, <code>R_LineAssembler</code> class,
 * <code>I_LineAssembler</code> class, <code>J_LineAssembler</code> class.
 * @details This file exports <code>LineAssembler</code> class, which handles assembling
 * one line of assembly code and serves as an abstraction providing common toolkit of
 * determining operand value for subclasses <code>R_LineAssembler</code> class,
 * <code>I_LineAssembler</code> class, <code>J_LineAssembler</code> class.
 * Meanwhile, three subclasses overwrites assemble fucntion.
 */

#ifndef LINEASSEMBLER_H
#define LINEASSEMBLER_H

#include "objectfile.h"
#include <map>
#include <string>
#include <vector>

enum OperandType { NONE, RD, RS, RT, SA, IMM, IMM_RS, LABEL };
struct Format {OperandType op1; OperandType op2; OperandType op3; int id;};

/**
 * @brief Handles one-line assembly code assembling and provides common toolkit
 * for subclasses for further assembling.
 */
class LineAssembler {
public:

/** Bins recording necessary information. */

    const static std::map<std::string, Format> R_BIN;
    const static std::map<std::string, Format> I_BIN;
    const static std::map<std::string, Format> J_BIN;
    const static std::vector<std::string> REG_BIN;

/**
 * @brief Initialize a <code>LineAssembler</code> object.
 */

    LineAssembler(ObjectFile obj_file, uint32_t address);

/**
 * @brief Return assembled object file.
 */

    virtual ObjectFile assemble();

protected:

    std::string asm_line;
    ObjectFile obj_file;
    uint32_t address;

/**
 * @brief Void default constructor. Hidden from the clients.
 */

    LineAssembler(){};

/**
 * @brief Void method. Overriden in subclasses.
 */

    virtual void handleOperand(OperandType op_type, const std::string &op){};

/**
 * @brief Return integer representation of a operand.
 */

    int getOperandInt(OperandType op_type, const std::string &operand);


private:

/**
 * @brief Return integer representation of a register.
 */

    int getRegInt(const std::string &reg);

};

/**
 * @brief Subclass of <code>LineAssembler</code>. Handles R-type instruction
 * assembling. Determining fields specified would be enough.
 */
class R_LineAssembler : LineAssembler {
public:

/**
 * @brief Construct a <code>R_LineAssembler</code> object.
 * Initialize all private characteristic attributes.
 */

    R_LineAssembler(std::string asm_line, ObjectFile obj_file, uint32_t address);

    ObjectFile assemble() override;

private:

    int rd, rs, rt, sa, fn;

    void handleOperand(OperandType op_type, const std::string &op) override;
};


/**
 * @brief Subclass of <code>LineAssembler</code>. Handles I-type instruction
 * assembling. Determining fields specified would be enough. Notice that assembling
 * may involve absolute address, which will be recorded in relocation information
 * for linker to perform operations.
 */
class I_LineAssembler : LineAssembler {
public:

/**
 * @brief Construct an <code>I_LineAssembler</code> object.
 * Initialize all private characteristic attributes.
 */

    I_LineAssembler(std::string asm_line, ObjectFile obj_file, uint32_t address);

    ObjectFile assemble() override;

private:

    int op, rs, rt, imm;

    void handleOperand(OperandType op_type, const std::string &op) override;

};

/**
 * @brief Subclass of <code>LineAssembler</code>. Handles J-type instruction
 * assembling. Immediately records in relocation information.
 */
class J_LineAssembler : LineAssembler {
public:

/**
 * @brief Construct a <code>J_LineAssembler</code> object.
 * Initialize all private characteristic attributes.
 */

    J_LineAssembler(std::string asm_line, ObjectFile obj_file, uint32_t address);

    ObjectFile assemble() override;

private:

    int op, target;

    void handleOperand(OperandType op_type, const std::string &op) override;
};

#endif // LINEASSEMBLER_H
