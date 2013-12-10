/* 
 * File:   main.cpp
 * Author: Devin
 *
 * Created on December 7, 2013, 1:28 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include "Instruction.h"
#include "Pipeline.h"

using namespace std;

int loadReg(ifstream &infile, int reg[]);
int loadMem(ifstream &infile, int mem[]);
int loadIns(ifstream &infile, Instruction ** i_mem, string loop_label[]);
int getRegNumber(string regs);
void init(int reg[], int memory[]);

int main(int argc, char** argv) {
    Instruction** i_mem;
    Instruction * test;
    int cycle_count = 1;
    int ins_count = 1;
    string loop_label[50] = "";
    int reg[32];
    int memory[124];
    string input;
    string file(argv[1]);
    
    i_mem = new Instruction*[50];
    init(reg, memory);
    
   ifstream infile(file.c_str());

    infile >> input; 
    loadReg(infile, reg);
    loadMem(infile, memory);
    loadIns(infile, i_mem, loop_label);   
    infile.close();
    
    Pipeline p(i_mem, reg, memory, loop_label);
    

    
    do
    {
     p.writeBack();
     p.memory3();
     p.memory2();
     p.memory1();
     p.execute();
     p.decode();
     p.fetch2();
     p.fetch1(ins_count);
     p.output(cycle_count);
     
     cycle_count++;
    }  while(!p.empty());
      
}
int loadIns(ifstream &infile, Instruction ** i_mem, string loop_label[]){
    string input;
    string parse;


    int size;
    int index = 0;
    int immediateIndex;
    int immediateEnd;
    string rs_string;
    int rs_index;
    char immediate[4] = "";
    char rs[3] = "";
    
    while(!infile.eof()) {
        Instruction * i = new Instruction();
        getline(infile, input);
        stringstream ss;
        ss << input;
            while(ss >> parse) { 
                if( parse.find(":") != -1 ) {
                    loop_label[index] = parse;
                    ss >> parse;
                }
                if(parse == "LD" || parse == "SD" ) {
                        i->setOp( parse );
                        ss >> parse;
                        parse.pop_back();
                        i->setRt(getRegNumber(parse));
                        ss >> parse;
                        immediateIndex = parse.find_first_of("(");
                        immediateEnd = parse.find_first_of(")");
                        parse.copy(immediate, immediateIndex, 0);
                        parse.copy(rs, immediateEnd-immediateIndex - 1, immediateIndex+1);
                        i->setImmediate(atoi(immediate));
                        rs_string.assign(rs);
                        i->setRs(getRegNumber(rs_string));
                        i->setInsType("i-type");
                    }
                    if(parse == "DADD" || parse == "SUB") {
                        i->setOp( parse );
                        ss >> parse;
                        parse.pop_back();
                        i->setRd( getRegNumber(parse) );
                        ss >> parse;
                        parse.pop_back();
                        i->setRs( getRegNumber(parse) );
                        ss >> parse;
                        if(parse.find("#") == -1) {
                        i->setRt( getRegNumber(parse) );
                        i->setInsType("r-type");
                        }
                        else {
                        i->setImmediate(atoi(parse.erase(0,1).c_str()));
                        i->setInsType("i-type");
                             
                    }
                    }
                    if( parse == "BNEZ" ) {
                        i->setOp( parse );
                        ss >> parse;
                        parse.pop_back();
                        i->setRs( getRegNumber( parse ) );
                        ss >> parse;
                        i->setLabel( parse );
                    }

            }
        i->setNumber(index);
        i_mem[index] = i;
        index++;
    }
}

int loadReg(ifstream &infile, int reg[]){
    string input;
    int value;
    int index = 0;
    string regs;
    
    while(infile >> input) {
        if(input == "MEMORY") {
            return 0;
        }
        else {
            infile >> value;
            index = getRegNumber(input);
            reg[index] = value;
        }   
    }  
    return 0;
}

int loadMem(ifstream &infile, int mem[]) {
    string input;
    int memory;
    int value;
    
    while(infile >> input) {
        if(input == "CODE") {
            return 0;
        }
        else {
            infile >> value;
            memory = atoi(input.c_str());
            mem[memory/8] = value;
        }
    }
}
int getRegNumber(string reg)
{
    int index;
    if(reg.size() == 2) {
        index = reg[1] - '0';
    }
   else if(reg.size() == 3) {
        index = atoi(reg.substr(1,2).c_str());
   } 
   
   return index;
}

void init(int reg[], int memory[])
{
    for(int i = 0; i < 32; i++) {
        reg[i] = 0;
    }
    for(int i = 0; i < 124; i++) {
        memory[i] = 0;
    }
}