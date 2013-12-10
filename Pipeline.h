/* 
 * File:   Pipeline.h
 * Author: Devin
 *
 * Created on December 8, 2013, 6:15 PM
 */

#ifndef PIPELINE_H
#define	PIPELINE_H
#include "Instruction.h"
#include <iostream>
using namespace std;

class Pipeline {
public:
    Pipeline(Instruction ** i, int * r, int * m, string * l);
    Pipeline(const Pipeline& orig);
    virtual ~Pipeline();
    void writeBack();
    void memory1();
    void memory2();
    void memory3();
    int execute();
    int decode();
    int fetch1(int &i);
    int fetch2();
    void output(int i);
    bool empty();
    struct {
    Instruction * EXS;
    Instruction * IDS;
    Instruction * IF2S;
    Instruction * IF1S;
        
    } save;
private:
    Instruction * WB;
    Instruction * MEM1;
    Instruction * MEM2;
    Instruction * MEM3;
    Instruction * EX;
    Instruction * ID;
    Instruction * IF2;
    Instruction * IF1;
    Instruction ** i_mem;
    int * registers;
    int * memory;
    int address;
    int loop_address;
    string * loop_tag;
    bool stall;
    bool resume;
    

};

#endif	/* PIPELINE_H */

