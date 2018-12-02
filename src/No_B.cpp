#include "../headers/libraries.h"

No_B::No_B(int tam, bool f)
{
    tamanho = tam;
    folha = f;
    numChaves = 0;
    info = new int[2*tamanho-1]();
    dep = new GastoDeputado[2*tamanho-1]();
    filho = new No_B*[2*tamanho]();
}

No_B::~No_B()
{
    delete []info;
    delete []filho;
    delete []dep;
}


int No_B::getPosicao(int valor, unsigned int *comp, unsigned int *copias)
{
    int aux=0;
    *comp += 1;
    while (aux<numChaves && this->info[aux] < valor) {
        ++aux;
        *comp += 1;
    }
    return aux;
}

No_B* No_B::buscaNo(int valor, unsigned int *comp, unsigned int *copias)
{
    int aux= 0;
    *comp += 1;
    while(aux < numChaves && valor > info[aux])
    {
        aux++;
        *comp += 1;
    }
    *comp += 1;
    if(info[aux] == valor)
    {
        return this;
    }
    if(folha == true)
    {
        return NULL;
    }
    return filho[aux]->buscaNo(valor, comp, copias);
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

void No_B::split(int valor, No_B* no, unsigned int *comp, unsigned int *copias)
{
    No_B* aux = new No_B(no->tamanho, no->folha);
    aux->numChaves = tamanho-1;

    for(int i =0; i < tamanho-1; i++)
    {
        aux->info[i]= no->info[tamanho+i];
        aux->dep[i]= no->dep[tamanho+i];
        *copias += 1;
    }
    if(no->folha == false)
    {
        for(int i =0; i< tamanho; i++) {
            aux->filho[i]= no->filho[tamanho+i];
        }
    }
    no->numChaves = tamanho-1;
    for (int i = numChaves; i >= valor +1; i--)
    {
        filho[i+1] = filho[i];
    }
    filho[valor+1] = aux;
    for(int i =numChaves-1; i >= valor; i--)
    {
        this->info[i+1] = this->info[i];
        this->dep[i+1] = this->dep[i];
        *copias += 1;
    }
    this->info[valor] = no->info[tamanho-1];
    this->dep[valor] = no->dep[tamanho-1];
    *copias += 1;
    numChaves = numChaves + 1;
    return;
}

void No_B::insereBaldeNaoCheio(GastoDeputado d, unsigned int *comp, unsigned int *copias)
{
    int valor = d.getGastoId();
    int aux = numChaves -1;
    if(folha == true)
    {
        *comp += 1;
        while (aux >= 0 && this->info[aux] > valor)
        {
            this->info[aux+1] = this->info[aux];
            this->dep[aux+1] = this->dep[aux];
            *copias += 1;
            aux--;
            *comp += 1;
        }
        this->info[aux+1] = valor;
        this->dep[aux+1] = d;
        *copias += 1;
        numChaves= numChaves+1;
    }
    else
    {
        *comp += 1;
        while (aux >= 0 && this->info[aux] > valor) {
            aux--;
            *comp += 1;
        }
        if (filho[aux+1]->numChaves == 2*tamanho-1)
        {
            split(aux+1, filho[aux+1], comp, copias);
            *comp += 1;
            if (this->info[aux+1] < valor)
                aux++;
        }
        filho[aux+1]->insereBaldeNaoCheio(d, comp, copias);
    }
    return;

}

void No_B::removeNaoFolha(int valor, unsigned int *comp, unsigned int *copias)
{
    int aux = this->info[valor];
    if (filho[valor]->numChaves >= tamanho)
    {
        GastoDeputado anterior = getAnt(valor);
        this->info[valor] = anterior.getGastoId();
        this->dep[valor] = anterior;
        *copias += 1;
        filho[valor]->remover(anterior.getGastoId(), comp, copias);
    }
    else if  (filho[valor+1]->numChaves >= tamanho)
    {
        GastoDeputado proximo = getProx(valor);
        this->info[valor] = proximo.getGastoId();
        this->dep[valor] = proximo;
        *copias += 1;
        filho[valor+1]->remover(proximo.getGastoId(), comp, copias);
    }
    else
    {
        merge(valor, comp, copias);
        filho[valor]->remover(aux, comp, copias);
    }
    return;

}

void No_B::removeFolha(int valor, unsigned int *comp, unsigned int *copias)
{
    for(int i = valor+1; i<numChaves; ++i) {
        this->info[i-1] = this->info[i];
        this->dep[i-1] = this->dep[i];
        *copias += 1;
    }
    numChaves--;
}

GastoDeputado No_B::getAnt(int valor)
{
    No_B* aux = filho[valor+1];
    while(!aux->folha)
        aux = aux->filho[0];
    return aux->dep[0];
}

GastoDeputado No_B::getProx(int valor)
{
    No_B *aux = filho[valor];
    while(!aux->folha)
        aux = aux->filho[aux->numChaves];
    return aux->dep[aux->numChaves-1];
}

void No_B::remover(int valor, unsigned int *comp, unsigned int *copias)
{
    int aux = getPosicao(valor, comp, copias);
    *comp += 1;
    if (aux < numChaves && info[aux] == valor)
    {
        if (folha)
            removeFolha(aux, comp, copias);
        else
            removeNaoFolha(aux, comp, copias);
    }
    else
    {
        if (folha)
        {
            //cout << "ESSA CHAVE NAO EXISTE NA ARVORE";
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
            completarBalde(aux, comp, copias);
        }
        if (flag && aux > numChaves)
        {
            filho[aux-1]->remover(valor, comp, copias);
        }
        else
        {
            filho[aux]->remover(valor, comp, copias);
        }
    }
    return;

}

void No_B::merge(int valor, unsigned int *comp, unsigned int *copias)
{
    No_B *baldeFilho = filho[valor];
    No_B *aux = filho[valor+1];

    baldeFilho->info[tamanho-1] = this->info[valor];
    baldeFilho->dep[tamanho-1] = this->dep[valor];
    *copias += 1;

    for (int i=0; i< aux->numChaves; ++i) {
        baldeFilho->info[i+tamanho] = aux->info[i];
        baldeFilho->dep[i+tamanho] = aux->dep[i];
        *copias += 1;
    }

    if (!baldeFilho->folha)
    {
        for(int i=0; i<= aux ->numChaves; ++i) {
            baldeFilho->filho[i+tamanho] = aux->filho[i];
        }
    }

    for (int i= valor+1; i< numChaves; ++i)
    {
        this->info[i-1] = this->info[i];
        this->dep[i-1] = this->dep[i];
        *copias += 1;
    }

    for (int i= valor+2; i<= numChaves; ++i)
    {
        filho[i-1] = filho[i];
    }

    baldeFilho->numChaves += aux->numChaves+1;
    numChaves--;

    delete(aux);
    return;
}

void No_B::completarBalde(int valor, unsigned int *comp, unsigned int *copias)
{
    if (valor != 0 && filho[valor-1]->numChaves >= tamanho)
    {
        pegarDoAnterior(valor, comp, copias);
    }
    else
    {
        if (valor != numChaves && filho[valor+1]->numChaves >= tamanho)
        {
            pegarDoProximo(valor, comp, copias);
        }
        else
        {
            if (valor != numChaves)
                merge(valor, comp, copias);
            else
                merge(valor-1, comp, copias);
        }
    }
    return;

}

void No_B::pegarDoAnterior(int valor, unsigned int *comp, unsigned int *copias)
{
    No_B* baldeFilho = filho[valor];
    No_B* aux = filho[valor-1];

    for (int i = baldeFilho->numChaves-1; i>=0; --i)
    {
        baldeFilho->info[i+1] = baldeFilho->info[i];
        baldeFilho->dep[i+1] = baldeFilho->dep[i];
        *copias += 1;
    }
    if (!baldeFilho->folha)
    {
        for(int i = baldeFilho->numChaves; i >= 0; --i)
        {
            baldeFilho->filho[i+1] = baldeFilho->filho[i];
        }
    }
    baldeFilho->info[0] = this->info[valor-1];
    baldeFilho->dep[0] = this->dep[valor-1];
    *copias += 1;
    if(!baldeFilho->folha)
    {
        baldeFilho->filho[0] = aux->filho[aux->numChaves];
    }
    this->info[valor-1] = aux->info[aux->numChaves-1];
    this->dep[valor-1] = aux->dep[aux->numChaves-1];
    *copias += 1;

    baldeFilho->numChaves += 1;
    aux->numChaves -= 1;
    return;

}

void No_B::pegarDoProximo(int valor, unsigned int *comp, unsigned int *copias)
{
    No_B* baldeFilho = filho[valor];
    No_B* aux = filho[valor+1];

    baldeFilho->info[(baldeFilho->numChaves)] = this->info[valor];
    baldeFilho->dep[(baldeFilho->numChaves)] = this->dep[valor];
    *copias += 1;
    if (!(baldeFilho->folha))
    {
        baldeFilho->filho[(baldeFilho->numChaves)+1] = aux->filho[0];
    }
    this->info[valor] = aux->info[0];
    this->dep[valor] = aux->dep[0];
    *copias += 1;
    for (int i=1; i< aux->numChaves; ++i)
    {
        aux->info[i-1] = aux->info[i];
        aux->dep[i-1] = aux->dep[i];
        *copias += 1;
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
