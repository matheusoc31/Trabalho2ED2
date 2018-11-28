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
        NoTST* getMeio() {return meio;};
        void setMeio(NoTST* novo) {meio = novo;};
        string getInfo() {return info;};
        void setInfo(string novo) {info = novo;};
        bool getFim() {return fim;};
        void SetFim(bool novo) {fim = novo;};
        double getGasto() {return gasto;};
        void setGasto(double novo) {gasto = novo;};
    private:
        NoTST* esq;
        NoTST* dir;
        NoTST* meio;
        string info;
        bool fim;
        double gasto;
};

#endif // NOTST_H
