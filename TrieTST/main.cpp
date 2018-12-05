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
    arvT.insere(frase1, 332.2);
    arvT.insere(frase2, 403);
    arvT.insere(frase3, 344);
    arvT.insere(frase4, 932);
    arvT.insere(frase5, 1299);
    arvT.insere(frase6, 4000);
    arvT.insere(frase7, 304);
    arvT.imprimir();
    return 0;
}
