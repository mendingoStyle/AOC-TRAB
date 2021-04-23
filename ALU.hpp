#ifndef ALU_HPP
#define ALU_HPP

class ALU {
   private:
      char *bits1;
      char *bits2;
      char zero;
      char *ctrlFlag;
      char *result;

      char *execAND();
      char *execOR();
      char *execADD();
      char *execSUB();

   public:
      ALU(); // construtor inicializa o ponteiro de result com 32 bits "0000000000..00" 
      ALU(char *bits1, char *bits2, char *ctrlFlag); 
      // inicializa os ponteiros bits1, bits2, ctrlFlag, zero = 0 e result com 32 bits "0000000000..00"
      ~ALU(); // Destrutor
      void setALU(char *bits1, char *bits2, char *ctrlFlag); // Seta as váriaveis bits1, bits2, e ctrlFlag;
      char getZero() const; //retorna zero
      /* 
         Verifica as variaveis de controle e executa AND || SUB || OR || ADD
      */
      char *execute();
};

#endif // !ALU_HPP
