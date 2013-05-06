#include <iostream>
#include "Matriz.h"
#include "Ecuaciones.h"
using namespace std;

int main() {
	//Matriz *g = MatrizG(5);
	//g->print();
	//Matriz *st = MatrizSt(5);
	//st->print();
	//delete g;
	//delete st;
	Matriz *t = MatrizT(5);
	t->print();
	//Matriz *Msom = MatrizMsombrero(5);
	//Msom->print();
	//delete &Msom;
	return 0;
}
