#ifndef REGISTERFILE_HPP
#define REGISTERFILE_HPP

#include <vector>

#include "Register.hpp"

class RegisterFile {
   private:
      std::vector<Register *> registers; // vetor para o Register
   public:
      RegisterFile(); // Construtor do RegisterFile, inicia 1 registerFile com 32 numeros binario com 0
      ~RegisterFile(); // Destrutor do Register File
      Register *readRegister(char *bits, int end, int start); // Retorna um número binario
      void writeRegister(char *adrWriteReg, char *writeData, char li) ; // Escreve um número binário no Registro com 32 bits ou 16; 
};

#endif // !REGISTERFILE_HPP
