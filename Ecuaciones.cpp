#include "Ecuaciones.h"
#include <cmath>
#include "Matriz.h"
#include <iostream> //Para algunos cout, borrar si no estan
using namespace std;
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

Matriz *MatrizM(const int n, const int rango) { //Rango es Q = max - min de la señal
	Matriz *Msombrero = MatrizMsombrero(n);
	for(int j=0;j<Msombrero->cols();j++) {
		for(int i=0;i<Msombrero->fils();i++) {
			Msombrero->elem(i,j) = floor((rango * Msombrero->elem(i,j) +1)/2.0);
		}
	}
	return Msombrero;
}

//PSNR para ondas de sonido
double PSNR(Matriz *matOriginal, Matriz *matPerturbada, const int rangoMax) {
	//10 * log10( rango^2 / ECM)
	return 10 * log10( pow(rangoMax, 2) / ECM(matOriginal, matPerturbada) );
}

//Error cuadrático medio para ondas de sonido
double ECM(Matriz *matOriginal, Matriz *matPerturbada) {
	double acum = 0;
	for(int i=0;i<matOriginal->fils();i++) {
		for(int j=0;j<matOriginal->cols();j++) {
			acum += pow( matOriginal->elem(i,j) - matPerturbada->elem(i,j) , 2);
		}
	}
	return acum/(matOriginal->fils()*matOriginal->cols());
}

void PruebaMetodo1(Matriz *Xoriginal) {
	//Creo 'y' y x
	cout << "Matriz original" << endl;
	Xoriginal->print();
	Matriz XconRuido = Matriz(Xoriginal->fils(),Xoriginal->cols());
	//Uso como rango max, pongo en y y la matriz M para hacer y = m*x'
	Matriz *y = MatrizM(Xoriginal->fils(), Xoriginal->max());
	XconRuido = (*Xoriginal); //La copio de la original
	//Agrego ruido a x (señal original)
	//XconRuido.agregarRuidoAditivo(); //Le agrego ruido
	//cout << "Ruido agregado PSNR: " << PSNR(Xoriginal, &XconRuido, Xoriginal->max()) << endl;
	(*y)*XconRuido; // y = m*x
	//Modifico y para intentar remover el ruido
	//y->eliminarRuidoMetodo1();
	//Vuelvo para atrás resolviendo M * Xreconstruido =y'
	Matriz *u = MatrizM(Xoriginal->fils(), Xoriginal->max());
	pair<Matriz*, Matriz*> pl = u->factorizacionPLU();
	cout << "Matriz L: " << endl;
	pl.second->print();
	//Hago Lj = Py
	(*pl.first)*(*y); //Py
	Matriz *j = pl.second->forwardSubstitution(pl.first); //Lj = Py
	//Hago Ux = j
	Matriz *XSinRuido = u->backwardsSubstitution(j);
	cout << "Matriz devuelta" << endl;
	XSinRuido->print();
	cout << "Resultado PSNR: " << PSNR(Xoriginal, XSinRuido, Xoriginal->max()) << endl;
	delete y;
	delete u;
	delete pl.first;
	delete pl.second;
	delete j;
	delete XSinRuido;
}