#include <iostream>
#include "arv_splay.h"
#include <cstdio>

using namespace std;

int main()
{
    arv_splay arvoreS;
    arvoreS.insere(10);
    arvoreS.insere(20);
    arvoreS.insere(30);
    arvoreS.insere(25);
    arvoreS.insere(5);
    arvoreS.insere(15);
    arvoreS.insere(50);

    arvoreS.busca(20);
    arvoreS.remove(25);




    arvoreS.imprime();



    cout << "Preorder traversal of the constructed AVL tree is " << endl;
    arvoreS.preOrder(arvoreS.getRaiz());

    cout << "\nTree: " << endl;
    arvoreS.printBT("", arvoreS.getRaiz(), false);

    return 0;
}
