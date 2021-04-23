#include "RegisterFile.hpp"
#include "util.hpp"

RegisterFile::RegisterFile() {
   for (int i = 0; i < 32; ++i) {
      registers.push_back(new Register());
   }
}

Register *RegisterFile::readRegister(char *bits, int end, int start) {
   return registers[binToDec(bits, end, start)];
}

void RegisterFile::writeRegister(char *adrWriteReg, char *writeData, char li) {
   int indexReg = binToDec(adrWriteReg, 4, 0);
   if (li == '1') {
      registers[indexReg]->writeData(writeData, 16);
   } else {
      registers[indexReg]->writeData(writeData, 32);
   }
}

RegisterFile::~RegisterFile() {
   for (size_t i = 0; i < registers.size(); ++i) {
      delete registers[i];
   }
}
