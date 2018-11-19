#include <iostream>
#include "arv_splay.h"
#include <cstdio>

using namespace std;

arv_splay::arv_splay()
{
    raiz = NULL;
}

No* arv_splay::getRaiz()
{
    return raiz;
}

No* arv_splay::splaying(No* no, int val)
{
    if(no == NULL)
    {
        return NULL;
    }
    if(no->getInfo() == val)
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

No* arv_splay::zagDir(No* no)
{
    No* temp = no;
    no = no->getEsq();
    temp->setEsq(no->getDir());
    no->setDir(temp);
    return no;
}

No* arv_splay::zigEsq(No* no)
{
    No* temp = no;
    no = no->getDir();
    temp->setDir(no->getEsq());
    no->setEsq(temp);
    return no;
}

void arv_splay::insere(int val)
{
    raiz = auxInsere(raiz, val);
}

No* arv_splay::auxInsere(No* no, int val)
{
    if(no == NULL)
    {
        no = new No;
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
        No* aux = raiz;
        if(aux->getEsq()!= NULL)
        {
            aux = aux->getEsq();
            raiz = splaying(raiz,aux->getInfo());
        }
        raiz = auxRemove(raiz,val);
    }
}

No* arv_splay::auxRemove(No* no, int val)
{
    if(no == NULL)
        return NULL;
    else if(val < no->getInfo())
        no->setEsq(auxRemove(no->getEsq(), val));
    else if(val > no->getInfo())
        no->setDir(auxRemove(no->getDir(), val));
    else
    {
        if(no->getEsq() == NULL && no->getDir() == NULL)
            no = removeFolha(no);
        else if((no->getEsq() == NULL) || (no->getDir() == NULL))
            no = removeUmFilho(no);
        else
        {
            No *aux = menorSubArvDireita(no);
            int auxC = aux->getInfo();
            no->setInfo(auxC);
            aux->setInfo(val);
            no->setDir(auxRemove(no->getDir(), val));
        }
    }
    return no;
}

No* arv_splay::removeFolha(No* no)
{
    delete no;
    return NULL;
}

No* arv_splay::removeUmFilho(No* no)
{
    No* aux;
    if(no->getEsq() == NULL)
        aux = no->getDir();
    else
        aux = no->getEsq();
    delete no;
    return aux;
}

No* arv_splay::menorSubArvDireita(No* no)
{
    No *aux = no->getDir();
    while(aux->getEsq() != NULL)
        aux = aux->getEsq();
    return aux;
}

void arv_splay::imprime()
{
    imprimeporNivel(raiz,0);
}

void arv_splay::imprimeporNivel(No* no, int nivel)
{
    if (no != NULL)
    {
        cout << "(" << nivel << ")";
        for(int i = 1; i <= nivel; i++)
            cout << "--";
        cout << no->getInfo() << endl;
        imprimeporNivel(no->getEsq(), nivel+1);
        imprimeporNivel(no->getDir(), nivel+1);
    }
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

bool arv_splay::auxBusca(No* no, int val)
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

void arv_splay::printBT(const std::string& prefix, No *node, bool isRight)
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

void arv_splay::preOrder(No* root)
{
    if(root != NULL)
    {
        printf("%d ", root->getInfo());
        preOrder(root->getEsq());
        preOrder(root->getDir());
    }
}



