#include <iostream>
#include "Arv_VP.h"
#include <cstdio>

using namespace std;

int main()
{
    Arv_VP arvoreRN;
    arvoreRN.inserir(20);
    arvoreRN.inserir(43);
    arvoreRN.inserir(50);
    arvoreRN.inserir(3);
    arvoreRN.inserir(60);
    arvoreRN.inserir(13);
    arvoreRN.imprimir();
    cout << "Preorder traversal of the constructed AVL tree is " << endl;
    arvoreRN.preOrder(arvoreRN.getRaiz());
    cout << "\nTree: " << endl;
    arvoreRN.printBT("", arvoreRN.getRaiz(), false);
    return 0;
}
