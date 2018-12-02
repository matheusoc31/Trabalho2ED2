#include "../headers/libraries.h"

No_splay::No_splay() {}

No_splay::No_splay(GastoDeputado dep) {
    this->dep = dep;
    this->info = dep.getGastoId();
}

void No_splay::setInfo(int val)
{
    info = val;
}

void No_splay::setDep(GastoDeputado dep)
{
    this->dep = dep;
}

void No_splay::setEsq(No_splay* p)
{
    esq = p;
}

void No_splay::setDir(No_splay* p)
{
    dir = p;
}


int No_splay::getInfo()
{
    //cout << "INFO = " << info << endl;
    return info;
}

GastoDeputado No_splay::getDep()
{
    return dep;
}

No_splay* No_splay::getEsq()
{
    return esq;
}

No_splay* No_splay::getDir()
{
    return dir;
}

