#include "ArvTST.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sstream>

using namespace std;

ArvTST::ArvTST()
{
    //ctor
}

ArvTST::~ArvTST()
{
    //dtor
}

void ArvTST::insere(string palavra)
{
    auxInsere(raiz, palavra);
}

NoTST* ArvTST::auxInsere(NoTST* no, string palavra)
{
    if(busca2(palavra) == true)
    {
        cout << "Palavra ja existente" << endl;
    }
    else
    {
        no = auxBusca(no, palavra); /// AQUI...
        int indice = retornaIndice(raiz,palavra);
        for(int i=indice;i<palavra.size();i++)
        {
            while()
            if((int)no->getInfo()[0] < palavra[o])
            {
                no = no->getDir();
            }
            novo = new NoTST();
            no->setDir(NULL);
            no->setEsq(NULL);
            no->setFilho(NULL);
            no->setInfo(palavra);
        }
    }

    if(no == NULL)
    {
        no = new NoTST();
        no->setDir(NULL);
        no->setEsq(NULL);
        no->setFilho(NULL);
        no->setInfo(palavra);
    }
    else
    {
        if((int)no->getInfo()[0] > (int)palavra[0])
            no->setEsq(auxInsere(no->getEsq(), palavra));
        else
            no->setDir(auxInsere(no->getDir(), palavra));
    }
    return no;
}

NoTST* ArvTST::busca(string palavra)
{
    NoTST* novo = new NoTST();
    NoTST* auxiliar = new NoTST();
    novo = raiz;
    string aux;
    for(int i=0;i<palavra.size() && novo != NULL;i++)
    {
        aux = palavra[i];
        auxiliar = novo;
        novo = auxBusca(novo, aux);
    }
    return auxiliar;
}

NoTST* ArvTST::auxBusca(NoTST* no, string palavra)
{
    if (no == NULL)
        return NULL;
    else if ((int)no->getInfo()[0] == (int)palavra[0])
        return no->getFilho();
    else if ((int)no->getInfo()[0] < (int)palavra[0])
        return no->getDir();
    else
        return no->getEsq();
}

bool ArvTST::busca2(string palavra)
{
    NoTST* novo = new NoTST();
    NoTST* auxiliar = new NoTST();
    novo = raiz;
    string aux;
    for(int i=0;i<palavra.size() && novo != NULL;i++)
    {
        aux = palavra[i];
        if(auxBusca2(novo, aux) == false)
        {
            return false;
        }
        auxiliar = novo;
        novo = novo->getFilho();
    }
    if(auxiliar->getFim() == false)
    {
        auxiliar->SetFim(true);
    }
    return true;
}

bool ArvTST::auxBusca2(NoTST* no, string palavra)
{
    if ((int)no->getInfo()[0] == (int)palavra[0])
        return true;
    else
        return false;
}

int ArvTST::retornaIndice(NoTST* no, string palavra)
{
    NoTST* novo = new NoTST();
    novo = raiz;
    string aux;
    int i=0;
    for(;i<palavra.size() && novo != NULL;i++)
    {
        aux = palavra[i];
        novo = auxBusca(novo, aux);
    }
    return i-1;
}
