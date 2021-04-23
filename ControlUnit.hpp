#ifndef CONTROLUNIT_HPP
#define CONTROLUNIT_HPP

class ControlUnit {
   private:
      char *controlFlags;
   public:
      ControlUnit(); // construtor Aloca o ponteiro para char controllFlag 
      ~ControlUnit(); // destrutor
      /* processCU
         Coloca os 6 primeiros bits na variável f bits 5-0 para UC, e os 6 ultimos em p bits 31-26 para UC.
         Após isso, Inicia as váriaveis de controle utilizando os vetores f e p
         retorna o vetor com as váriaveis de controle
      */
      char *processCU(char *bits);  
      /*processALUControl
         obtem os 6 bits 5-0 corresponte a funct, retorna a váriavel vetor inteiro out de tamanho 3
         out[2] corresponde ao resultado do AND do segundo bit UC e o OR do controlFlags na posição 8
         out[1] corresponde ao resultado do OR do NOT do terceirto bit UC e o not do controlFlags na posição 8
         out[0] corresponde ao resultado do OR do primeiro bit de UC com o quarto bit de UC eo AND do controlFlags na posição 8
      */
      char *processALUControl(char *bits); 
      char processJrControl(char *bits); // Retorna o bit de controle JR
};

#endif // !CONTROLUNIT_HPP
