#ifndef CPU_HPP
#define CPU_HPP

#include <vector>

#include "DataMemory.hpp"
#include "RegisterFile.hpp"
#include "InstructionMEM.hpp"
#include "ControlUnit.hpp"
#include "Multiplex.hpp"
#include "ALU.hpp"
#include "PC.hpp"

class Cpu {
   private:
      RegisterFile *regFile; // Contém 32 Registros de memória inicialmente escritos com '00000..00'
      InstructionMEM *instructionMEM; // Carrega as instruções
      DataMemory *dataMemory; // Carrega para memória as variáveis de memoria
      ControlUnit *cu; // Inicializa as variáveis de controle
      ALU *alu; // executa AND || SUB || OR || ADD
      std::vector<Multiplex *> muxs; // Vetor de ponteiros que contem os vetores de select e input 
      PC *pc; // 

      bool executeAux();
   public:
      Cpu(std::vector<char *>); // Inicializa as váriaveis
      void execute();
      ~Cpu();
};

#endif // !CPU_HPP
