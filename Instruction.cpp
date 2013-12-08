/* 
 * File:   Instruction.cpp
 * Author: Devin
 * 
 * Created on December 7, 2013, 1:50 PM
 */

#include "Instruction.h"


Instruction::Instruction() {
    this->op = "";
    this->rs = 0;
    this->rt = 0;
    this->rd = 0;
    this->immediate = 0;
    this->insType = "";
}
Instruction::Instruction(string op, int rs, int rt, int rd) {
    this->op = op;
    this->rs = rs;
    this->rt = rt;
    this->rd = rd;
    this->insType = "r_type";
}


Instruction::Instruction(int address) {
    this->address = address;
    this->insType = "j_type";
}

Instruction::Instruction(const Instruction& orig) {
}

Instruction::~Instruction() {
}

