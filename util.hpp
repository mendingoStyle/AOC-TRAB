#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>

int binToDec(char *bits, int end, int start); //transforma de binario para decimal 
int charToInt(char c); //Char para inteiro
char intToChar(int i); //Inteiro para CHAR
char *subBits(char *bits, int end, int start) ; // Cria um novo ponteiro char para represebtar um numero em binário e passa os bits
char *signExtend(char *bits, int length) ; // Passa os bits com sinal para um ponteiro char
char *adder(char *bits1, char *bits2); // faz a soma de dois números binarios incluindo o bit carry produz um novo vetor de bits  
char sub(char *bits1, char *bits2, char *result); // Faz a subtração de nois numeros em binário o resultado é um char em result
char *shiftLeft(char *bits, int end, int start, int d); // Faz o shitf left de um número binario
void concat(char *dst, char *src, int end1, int start1, int end2, int start2) ; // concatena dois char, o resultado será gravado no primeiro parametro
char *convertToBits(char *str); // converte um número decimal em binario
char *complementBy2(char *bits); // Efetua a conversão para Complemento de 2
void showBits(char *bits, int end, int start) ; // printa os bits na tela

#endif // !UTIL_HPP
