#ifndef PC_HPP
#define PC_HPP

class PC {
   private:
      char *bits; 
   public:
      PC(); // construtor inicializa os bits com 0
      ~PC(); // destrutor
      char *getBits(); // retorna a váriavel bits
      void increment(char *inc); // faz a soma de dois números binarios incluindo o bit carry produz um novo vetor de bits  
                                 // e coloca o resultado em bits
      void incrementBy4();       // incrementa o bits por mais 4
      void updatePc(char *newPC);// Coloca a váriavel newPC em bits
};

#endif // !PC_HPP
