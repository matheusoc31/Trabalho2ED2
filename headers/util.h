#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include "GastoDeputado.h"

int randomInt(int from, int to);
void swapPtr(int *a, int *b);
void printVec(int *vec, int vecSize);
int minVec(int *vec, int vecSize);
int minVecPos(int *vec, int vecSize, unsigned int *comp, unsigned int *copias);
double minVec(double *vec, int vecSize);
int maxVec(int *vec, int vecSize);
void swapPtr(int *a, int *b);
void swapPtrDep(GastoDeputado *a, GastoDeputado *b);
bool ordenado(int *vec, int vecSize);
bool ordenado(GastoDeputado *vec, int vecSize);
void ordena(int *vec, int vecSize, unsigned int *comp, unsigned int *copias);
void countingSort(int *vec, int vecSize, unsigned int *comp, unsigned int *copias);

#endif // UTIL_H_INCLUDED
