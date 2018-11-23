#include <iostream>
#include "arv_B.h"
#include "No_B.h"

using namespace std;

int main()
{
    arv_B arvB(3);

    arvB.insere(31);
    arvB.insere(15);
    arvB.insere(10);
    arvB.insere(5);
    arvB.insere(20);
    arvB.insere(30);
    arvB.insere(8);
    arvB.insere(22);
    arvB.insere(25);
    arvB.insere(35);
    arvB.insere(45);
    arvB.insere(3);
    arvB.insere(2);
    arvB.insere(43);
    arvB.insere(77);


    arvB.imprime();

    cout << arvB.getRaiz()->info[0] << endl;
    cout << arvB.getRaiz()->info[1] << endl;
    cout << arvB.getRaiz()->info[2] << endl;
    cout << arvB.getRaiz()->info[3] << endl;
    cout << arvB.getRaiz()->info[4] << endl;

    arvB.deletar(35);
    arvB.imprime();

    cout << arvB.getRaiz()->info[0] << endl;
    cout << arvB.getRaiz()->info[1] << endl;
    cout << arvB.getRaiz()->info[2] << endl;
    cout << arvB.getRaiz()->info[3] << endl;
    cout << arvB.getRaiz()->info[4] << endl;

     if(arvB.busca(15)==NULL)
         cout<< 15 <<" NAO EXISTE NA ARVORE" << endl;
     else
         cout<< 15 << " EXISTENTE NA ARVORE" << endl;

     if(arvB.busca(34)==NULL)
         cout<< 34 << " NAO EXISTE NA ARVORE" << endl;
     else
         cout<< 34 << " EXISTENTE NA ARVORE" << endl;

     if(arvB.busca(25)==NULL)
         cout<< 25 << " NAO EXISTE NA ARVORE" << endl;
     else
         cout<< 25 << " EXISTENTE NA ARVORE" << endl;


     arvB.deletar(31);
     arvB.imprime();
     arvB.deletar(8);
     arvB.imprime();
     arvB.deletar(34);
     arvB.imprime();




}
