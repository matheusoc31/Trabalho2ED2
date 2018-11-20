#include "No_splay.h"

No_splay::No_splay()
{
}

void No_splay::setInfo(int val)
{
    info = val;
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
    return info;
}

No_splay* No_splay::getEsq()
{
    return esq;
}

No_splay* No_splay::getDir()
{
    return dir;
}

