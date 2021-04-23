#include <iostream>

#include "Register.hpp"
#include "util.hpp"

Register::Register() {
   bits = new char[32];
   for (size_t i = 0; i < 32; ++i) {
      bits[i] = '0';
   }
}

char *Register::readData() {
   return bits;
}

void Register::writeData(char *data, int numBits) {
   for (size_t i = 0; i < numBits; ++i) {
      bits[i] = data[i];
   }
}

int Register::getInt() {
   return binToDec(bits, 31, 0);
}

Register::~Register() {
   delete bits;
}
