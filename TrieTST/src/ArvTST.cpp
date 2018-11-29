#include "ArvTST.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sstream>

using namespace std;

ArvTST::ArvTST()
{
    raiz = NULL;
}

ArvTST::~ArvTST()
{
}

void ArvTST::insere(string palavra, double valor)
{
    if(!busca(palavra))
    {
        auxInsere(raiz, palavra, 0, valor, 0);
    }
}

void ArvTST::auxInsere(NoTST* no, string palavra, int i, double valor, int tam)
{
    if(tam < palavra.size())
    {
        if(!no)
        {
            no->setInfo(palavra[i]);
            no->setDir(NULL);
            no->setEsq(NULL);
            no->setMeio(NULL);
            no->SetFim(false);
        }
        if(palavra[i] > no->getInfo())
        {
            auxInsere(no->getDir(), palavra,i, valor, tam);
        }
        else if(palavra[i] < no->getInfo())
        {
            auxInsere(no->getEsq(),palavra,i, valor, tam);
        }
        else
        {
            if(palavra[i] == no->getInfo())
            {
                auxInsere(no->getMeio(), palavra,i++, valor, tam++);

            }
            else
            {
                no->SetFim(true);
                no->setGasto(valor);
            }
        }
    }
}


bool ArvTST::busca(string palavra)
{
    return auxBusca(raiz,palavra,0);
}

bool ArvTST::auxBusca(NoTST* no, string palavra, int i)
{
    if(no->getFim()== true)
    {
        return true;
    }
    if(no == NULL)
    {
        return false;
    }

    if(no->getInfo() < palavra[i])
        return auxBusca(no->getEsq(),palavra,i);
    else
    {
        if(no->getInfo()> palavra[i])
            return auxBusca(no->getDir(),palavra,i);
        else
        {
            return auxBusca(no->getMeio(),palavra,i++);
        }
    }
}
