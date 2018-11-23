#include "No_B.h"
#include "iostream"

using namespace std;


No_B::No_B(int tam, bool f)
{
    tamanho = tam;
    folha = f;
    numChaves = 0;
    info = new int[2*tamanho-1]();
    filho = new No_B*[2*tamanho]();
}

No_B::~No_B()
{
    delete []info;
    delete []filho;
}


int No_B::getPosicao(int valor)
{
    int aux=0;
    while (aux<numChaves && info[aux] < valor)
        ++aux;
    return aux;
}

No_B* No_B::buscaNo(int valor)
{
    int aux= 0;
    while(aux < numChaves && valor > info[aux])
    {
        aux++;
    }
    if(info[aux] == valor)
    {
        return this;
    }
    if(folha == true)
    {
        return NULL;
    }
    return filho[aux]->buscaNo(valor);
}

void No_B::imprimeNo()
{
    int i;
    for (i = 0; i < numChaves; i++)
    {
        if (folha == false)
            filho[i]->imprimeNo();
        cout << " " << info[i];
    }
    if (folha == false)
        filho[i]->imprimeNo();
}

void No_B::split(int valor, No_B* no)
{
    No_B* aux = new No_B(no->tamanho, no->folha);
    aux->numChaves = tamanho-1;

    for(int i =0; i < tamanho-1; i++)
    {
        aux->info[i]= no->info[tamanho+i];
    }
    if(no->folha == true)
    {
        for(int i =0; i< tamanho; i++)
            aux->filho[i]= no->filho[tamanho+i];
    }
    no->numChaves = tamanho-1;
    for (int i = numChaves; i >= valor +1; i--)
    {
        filho[i+1] = filho[i];
    }
    filho[valor+1] = aux;
    for(int i =numChaves-1; i >= valor; i--)
    {
        info[i+1] = info[i];
    }
    info[valor] = no->info[tamanho-1];
    numChaves = numChaves + 1;
    return;
}

void No_B::insereBaldeNaoCheio(int valor)
{
    int aux = numChaves -1;
    if(folha == true)
    {
        while (aux >= 0 && info[aux] > valor)
        {
            info[aux+1] = info[aux];
            aux--;
        }
        info[aux+1] = valor;
        numChaves= numChaves+1;
    }
    else
    {
        while (aux >= 0 && info[aux] > valor)
            aux--;
        if (filho[aux+1]->numChaves == 2*tamanho-1)
        {
            split(aux+1, filho[aux+1]);
            if (info[aux+1] < valor)
                aux++;
        }
        filho[aux+1]->insereBaldeNaoCheio(valor);
    }
    return;

}

void No_B::removeNaoFolha(int valor)
{
    int aux = info[valor];
    if (filho[valor]->numChaves >= tamanho)
    {
        int anterior = getAnt(valor);
        info[valor] = anterior;
        filho[valor]->remover(anterior);
    }
    else if  (filho[valor+1]->numChaves >= tamanho)
    {
        int proximo = getProx(valor);
        info[valor] = proximo;
        filho[valor+1]->remover(proximo);
    }
    else
    {
        merge(valor);
        filho[valor]->remover(aux);
    }
    return;

}

void No_B::removeFolha(int valor)
{
    for(int i= valor+1; i<numChaves; ++i)
        info[i-1] = info[i];
    numChaves--;
}

int No_B::getAnt(int valor)
{
    No_B* aux = filho[valor+1];
    while(!aux->folha)
        aux = aux->filho[0] ;
    return aux->info[0];
}

int No_B::getProx(int valor)
{
    No_B *aux = filho[valor];
    while(!aux->folha)
        aux = aux->filho[aux->numChaves];
    return aux->info[aux->numChaves-1];
}

void No_B::remover(int valor)
{
    int aux = getPosicao(valor);
    if (aux < numChaves && info[aux] == valor)
    {
        if (folha)
            removeFolha(aux);
        else
            removeNaoFolha(aux);
    }
    else
    {
        if (folha)
        {
            cout << "ESSA CHAVE NAO EXISTE NA ARVORE";
            return;
        }
        bool flag;
        if(aux==numChaves)
        {
            flag=true;
        }
        else
        {
            flag = false;
        }

        if (filho[aux]->numChaves < tamanho)
        {
            completarBalde(aux);
        }
        if (flag && aux > numChaves)
        {
            filho[aux-1]->remover(valor);
        }
        else
        {
            filho[aux]->remover(valor);
        }
    }
    return;

}

void No_B::merge(int valor)
{
    No_B *baldeFilho = filho[valor];
    No_B *aux = filho[valor+1];

    baldeFilho->info[tamanho-1] = info[valor];

    for (int i=0; i< aux->numChaves; ++i)
        baldeFilho->info[i+tamanho] = aux->info[i];

    if (!baldeFilho->folha)
    {
        for(int i=0; i<= aux ->numChaves; ++i)
            baldeFilho->filho[i+tamanho] = aux ->filho[i];
    }

    for (int i= valor+1; i< numChaves; ++i)
    {
        info[i-1] = info[i];
    }

    for (int i= valor+2; i<= numChaves; ++i)
    {
        filho[i-1] = filho[i];
    }

    baldeFilho->numChaves += aux ->numChaves+1;
    numChaves--;

    delete(aux);
    return;
}

void No_B::completarBalde(int valor)
{
    if (valor != 0 && filho[valor-1]->numChaves >= tamanho)
    {
        pegarDoAnterior(valor);
    }
    else
    {
        if (valor != numChaves && filho[valor+1]->numChaves >= tamanho)
        {
            pegarDoProximo(valor);
        }
        else
        {
            if (valor != numChaves)
                merge(valor);
            else
                merge(valor-1);
        }
    }
    return;

}

void No_B::pegarDoAnterior(int valor)
{
    No_B* baldeFilho = filho[valor];
    No_B* aux = filho[valor-1];

    for (int i = baldeFilho->numChaves-1; i>=0; --i)
    {
        baldeFilho->info[i+1] = baldeFilho->info[i];
    }
    if (!baldeFilho->folha)
    {
        for(int i = baldeFilho->numChaves; i >= 0; --i)
        {
            baldeFilho->filho[i+1] = baldeFilho->filho[i];
        }
    }
    baldeFilho->info[0] = info[valor-1];
    if(!baldeFilho->folha)
    {
        baldeFilho->filho[0] = aux->filho[aux->numChaves];
    }
    info[valor-1] = aux->info[aux->numChaves-1];
    baldeFilho->numChaves += 1;
    aux->numChaves -= 1;
    return;

}

void No_B::pegarDoProximo(int valor)
{
    No_B* baldeFilho = filho[valor];
    No_B* aux = filho[valor+1];

    baldeFilho->info[(baldeFilho->numChaves)] = info[valor];
    if (!(baldeFilho->folha))
    {
        baldeFilho->filho[(baldeFilho->numChaves)+1] = aux->filho[0];
    }
    info[valor] = aux->info[0];
    for (int i=1; i< aux->numChaves; ++i)
    {
        aux->info[i-1] = aux->info[i];
    }
    if (!aux->folha)
    {
        for(int i = 1; i <= aux->numChaves; ++i)
        {
            aux->filho[i-1] = aux->filho[i];
        }
    }
    baldeFilho->numChaves += 1;
    aux->numChaves -= 1;
    return;

}
