#ifndef ARV_B_H
#define ARV_B_H
#include "No_B.h"

class arv_B
{
    public:
         arv_B(int t);
        ~arv_B();
        No_B* getRaiz();
        void setRaiz(No_B* no);
        void imprime();

        No_B* busca(int valor, unsigned int *comp, unsigned int *copias);
        void insere(GastoDeputado d, unsigned int *comp, unsigned int *copias);
        void deletar(int valor, unsigned int *comp, unsigned int *copias);

        void deletarArvore(No_B* no);//FUNCAO PARA DELETAR A ARVORE

    private:
        No_B* raiz;
        int tam;

        void auxImprime(No_B* no);

};


#endif // ARV_B_H
