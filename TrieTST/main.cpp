#include <iostream>
#include <string.h>
#include <stdio.h>
#include <ArvTST.h>

using namespace std;

int main()
{
    ArvTST arvT;
    string frase = "ba";
    arvT.insere(frase);
    if(arvT.busca("ba"))
    {
        cout << "Achou";
    }
    return 0;
}
