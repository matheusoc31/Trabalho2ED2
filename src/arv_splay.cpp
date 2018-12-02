#include "../headers/libraries.h"

using namespace std;

arv_splay::arv_splay() {
    this->raiz = NULL;
}

arv_splay::~arv_splay() {
    cout << "Splay Tree: Destructor called. Deleting Splay Tree." << this << endl;
    deleteSubTree(this->raiz);
}

void arv_splay::deleteSubTree(No_splay* rx) {

    if(rx == NULL)
        return;

    if(rx->getEsq() != NULL) {
        deleteSubTree(rx->getEsq());
        rx->setEsq(NULL);
    }
    else if(rx->getDir() != NULL) {
        deleteSubTree(rx->getDir());
        rx->setDir(NULL);
    }

    cout << "Splay Tree: Deleting No_splay " << rx << endl;
    rx = NULL;
    delete rx;
    return;
}


No_splay* arv_splay::getRaiz() {
    return this->raiz;
}

void arv_splay::setRaiz(No_splay* raiz) {
    this->raiz = raiz;
}

No_splay* arv_splay::newNoSplay(GastoDeputado dep) {
    No_splay* node = new No_splay(dep);
    node->setInfo(dep.getGastoId());
    node->setDep(dep);
    node->setEsq(NULL);
    node->setDir(NULL);
    return node;
}

No_splay* arv_splay::rotateRight(No_splay* node, unsigned int *comp, unsigned int *copias) {/// zig DIREITA

    No_splay* aux = node->getEsq();//NO UTILIZADO PARA AUXILIAR NA ROTACAO
    node->setEsq(aux->getDir()); if(aux->getDir() == NULL) {*copias += 1;}
    aux->setDir(node);
    *copias += 1;
    return aux;
}

No_splay* arv_splay::rotateLeft(No_splay* node, unsigned int *comp, unsigned int *copias) {/// zig ESQUERDA

    No_splay* aux = node->getDir();//NO UTILIZADO PARA AUXILIAR NA ROTACAO
    node->setDir(aux->getEsq()); if(aux->getEsq() == NULL) {*copias += 1;}
    aux->setEsq(node);
    *copias += 1;
    return aux;
}

No_splay* arv_splay::splaying(No_splay* node, int val, unsigned int *comp, unsigned int *copias) {

     if(node != NULL)
         *comp += 1;

     if(node == NULL || node->getInfo() == val)
         return node;

     No_splay* aux; *comp += 1;
     if (node->getInfo() > val) {

         if(node->getEsq()==NULL)
             return node;

         if(node->getEsq()->getInfo() > val) { /// zig-zig
             *comp += 1;
             aux = node->getEsq();
             aux->setEsq(splaying(aux->getEsq(), val, comp, copias));
             node = rotateRight(node, comp, copias);
             *copias += 1;
         }
         else if (node->getEsq()->getInfo() < val) { /// zig-zag
             *comp += 2;
             aux = node->getEsq();
             aux->setDir(splaying(aux->getDir(), val, comp, copias));
             *copias += 1;

             if(aux->getDir() != NULL) {
                 node->setEsq(rotateLeft(node->getEsq(), comp, copias));
                 *copias += 1;
             }
         }
         *comp += 2;

         if(node->getEsq() == NULL) {
             return node;
         } else {
             return rotateRight(node, comp, copias);
         }
//         return (node->getEsq() == NULL)? node: rotateRight(node, comp, copias);
     }
     else {

         if(node->getDir()==NULL) {
             return node;
         }

         if(node->getDir()->getInfo() > val) { /// zag-zig
             *comp += 1;
             aux = node->getDir();
             aux->setEsq(splaying(aux->getEsq(),val, comp, copias));
             *copias += 1;

             if(aux->getEsq() != NULL) {
                 node->setDir(rotateRight(node->getDir(), comp, copias));
                 *copias += 1;
             }
         }
         else if(node->getDir()->getInfo() < val) { /// zag-zag
             *comp += 2;
             aux = node->getDir();
             aux->setDir(splaying(aux->getDir(), val, comp, copias));
             node = rotateLeft(node, comp, copias);
             *copias += 1;
         }
         *comp += 2;

         if(node->getDir() == NULL) {
             return node;
         } else {
             return rotateLeft(node, comp, copias);
         }
//         return (node->getDir() == NULL)? node: rotateLeft(node, comp, copias);
     }
}


void arv_splay::buscaDep(int val, unsigned int *comp, unsigned int *copias) {
    this->raiz = splaying(this->raiz, val, comp, copias);
    *copias += 1;
}

///******************************************************************************************


void arv_splay::insereDep(GastoDeputado dep, unsigned int *comp, unsigned int *copias) {
    raiz = auxInsere(raiz, dep, comp, copias);
    *copias += 1;
}

No_splay* arv_splay::auxInsere(No_splay* node, GastoDeputado dep, unsigned int *comp, unsigned int *copias) {

    int val = dep.getGastoId();

    if(node == NULL)
        return newNoSplay(dep);

    node = splaying(node, val, comp, copias);

    if(node->getInfo() == val)
        return node;

    No_splay* newNo = new No_splay;
    newNo->setInfo(val);
    newNo->setDep(dep);
    newNo->setEsq(NULL);
    newNo->setDir(NULL);

    *comp += 1;
    if(node->getInfo() > val) {
        newNo->setDir(node);
        newNo->setEsq(node->getEsq());
        node->setEsq(NULL);
        *copias += 2;
    } else {
        newNo->setEsq(node);
        newNo->setDir(node->getDir());
        node->setDir(NULL);
        *copias += 2;
    }
    return newNo;
}

void arv_splay::removeDep(int val, unsigned int *comp, unsigned int *copias) {
    this->raiz = auxRemove(this->raiz, val, comp, copias);
    *copias += 1;
}

No_splay* arv_splay::auxRemove(No_splay* node, int val, unsigned int *comp, unsigned int *copias) {

    if(node == NULL)
        return NULL;

    node = splaying(node, val, comp, copias); /// "busca" de arvore binaria, e espalhamento para que o no a ser removido (se existir) fique na raiz

    *comp += 1;
    if(node->getInfo() != val) /// nao existe no com a chave a ser removida
        return node;

    No_splay* aux; /// existe o no. remoção segue de acordo com a disposição dos nós na arvore
    if(node->getEsq() == NULL) {
        aux = node;
        node = node->getDir();
    } else {
        aux = node;
        node = splaying(node->getEsq(), val, comp, copias);
        node->setDir(aux->getDir());
        *copias += 1;
    }

    delete aux;
    return node; /// raiz da splay apos remocao
}
