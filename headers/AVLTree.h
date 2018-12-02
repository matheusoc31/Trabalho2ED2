#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED

#include "GastoDeputado.h"
#include "NoAVL.h"

class AVLTree {

    public:

        AVLTree();
        AVLTree(NoAVL* raiz);

        ~AVLTree();
        void deleteSubTree(NoAVL* rx);

        NoAVL* getRaiz();
        void setRaiz(NoAVL* rx);

        int height(NoAVL* node);
        int getBalance(NoAVL* node);


//        bool insereNo(GastoDeputado dep, int key);
//        bool insereNo(GastoDeputado dep);
//        bool insereNoAux(NoAVL* rx, int key, GastoDeputado dep);

        void insereDep(GastoDeputado dep, unsigned int *comp, unsigned int *copias);
        NoAVL* newNodeDep(GastoDeputado dep) ;
        NoAVL* insertion(NoAVL* node, GastoDeputado dep, unsigned int *comp, unsigned int *copias);

        void buscaDep(int key, unsigned int *comp, unsigned int *copias);
        NoAVL* searchTree(NoAVL* node, int key, unsigned int *comp, unsigned int *copias);

        void removeNo(int key, unsigned int *comp, unsigned int *copias);
        NoAVL* minValueNode(NoAVL* node);
        NoAVL* deletion(NoAVL* node, int key, unsigned int *comp, unsigned int *copias);

        NoAVL* rotateLeft(NoAVL* y, unsigned int *comp, unsigned int *copias);
        NoAVL* rotateRight(NoAVL* y, unsigned int *comp, unsigned int *copias);
//        void rotacaoLR(NoAVL* y);
//        void rotacaoRL(NoAVL* y);

        NoAVL* balanceSubTree(NoAVL* y, unsigned int *comp, unsigned int *copias);

//        void updateBalanceHeightTree2(NoAVL* rx);

    private:
        NoAVL* raiz;

};


#endif // AVLTREE_H_INCLUDED
