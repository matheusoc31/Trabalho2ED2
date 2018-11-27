#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

void imprimeString(string palavra)
{
    cout << palavra[0];
}

int main()
{
    string letra, letra2;
    cin >> letra;
    letra2 = letra[1];
    imprimeString(letra2);
    return 0;
}
