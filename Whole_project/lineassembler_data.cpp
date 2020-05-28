#include "lineassembler.h"
using namespace std;

const map<string, Format> LineAssembler::R_BIN =
{ {"add",     {RD,   RS,   RT,   0b100000} },
	{"addu",    {RD,   RS,   RT,   0b100001} },
	{"and",     {RD,   RS,   RT,   0b100100} },
	{"break",   {NONE, NONE, NONE, 0b001101} },
	{"div",     {RS,   RT,   NONE, 0b011010} },
	{"divu",    {RS,   RT,   NONE, 0b011011} },
	{"jalr",    {RS,   RD,   NONE, 0b001001} },
	{"jr",      {RS,   NONE, NONE, 0b001000} },
	{"mfhi",    {RD,   NONE, NONE, 0b010000} },
	{"mflo",    {RD,   NONE, NONE, 0b010010} },
	{"mthi",    {RS,   NONE, NONE, 0b010001} },
	{"mtlo",    {RS,   NONE, NONE, 0b010011} },
	{"mult",    {RS,   RT,   NONE, 0b011000} },
	{"multu",   {RS,   RT,   NONE, 0b011001} },
	{"nor",     {RD,   RS,   RT,   0b100111} },
	{"or",      {RD,   RS,   RT,   0b100101} },
	{"sll",     {RD,   RT,   SA,   0b000000} },
	{"sllv",    {RD,   RT,   RS,   0b000100} },
	{"slt",     {RD,   RS,   RT,   0b101010} },
	{"sltu",    {RD,   RS,   RT,   0b101011} },
	{"sra",     {RD,   RT,   SA,   0b000011} },
	{"srav",    {RD,   RT,   RS,   0b000111} },
	{"srl",     {RD,   RT,   SA,   0b000010} },
	{"srlv",    {RD,   RT,   RS,   0b000110} },
	{"sub",     {RD,   RS,   RT,   0b100010} },
	{"subu",    {RD,   RS,   RT,   0b100011} },
	{"syscall", {NONE, NONE, NONE, 0b001100} },
	{"xor",     {RD,   RS,   RT,   0b100110} },

	{"teq",     {RS,   RT,   NONE, 0x34    } },
	{"tne",     {RS,   RT,   NONE, 0X36    } },
	{"tge",     {RS,   RT,   NONE, 0X30    } },
	{"tgeu",    {RS,   RT,   NONE, 0X31    } },
	{"tlt",     {RS,   RT,   NONE, 0X32    } },
	{"tltu",    {RS,   RT,   NONE, 0X33    } }
};

const map<string, Format> LineAssembler::I_BIN =
{ {"addi",  {RT, RS,     IMM,   0b001000} },
	{"addiu", {RT, RS,     IMM,   0b001001} },
	{"andi",  {RT, RS,     IMM,   0b001100} },
	{"beq",   {RS, RT,     LABEL, 0b000100} },
	{"bgez",  {RS, LABEL,  NONE,  0b000001} },
	{"bgtz",  {RS, LABEL,  NONE,  0b000111} },
	{"blez",  {RS, LABEL,  NONE,  0b000110} },
	{"bltz",  {RS, LABEL,  NONE,  0b000001} },
	{"bne",   {RS, RT,     LABEL, 0b000101} },
	{"lb",    {RT, IMM_RS, NONE,  0b100000} },
	{"lbu",   {RT, IMM_RS, NONE,  0b100100} },
	{"lh",    {RT, IMM_RS, NONE,  0b100001} },
	{"lhu",   {RT, IMM_RS, NONE,  0b100101} },
	{"lui",   {RT, IMM,    NONE,  0b001111} },
	{"lw",    {RT, IMM_RS, NONE,  0b100011} },

	{"ori",   {RT, RS,     IMM,   0b001101} },
	{"sb",    {RT, IMM_RS, NONE,  0b101000} },
	{"slti",  {RT, RS,     IMM,   0b001010} },
	{"sltiu", {RT, RS,     IMM,   0b001011} },
	{"sh",    {RT, IMM_RS, NONE,  0b101001} },
	{"sw",    {RT, IMM_RS, NONE,  0b101011} },

	{"xori",  {RT, RS,     IMM,   0b001110} },

	{"bgezal",{RS, LABEL,  NONE,  0b000001} },
	{"bltzal",{RS, LABEL,  NONE,  0b000001} },
	{"teqi",  {RS, IMM,    NONE,  0b000001} },
	{"tnei",  {RS, IMM,    NONE,  0b000001} },
	{"tgei",  {RS, IMM,    NONE,  0b000001} },
	{"tgeiu", {RS, IMM,    NONE,  0b000001} },
	{"tlti",  {RS, IMM,    NONE,  0b000001} },
	{"tltiu", {RS, IMM,    NONE,  0b000001} },
	{"lwl",   {RT, IMM_RS, NONE,  0x22    } },
	{"lwr",   {RT, IMM_RS, NONE,  0x26    } },
	{"ll",    {RT, IMM_RS, NONE,  0x30    } },
	{"swl",   {RT, IMM_RS, NONE,  0x2a    } },
	{"swr",   {RT, IMM_RS, NONE,  0x2e    } },
	{"sc",    {RT, IMM_RS, NONE,  0x38    } }
};

const map<string, Format> LineAssembler::J_BIN =
{ {"j",   {LABEL, NONE, NONE, 0b000010} },
	{"jal", {LABEL, NONE, NONE, 0b000011} }
};

const vector<string> LineAssembler::REG_BIN =
{ "$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0",
	 "$t1",   "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1",
	 "$s2",   "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0",
	 "$k1",   "$gp", "$sp", "$fp", "$ra"
};


