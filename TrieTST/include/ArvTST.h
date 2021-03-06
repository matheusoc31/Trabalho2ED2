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
    void insere(string palavra, double gasto);
    bool busca(string palavra);
    void autocompletar(string palavra);
    void imprimir();
private:
    NoTST* raiz;
    void auxInsere(NoTST* no, string palavra, int i, double gasto);
    void auxInsere2(NoTST* no, string palavra, int i, double gasto);
    bool auxBusca(NoTST* no, string palavra,int i);
    void auxAutocompletar(NoTST* no, string palavra, int i, string novapalavra);
    void imprimeAutocompletar(NoTST* no, string novapalavra);
};

#endif // ARVTST_H
