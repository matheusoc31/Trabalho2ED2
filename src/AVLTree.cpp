#include "../headers/libraries.h"


AVLTree::AVLTree() {
    cout << "AVLTree: Default constructor called. Raiz = NULL" << endl;
    this->raiz = NULL;
};

AVLTree::AVLTree(NoAVL* raiz) {
    cout << "AVLTree: Parametrized constructor called. Raiz = raiz" << endl;
    this->raiz = raiz;
}

AVLTree::~AVLTree() {
    cout << "AVLTree: Destructor called. Deleting AVLTree." << endl;
    deleteSubTree(this->raiz);
}

void AVLTree::deleteSubTree(NoAVL* rx) {

    if(rx == NULL)
        return;

    if(rx->getLeft() != NULL)
        deleteSubTree(rx->getLeft());
    else if(rx->getRight() != NULL)
        deleteSubTree(rx->getRight());

    cout << "AVLTree: Deleting NoAVL " << rx << endl;
    rx = NULL;
    delete rx;
    return;
}


NoAVL* AVLTree::getRaiz() {
    return this->raiz;
}

void AVLTree::setRaiz(NoAVL* rx) {
    this->raiz = rx;
}

NoAVL* AVLTree::rotateLeft(NoAVL* x, unsigned int *comp, unsigned int *copias) {

    /** Rotacionando **/
    NoAVL* y = x->getRight();
    x->setRight(y->getLeft()); if(y->getLeft() != NULL){*copias += 1;};
    y->setLeft(x); *copias += 1;

    /** Atualizando as alturas **/
    x->setHeight(1 + max(height(x->getLeft()), height(x->getRight())));
    y->setHeight(1 + max(height(y->getLeft()), height(y->getRight())));

    /** Nova raiz **/
    return y;
}

NoAVL* AVLTree::rotateRight(NoAVL* y, unsigned int *comp, unsigned int *copias) {

    /** Rotacionando **/
    NoAVL* x = y->getLeft();
    y->setLeft(x->getRight()); if(x->getRight() != NULL){*copias += 1;};
    x->setRight(y); *copias += 1;

    /** Atualizando as alturas **/
    y->setHeight(1 + max(height(y->getLeft()), height(y->getRight())));
    x->setHeight(1 + max(height(x->getLeft()), height(x->getRight())));

    /** Nova raiz **/
    return x;
}

//void AVLTree::rotacaoLR(NoAVL* y) {
//    rotacaoRR(y->getLeft());
//    return rotacaoLL(y);
//}
//
//void AVLTree::rotacaoRL(NoAVL* y) {
//    rotacaoLL(y->getRight());
//    return rotacaoRR(y);
//}

//bool AVLTree::insereNo(GastoDeputado dep, int key) {
//    if(this->raiz == NULL) {
//        NoAVL* node = new NoAVL(dep, key);
//        this->setRaiz(node);
//        return true;
//    }
//    else return this->insereNoAux(this->raiz, key, dep);
//
//    this->updateBalanceHeightTree2(this->raiz);
//}
//
//bool AVLTree::insereNo(GastoDeputado dep) {
//    if(this->raiz == NULL) {
//        NoAVL* node = new NoAVL(dep, dep.getGastoId());
//        this->setRaiz(node);
//        return true;
//    }
//
//
//    bool v = this->insereNoAux(this->raiz, dep.getGastoId(), dep);
//
//    this->updateBalanceHeightTree2(this->raiz);
//
//    return v;
//}

//bool AVLTree::insereNoAux(NoAVL* rx, int key, GastoDeputado dep) {
//
//    if(rx == NULL)
//        return false;
//
//    bool insertedThisIt = false;
//
//    if(key <= rx->getKey()) { // se chave for menor ou igual a da raiz, insere na subarvore esquerda
//        if(!(this->insereNoAux(rx->getLeft(), key, dep))) { // se for false, a insercao nao foi bem-sucedida, ou seja, nao existe subarvore a esquerda
//            NoAVL* nodeL = new NoAVL(); //podemos realizar a insercao imediatamente a esquerda
//
//            nodeL->setDeputado(dep);
//            nodeL->setKey(key);
//
////            nodeL->setFather(rx);
//            rx->setLeft(nodeL);
//
//            insertedThisIt = true;
//        }
//    } else if(!(this->insereNoAux(rx->getRight(), key, dep))) {
//        NoAVL* nodeR = new NoAVL(); //podemos realizar a insercao imediatamente a esquerda
//
//        nodeR->setDeputado(dep);
//        nodeR->setKey(key);
//
////        nodeR->setFather(rx);
//        rx->setRight(nodeR);
//
//        insertedThisIt = true;
//    }
//
//    if(insertedThisIt)
//        this->updateBalanceHeightTree2(this->raiz);
//
//    this->balanceia(rx);
//
//    return true;
//
//}


/************************************************************/

void AVLTree::insereDep(GastoDeputado dep, unsigned int *comp, unsigned int *copias) {
    this->raiz = insertion(this->raiz, dep, comp, copias);
    *copias += 1;
}

int AVLTree::height(NoAVL* node) {
    return (node == NULL) ? 0:node->getHeight();
}

NoAVL* AVLTree::newNodeDep(GastoDeputado dep) {
    NoAVL* node = new NoAVL(dep);

    node->setKey(dep.getGastoId());
    node->setDeputado(dep);
    node->setLeft(NULL);
    node->setRight(NULL);
    node->setHeight(1); //adicionado como folha

    return node;
}

int AVLTree::getBalance(NoAVL* node) {
    return (node == NULL) ? 0:(height(node->getLeft()) - height(node->getRight()));
}

NoAVL* AVLTree::insertion(NoAVL* node, GastoDeputado dep, unsigned int *comp, unsigned int *copias) {

    int key = dep.getGastoId();

    /** 1.Inserção de árvore binária **/
    if(node == NULL) {
        return(newNodeDep(dep));
    }

    *comp += 1;
    if(key <= node->getKey()) {
        node->setLeft(insertion(node->getLeft(), dep, comp, copias));
        *copias += 1;
    }
    else {
        node->setRight(insertion(node->getRight(), dep, comp, copias));
        *copias += 1;
    }

    /** 2.Atualizando a altura do nó pai (e de todos os ancestrais, conforme o fim de cada chamada recursiva) **/
    node->setHeight(1 + max(height(node->getLeft()), height(node->getRight())));

    /** 3.Balanceando **/
    node = balanceSubTree(node, comp, copias);

    /** Retorna o pointeiro para o nó novo(raiz da subárvore rotacionada) **/
    return node;

}

NoAVL* AVLTree::balanceSubTree(NoAVL* node, unsigned int *comp, unsigned int *copias) {

    int balance = getBalance(node);

    if(balance > 1) {
        if(getBalance(node->getLeft()) == -1) {
            node->setLeft(rotateLeft(node->getLeft(), comp, copias));
            *copias += 1;
        }
        *copias += 1; /// porque node = balanceSubTree(node)
        return rotateRight(node, comp, copias);

    } else if(balance < -1) {
        if(getBalance(node->getRight()) == 1) {
            node->setRight(rotateRight(node->getRight(), comp, copias));
            *copias += 1;
        }
        *copias += 1; /// porque node = balanceSubTree(node)
        return rotateLeft(node, comp, copias);

    } else return node;
}


/************************************************************/

void AVLTree::buscaDep(int key, unsigned int *comp, unsigned int *copias) {
//    NoAVL* node =
    searchTree(this->raiz, key, comp, copias);
//    if(node == NULL)
//        cout << "Chave não encontrada na árvore." << endl;
//    else {
//        cout << "gasto_id = " << node->getKey() << " encontrado." << endl;
//        if(node->getLeft() == NULL)
//            cout << "Left = --" << endl;
//        else cout << "Left = " << node->getLeft()->getKey() << endl;
//        if(node->getRight() == NULL)
//            cout << "Right = --" << endl;
//        else cout << "Right = " << node->getRight()->getKey() << endl << endl;
//    }
}

NoAVL* AVLTree::searchTree(NoAVL* node, int key, unsigned int *comp, unsigned int *copias) {
    if(node == NULL) {
        return NULL;
    }

    if(key == node->getKey()) {
        *comp += 1;
        return node;
    }
    else if(key < node->getKey()) {
        *comp += 2;
        return searchTree(node->getLeft(), key, comp, copias);
    }
    else {
        *comp += 2;
        return searchTree(node->getRight(), key, comp, copias);
    }
}

/************************************************************/

void AVLTree::removeNo(int key, unsigned int *comp, unsigned int *copias) {
    this->raiz = deletion(this->raiz, key, comp, copias);
    *copias += 1;
}

NoAVL* AVLTree::minValueNode(NoAVL* node) {

    NoAVL* current = node;

    while (current->getLeft() != NULL)
        current = current->getLeft();

    return current;
}

NoAVL* AVLTree::deletion(NoAVL* node, int key, unsigned int *comp, unsigned int *copias) {

    /** 1.Remoção de Árvore Binária**/
    if(node == NULL) /// Chave não está na árvore
        return node;

    if(key < node->getKey()) {
        *comp += 1;
        node->setLeft(deletion(node->getLeft(), key, comp, copias));
        *copias += 1;
    }
    else if(key > node->getKey()) {
        *comp += 2;
        node->setRight(deletion(node->getRight(), key, comp, copias));
        *copias += 1;
    }
    else {
        *comp += 2;
        /// Casos 1 e 2: Sem filhos ou só 1 filho
        if((node->getLeft() == NULL) || (node->getRight() == NULL)) {
            NoAVL *aux = (node->getLeft() != NULL) ? node->getLeft():node->getRight();

            /// Sem filhos
            if (aux == NULL) {
                aux = node;
                node = NULL;
            } else {
                *node = *aux; /// 1 filho
                *copias += 1;
            }

            delete aux;

        } else { /// Caso 3: 2 filhos. Substituir pelo sucessor mais próximo (menor descendente à direita)
            NoAVL* aux = minValueNode(node->getRight());
            node->setKey(aux->getKey());
            node->setDeputado(aux->getDeputado());
            *copias += 1;
            node->setRight(deletion(node->getRight(), aux->getKey(), comp, copias));
            *copias += 1;
        }
    }

    /// Verificando se a árvore tem somente 1 nó
    if (node == NULL)
        return node;

    /** 2.Atualizando a altura do nó **/
    node->setHeight(1 + max(height(node->getLeft()), height(node->getRight())));

    /** 3.Balanceando **/
    node = balanceSubTree(node, comp, copias);

    /** Retorna o pointeiro para o nó novo(raiz da subárvore rotacionada) **/
    return node;
}

/************************************************************/

//void AVLTree::updateBalanceHeightTree2(NoAVL* rx) { // atualiza as heights e fatores de balanceamento da arvore com raiz rx
//
//    if(rx->getRight() == NULL && rx->getLeft() == NULL) { //folha
//
//        cout << "folha = " << rx->getKey() << endl;
//
//        rx->setBalance(0);
//        rx->setHeight(0);
//
//    } else if (rx->getRight() != NULL && rx->getLeft() == NULL) { // so tem filho a direita
//
//        cout << "no interior = " << rx->getKey() << "; filho a direita = " << rx->getRight()->getKey() << endl;
//
//        updateBalanceHeightTree2(rx->getRight());
//        rx->setBalance(0 - (rx->getRight())->getHeight());
//        rx->setHeight(1 + (rx->getRight())->getHeight());
//
//    } else if (rx->getRight() == NULL && rx->getLeft() != NULL) { // so tem filho a esquerda
//
//        cout << "no interior = " << rx->getKey() << "; filho a esquerda = " << rx->getLeft()->getKey() << endl;
//
//        updateBalanceHeightTree2(rx->getLeft());
//        rx->setBalance((rx->getLeft())->getHeight());
//        rx->setHeight(1 + (rx->getLeft())->getHeight());
//
//    } else { // tem os 2 filhos
//
//        cout << "no interior = " << rx->getKey() << "; filho a direita = " << rx->getRight()->getKey() << "; filho a esquerda = " << rx->getLeft()->getKey() << endl;
//
//        updateBalanceHeightTree2(rx->getRight());
//        updateBalanceHeightTree2(rx->getLeft());
//        rx->setBalance((rx->getLeft())->getHeight() - (rx->getRight())->getHeight());
//        rx->setHeight(1 + max((rx->getRight())->getHeight(), (rx->getLeft())->getHeight()));
//
//    }
//}





