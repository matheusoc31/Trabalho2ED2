#ifndef ARVTST_H
#define ARVTST_H
#include <iostream>
#include "NoTST.h"

using namespace std;

class ArvTST
{
public:
    ArvTST();
    ~ArvTST();
    NoTST* getRaiz(){return raiz;};
    void setRaiz(NoTST* novo){raiz=novo;};
    void insere(string palavra);
    bool busca(string palavra);
    void imprime();
private:
    NoTST* raiz;
    void auxInsere(NoTST* no, string palavra, int i);
    bool auxBusca(NoTST* no, string palavra,int i);
    void auxImprime(NoTST* raiz);
};

#endif // ARVTST_H
