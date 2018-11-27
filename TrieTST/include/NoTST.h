#ifndef NOTST_H
#define NOTST_H

using namespace std;

class NoTST
{
    public:
        NoTST(){};
        ~NoTST(){};
        NoTST* getEsq() {return esq;};
        void setEsq(NoTST* novo) {esq = novo;};
        NoTST* getDir() {return dir;};
        void setDir(NoTST* novo) {dir = novo;};
        NoTST* getFilho() {return filho;};
        void setFilho(NoTST* novo) {filho = novo;};
        string getInfo() {return info;};
        void setInfo(string novo) {info = novo;};
        bool getFim() {return fim;};
        void SetFim(bool novo) {fim = novo;};
    private:
        NoTST* esq;
        NoTST* dir;
        NoTST* filho;
        string info;
        bool fim;
};

#endif // NOTST_H
