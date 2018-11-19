#ifndef NO_H
#define NO_H

class No
{
    public:
    No()                  {};
    ~No()                 {};
    void setEsq(No* p)    { esq = p; };
    void setInfo(int val) { info = val; };
    void setDir(No* p)    { dir = p; };
    No* getEsq()          { return esq; };
    int getInfo()         { return info; };
    No* getDir()          { return dir; };

  private:
    No* esq; // ponteiro para o filho a esquerda
    int info; // informação do No (int)
    No* dir; // ponteiro para o filho a direita
};

#endif // NO_H
