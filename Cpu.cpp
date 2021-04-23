#include "Cpu.hpp"
#include "util.hpp"
#include <iostream>

Cpu::Cpu(std::vector<char *> instructions) {
   regFile = new RegisterFile();
   instructionMEM = new InstructionMEM(instructions);
   dataMemory = new DataMemory();
   cu = new ControlUnit();
   alu = new ALU();
   pc = new PC();

   for (int i = 0; i < 7; ++i) {
      //2-to-1 channel mux
      muxs.push_back(new Multiplex(2));
   }
}

void Cpu::execute() {
   while (executeAux());
}

bool Cpu::executeAux() {
   char *instruction = instructionMEM->readAddress(pc->getBits());
   if (instruction == nullptr) {
      return false;
   }

   std::clog << "\n#########[INICIO DO PROCESSAMENTO DE INSTRUCAO]#########\n"
             << "\n=> conteudo de PC: ";
   showBits(pc->getBits(), 31, 0);
   std::clog << "=> instrucao referenciada por PC: ";
   showBits(instruction, 31, 0);

   char *flagsCU = cu->processCU(instruction);

   Register *reg1 = regFile->readRegister(instruction, 25, 21);
   Register *reg2 = regFile->readRegister(instruction, 20, 16);

   std::clog << "=> readRegister1 (25-21): "; showBits(instruction, 25, 21);
   std::clog << "=> conteudo de Register1: "; showBits(reg1->readData(), 31, 0);
   std::clog << "=> readRegister2 (20-16): "; showBits(instruction, 20, 16);
   std::clog << "=> conteudo de Register2: "; showBits(reg2->readData(), 31, 0);

   //datapath to regDst Mux:
   //mux[0] is a 2-to-1 channel multiplex
   //select between 20-16 and 15-11 where regDst is the switch selector
   char *subBits20_16 = subBits(instruction, 20, 16);
   char *subBits15_11 = subBits(instruction, 15, 11);
   muxs[0]->reset();
   muxs[0]->addInputs(subBits20_16);
   muxs[0]->addInputs(subBits15_11);
   muxs[0]->addSelects(flagsCU[0]);
   char *adrWriteReg = muxs[0]->getOutput();

   std::clog << "=> mux p/ regDst:\n"
             << " entradas:\n"
             << "   "; showBits(instruction, 20, 16);
   std::clog << "   "; showBits(instruction, 15, 11);
   std::clog << " selects (chave p/ switch):\n"
             << "   regDst: " << flagsCU[0] << "\n"
             << " saida selecionada:\n"
             << "   "; showBits(adrWriteReg, 4, 0);

   char *inputConst = subBits(instruction, 15, 0);
   char *signExtendConst = signExtend(inputConst, 16);

   std::clog << "=> constante (15-0):       ";
   showBits(inputConst, 15, 0);
   std::clog << "=> contante sign-extended: ";
   showBits(signExtendConst, 31, 0);

   //datapath to ALUSrc
   muxs[1]->reset();
   muxs[1]->addInputs(reg2->readData());
   muxs[1]->addInputs(signExtendConst);
   muxs[1]->addSelects(flagsCU[1]);
   char *input2ALU = muxs[1]->getOutput();

   std::clog << "=> mux p/ ALUSrc:\n"
             << " entradas:\n"
             << "   "; showBits(reg2->readData(), 31, 0);
   std::clog << "   "; showBits(signExtendConst, 31, 0);
   std::clog << " selects (chave p/ switch):\n"
             << "   ALUSrc: " << flagsCU[1] << "\n"
             << " saida selecionada:\n"
             << "   "; showBits(input2ALU, 31, 0);

   //ALU INPUTS
   char *op = cu->processALUControl(instruction);
   alu->setALU(reg1->readData(), input2ALU, 
     op);
   
   char *aluResult = alu->execute();
   std::clog << "=> ALU result: "; showBits(aluResult, 31, 0);

   dataMemory->set(aluResult, reg2->readData(), flagsCU[4], flagsCU[5]);
   char *readData = dataMemory->process();
   std::clog << "=> read data: "; showBits(readData, 31, 0);
   
   //datapath to memToReg
   muxs[2]->reset();
   muxs[2]->addInputs(aluResult);
   muxs[2]->addInputs(readData);
   muxs[2]->addSelects(flagsCU[2]);
   char *outputMux2 = muxs[2]->getOutput();

   std::clog << "=> mux p/ memToReg:\n"
             << " entradas:\n"
             << "   "; showBits(aluResult, 31, 0);
   std::clog << "   "; showBits(readData, 31, 0);
   std::clog << " selects (chave p/ switch):\n"
             << "   memToReg: " << flagsCU[2] << "\n"
             << " saida selecionada:\n"
             << "   "; showBits(outputMux2, 31, 0);

   //datapath to li
   muxs[5]->reset();
   muxs[5]->addInputs(outputMux2);
   muxs[5]->addInputs(signExtendConst);
   muxs[5]->addSelects(flagsCU[11]);
   char *writeData = muxs[5]->getOutput();

   std::clog << "=> mux p/ li:\n"
             << " entradas:\n"
             << "   "; showBits(outputMux2, 31, 0);
   std::clog << "   "; showBits(signExtendConst, 31, 0);
   std::clog << " selects (chave p/ switch):\n"
             << "   liFlag: " << flagsCU[11] << "\n"
             << " saida selecionada:\n"
             << "   "; showBits(writeData, 31, 0);

   //regWrite
   if (flagsCU[3] == '1') {
      regFile->writeRegister(adrWriteReg, writeData, flagsCU[11]);
      std::clog << "=> WriteData (Reg): reg[" << binToDec(adrWriteReg, 4, 0) 
                << "]" << " = "; 
      showBits(regFile->readRegister(adrWriteReg, 4, 0)->readData(), 31, 0);
   } else {
      std::clog << "=> como regWrite = 0 n houve escrita em registrador\n";
   }

   pc->incrementBy4();
   char *offset = shiftLeft(signExtendConst, 31, 0, 2);
   char *branchPC = adder(pc->getBits(), offset);
   std::clog << "=> processamento de (PC+4) + (const*4):\n";
   std::clog << "  PC+4:     "; showBits(pc->getBits(), 31, 0);
   std::clog << "  offset*4: "; showBits(offset, 31, 0);
   std::clog << "  adder:    "; showBits(branchPC, 31, 0);

   int zero = charToInt(alu->getZero());
   int firstAnd = charToInt(flagsCU[6]) & zero;
   int secAnd = charToInt(flagsCU[10]) & !zero;
   int orResult = firstAnd | secAnd; 

   std::clog << "=> processamento de (branch AND zero) OR (bne AND !zero):\n";
   std::clog << "  (" << flagsCU[6] << " AND " << zero << ") OR"
             << " (" << flagsCU[10] << " AND !" << zero << ")"
             << " = " << intToChar(orResult) << "\n"; 

   muxs[3]->reset();
   muxs[3]->addInputs(pc->getBits());
   muxs[3]->addInputs(branchPC);
   muxs[3]->addSelects(intToChar(orResult));
   char *outputMux3 = muxs[3]->getOutput();

   std::clog << "=> mux p/ branch:\n"
             << " entradas:\n"
             << "   "; showBits(pc->getBits(), 31, 0);
   std::clog << "   "; showBits(branchPC, 31, 0);
   std::clog << " selects (chave p/ switch):\n"
             << "   (branch AND zero) OR (bne AND !zero): " << orResult << "\n"
             << " saida selecionada:\n"
             << "   "; showBits(outputMux3, 31, 0);

   char *jmpAddress = shiftLeft(instruction, 31, 0, 2);
   std::clog << "=> instrucao (25-0):   "; showBits(instruction, 25, 0);
   std::clog << "=> shift left 2:       "; showBits(jmpAddress, 27, 0);

   concat(jmpAddress, instruction, 31, 28, 31, 28);
   std::clog << "=> jump adress (31-0): "; showBits(jmpAddress, 31, 0);

   muxs[4]->reset();
   muxs[4]->addInputs(outputMux3);
   muxs[4]->addInputs(jmpAddress);
   muxs[4]->addSelects(flagsCU[9]);
   char *outputMux4 = muxs[4]->getOutput();

   std::clog << "=> mux p/ jump:\n"
             << " entradas:\n"
             << "   "; showBits(outputMux3, 31, 0);
   std::clog << "   "; showBits(jmpAddress, 31, 0);
   std::clog << " selects (chave p/ switch):\n"
             << "   jump: " << flagsCU[9] << "\n"
             << " saida selecionada:\n"
             << "   "; showBits(outputMux4, 31, 0);

   char isJr = cu->processJrControl(instruction);

   muxs[6]->reset();
   muxs[6]->addInputs(outputMux4);
   muxs[6]->addInputs(reg1->readData());
   muxs[6]->addSelects(isJr);
   char *outputMux6 = muxs[6]->getOutput();

   std::clog << "=> mux p/ jumpReg:\n"
             << " entradas:\n"
             << "   "; showBits(outputMux4, 31, 0);
   std::clog << "   "; showBits(reg1->readData(), 31, 0);
   std::clog << " selects (chave p/ switch):\n"
             << "   jumpReg: " << isJr << "\n"
             << " saida selecionada:\n"
             << "   "; showBits(outputMux6, 31, 0);

   pc->updatePc(outputMux6);
   std::clog << "=> logo, PC agora sera: "; showBits(pc->getBits(), 31, 0);

   delete instruction;
   delete subBits20_16;
   delete subBits15_11;
   delete inputConst;
   delete op;
   delete signExtendConst;
   delete branchPC;
   delete offset;
   delete jmpAddress;

   return true;
}

Cpu::~Cpu() {
   delete regFile;
   delete instructionMEM;
   delete dataMemory;
   delete cu;
   delete alu;
   delete pc;
   for (size_t i = 0; i < muxs.size(); ++i) {
      delete muxs[i];
   }
}
