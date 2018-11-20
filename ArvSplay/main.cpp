#include <iostream>
#include "arv_splay.h"
#include <cstdio>

using namespace std;

int main()
{
    arv_splay arvS;
    arvS.insere(10);
    arvS.insere(20);
    arvS.insere(30);
    arvS.insere(25);
    arvS.insere(5);
    arvS.insere(15);
    arvS.insere(50);
    arvS.insere(12);

    arvS.busca(20);
        arvS.remove(30);



    cout << "Preorder traversal of the constructed SPLAY tree is " << endl;
    arvS.preOrder(arvS.getRaiz());

    cout << "\nTree: " << endl;
    arvS.printBT("", arvS.getRaiz(), false);

    return 0;
}
