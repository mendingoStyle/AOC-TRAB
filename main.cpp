#include <vector>
#include <iostream>
#include <cstring>
#include "Cpu.hpp"
#include "util.hpp"

int main(int argc, char **argv) {
   if (argc == 2) {
      FILE *fp = fopen(argv[1], "r");
      if (!fp) {
         std::clog << "falha ao abrir arquivo!\n";
      } else {
         char *line = new char[50];
         std::vector<char *> instructions;
         while (fgets(line, 50, fp)) {
            if (strlen(line) >= 32) {
               char *bits = convertToBits(line);
               instructions.push_back(bits);
            }
         }
         delete line;

         Cpu *risc = new Cpu(instructions);
         risc->execute();
         delete risc;
         for (size_t i = 0; i < instructions.size(); ++i) {
            delete instructions[i];
         }
      }
    
   } else {
      std::cerr << "Argumentos invalidos!\n";
   }   

   return 0;
}
