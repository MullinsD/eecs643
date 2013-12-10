/* 
 * File:   Instruction.h
 * Author: Devin
 *
 * Created on December 7, 2013, 1:50 PM
 */

#ifndef INSTRUCTION_H
#define	INSTRUCTION_H
#include <string>
using namespace std;

class Instruction {
public:
    Instruction();
    Instruction(string op, int rs, int rt, int rd);
    Instruction(int address);
    Instruction(const Instruction& orig);
    virtual ~Instruction();
    
    void setAddress(int address) {
        this->address = address;
    }
    
    void setNumber(int number) {
        this->number = number;
    }
    
    void setisStall(bool b) {
        this->isStall = b;
    }
    
    void setLabel(string label) {
        this->label = label;
    }
    void setImmediate(int immediate) {
        this->immediate = immediate;
    }
    void setOp(string op) {
        this->op.assign(op);
    }
    void setInsType(string insType) {
        this->insType = insType;
    }

    void setRd(int rd) {
        this->rd = rd;
    }
    void setRs(int rs) {
        this->rs = rs;
    }
    void setRt(int rt) {
        this->rt = rt;
    }
    int getAddress() const {
        return address;
    }
    bool getisStall() {
        return isStall;
    }
    int getImmediate() const {
        return immediate;
    }
    int getNumber() const {
        return number;
    }
    string getinsType() const {
        return insType;
    }
    
    string getLabel() const {
        return label;
    }
    string getOp() const {
        return op;
    }
    int getRd() const {
        return rd;
    }
    int getRs() const {
        return rs;
    }
    int getRt() const {
        return rt;
    }
private:
    int rd;
    int rt;
    int rs;
    int immediate;
    string op;
    string insType;
    string label;
    int address;
    int number;
    bool isStall;
};

#endif	/* INSTRUCTION_H */

