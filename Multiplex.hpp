#ifndef MULTIPLEX_HPP
#define MULTIPLEX_HPP

#include <vector>

class Multiplex {
   private:
      std::vector<char> selects;
      std::vector<char *> inputs;
      int order;
   
   public:
      Multiplex(int=2); // Construtor inicia a variável ordem com 2
      ~Multiplex(); // Destrutor
      void addInputs(char *input); // coloca no vetor de inputs um char
      void addSelects(char select); // Adiciona o Char Select no vetor
      void reset(); // reseta os vetores
      char *getOutput(); // pega o conteudo do vetor na posição selects[0]
};

#endif // !MULTIPLEX_HPP
