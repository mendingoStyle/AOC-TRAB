#include <iostream>

#include "ALU.hpp"
#include "util.hpp"

ALU::ALU() {
   result = new char[32];
   for (size_t i = 0; i < 32; ++i) {
      result[i] = '0';
   }
   zero = '0';
}

ALU::ALU(char *bits1, char *bits2, char *ctrlFlag) {
   this->bits1 = bits1;
   this->bits2 = bits2;
   this->ctrlFlag = ctrlFlag;
   result = new char[32];
   for (size_t i = 0; i < 32; ++i) {
      result[i] = '0';
   }
   zero = '0';
}

void ALU::setALU(char *bits1, char *bits2, char *ctrlFlag) {
   std::clog << "=> entrada1 ALU: "; showBits(bits1, 31, 0);
   std::clog << "=> entrada2 ALU: "; showBits(bits2, 31, 0);

   this->bits1 = bits1;
   this->bits2 = bits2;
   this->ctrlFlag = ctrlFlag; 
   //zero = '0';
}

char *ALU::execute() {
   if (ctrlFlag[0] == ctrlFlag[1] && ctrlFlag[1] == ctrlFlag[2]
     && ctrlFlag[2] == '0') {
        return execAND();
   } else if (ctrlFlag[0] != ctrlFlag[1] && ctrlFlag[1] == ctrlFlag[2]
     && ctrlFlag[0] == '1') {
        return execOR();
   } else if (ctrlFlag[0] == ctrlFlag[2] && ctrlFlag[0] != ctrlFlag[1]
     && ctrlFlag[2] == '0') {
        return execADD();
   } else if (ctrlFlag[0] != ctrlFlag[1] && ctrlFlag[1] == ctrlFlag[2]
     && ctrlFlag[0] == '0') {
        return execSUB();
   } else if (ctrlFlag[0] == ctrlFlag[1] && ctrlFlag[1] == ctrlFlag[2]
     && ctrlFlag[0] == '1') {
        //set on less than
   }
   return result;
}

char *ALU::execAND() {
   std::clog << "=> AND executada\n";
   for (size_t i = 0; i < 32; ++i) {
      result[i] = intToChar(charToInt(bits1[i]) & charToInt(bits2[i]));
   }
   return result;
}

char *ALU::execOR() {
   std::clog << "=> OR executada\n";
   for (size_t i = 0; i < 32; ++i) {
      result[i] = intToChar(charToInt(bits1[i]) | charToInt(bits2[i]));
   }
   return result;
}

char *ALU::execADD() {
   std::clog << "=> ADD executada\n";
   char *tmp = adder(bits1, bits2);
   for (size_t i = 0; i < 32; ++i) {
      result[i] = tmp[i];
   }
   delete tmp;
   return result;
}

char *ALU::execSUB() {
   zero = sub(bits1, bits2, result);
   std::clog << "=> SUB executada\n"
             << "=> zero flag: " << zero << "\n";
   return result;
}

char ALU::getZero() const {
   return zero;
}

ALU::~ALU() {
   delete result;
}
