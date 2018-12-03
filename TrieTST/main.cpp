#include <iostream>
#include <string.h>
#include <stdio.h>
#include <ArvTST.h>

using namespace std;

int main()
{
    ArvTST arvT;
    string frase = "botaagua";
    string frase2 = "botafogo";
    arvT.insere(frase);
    arvT.insere(frase2);
    arvT.autocompletar("bo");
    return 0;
}
