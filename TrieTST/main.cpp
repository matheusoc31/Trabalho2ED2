#include <iostream>
#include <string.h>
#include <stdio.h>
#include <ArvTST.h>

using namespace std;

int main()
{
    ArvTST arvT;
    string frase1 = "cruzeiro";
    string frase2 = "corinthians";
    string frase3 = "coritiba";
    string frase4 = "colcha";
    string frase5 = "castelo";
    string frase6 = "vaca";
    string frase7 = "ana";
    arvT.insere(frase1);
    arvT.insere(frase2);
    arvT.insere(frase3);
    arvT.insere(frase4);
    arvT.insere(frase5);
    arvT.insere(frase6);
    arvT.insere(frase7);
    arvT.imprimir();
    return 0;
}
