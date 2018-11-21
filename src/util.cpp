#include "../headers/libraries.h"


int randomInt(int from, int to) {
    return rand()%(to - from + 1) + from;
} /// end randomInt();


void printVec(int *vec, int vecSize) {
    for(int i = 0; i < vecSize; i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << endl;
} /// end printVec();


int minVec(int *vec, int vecSize) {
    int m = vec[0];
    for(int i=1; i < vecSize; i++) {
        if(vec[i] < m)
            m = vec[i];
    }
    return m;
} /// end minVec();


int minVecPos(int *vec, int vecSize, unsigned int *comp, unsigned int *copias) {
    int m = 0;
    for(int i=1; i < vecSize; i++) {
        (*comp) += 1;
        if(vec[i] < vec[m])
            m = i;
    }
    return m;
} /// end minVecPos();


double minVec(double *vec, int vecSize) {
    double m = vec[0];
    for(int i=1; i < vecSize; i++) {
        if(vec[i] < m)
            m = vec[i];
    }
    return m;
} /// end minVec();



int maxVec(int *vec, int vecSize) {
    int m = vec[0];
    for(int i=1; i < vecSize; i++) {
        if(vec[i] > m)
            m = vec[i];
    }
    return m;
} /// end maxVec();


void swapPtr(int *a, int *b) {
    int aux = *a;
    *a = *b;
    *b = aux;
} /// end swapPtr();


void swapPtrDep(GastoDeputado *a, GastoDeputado *b) {
    GastoDeputado aux = *a;
    *a = *b;
    *b = aux;
} /// end swapPtrDep();


bool ordenado(int *vec, int vecSize) {
    for(int i = 1; i < vecSize; i++) {
        if(vec[i] < vec[i-1])
            return false;
    }
    return true;
} /// end ordenado();


bool ordenado(GastoDeputado *vec, int vecSize) {
    for(int i = 1; i < vecSize; i++) {
        if(vec[i].getDeputyId() < vec[i-1].getDeputyId())
            return false;
    }
    return true;
} /// end ordenado();


void ordena(int *vec, int vecSize, unsigned int *comp, unsigned  int *copias) { ///
    countingSort(vec, vecSize, comp, copias);
} /// end ordena();


void countingSort(int *vec, int vecSize, unsigned int *comp, unsigned int *copias) { // versão modificada do algoritmo countingSort
    int minRange, maxRange, range, i;
    minRange = minVec(vec, vecSize); // vecSize operações (O(n))
    maxRange = maxVec(vec, vecSize); // vecSize operações (O(n))

    range = maxRange - minRange + 1;

    int *countVec = new int[range](); // inicializando com 0
    int *output = new int[vecSize];

    for(i = 0; i < vecSize; i++) {
        ++countVec[vec[i]-minRange];
    }

    for(i = 1; i < range; i++) {
        countVec[i] += countVec[i-1];
    }

    for (i = vecSize-1; i >= 0; i--) { // montando o vetor output, na ordem correta
        output[countVec[vec[i]-minRange]-1] = vec[i];
        (*copias) += 1;
        --countVec[vec[i]-minRange];
    }

    for(i = 0; i < vecSize; i++) { // copiando para vetor vec na ordem correta
        vec[i] = output[i];
        (*copias) += 1;
    }

    delete [] countVec; // Liberando memória
    delete [] output;
} /// end countingSort();



