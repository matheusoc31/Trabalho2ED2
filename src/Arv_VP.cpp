#include "../headers/libraries.h"

using namespace std;

Arv_VP::Arv_VP() {
    this->raiz = NULL;
}

Arv_VP::~Arv_VP() {
    cout << "VP: Destructor called. Deleting VP." << endl;
    deleteSubTree(this->raiz);
}

void Arv_VP::deleteSubTree(No_VP* rx) {

    if(rx == NULL)
        return;

    if(rx->esq != NULL) {
        deleteSubTree(rx->esq);
        rx->esq = NULL;
    }
    else if(rx->dir != NULL) {
        deleteSubTree(rx->dir);
        rx->dir = NULL;
    }

    cout << "VP: Deleting No_VP" << rx << endl;
    //rx = NULL;
    delete rx;
    rx = NULL;
    return;
}

void Arv_VP::setRaiz(No_VP* rx) {
    this->raiz = rx;
}


int Arv_VP::getCor(No_VP *N) {
    if (N == NULL)
        return BLACK;

    return N->cor;
}

void Arv_VP::setCor(No_VP *N, Color cor) {
    if (N == NULL)
        return;

    N->cor = cor;
}

No_VP* Arv_VP::inserirRN(No_VP *raiz, No_VP *ptr, unsigned int *comp, unsigned int *copias) {
    if (raiz == NULL)
        return ptr;

    if (ptr->info < raiz->info) {
        *comp += 1;
        raiz->esq = inserirRN(raiz->esq, ptr, comp, copias);
        raiz->esq->pai = raiz;
        *copias += 1;
    } else if (ptr->info > raiz->info) {
        *comp += 2;
        raiz->dir = inserirRN(raiz->dir, ptr, comp, copias);
        raiz->dir->pai = raiz;
        *copias += 1;
    }
    *comp += 2;

    return raiz;
}

void Arv_VP::inserir(GastoDeputado dep, unsigned int *comp, unsigned int *copias) {
    No_VP *N = new No_VP(dep);
    N->dep = dep;
    N->info = dep.getGastoId();
    raiz = inserirRN(raiz, N, comp, copias);
    balancearInsercao(N, comp, copias);
}

void Arv_VP::rotacionarEsquerda(No_VP *ptr, unsigned int *comp, unsigned int *copias) {
    No_VP *dir_filho = ptr->dir;
    ptr->dir = dir_filho->esq;
    *copias += 1;

    if (ptr->dir != NULL) {
        ptr->dir->pai = ptr;
        *copias += 1;
    }

    dir_filho->pai = ptr->pai;
    *copias += 1;

    if (ptr->pai == NULL) {
        raiz = dir_filho;
    }
    else if (ptr == ptr->pai->esq) {
        ptr->pai->esq = dir_filho;
        *copias += 1;
    }
    else {
        ptr->pai->dir = dir_filho;
        *copias += 1;
    }

    dir_filho->esq = ptr;
    ptr->pai = dir_filho;
    *copias += 2;
}

void Arv_VP::rotacionarDireita(No_VP *ptr, unsigned int *comp, unsigned int *copias) {
    No_VP *esq_filho = ptr->esq;
    ptr->esq = esq_filho->dir;
    *copias += 1;

    if (ptr->esq != NULL) {
        ptr->esq->pai = ptr;
        *copias += 1;
    }

    esq_filho->pai = ptr->pai;
    *copias += 1;

    if (ptr->pai == NULL) {
        raiz = esq_filho;
        *copias += 1;
    }
    else if (ptr == ptr->pai->esq) {
        ptr->pai->esq = esq_filho;
        *copias += 1;
    }
    else {
        ptr->pai->dir = esq_filho;
        *copias += 1;
    }

    esq_filho->dir = ptr;
    ptr->pai = esq_filho;
    *copias += 2;
}

void Arv_VP::balancearInsercao(No_VP *ptr, unsigned int *comp, unsigned int *copias) {
    No_VP *pai = NULL;
    No_VP *avo = NULL;
    while (ptr != raiz && getCor(ptr) == RED && getCor(ptr->pai) == RED) {
        pai = ptr->pai;
        avo = pai->pai;
        if (pai == avo->esq) {
            No_VP *tio = avo->dir;
            if (getCor(tio) == RED) {
                setCor(tio, BLACK);
                setCor(pai, BLACK);
                setCor(avo, RED);
                ptr = avo;
            } else {
                if (ptr == pai->dir) {
                    rotacionarEsquerda(pai, comp, copias);
                    ptr = pai;
                    pai = ptr->pai;
                }
                rotacionarDireita(avo, comp, copias);
                swap(pai->cor, avo->cor);
                ptr = pai;
            }
        } else {
            No_VP *tio = avo->esq;
            if (getCor(tio) == RED) {
                setCor(tio, BLACK);
                setCor(pai, BLACK);
                setCor(avo, RED);
                ptr = avo;
            } else {
                if (ptr == pai->esq) {
                    rotacionarDireita(pai, comp, copias);
                    ptr = pai;
                    pai = ptr->pai;
                }
                rotacionarEsquerda(avo, comp, copias);
                swap(pai->cor, avo->cor);
                ptr = pai;
            }
        }
    }
    setCor(raiz, BLACK);
}

void Arv_VP::balancearRemocao(No_VP *N, unsigned int *comp, unsigned int *copias) {
    if (N == NULL)
        return;

    if (N == raiz) {
        raiz = NULL;
        return;
    }

    if (getCor(N) == RED || getCor(N->esq) == RED || getCor(N->dir) == RED) {
        No_VP *filho = N->esq != NULL ? N->esq : N->dir;

        if (N == N->pai->esq) {
            N->pai->esq = filho;
            *copias += 1;
            if (filho != NULL) {
                filho->pai = N->pai;
                *copias += 1;
            }
            setCor(filho, BLACK);
            delete (N);
        } else {
            N->pai->dir = filho;
            *copias += 1;
            if (filho != NULL) {
                filho->pai = N->pai;
                *copias += 1;
            }
            setCor(filho, BLACK);
            delete (N);
        }
    } else {
        No_VP *irmao = NULL;
        No_VP *pai = NULL;
        No_VP *ptr = N;
        setCor(ptr, DOUBLE_BLACK);
        while (ptr != raiz && getCor(ptr) == DOUBLE_BLACK) {
            pai = ptr->pai;
            if (ptr == pai->esq) {
                irmao = pai->dir;
                if (getCor(irmao) == RED) {
                    setCor(irmao, BLACK);
                    setCor(pai, RED);
                    rotacionarEsquerda(pai, comp, copias);
                } else {
                    if (getCor(irmao->esq) == BLACK && getCor(irmao->dir) == BLACK) {
                        setCor(irmao, RED);
                        if(getCor(pai) == RED)
                            setCor(pai, BLACK);
                        else
                            setCor(pai, DOUBLE_BLACK);
                        ptr = pai;
                    } else {
                        if (getCor(irmao->dir) == BLACK) {
                            setCor(irmao->esq, BLACK);
                            setCor(irmao, RED);
                            rotacionarDireita(irmao, comp, copias);
                            irmao = pai->dir;
                        }
                        setCor(irmao, pai->cor);
                        setCor(pai, BLACK);
                        setCor(irmao->dir, BLACK);
                        rotacionarEsquerda(pai, comp, copias);
                        break;
                    }
                }
            } else {
                irmao = pai->esq;
                if (getCor(irmao) == RED) {
                    setCor(irmao, BLACK);
                    setCor(pai, RED);
                    rotacionarDireita(pai, comp, copias);
                } else {
                    if (getCor(irmao->esq) == BLACK && getCor(irmao->dir) == BLACK) {
                        setCor(irmao, RED);
                        if (getCor(pai) == RED)
                            setCor(pai, BLACK);
                        else
                            setCor(pai, DOUBLE_BLACK);
                        ptr = pai;
                    } else {
                        if (getCor(irmao->esq) == BLACK) {
                            setCor(irmao->dir, BLACK);
                            setCor(irmao, RED);
                            rotacionarEsquerda(irmao, comp, copias);
                            irmao = pai->esq;
                        }
                        setCor(irmao, pai->cor);
                        setCor(pai, BLACK);
                        setCor(irmao->esq, BLACK);
                        rotacionarDireita(pai, comp, copias);
                        break;
                    }
                }
            }
        }
        if (N == N->pai->esq)
            N->pai->esq = NULL;
        else
            N->pai->dir = NULL;
        delete(N);
        setCor(raiz, BLACK);
    }
}

No_VP* Arv_VP::removerRN(No_VP *no, int info, unsigned int *comp, unsigned int *copias) {
    if (no == NULL)
        return no;

    *comp += 1;
    if (info < no->info)
        return removerRN(no->esq, info, comp, copias);

    *comp += 1;
    if (info > no->info)
        return removerRN(no->dir, info, comp, copias);

    if (no->esq == NULL || no->dir == NULL)
        return no;

    No_VP *temp = minValorNoRN(no->dir);
    no->info = temp->info;
    no->dep = temp->dep;
    return removerRN(no->dir, temp->info, comp, copias);
}

void Arv_VP::remover(int info, unsigned int *comp, unsigned int *copias) {
    No_VP *N = removerRN(raiz, info, comp, copias);
    balancearRemocao(N, comp, copias);
}

No_VP *Arv_VP::minValorNoRN(No_VP *N) {

    No_VP *ptr = N;

    while (ptr->esq != NULL)
        ptr = ptr->esq;

    return ptr;
}

No_VP* Arv_VP::maxValorNoRN(No_VP *N) {
    No_VP *ptr = N;

    while (ptr->dir != NULL)
        ptr = ptr->dir;

    return ptr;
}

int Arv_VP::getAlturaNegra(No_VP *N) {
    int alturaNegra = 0;
    while (N != NULL) {
        if (getCor(N) == BLACK)
            alturaNegra++;
        N = N->esq;
    }
    return alturaNegra;
}

void Arv_VP::imprimir()
{
    imprimePorNivel(raiz, 0);
}

void Arv_VP::imprimePorNivel(No_VP* p, int nivel)
{
    if (p != NULL)
    {
        cout << "(" << nivel << ")";
        for(int i = 1; i <= nivel; i++)
            cout << "--";
        cout << p->info << " " << p->cor << endl;
        imprimePorNivel(p->esq, nivel+1);
        imprimePorNivel(p->dir, nivel+1);
    }
}

bool Arv_VP::busca(int C, unsigned int *comp, unsigned int *copias)
{
    return auxBusca(raiz, C, comp, copias);
}

bool Arv_VP::auxBusca(No_VP* p, int C, unsigned int *comp, unsigned int *copias)
{
    if(p == NULL)
        return false;
    else if(p->info == C) {
        *comp += 1;
        return true;
    }
    else if(C < p->info) {
        *comp += 2;
        return auxBusca(p->esq, C, comp, copias);
    }
    else {
        *comp += 2;
        return auxBusca(p->dir, C, comp, copias);
    }
}

No_VP* Arv_VP::getRaiz()
{
    return raiz;
}

void Arv_VP::preOrder(No_VP *root)
{
    if(root != NULL)
    {
        cout << root->info << " ";
        preOrder(root->esq);
        preOrder(root->dir);
    }
}

void Arv_VP::printBT(const std::string& prefix, No_VP* node, bool isRight)
{
    if( node != NULL )
    {
        std::cout << prefix;

        std::cout << (isRight ? "├──" : "└──" );

        // print the value of the node
        std::cout << node->info << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isRight ? "│   " : "    "), node->dir, true);
        printBT( prefix + (isRight ? "│   " : "    "), node->esq, false);
    }
}
