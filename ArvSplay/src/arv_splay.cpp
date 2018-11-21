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

No_splay* arv_splay::zag(No_splay* no)
{
    /*
    No_splay* temp = no->getDir();
    No_splay* dir = no->getDir();

    dir = temp->getEsq();
    temp = temp->getEsq();
    temp= no;
    return no;
    */
    No_splay* temp = no->getEsq();//NO UTILIZADO PARA AUXILIAR NA ROTACAO
    no->setEsq(temp->getDir());
    temp->setDir(no);
    return temp;
}

No_splay* arv_splay::zig(No_splay* no)
{
    /*
     No_splay* temp = no->getEsq();//NO UTILIZADO PARA AUXILIAR NA ROTACAO
     No_splay* esq = no->getEsq();

     esq = temp->getDir();
     temp = temp->getDir();
     temp= no;
     return no;
     */

    No_splay* temp = no->getDir();//NO UTILIZADO PARA AUXILIAR NA ROTACAO
    no->setDir(temp->getEsq());
    temp->setEsq(no);
    return temp;

}

No_splay* arv_splay::splaying(No_splay* no, int val)
{
     if(no == NULL || no->getInfo() == val)
     {
         return no;
     }
     No_splay* aux;
     if (no->getInfo() > val)
     {
         if(no->getEsq()==NULL)
             return no;
         if(no->getEsq()->getInfo() > val)
         {
             aux = no->getEsq();
             aux->setEsq(splaying(aux->getEsq(), val));
             no = zig(no);
         }
         else if (no->getEsq()->getInfo() < val)
         {
             aux = no->getEsq();
             aux->setDir(splaying(aux->getDir(),val));
             if(aux->getDir() != NULL)
                 no->setEsq(zag(no->getEsq()));
         }
         return (no->getEsq() == NULL)? no: zig(no);
     }
     else
     {
         if(no->getDir()==NULL)
             return no;
         if(no->getDir()->getInfo() >  val)
         {
             aux = no->getDir();
             aux->setEsq(splaying(aux->getEsq(),val));
             if(aux->getEsq() != NULL)
             {
                 no->setDir(zig(no->getDir()));
             }
         }
         else if(no->getDir()->getInfo() < val)
         {
             aux = no->getDir();
             aux->setDir(splaying(aux->getDir(), val));
             no = zag(no);
         }
         return (no->getDir() == NULL)? no: zag(no);
     }

    /*
    if(no==NULL || no->getInfo() == val)
    {
        return no;
    }

    if(val < no->getInfo())
    {
        if(no->getEsq() != NULL)
        {
            no->setEsq(splaying(no->getEsq(), val));
            no = zag(no);
        }
    }
    if(val > no->getInfo())
    {
        if(no->getDir() != NULL)
        {
            no->setDir(splaying(no->getDir(), val));
            no = zig(no);
        }
    }
    return no;
    */
}

void arv_splay::insere(int val)
{
    raiz = auxInsere(raiz, val);
}

No_splay* arv_splay::auxInsere(No_splay* no, int val)
{
    if(no == NULL)
    {
        No_splay* aux = new No_splay;
        aux->setInfo(val);
        aux->setEsq(NULL);
        aux->setDir(NULL);
        return(aux);
    }
    no = splaying(no, val);

    if(no->getInfo() == val)
        return no;

    No_splay* newNo = new No_splay;
    newNo->setInfo(val);
    newNo->setEsq(NULL);
    newNo->setDir(NULL);

    if(no->getInfo() > val) {
        newNo->setDir(no);
        newNo->setEsq(no->getEsq());
        no->setEsq(NULL);
    } else {
        newNo->setEsq(no);
        newNo->setDir(no->getDir());
        no->setDir(NULL);
    }
    return newNo;

    /*
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
    */

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
