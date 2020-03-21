#ifndef REGISTERS_SIMULATOR_H
#define REGISTERS_SIMULATOR_H

#include <map>
#include <string>

class Registers_Simulator {

enum REG
{$zero, $at, $v0, $v1, $a0, $a1, $a2, $a3,
 $t0,   $t1, $t2, $t3, $t4, $t5, $t6, $t7,
 $s0,   $s1, $s2, $s3, $s4, $s5, $s6, $s7,
 $t8,   $t9, $k0, $k1, $gp, $sp, $fp, $ra };

public:

/**
 * Constructor: Registers_Simulator
 * Usage: Registers_Simulator regs_sim;
 * ------------------------------------
 * @brief Initialize a simulator for registers.
 */

    Registers_Simulator();

/**
 * Method: readReg
 * Usage: string data = regs_sim.readReg(number);
 * ----------------------------------------------
 * @brief Read data from given number register.
 */

    std::string readReg(unsigned int number);

/**
 * Method: writeReg
 * Usage: regs_sim.write(number, data);
 * ------------------------------------
 * @brief Write data to given number register.
 */

    void writeReg(unsigned int number, std::string data);

private:

    std::map<REG, std::string> regs;

};

#endif // REGISTERS_SIMULATOR_H
