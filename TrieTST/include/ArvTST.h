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
        void insere(string palavra);
        NoTST* busca(string palavra);
        bool busca2(string palavra);
    private:
        NoTST* raiz;
        bool auxBusca2(NoTST* no, string palavra);
        NoTST* auxBusca(NoTST* no, string palavra);
        void auxInsere(NoTST* no, string palavra);
        int retornaIndice(NoTST* no, string palavra);
};

#endif // ARVTST_H
