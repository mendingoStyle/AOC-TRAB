#include <iostream>

#include "ControlUnit.hpp"
#include "util.hpp"

ControlUnit::ControlUnit() {
   controlFlags = new char[13](); 
}

char *ControlUnit::processCU(char *bits) {
   int f[6], op[6];
   for (int i = 5, j = 31; i >= 0; --i, --j) {
      f[i] = charToInt(bits[i]);
      op[i] = charToInt(bits[j]);
   }

   std::clog << "=> bits 31-26 para UC: ";
   showBits(bits, 31, 26);
   std::clog << "=> bits 5-0 para UC: ";
   showBits(bits, 5, 0);

   int rFormat = !op[5] & !op[4] & !op[3] & !op[2] & !op[1] & !op[0];
   int lw = op[5] & !op[4] & !op[3] & !op[2] & op[1] & op[0];
   int sw = op[5] & !op[4] & op[3] & !op[2] & op[1] & op[0];
   int beq = !op[5] & !op[4] & !op[3] & op[2] & !op[1] & !op[0];
   int bne = !op[5] & !op[4] & !op[3] & op[2] & !op[1] & op[0];
   int li = !op[5] & !op[4] & op[3] & op[2] & op[1] & op[0];
   int j = !op[5] & !op[4] & !op[3] & !op[2] & op[1] & !op[0];
   int jr = rFormat & !f[0] & !f[1] & !f[2] & f[3] & !f[4] & !f[5];

   std::clog << "=> instrucao do tipo:\n"
             << "  r:   " << rFormat << "\n"
             << "  lw:  " << lw  << "\n"
             << "  sw:  " << sw  << "\n"
             << "  beq: " << beq << "\n"
             << "  bne: " << bne << "\n"
             << "  li:  " << li  << "\n"
             << "  j:   " << j   << "\n"
             << "  jr:  " << jr  << "\n"; 

   controlFlags[0] = intToChar(rFormat);
   controlFlags[1] = intToChar(lw | sw);
   controlFlags[2] = intToChar(lw);
   controlFlags[3] = intToChar((rFormat | lw | li) & !jr);
   controlFlags[4] = intToChar(lw);
   controlFlags[5] = intToChar(sw);
   controlFlags[6] = intToChar(beq);
   controlFlags[7] = intToChar(rFormat);
   controlFlags[8] = intToChar(beq | bne);
   controlFlags[9] = intToChar(j);
   controlFlags[10] = intToChar(bne);
   controlFlags[11] = intToChar(li);

   std::clog << "=> flags de controle:\n"
             << "   RegDst:   " << controlFlags[0] << "\n"
             << "   ALUSrc:   " << controlFlags[1] << "\n"
             << "   MemToReg  " << controlFlags[2] << "\n"
             << "   RegWrite: " << controlFlags[3] << "\n"
             << "   MemRead:  " << controlFlags[4] << "\n"
             << "   MemWrite: " << controlFlags[5] << "\n"
             << "   Branch:   " << controlFlags[6] << "\n"
             << "   ALUOp1:   " << controlFlags[7] << "\n"
             << "   ALUOp0:   " << controlFlags[8] << "\n"
             << "   JUMP:     " << controlFlags[9] << "\n"
             << "   Bne:      " << controlFlags[10] << "\n"
             << "   Li:       " << controlFlags[11] << "\n";

   return controlFlags;
}

char *ControlUnit::processALUControl(char *bits) {
   //obtem os bits 6 bits 5-0 corresponte a funct
   int f[6];
   for (int i = 5; i >= 0; --i) {
      f[i] = charToInt(bits[i]);
   }

   std::clog << "=> bits func (5-0) p/ ALU Control: ";
   showBits(bits, 5, 0);

   char *out = new char[3];
   out[2] = intToChar(
      (charToInt(controlFlags[7]) & f[1]) | charToInt(controlFlags[8]));
   out[1] = intToChar(
      !charToInt(controlFlags[7]) | !f[2]);
   out[0] = intToChar(
      (f[0] | f[3]) & charToInt(controlFlags[7]));

   std::clog << "=> bits de saida da ALU Control (op): ";
   showBits(out, 2, 0);
   
   return out;
}

char ControlUnit::processJrControl(char *bits) {
   int f[6], op[6];
   for (int i = 5, j = 31; i >= 0; --i, --j) {
      f[i] = charToInt(bits[i]);
      op[i] = charToInt(bits[j]);
   }
   return intToChar(!op[0] & !op[1] & !op[2] & !op[3] & !op[4] & !op[5] & 
   !f[0] & !f[1] & !f[2] & f[3] & !f[4] & !f[5]);
}

ControlUnit::~ControlUnit() {
   delete controlFlags;
}
