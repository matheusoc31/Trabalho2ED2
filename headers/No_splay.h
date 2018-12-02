#ifndef NO_SPLAY_H
#define NO_SPLAY_H
#include "GastoDeputado.h"

class No_splay {

    public:
        No_splay();
        No_splay(GastoDeputado dep);

        void setInfo(int val);
        void setDep(GastoDeputado dep);

        void setEsq(No_splay* p);
        void setDir(No_splay* p);

        int getInfo();
        GastoDeputado getDep();

        No_splay* getEsq();
        No_splay* getDir();

    private:
        int info; // informação do No (int)
        GastoDeputado dep;
        No_splay* esq; // ponteiro para o filho a esquerda
        No_splay* dir; // ponteiro para o filho a direita
};

#endif // NO_SPLAY_H
