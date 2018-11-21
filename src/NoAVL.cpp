#include "../headers/libraries.h"

NoAVL::NoAVL() {

//    cout << "NoAVL: Default constructor called. Key = -1" << endl;

    this->right = NULL;
    this->left = NULL;
    this->height = 1; // inicializado como folha
    this->deputado.setGastoId(-1);
    this->key = -1;
};

NoAVL::NoAVL(GastoDeputado dep) {

//    cout << "NoAVL: Parametrized constructor called. Key = " << dep.getGastoId() << endl;

    this->right = NULL;
    this->left = NULL;
    this->height = 1; // inicializado como folha
    this->deputado = dep;
    this->key = dep.getGastoId();
}

NoAVL::~NoAVL() {
//    cout << "NoAVL: Destructor called. Deleting NoAVL." << endl;
};


int NoAVL::getKey() {
    return this->key;
}

void NoAVL::setKey(int key) {
    this->key = key;
}

GastoDeputado NoAVL::getDeputado() {
    return this->deputado;
}
void NoAVL::setDeputado(GastoDeputado dep) {
    this->deputado = dep;
}

NoAVL* NoAVL::getRight() {
    return this->right;
}

void NoAVL::setRight(NoAVL* right) {
    this->right = right;
}

NoAVL* NoAVL::getLeft() {
    return this->left;
}

void NoAVL::setLeft(NoAVL* left) {
    this->left = left;
}

int NoAVL::getHeight() {
    return this->height;
}

void NoAVL::setHeight(int height) {
    this->height = height;
}

//int NoAVL::getHeightRec() { //igual a getSetHeightTree, retorna a height do no, mas NAO atualiza as heights dos nos descendentes
//
//    if(this->right == NULL && this->left == NULL) { //folha
//        return 1;
//    } else if (this->left == NULL) { // so tem filho a direita
//        return 1 + this->right->getHeightRec();
//    } else if (this->right == NULL) { // so tem filho a esquerda
//        return 1 + this->left->getHeightRec();
//    } else { // tem os 2 filhos
//        return 1 + max(right->getHeightRec(), left->getHeightRec());
//    }
//}

//void NoAVL::updateHeight() { //usa a rotina getHeightRec, atualizando a height do No mas NAO atualizando as heights dos descendentes
//    this->height = this->getHeightRec();
//}

//void NoAVL::updateBalance() { //atualiza o fator de balanceamento sem atualizar as heights dos descendentes
//    if(this->right == NULL && this->left == NULL) { // folha
//        this->balance = 0;
//    } else if(this->left == NULL) {
//        this->balance = 0 - this->right->getHeightRec();
//    } else if(this->right == NULL) {
//        this->balance = this->left->getHeightRec();
//    } else {
//        this->balance = this->left->getHeightRec() - this->right->getHeightRec();
//    }
//}




