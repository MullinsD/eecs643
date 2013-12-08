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

using namespace std;

int loadReg(ifstream &infile, int reg[]);
int loadMem(ifstream &infile, int mem[]);
int loadIns(ifstream &infile, Instruction ** i_mem);
int getRegNumber(string regs);
void init(int reg[], int memory[]);

int main(int argc, char** argv) {
    Instruction** i_mem;
    Instruction * test;
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
    loadIns(infile, i_mem);
    
    infile.close();
    cout << "Rt: " << i_mem[0]->getRt() << " Rs: " << i_mem[0]->getRs() << " Index: " << i_mem[0]->getImmediate() << endl;


}
int loadIns(ifstream &infile, Instruction ** i_mem){
    string input;
    string parse;

    Instruction * i;
    int size;
    int index = 0;
    int immediateIndex;
    int immediateEnd;
    string rs_string;
    int rs_index;
    char immediate[4] = "";
    char rs[3] = "";
    
    while(!infile.eof()) {
        getline(infile, input);
        stringstream ss;
        ss << input;
        while(ss >> parse) {  
            if(strstr(parse.c_str(), ":")) {

            }
            else {
                if(parse == "LD" || parse == "SD" ) {
                    ss >> parse;
                    i->setRt(getRegNumber(parse));
                    ss >> parse;
                    immediateIndex = parse.find_first_of("(");
                    immediateEnd = parse.find_first_of(")");
                    parse.copy(immediate, immediateIndex, 0);
                    parse.copy(rs, immediateEnd-immediateIndex - 1, immediateIndex+1);
       
                    i->setImmediate(atoi(immediate));
                    rs_string.assign(rs);
                    rs_index = getRegNumber(rs_string);
                    cout << rs_index << endl;
                    i->setRs(rs_index);
                }
            }
        }
       // i_mem[index] = i;
        index++;
    } 
    size = index + 1;
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