#ifndef ARV_SPLAY_H
#define ARV_SPLAY_H
#include "No_splay.h"

class arv_splay {

    public:
        arv_splay();
        ~arv_splay();
        void deleteSubTree(No_splay* rx);

        No_splay* getRaiz();//GET PARA RETORNAR A RAIZ DA ARVORE
        void setRaiz(No_splay* raiz);

        No_splay* newNoSplay(GastoDeputado dep);

        void insereDep(GastoDeputado dep, unsigned int *comp, unsigned int *copias);
        void removeDep(int val, unsigned int *comp, unsigned int *copias);
        void buscaDep(int val, unsigned int *comp, unsigned int *copias);
        No_splay* splaying(No_splay* node, int val, unsigned int *comp, unsigned int *copias);//FUNCAO QUE CALCULA AS ROTACOES ATRAVES DAS FUNCOES ZIG E ZAG
        No_splay* auxInsere(No_splay* node, GastoDeputado dep, unsigned int *comp, unsigned int *copias);
        No_splay* auxRemove(No_splay* node, int val, unsigned int *comp, unsigned int *copias);

        No_splay* rotateRight(No_splay* node, unsigned int *comp, unsigned int *copias);//FUNCAO PARA A ROTACAO SIMPLES -- ZIG DIREITA
        No_splay* rotateLeft(No_splay* node, unsigned int *comp, unsigned int *copias); //FUNCAO PARA A ROTACAO SIMPLES -- ZIG ESQUERDA

    private:
        No_splay* raiz;

};

#endif // ARV_SPLAY_H
