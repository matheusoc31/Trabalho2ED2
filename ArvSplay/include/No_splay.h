#ifndef NO_SPLAY_H
#define NO_SPLAY_H


class No_splay
{
public:
    No_splay() ;

    void setInfo(int val);
    void setEsq(No_splay* p);
    void setDir(No_splay* p);

    int getInfo();
    No_splay* getEsq();
    No_splay* getDir();

private:
    int info; // informação do No (int)
    No_splay* esq; // ponteiro para o filho a esquerda
    No_splay* dir; // ponteiro para o filho a direita
};

#endif // NO_SPLAY_H
