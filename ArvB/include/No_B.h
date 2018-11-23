#ifndef NO_B_H
#define NO_B_H
#include <iostream>

using namespace std;

class No_B
{
public:
    No_B();
    No_B(int tamanho, bool f);
    ~No_B();

    No_B* buscaNo(int valor);
    int getPosicao(int chave);
    void imprimeNo();

    void split(int valor, No_B* no);
    void insereBaldeNaoCheio(int valor);
    void removeNaoFolha(int valor);
    void removeFolha(int valor);
    void remover(int valor);
    int getProx(int valor);
    int getAnt(int valor);
    void merge(int valor);
    void completarBalde(int valor);
    void pegarDoAnterior(int valor);
    void pegarDoProximo(int valor);




    int tamanho;
    int numChaves;
    bool folha;
    int* info;
    No_B** filho;

};

#endif // NO_B_H
