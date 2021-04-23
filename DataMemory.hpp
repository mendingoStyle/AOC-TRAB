#ifndef DATAMEMORY_HPP
#define DATAMEMORY_HPP

class DataMemory {
   private:
      char *memory;
      char *address;
      char *writeData;
      char *readData;
      char memRead;
      char memWrite;
   
   public:
      DataMemory(); // construtor inicializa os ponteiros readData e o memory
      ~DataMemory(); // destrutor
      void set(char *adrs, char *wrtdata, char memRead, char memWrite); //carrega para memoria as variáveis o memory, writeData, memRead e o memWrite
      char *process(); // Se o memWrite for igual a "1", escreve o writeData na memory e mostra na tela
                       // Se o readData for igual a "1", escreve o readData na memory e mostra na tela
};

#endif // !DATAMEMORY_HPP
