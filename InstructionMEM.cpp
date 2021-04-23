#include <iostream>

#include "InstructionMEM.hpp"
#include "util.hpp"

InstructionMEM::InstructionMEM(std::vector<char *> instructions) {
   memSize = instructions.size() * 32;
   memory = new char[memSize];
   for (size_t i = 0; i < instructions.size(); ++i) {
      for (size_t j = 0; j < 32; ++j) {
         memory[i * 32 + j] = instructions[i][j];
      }
   }
}

int InstructionMEM::getMemSize() const {
   return memSize;
}

char *InstructionMEM::readAddress(char *bitsPC) {
   int firstIndex = binToDec(bitsPC, 31, 0) * 8;
   int lastIndex = firstIndex + 31;

   if (lastIndex >= memSize) return nullptr;

   char *instruction = new char[32];
   for (size_t i = firstIndex, j = 0; i <= lastIndex; ++i, ++j) {
      instruction[j] = memory[i];
   }
   return instruction;
}

InstructionMEM::~InstructionMEM() {
   delete memory;
}
