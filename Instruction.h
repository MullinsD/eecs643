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
    void setImmediate(int immediate) {
        this->immediate = immediate;
    }
    void setInsType(string insType) {
        this->insType = insType;
    }
    void setOp(string op) {
        this->op = op;
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
    int getImmediate() const {
        return immediate;
    }
    string getinsType() const {
        return insType;
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
    int rs;
    int rd;
    int rt;
    int immediate;
    string op;
    string insType;
    int address;
};

#endif	/* INSTRUCTION_H */

