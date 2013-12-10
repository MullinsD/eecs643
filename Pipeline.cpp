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
    stall = false;
    resume = false;
    count = 0;
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

    if(stall)
    {
        count++;
        if(count == 2)
        {
            stall = false;
            resume = true;
        }
    }



    
}

void Pipeline::memory2() {
        
    MEM2 = MEM1;
    
    
    
}

void Pipeline::memory1() {
   
       
    MEM1 = EX;

    
}

int Pipeline::execute() {    
    if( MEM1 != NULL  )
    {   
        if(MEM1->getOp() == "LD" && ( MEM1->getRt() == ID->getRs()
                || MEM1->getRt() == ID->getRt() ) ) {   
            stall = true;
        }
     }   
     if(stall) {
         if(count == 0)
            {
                save.EXS = ID;
                EX = NULL;
   
            }
            if(count == 1)
            {
                save.EXS = save.EXS;
                EX = NULL;
            }

            return 0;
     }
  
    if(resume) {
          EX = save.EXS;
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
          return 0;
      }
    EX = ID;
    if(EX != NULL) {
        if(EX->getOp() == "DADD" && EX->getinsType() == "r-type") {
            registers[EX->getRd()] = registers[EX->getRs()] + registers[EX->getRt()];
        }
        else if(EX->getOp() == "SUB" && EX->getinsType() == "r-type") {
            registers[EX->getRd()] = registers[EX->getRs()] - registers[EX->getRt()];
        }
        else if(EX->getOp() == "DADD" && EX->getinsType() == "i-type") {
            registers[EX->getRd()] = registers[EX->getRs()] + EX->getImmediate();
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

int Pipeline::decode() {
        if(stall ) {
            if(count == 0)
            {
                save.IDS = IF2;
                ID = NULL;
            }
            if(count == 1)
            {
                save.IDS = save.IDS;
                ID = NULL;
            }
            return 0;
        }
    if(resume) {
          ID = save.IDS;
          return 0;
      }
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

int Pipeline::fetch2() {
    if(stall )
    {
        if(count == 0)
            {
                save.IF2S = IF1;
                IF2 = NULL;
            }
            if(count == 1)
            {
                save.IF2S = save.IF2S;
                IF2 = NULL;
            }
        return 0;
    }  
    if(resume) {
          IF2 = save.IF2S;
          return 0;
      }
    
    IF2 = IF1;
        
    
}

int Pipeline::fetch1(int &i) {

   if(stall)
    {
       if(count == 0 && i_mem[i] != NULL)
            {
            save.IF1S = i_mem[i];
            save.IF1S->setNumber(i);
            IF1 = NULL;
            }
            if(count == 1)
            {
                save.IF1S = save.IF1S;
                IF1 = NULL;
            }

       return 0;
    }
   if(resume)
   {
       IF1 = save.IF1S;
       resume = false;
       count = 0;
       return 0;
   }
   if( i_mem[i] != NULL ) {
        IF1 = i_mem[i];
        IF1->setNumber(i);
        i++;
    }
    else{
        IF1 = NULL;
    }
}   
