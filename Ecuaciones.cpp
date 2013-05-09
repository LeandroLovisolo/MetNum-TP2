#include "Ecuaciones.h"
#include <cmath>
#include "Matriz.h"
//M_PI 3.14159265358979323846 definido en math
Matriz *MatrizG(const int n) {
	Matriz *mat = new Matriz(n,1);
	for(int i=0;i<n;i++) {
		mat->elem(i,0) = i;
	}
	return mat;
}

Matriz *MatrizSt(const int n) {
	Matriz *mat = new Matriz(1,n);
	for(int j=0;j<n;j++) {
		mat->elem(0,j) = j+(1/2.0); //(n-1) + 1/2, Como empieza en i = 0, ((n+1)-1) + 1/2 = n + 1/2
	}
	*mat*(M_PI/n); //Multiplico por el escalar M_PI/n
	return mat;
}

double C(const int k, const int n) {
	if(k==1) return sqrt(1.0/n);
	return sqrt(2.0/n);
}

Matriz *MatrizT(const int n) {
	Matriz *st = MatrizSt(n);
	Matriz *g = MatrizG(n);
	(*g)*(*st);
	for(int j=0;j<g->cols();j++) {
		for(int i=0;i<g->fils();i++) {
			g->elem(i,j) = cos(g->elem(i,j)); //Aplico coseno a todos los elementos
		}
	}
	delete st;
	return g;
}

Matriz *MatrizMsombrero(const int n) {
	Matriz *t = MatrizT(n);
	for(int j=0;j<t->cols();j++) {
		for(int i=0;i<t->fils();i++) {
			t->elem(i,j) = C(i+1,n) * t->elem(i,j); //Mutiplico por la función C. (i+1) porque empieza en 0
		}
	}
	return t;
}

Matriz *MatrizM(const int n, const int rango) { //Rango es Q
	Matriz *Msombrero = MatrizMsombrero(n);
	for(int j=0;j<Msombrero->cols();j++) {
		for(int i=0;i<Msombrero->fils();i++) {
			Msombrero->elem(i,j) = floor((rango * Msombrero->elem(i,j) +1)/2.0);
		}
	}
	return Msombrero;
}
