#include <iostream>
#include <string.h>
#include <stdio.h>
#include <ArvTST.h>

using namespace std;

int main()
{
    ArvTST arvT;
    string frase = "bilu";
    arvT.insere(frase);
    if(arvT.busca("bilut"))
    {
        cout << "Achoooou";
    }
    else
    {
        cout << "Nao achooou";
    }
    return 0;
}
