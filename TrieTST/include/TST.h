#ifndef TST_H
#define TST_H
#include "NoTST.h"
#include <iostream>

using namespace std;

class TST
{
    public:
        TST();
        ~TST();
        NoTST* getRaiz();
        void setRaiz(NoTST* novo);
        void insere(string palavra);
        NoTST* auxInsere(NoTST* no, string palavra);
    private:
        NoTST* raiz;
};

#endif // TST_H
