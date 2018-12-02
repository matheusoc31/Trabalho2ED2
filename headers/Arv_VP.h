#ifndef ARV_VP_H
#define ARV_VP_H
#include "No_VP.h"

using namespace std;

class Arv_VP
{
    private:
        No_VP *raiz;
    public:
        Arv_VP();
        ~Arv_VP();
        void deleteSubTree(No_VP* rx);
        void inserir(GastoDeputado dep, unsigned int *comp, unsigned int *copias);
        void remover(int info, unsigned int *comp, unsigned int *copias);
        void imprimir();
        void imprimePorNivel(No_VP* p, int nivel);
        bool busca(int C, unsigned int *comp, unsigned int *copias);
        void printBT(const std::string& prefix, No_VP* node, bool isRight);
        void preOrder(No_VP *root);
        No_VP *getRaiz();
        void setRaiz(No_VP* rx);
        void rotacionarEsquerda(No_VP *ptr, unsigned int *comp, unsigned int *copias);
        void rotacionarDireita(No_VP *ptr, unsigned int *comp, unsigned int *copias);
        void balancearInsercao(No_VP *ptr, unsigned int *comp, unsigned int *copias);
        void balancearRemocao(No_VP *N, unsigned int *comp, unsigned int *copias);
        int getCor(No_VP *N);
        void setCor(No_VP *N, Color cor);
        No_VP *minValorNoRN(No_VP *N);
        No_VP *maxValorNoRN(No_VP *N);
        No_VP* inserirRN(No_VP *raiz, No_VP *ptr, unsigned int *comp, unsigned int *copias);
        No_VP* removerRN(No_VP *raiz, int info, unsigned int *comp, unsigned int *copias);
        int getAlturaNegra(No_VP *N);
        bool auxBusca(No_VP* p, int C, unsigned int *comp, unsigned int *copias);
};

#endif // ARV_VP_H
