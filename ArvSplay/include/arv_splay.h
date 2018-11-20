#ifndef ARV_SPLAY_H
#define ARV_SPLAY_H
#include "No_splay.h"

class arv_splay
{
public:
    arv_splay();
    No_splay* getRaiz();//GET PARA RETORNAR A RAIZ DA ARVORE

    void insere(int val);
    void remove (int val);
    void busca(int val);
    No_splay* splaying(No_splay* no, int val);//FUNCAO QUE CALCULA AS ROTACOES ATRAVES DAS FUNCOES ZIG E ZAG

    void preOrder(No_splay* root);
    void printBT(const std::string& prefix, No_splay *node, bool isRight);


private:
    No_splay* raiz;

    No_splay* auxInsere(No_splay* no, int val);
    No_splay* auxRemove(No_splay* no, int val);
    bool auxBusca(No_splay* no, int val);
    No_splay* zigEsq(No_splay* no);//FUNCAO PARA A ROTACAO SIMPLES
    No_splay* zagDir(No_splay* no);//FUNCAO PARA A ROTACAO SIMPLES
    No_splay* menorSubArvDireita(No_splay *no);
};

#endif // ARV_SPLAY_H
