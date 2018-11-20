#include <iostream>
#include "arv_splay.h"
#include <cstdio>

using namespace std;

arv_splay::arv_splay()
{
    raiz = NULL;
}

No_splay* arv_splay::getRaiz()
{
    return raiz;
}

No_splay* arv_splay::splaying(No_splay* no, int val)
{
    if(no == NULL)//CONDICAO DE PARADA SE NAO ACHAR O VALOR
    {
        return NULL;
    }
    if(no->getInfo() == val)//CONDICAO DE PARADA SE ACHAR O NO
    {
        return no;
    }
    if(val < no->getInfo())
    {
        if(no->getEsq() != NULL)
        {
            no->setEsq(splaying(no->getEsq(), val));
            no = zagDir(no);
        }
    }
    if(val > no->getInfo())
    {
        if(no->getDir() != NULL)
        {
            no->setDir(splaying(no->getDir(), val));
            no = zigEsq(no);
        }
    }
    return no;
}

No_splay* arv_splay::zagDir(No_splay* no)
{
    No_splay* temp = no;//NO UTILIZADO PARA AUXILIAR NA ROTACAO
    no = no->getEsq();
    temp->setEsq(no->getDir());
    no->setDir(temp);
    return no;
}

No_splay* arv_splay::zigEsq(No_splay* no)
{
    No_splay* temp = no;//NO UTILIZADO PARA AUXILIAR NA ROTACAO
    no = no->getDir();
    temp->setDir(no->getEsq());
    no->setEsq(temp);
    return no;
}

void arv_splay::insere(int val)
{
    raiz = auxInsere(raiz, val);
}

No_splay* arv_splay::auxInsere(No_splay* no, int val)
{
    if(no == NULL)
    {
        no = new No_splay;
        no->setInfo(val);
        no->setEsq(NULL);
        no->setDir(NULL);
    }
    else if(val < no->getInfo())
        no->setEsq(auxInsere(no->getEsq(), val));
    else
        no->setDir(auxInsere(no->getDir(), val));
    no = splaying(no, val);
    return no;
}

void arv_splay::remove(int val)
{
    if(auxBusca(raiz,val))
    {
        No_splay* aux = raiz;
        if(aux->getEsq()!= NULL)
        {
            aux = aux->getEsq();
            raiz = splaying(raiz,aux->getInfo());
        }
        raiz = auxRemove(raiz,val);
    }
}

No_splay* arv_splay::auxRemove(No_splay* no, int val)
{
    if(no == NULL)
        return NULL;
    else if(val < no->getInfo())
        no->setEsq(auxRemove(no->getEsq(), val));
    else if(val > no->getInfo())
        no->setDir(auxRemove(no->getDir(), val));
    else
    {
        if(no->getEsq() == NULL && no->getDir() == NULL)//SE O NO FOR UMA FOLHA
        {
            delete no;
            no = NULL;
        }
        else if((no->getEsq() == NULL) || (no->getDir() == NULL))//SE O NO TIVER UM FILHO
        {
            No_splay* aux;
            if(no->getEsq() == NULL)
                aux = no->getDir();
            else
                aux = no->getEsq();
            delete no;
            no = aux;
        }
        else
        {
            No_splay *aux = menorSubArvDireita(no);
            int auxC = aux->getInfo();
            no->setInfo(auxC);
            aux->setInfo(val);
            no->setDir(auxRemove(no->getDir(), val));
        }
    }
    return no;
}

No_splay* arv_splay::menorSubArvDireita(No_splay* no)
{
    No_splay *aux = no->getDir();
    while(aux->getEsq() != NULL)
        aux = aux->getEsq();
    return aux;
}

void arv_splay::busca(int val)
{
    if(auxBusca(raiz,val))
    {
        cout << "Elemento encontrado!" << endl;
    }
    else
    {
        cout << "Elemento inexistente!" << endl;
    }
}

bool arv_splay::auxBusca(No_splay* no, int val)
{
    if(no != NULL)
    {
        if(val < no->getInfo() && no->getEsq() == NULL)
        {
            raiz = splaying(raiz, no->getInfo());
            return false;
        }
        else if(val > no->getInfo() && no->getDir() == NULL)
        {
            raiz = splaying(raiz, no->getInfo());
            return false;
        }
        else if(val < no->getInfo())
        {
            auxBusca(no->getEsq(), val);
        }
        else if(val > no->getInfo())
        {
            auxBusca(no->getDir(), val);
        }
        else
        {
            raiz = splaying(raiz, val);
            return true;
        }
    }
    else
    {
        cout << "Arvore vazia!" << endl;
        return false;
    }
}

void arv_splay::printBT(const std::string& prefix, No_splay* node, bool isRight)
{
    if( node != nullptr )
    {
        std::cout << prefix;

        std::cout << (isRight ? "|----" : "|____" );

        // print the value of the node
        std::cout << node->getInfo() << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isRight ? "|   " : "    "), node->getDir(), true);
        printBT( prefix + (isRight ? "|   " : "    "), node->getEsq(), false);
    }
}

void arv_splay::preOrder(No_splay* root)
{
    if(root != NULL)
    {
        printf("%d ", root->getInfo());
        preOrder(root->getEsq());
        preOrder(root->getDir());
    }
}
