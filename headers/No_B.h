#ifndef NO_B_H
#define NO_B_H

#include "GastoDeputado.h"

class No_B {

    public:
        No_B();
        No_B(int tamanho, bool f);
        ~No_B();

        No_B* buscaNo(int valor, unsigned int *comp, unsigned int *copias);
        int getPosicao(int chave, unsigned int *comp, unsigned int *copias);
        void imprimeNo();

        void split(int valor, No_B* no, unsigned int *comp, unsigned int *copias);
        void insereBaldeNaoCheio(GastoDeputado d, unsigned int *comp, unsigned int *copias);
        void removeNaoFolha(int valor, unsigned int *comp, unsigned int *copias);
        void removeFolha(int valor, unsigned int *comp, unsigned int *copias);
        void remover(int valor, unsigned int *comp, unsigned int *copias);
        GastoDeputado getProx(int valor);
        GastoDeputado getAnt(int valor);
        void merge(int valor, unsigned int *comp, unsigned int *copias);
        void completarBalde(int valor, unsigned int *comp, unsigned int *copias);
        void pegarDoAnterior(int valor, unsigned int *comp, unsigned int *copias);
        void pegarDoProximo(int valor, unsigned int *comp, unsigned int *copias);




        int tamanho;
        int numChaves;
        bool folha;
        int* info;
        GastoDeputado *dep;
        No_B** filho;

};

#endif // NO_B_H
