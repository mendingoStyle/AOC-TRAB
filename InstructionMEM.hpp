#ifndef INSTRUCTIONMEM_HPP
#define INSTRUCTIONMEM_HPP

#include <vector>

class InstructionMEM {
   private:
      char *memory; // passa para a memoria o conteudo do vetor de instruções
      int memSize; // inicializa o memSize com o numero de instruções vezes 32

   public:
      InstructionMEM(std::vector<char *>); // construtor do InstructionMEM
      int getMemSize() const; // retorna o memSize
      char *readAddress(char *); //  retorna a instrução
      ~InstructionMEM(); // Destrutor do InstructionMEM
};

#endif // !INSTRUCTIONMEM_HPP
