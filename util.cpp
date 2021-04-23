#include <iostream>

#include "util.hpp"

int binToDec(char *bits, int end, int start) {
   int base = 1;
   int dec = 0;
   for (int i = start; i <= end; ++i, base *= 2) {
      dec += charToInt(bits[i]) * base;
   }
   return dec;
}

int charToInt(char c) {
   return c - '0';
}

char intToChar(int i) {
   return i + '0';
}

char *subBits(char *bits, int end, int start) {
   char *sub = new char[end - start + 1];
   for (int i = end; i >= start; --i) {
      sub[i - start] = bits[i];
   }
   return sub;
}

char *signExtend(char *bits, int length) {
   char *bitsExtended = new char[32];
   for (int i = 0; i < length; ++i) {
      bitsExtended[i] = bits[i];
   }
   char signal = bitsExtended[length - 1];
   for (int i = length; i < 32; ++i) {
      bitsExtended[i] = signal;
   }
   return bitsExtended;
}

char *adder(char *bits1, char *bits2) {
   char *result = new char[32];
   int carry = 0;
   for (size_t i = 0; i < 32; ++i) {
      int bit1 = charToInt(bits1[i]);
      int bit2 = charToInt(bits2[i]);
      int tmp = (bit1 ^ bit2 ^ carry);
      result[i] = intToChar(tmp);
      carry = (bit1 & bit2) | (bit2 & carry) | (bit1 & carry);
   }
   return result;
}

char sub(char *bits1, char *bits2, char *result) {
   bits2 = complementBy2(bits2);
   int carry = 0;
   int zero  = 1; 
   for (size_t i = 0; i < 32; ++i) {
      int bit1 = charToInt(bits1[i]);
      int bit2 = charToInt(bits2[i]);
      int tmp = (bit1 ^ bit2 ^ carry);
      zero = !tmp & zero;
      result[i] = intToChar(tmp);
      carry = (bit1 & bit2) | (bit2 & carry) | (bit1 & carry);
   }
   return intToChar(zero);
}

char *shiftLeft(char *bits, int end, int start, int d) {
   char *str = new char[end - start + 1];
   for (int i = end; i >= start; --i) {
      if (i - d < start) {
         str[i] = '0';
      } else {
         str[i] = bits[i - d];
      }
   }
   return str;
}

void concat(char *dst, char *src, int end1, int start1, int end2, int start2) {
   for (int i = end1, j = end2; i >= start1; --i, --j) {
      dst[i] = src[j];
   }
}

char *convertToBits(char *str) {
   char *bits = new char[32];
   for (size_t i = 0, j = 31; i < 32; ++i, --j) {
      bits[i] = str[j];
   }
   return bits;
}

char *complementBy2(char *bits) {
   for (size_t i = 0; i < 32; ++i) {
      bits[i] = intToChar(!charToInt(bits[i]));
   }
   char one[] = "10000000000000000000000000000000";
   return adder(bits, one);
}

void showBits(char *bits, int end, int start) {
   for (int i = end; i >= start; --i) {
      std::clog << bits[i];
   }
   std::clog << "\n";
}
