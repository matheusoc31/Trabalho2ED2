#ifndef NOAVL_H_INCLUDED
#define NOAVL_H_INCLUDED

#include "GastoDeputado.h"

class NoAVL {

    public:
        NoAVL();
        NoAVL(GastoDeputado dep);

        ~NoAVL();

        int getKey();
        void setKey(int key);

        GastoDeputado getDeputado();
        void setDeputado(GastoDeputado dep);

//        NoAVL* getFather();
//        void setFather(NoAVL* father);

        NoAVL* getRight();
        void setRight(NoAVL* right);

        NoAVL* getLeft();
        void setLeft(NoAVL* left);

        int getHeight();
        void setHeight(int height);
//
//        int getHeightRec();
//        void updateHeight();

//        int getBalance();
//        void setBalance(int balance);
//        void updateBalance();


    private:
        int key;
        GastoDeputado deputado;
        NoAVL *right, *left;
//        int balance,
        int height;

};

#endif // NOAVL_H_INCLUDED
