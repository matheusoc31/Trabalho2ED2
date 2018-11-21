#ifndef AVLTREEMODIFIED_H_INCLUDED
#define AVLTREEMODIFIED_H_INCLUDED

#include "GastoDeputado.h"
#include "NoAVL.h"

class AVLTreeModified {

    public:

        AVLTreeModified();
        AVLTreeModified(NoAVL* raiz);

        ~AVLTreeModified();
        void deleteSubTree(NoAVL* rx);

        NoAVL* getRaiz();
        void setRaiz(NoAVL* rx);

        int height(NoAVL* node);
        int getBalance(NoAVL* node);

        void insereDep(GastoDeputado dep, unsigned int *comp, unsigned int *copiass);
        NoAVL* newNodeDep(GastoDeputado dep) ;
        NoAVL* insertion(NoAVL* node, GastoDeputado dep, unsigned int *comp, unsigned int *copias);

        void buscaDep(int key, unsigned int *comp, unsigned int *copias);
        NoAVL* searchTree(NoAVL* node, int key, unsigned int *comp, unsigned int *copias);

        void removeNo(int key, unsigned int *comp, unsigned int *copias);
        NoAVL* minValueNode(NoAVL* node);
        NoAVL* deletion(NoAVL* node, int key, unsigned int *comp, unsigned int *copias);

        NoAVL* rotateLeft(NoAVL* y, unsigned int *comp, unsigned int *copias);
        NoAVL* rotateRight(NoAVL* y, unsigned int *comp, unsigned int *copias);

        NoAVL* balanceSubTree(NoAVL* y, unsigned int *comp, unsigned int *copias);

    private:
        NoAVL* raiz;

};

#endif // AVLTREEMODIFIED_H_INCLUDED
