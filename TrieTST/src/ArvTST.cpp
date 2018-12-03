#include "ArvTST.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <sstream>

using namespace std;

ArvTST::ArvTST()
{
    setRaiz(NULL);
}

ArvTST::~ArvTST()
{

}

void ArvTST::insere(string palavra)
{
    if(getRaiz()==NULL)
    {
        NoTST* novo = new NoTST(palavra[0]);
        setRaiz(novo);
        auxInsere(getRaiz(),palavra,0);
    }
    else
    {
        if(getRaiz()->getInfo()==palavra[0])
        {
            auxInsere(getRaiz(),palavra,1);
        }
        else if(getRaiz()->getInfo()>palavra[0])
        {
            auxInsere(getRaiz()->getEsq(),palavra,0);
        }
        else if(getRaiz()->getInfo()<palavra[0])
        {
            auxInsere(getRaiz()->getDir(), palavra,0);
        }
    }
}

void ArvTST::auxInsere(NoTST* no, string palavra, int i)
{
    if(i < palavra.size())
    {
        if(no->getMeio()==NULL)
        {
            NoTST* novo = new NoTST(palavra[i+1]);
            no->setMeio(novo);
            if(i == palavra.size()-2)
            {
                novo->SetFim(true);
            }
            auxInsere(no->getMeio(), palavra, i+1);
        }
        else
        {
            if(no->getMeio()->getInfo()==palavra[i])
            {
                if(i == palavra.size()-2)
                {
                    no->getMeio()->SetFim(true);
                }
                auxInsere(no->getMeio(),palavra,i+1);
            }
            else if(no->getMeio()->getInfo()>palavra[i])
            {
                if(no->getMeio()->getEsq()==NULL)
                {
                    NoTST* novo = new NoTST(palavra[i]);
                    no->setEsq(novo);
                    if(i == palavra.size()-2)
                    {
                        novo->SetFim(true);
                    }
                    auxInsere(no->getEsq(),palavra,i);
                }
                else
                {
                    if(i == palavra.size()-2)
                    {
                        no->SetFim(true);
                    }
                    auxInsere(no->getEsq(),palavra,i);
                }
            }
            else if(no->getMeio()->getInfo()<palavra[i])
            {
                if(no->getMeio()->getDir()==NULL)
                {
                    NoTST* novo = new NoTST(palavra[i]);
                    no->setDir(novo);
                    if(i == palavra.size()-2)
                    {
                        novo->SetFim(true);
                    }
                    auxInsere(no->getDir(),palavra,i);
                }
                else
                {
                    if(i == palavra.size()-2)
                    {
                        no->SetFim(true);
                    }
                    auxInsere(no->getDir(), palavra,i);
                }
            }
        }
    }
}

bool ArvTST::busca(string palavra)
{
    if(getRaiz()==NULL)
    {
        return false;
    }
    else
    {
        if(getRaiz()->getFim() && palavra.size()==1 && getRaiz()->getInfo()==palavra[0])
        {
            return true;
        }
        else if(getRaiz()->getInfo()==palavra[0])
        {
            return auxBusca(getRaiz()->getMeio(),palavra,1);
        }
        else if(getRaiz()->getInfo()>palavra[0])
        {
            return auxBusca(getRaiz()->getEsq(),palavra,0);
        }
        else if(getRaiz()->getInfo()<palavra[0])
        {
            return auxBusca(getRaiz()->getDir(), palavra,0);
        }
    }
}

bool ArvTST::auxBusca(NoTST* no, string palavra, int i)
{
    if(i < palavra.size())
    {
        if(no==NULL)
        {
            return false;
        }
        else
        {
            if(no->getInfo()==palavra[i])
            {
                if(i == palavra.size()-1)
                {
                    if(no->getFim())
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                return auxBusca(no->getMeio(),palavra,i+1);
            }
            else if(no->getInfo()>palavra[0])
            {
                return auxBusca(no->getEsq(),palavra,i);
            }
            else if(no->getInfo()<palavra[0])
            {
                return auxBusca(no->getDir(), palavra,0);
            }
            return false;
        }
    }
    else
    {
        return false;
    }
}

void ArvTST::autocompletar(string palavra)
{
    if(getRaiz()==NULL)
    {
        cout << "Arvore vazia." << endl;
    }
    else
    {
        string novapalavra;
        if(getRaiz()->getInfo()==palavra[0])
        {
            novapalavra.push_back(getRaiz()->getInfo());
            auxAutocompletar(getRaiz()->getMeio(),palavra,1,novapalavra);
        }
        else if(getRaiz()->getInfo()>palavra[0])
        {
            auxAutocompletar(getRaiz()->getEsq(),palavra,0,novapalavra);
        }
        else if(getRaiz()->getInfo()<palavra[0])
        {
            auxAutocompletar(getRaiz()->getDir(), palavra,0,novapalavra);
        }
    }
}

void ArvTST::auxAutocompletar(NoTST* no, string palavra, int i,string novapalavra)
{
    if(i < palavra.size())
    {
        if(no->getInfo()==palavra[i])
        {
            if(i == palavra.size()-1)
            {
                imprimeAutocompletar(no, novapalavra);
            }
            else
            {
                novapalavra.push_back(no->getInfo());
                auxAutocompletar(no->getMeio(),palavra,i+1,novapalavra);
            }
        }
        else if(no->getInfo()>palavra[0])
        {
            if(i == palavra.size()-1)
            {
                imprimeAutocompletar(no, novapalavra);
            }
            else
            {
                auxAutocompletar(no->getEsq(),palavra,i,novapalavra);
            }
        }
        else if(no->getInfo()<palavra[0])
        {
            if(i == palavra.size()-1)
            {
                imprimeAutocompletar(no, novapalavra);
            }
            else
            {
                auxAutocompletar(no->getDir(), palavra,0,novapalavra);
            }
        }
    }
}

void ArvTST::imprimeAutocompletar(NoTST* no, string novapalavra)
{
    if(no!=NULL)
    {
        imprimeAutocompletar(no->getEsq(),novapalavra);
        novapalavra.push_back(no->getInfo());
        imprimeAutocompletar(no->getMeio(),novapalavra);
        if(no->getFim())
        {
            cout << novapalavra << ", ";
        }
        imprimeAutocompletar(no->getDir(), novapalavra);
        novapalavra.erase(novapalavra.end()-1);
    }
}
