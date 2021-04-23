#ifndef REGISTER_HPP
#define REGISTER_HPP

class Register {
   private:
      char *bits;
   public:
      Register(); // construtor que inicializa os bits
      ~Register(); // destrutor que deleta os bits
      char *readData(); // Get o bits
      void writeData(char *data, int numBits); // Set o bit
      int getInt(); // retorna os bits em decimal
};

#endif // !REGISTER_HPP
