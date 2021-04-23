#include <iostream>
#include <cstring>

#include "PC.hpp"
#include "util.hpp"

PC::PC() {
   bits = new char[32];
   for (size_t i = 0; i < 32; ++i) {
      bits[i] = '0';
   }
}

char *PC::getBits() {
   return bits;
}

void PC::increment(char *inc) {
   char *res = adder(bits, inc);
   for (size_t i = 0; i < 32; ++i) {
      bits[i] = res[i];
   }
   delete res;
}

void PC::incrementBy4() {
   char four[] = "00100000000000000000000000000000";
   increment(four);
}

void PC::updatePc(char *newPC) {
   memcpy(bits, newPC, 32);
}

PC::~PC() {
   delete bits;
}
