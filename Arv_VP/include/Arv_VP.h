#ifndef ARV_VP_H
#define ARV_VP_H
#include <iostream>
#include <cstdlib>
#include "No_VP.h"

class Arv_VP
{
    private:
        No_VP *raiz;
    public:
        Arv_VP();
        void inserir(int C);
        void remover(int info);
        void imprimir();
        void imprimePorNivel(No_VP* p, int nivel);
        bool busca(int C);
        void printBT(const std::string& prefix, No_VP* node, bool isRight);
        void preOrder(No_VP *root);
        No_VP *getRaiz();
        void rotacionarEsquerda(No_VP *ptr);
        void rotacionarDireita(No_VP *ptr);
        void balancearInsercao(No_VP *ptr);
        void balancearRemocao(No_VP *N);
        int getCor(No_VP *N);
        void setCor(No_VP *N, Color cor);
        No_VP *minValorNoRN(No_VP *N);
        No_VP *maxValorNoRN(No_VP *N);
        No_VP* inserirRN(No_VP *raiz, No_VP *ptr);
        No_VP* removerRN(No_VP *raiz, int info);
        int getAlturaNegra(No_VP *N);
        bool auxBusca(No_VP* p, int C);
};

#endif // ARV_VP_H
