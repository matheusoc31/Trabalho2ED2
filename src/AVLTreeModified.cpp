#include "../headers/libraries.h"


AVLTreeModified::AVLTreeModified() {
    cout << "AVLTreeModified: Default constructor called. Raiz = NULL" << endl;
    this->raiz = NULL;
};

AVLTreeModified::AVLTreeModified(NoAVL* raiz) {
    cout << "AVLTreeModified: Parametrized constructor called. Raiz = raiz" << endl;
    this->raiz = raiz;
}

AVLTreeModified::~AVLTreeModified() {
    cout << "AVLTreeModified: Destructor called. Deleting AVLTreeModified." << endl;
    deleteSubTree(this->raiz);
}

void AVLTreeModified::deleteSubTree(NoAVL* rx) {

    if(rx == NULL)
        return;

    if(rx->getLeft() != NULL)
        deleteSubTree(rx->getLeft());
    else if(rx->getRight() != NULL)
        deleteSubTree(rx->getRight());

    cout << "AVLTreeModified: Deleting NoAVL " << rx << endl;
    rx->setLeft(NULL);
    rx->setRight(NULL);
    rx = NULL;
    delete rx;
    return;
}


NoAVL* AVLTreeModified::getRaiz() {
    return this->raiz;
}

void AVLTreeModified::setRaiz(NoAVL* rx) {
    this->raiz = rx;
}

NoAVL* AVLTreeModified::rotateLeft(NoAVL* x, unsigned int *comp, unsigned int *copias) {

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

NoAVL* AVLTreeModified::rotateRight(NoAVL* y, unsigned int *comp, unsigned int *copias) {

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

/************************************************************/

void AVLTreeModified::insereDep(GastoDeputado dep, unsigned int *comp, unsigned int *copias) {
    this->raiz = insertion(this->raiz, dep, comp, copias);
    *copias += 1;
}

int AVLTreeModified::height(NoAVL* node) {
    return (node == NULL) ? 0:node->getHeight();
}

NoAVL* AVLTreeModified::newNodeDep(GastoDeputado dep) {
    NoAVL* node = new NoAVL(dep);

    node->setKey(dep.getGastoId());
    node->setDeputado(dep);
    node->setLeft(NULL);
    node->setRight(NULL);
    node->setHeight(1); //adicionado como folha

    return node;
}

int AVLTreeModified::getBalance(NoAVL* node) {
    return (node == NULL) ? 0:(height(node->getLeft()) - height(node->getRight()));
}

NoAVL* AVLTreeModified::insertion(NoAVL* node, GastoDeputado dep, unsigned int *comp, unsigned int *copias) {

    int key = dep.getGastoId();

    /** 1.Inserção de árvore binária **/
    if(node == NULL) {
        return(newNodeDep(dep));
    }

    *comp += 1;
    if(key <= node->getKey())
        node->setLeft(insertion(node->getLeft(), dep, comp, copias));
    else
        node->setRight(insertion(node->getRight(), dep, comp, copias));

    /** 2.Atualizando a altura do nó pai (e de todos os ancestrais, conforme o fim de cada chamada recursiva) **/
    node->setHeight(1 + max(height(node->getLeft()), height(node->getRight())));

    /** 3.Balanceando **/
    node = balanceSubTree(node, comp, copias);

    /** Retorna o pointeiro para o nó novo(raiz da subárvore rotacionada) **/
    return node;

}

NoAVL* AVLTreeModified::balanceSubTree(NoAVL* node, unsigned int *comp, unsigned int *copias) {

    int balance = getBalance(node);

    if(balance > 3) {
        if(getBalance(node->getLeft()) == -1) {
            node->setLeft(rotateLeft(node->getLeft(), comp, copias));
            *copias += 1;
        }
        *copias += 1; /// porque node = balanceSubTree(node)
        return rotateRight(node, comp, copias);

    } else if(balance < -3) {
        if(getBalance(node->getRight()) == 1) {
            node->setRight(rotateRight(node->getRight(), comp, copias));
            *copias += 1;
        }
        *copias += 1; /// porque node = balanceSubTree(node)
        return rotateLeft(node, comp, copias);

    } else return node;
}



/************************************************************/

void AVLTreeModified::buscaDep(int key, unsigned int *comp, unsigned int *copias) {
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

NoAVL* AVLTreeModified::searchTree(NoAVL* node, int key, unsigned int *comp, unsigned int *copias) {
    if(node == NULL) {
        return NULL;
    }

    if(key == node->getKey()) {
        *comp += 1;
        return node;
    }
    else if(key < node->getKey()) {
        comp += 2;
        return searchTree(node->getLeft(), key, comp, copias);
    }
    else {
        comp += 2;
        return searchTree(node->getRight(), key, comp, copias);
    }
}

/************************************************************/

void AVLTreeModified::removeNo(int key, unsigned int *comp, unsigned int *copias) {
    this->raiz = deletion(this->raiz, key, comp, copias);
    *copias += 1;
}

NoAVL* AVLTreeModified::minValueNode(NoAVL* node) {

    NoAVL* current = node;

    while (current->getLeft() != NULL)
        current = current->getLeft();

    return current;
}

NoAVL* AVLTreeModified::deletion(NoAVL* node, int key, unsigned int *comp, unsigned int *copias) {

    /** 1.Remoção de Árvore Binária**/
    if(node == NULL) /// Chave não está na árvore
        return node;

    if(key < node->getKey()) {
        comp += 1;
        node->setLeft(deletion(node->getLeft(), key, comp, copias));
        *copias += 1;
    }
    else if(key > node->getKey()) {
        comp += 2;
        node->setRight(deletion(node->getRight(), key, comp, copias));
        *copias += 1;
    }
    else {
        comp += 2;
        /// Casos 1 e 2: Sem filhos ou só 1 filho
        if((node->getLeft() == NULL) || (node->getRight() == NULL)) {
            NoAVL *aux = (node->getLeft() != NULL) ? node->getLeft():node->getRight();

            /// Sem filhos
            if (aux == NULL) {
                aux = node;
                node = NULL;
            } else *node = *aux; /// 1 filho
            *copias += 1;

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
