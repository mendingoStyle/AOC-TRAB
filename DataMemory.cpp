#include <iostream>

#include "DataMemory.hpp"
#include "util.hpp"

DataMemory::DataMemory() {
   readData = new char[32];
   for (size_t i = 0; i < 32; ++i) {
      readData[i] = '0';
   }
   memory = new char[100000];
   for (size_t i = 0; i < 100000; ++i) {
      memory[i] = '0';
   }
}

void DataMemory::set(char *adrs, char *wrtdata, char memRead, char memWrite) {
   this->address = adrs;
   this->writeData = wrtdata;
   this->memRead = memRead;
   this->memWrite = memWrite;

   std::clog << "=> data memory address: "; showBits(address, 31, 0);
   std::clog << "=> writeData (Data Memory): "; showBits(wrtdata, 31, 0);
}

char *DataMemory::process() {
   if (memWrite == '1') {
      int i = binToDec(address, 31, 0) * 8;
      std::clog << "=> escrita: mem[" << i/8 << "] = ";
      for (size_t j = 0; j < 32; ++j, ++i) {
         memory[i] = writeData[j];
      }
      showBits(writeData, 31, 0);
   } else {
      std::clog << "=> nao houve escrita na memoria\n";
   }
   if (memRead == '1') {
      //lembrar desse * 8
      int i = binToDec(address, 31, 0) * 8;
      std::clog << "=> leitura: mem[" << i/8 << "]\n";
      for (size_t j = 0; j < 32; ++j, ++i) {
         readData[j] = memory[i];
      } 
   } else {
      std::clog << "=> nao houve leitura da memoria\n";
   }
   return readData;
}

DataMemory::~DataMemory() {
   delete readData;
   delete memory;
}
