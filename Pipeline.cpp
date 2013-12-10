/* 
 * File:   Pipeline.cpp
 * Author: Devin
 * 
 * Created on December 8, 2013, 6:15 PM
 */

#include "Pipeline.h"

Pipeline::Pipeline(Instruction ** i, int * r, int * m, string * l) {
    i_mem = i;
    registers = r;
    memory = m;
    loop_tag = l;
    IF1 = NULL;
    IF2 = NULL;
    ID = NULL;
    EX = NULL;
    MEM1 = NULL;
    MEM2 = NULL;
    MEM3 = NULL;
    WB = NULL;
}

Pipeline::Pipeline(const Pipeline& orig) {
}

Pipeline::~Pipeline() {
}

void Pipeline::output(int i) {
    cout << "cf" << i;
    if( WB != NULL ) {
        cout << " I" << WB->getNumber() << "-WB ";
    }
    if( MEM3 != NULL ) {
        cout << " I" << MEM3->getNumber() << "-MEM3 ";
    }
    if( MEM2 != NULL ) {
        cout << " I" << MEM2->getNumber() << "-MEM2 ";
    }
    if( MEM1 != NULL ) {
        cout << " I" << MEM1->getNumber() << "-MEM1 ";
    }
    if( EX != NULL ) {
        cout << " I" << EX->getNumber() << "-EX ";
    }
    if( ID != NULL ) {
        cout << " I" << ID->getNumber() << "-ID ";
    }
    if( IF2 != NULL ) {
        cout << " I" << IF2->getNumber() << "-IF2 ";
    }
    if( IF1 != NULL ) {
        cout << " I" << IF1->getNumber() << "-IF1 ";
    }
   
    
    cout << endl;
    
    if(empty()) {
        cout << "REGISTERS" << endl;
        for(int i = 0; i < 31; i++) {
            if(registers[i] != 0) {
                cout << "R" << i << " " << registers[i] << endl;
            }
        }
        for(int i = 0; i < 124; i++) {
            if(memory[i] != 0 ) {
                cout << i*8 << " " << memory[i] << endl;
            }
        }
    }
}
bool Pipeline::empty() {
    if(WB == NULL && MEM3 == NULL &&
       MEM2 == NULL && MEM1 == NULL &&
       EX == NULL && ID == NULL &&
       IF2 == NULL && IF1 == NULL )
    {
        return true;
    }
    else {
        return false;
    }
 }

void Pipeline::writeBack() {
    
    WB = MEM3;
        
        
    
}    
void Pipeline::memory3() {
    
        //MEM3 SHTUFF
        
    MEM3 = MEM2;
    
}

void Pipeline::memory2() {
        
    MEM2 = MEM1;
    
    
    
}

void Pipeline::memory1() {
   
        
    MEM1 = EX;
    
}

void Pipeline::execute() {     
    EX = ID;
    if(EX != NULL) {
        if(EX->getOp() == "DADD" && EX->getinsType() == "r-type") {
            registers[EX->getRd()] = registers[EX->getRs()] + registers[EX->getRt()];
        }
        else if(EX->getOp() == "SUB" && EX->getinsType() == "r-type") {
            registers[EX->getRd()] = registers[EX->getRs()] - registers[EX->getRt()];
        }
        else if(EX->getOp() == "DADD" && EX->getinsType() == "i-type") {
            registers[EX->getRd()] = registers[EX->getRs()] - EX->getImmediate();
        }
        else if(EX->getOp() == "SUB" && EX->getinsType() == "i-type") {
            registers[EX->getRd()] = registers[EX->getRs()] - EX->getImmediate();
        }
       else if(EX->getOp() == "LD") {
            address = EX->getImmediate() + registers[EX->getRs()];
            registers[EX->getRt()] = memory[address/8];
        }
        else if(EX->getOp() == "SD") {
            address = EX->getImmediate() + registers[EX->getRs()];
            memory[address/8] = registers[EX->getRt()];
        }
        else if(EX->getOp() == "BNEZ") { 
            if(registers[EX->getRs()] != 0) {
                EX = NULL;
            }
            
        }
        
    }
    
}

void Pipeline::decode() {

    ID = IF2;
    if( ID != NULL ) {
        if( ID->getOp() == "BNEZ") {
                for(int i = 1; i < 7; i++) {
                    if( ID->getLabel() == loop_tag[i] ) {
                        loop_address = i;
                    }
                }

        }
    }
    
}

void Pipeline::fetch2() {
            IF2 = IF1;
        
    
}

void Pipeline::fetch1(int &i) {
    if( i_mem[i] != NULL ) {
        IF1 = i_mem[i];
        IF1->setNumber(i);
        i++;
        
    }
    else{
        IF1 = NULL;
    }
   
}