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

    NoTST* getRaiz();
    void setRaiz(NoTST* novo);
    void insere(string palavra, double valor);
    /*
    NoTST* busca(string palavra);
    bool busca2(string palavra);
    */
    bool busca(string palavra);


private:
    NoTST* raiz;
    void auxInsere(NoTST* no, string palavra, int i, double valor, int tam);
    /*
    bool auxBusca2(NoTST* no, string palavra);
    NoTST* auxBusca(NoTST* no, string palavra);
    int retornaIndice(NoTST* no, string palavra);
    */

    bool auxBusca(NoTST* no, string palavra,int i);
};

#endif // ARVTST_H
