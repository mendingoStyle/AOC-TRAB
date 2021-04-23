#include <iostream>
#include <cstring>

#include "Multiplex.hpp"
#include "util.hpp"

Multiplex::Multiplex(int numInputChannels) {
   order = numInputChannels;
}

void Multiplex::addInputs(char *input) {
   inputs.push_back(new char[32]);
   memcpy(inputs[inputs.size() - 1], input, 32);
}

void Multiplex::addSelects(char select) {
   selects.push_back(select);
}

void Multiplex::reset() {
   selects.clear();
   inputs.clear();
}

//so ta funcionando para mux 2->1
char *Multiplex::getOutput() {
   return inputs[charToInt(selects[0])];
}

Multiplex::~Multiplex() {
   for (size_t i = 0; i < inputs.size(); ++i) {
      delete inputs[i];
   }
}
