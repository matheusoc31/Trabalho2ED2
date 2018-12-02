#include "../headers/libraries.h"

arv_B::arv_B(int t)
{
    tam = t;
    raiz = NULL;
}

arv_B::~arv_B()
{
    deletarArvore(this->raiz);
    delete this->raiz;
}

void arv_B::deletarArvore(No_B* no)//DELETA A ARVORE DAS FOLHAS ATE A RAIZ ATRAVEZ DA RECURSIVIDADE
{

    if(no == NULL)
        return;
    for(int i = 0; i <= no->numChaves; i++)
    {
        deletarArvore(no->filho[i]);
        delete no->filho[i];
        no->filho[i] = NULL;
    }
}

No_B* arv_B::getRaiz()
{
    return raiz;
}

void arv_B::setRaiz(No_B* no) {
    this->raiz = no;
}

void arv_B::imprime()
{
    if(raiz != NULL)
        raiz->imprimeNo();
    cout << endl;
}

No_B* arv_B::busca(int valor, unsigned int *comp, unsigned int *copias)
{
    if(raiz == NULL)
        return NULL;
    else
        return raiz->buscaNo(valor, comp, copias);
}

void arv_B::insere(GastoDeputado d, unsigned int *comp, unsigned int *copias)
{
    int valor = d.getGastoId();
    if(raiz == NULL)
    {
        raiz = new No_B(tam,true);
        raiz->numChaves = 1;
        raiz->info[0]= valor;
        raiz->dep[0]= d;
    }
    else
    {
        if(raiz->numChaves != 2*tam-1)
        {
            raiz->insereBaldeNaoCheio(d, comp, copias);
        }
        else
        {
            No_B* aux = new No_B(tam, false);
            aux->filho[0]= raiz;
            aux->split(0, raiz, comp, copias);
            int i = 0;
            *comp += 1;
            if (aux->info[0] < valor)
            {
                i++;
            }
            aux->filho[i]->insereBaldeNaoCheio(d, comp, copias);
            raiz = aux;
        }
    }
}

void arv_B::deletar(int valor, unsigned int *comp, unsigned int *copias)
{
    if (raiz == NULL)
    {
        cout << "ARVORE VAZIA";
        return;
    }
    raiz->remover(valor, comp, copias);
    if (raiz->numChaves == 0)
    {
        No_B *no = raiz;
        if (raiz->folha)
        {
            raiz = NULL;
        }
        else
        {
            raiz = raiz->filho[0];
        }
        delete no;
    }
    return;
}
