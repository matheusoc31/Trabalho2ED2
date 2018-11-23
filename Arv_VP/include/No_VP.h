#ifndef NO_VP_H
#define NO_VP_H

enum Color {RED, BLACK, DOUBLE_BLACK};

class No_VP
{
public:
	No_VP(int c) { info = c; cor = RED; esq = NULL; dir = NULL; pai = NULL; }
	~No_VP() {}
    int info;
	Color cor;
	No_VP *esq;
	No_VP *dir;
	No_VP *pai;
};
#endif // NO_VP_H
