#ifndef ARV_B_H
#define ARV_B_H
#include "No_B.h"


class arv_B
{
    public:
     arv_B(int t);
    ~arv_B();
    No_B* getRaiz();
    void imprime();

    No_B* busca(int valor);
    void insere(int valor);
    void deletar(int valor);


    private:
    No_B* raiz;
    int tam;
    void deletarArvore(No_B* no);//FUNCAO PARA DELETAR A ARVORE

    void auxImprime(No_B* no);

};


#endif // ARV_B_H
