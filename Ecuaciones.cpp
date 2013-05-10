
#include <cmath>
#include <iostream> //Para algunos cout, borrar si no estan
#include <fstream>

#include "Ecuaciones.h"
#include "Metodos.h"

using namespace std;
//M_PI 3.14159265358979323846 definido en math
Matriz *MatrizG(const int n) {
	Matriz *mat = new Matriz(n,1);
	for(int i=0;i<n;i++) {
		mat->elem(i,0) = i;
	}
	return mat;
}

Matriz* MatrizSt(const int n) {
	Matriz m(1,n);
	for(int j = 0; j < n; j++) {
		m.elem(0, j) = j + (1 / 2.0); //(n-1) + 1/2, Como empieza en i = 0, ((n+1)-1) + 1/2 = n + 1/2
	}
	return m * (M_PI / n);
}

double C(const int k, const int n) {
	if(k==1) return sqrt(1.0/n);
	return sqrt(2.0/n);
}

Matriz *MatrizT(const int n) {
	Matriz *st = MatrizSt(n);
	Matriz *g = MatrizG(n);
	(*g)*(*st);
	for(int j=0;j<g->columnas();j++) {
		for(int i=0;i<g->filas();i++) {
			g->elem(i,j) = cos(g->elem(i,j)); //Aplico coseno a todos los elementos
		}
	}
	delete st;
	return g;
}

Matriz *MatrizMsombrero(const int n) {
	Matriz *t = MatrizT(n);
	for(int j=0;j<t->columnas();j++) {
		for(int i=0;i<t->filas();i++) {
			t->elem(i,j) = C(i+1,n) * t->elem(i,j); //Mutiplico por la función C. (i+1) porque empieza en 0
		}
	}
	return t;
}

Matriz *MatrizM(const int n, const int rango) { //Rango es Q = max - min de la señal
	Matriz *Msombrero = MatrizMsombrero(n);
	for(int j=0;j<Msombrero->columnas();j++) {
		for(int i=0;i<Msombrero->filas();i++) {
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
	for(int i=0;i<matOriginal->filas();i++) {
		for(int j=0;j<matOriginal->columnas();j++) {
			acum += pow( matOriginal->elem(i,j) - matPerturbada->elem(i,j) , 2);
		}
	}
	return acum/(matOriginal->filas()*matOriginal->columnas());
}

bool grabarSonido(Matriz *mat, char *fileName) {
	ofstream file(fileName);
	if(file.is_open()) {
		for(int i=0;i<mat->filas();i++) {
			for(int j=0;j<mat->columnas();j++) {
				file << mat->elem(i,j) << " ";
			}
		}
		file.close();
	}
	return mat;
}

void PruebaMetodo1(Matriz *Xoriginal) {
	/*
	//Creo 'y' y x
	//cout << "Matriz original: " << endl;
	//Xoriginal->print();

	//Matriz XconRuido = Matriz(Xoriginal->filas(),Xoriginal->columnas());
	Matriz XconRuido(*Xoriginal);

	//Uso como rango max, pongo en y y la matriz M para hacer y = m*x'
	Matriz *y = MatrizM(Xoriginal->filas(), Xoriginal->max());
	XconRuido = (*Xoriginal); //La copio de la original
	//Agrego ruido a x (señal original)
	agregarRuidoAditivo(XconRuido); //Le agrego ruido
	grabarSonido(&XconRuido, (char*) "dopp512ConRuido.txt");
	cout << "Ruido agregado PSNR: " << PSNR(Xoriginal, &XconRuido, Xoriginal->max()) << endl;
	(*y)*XconRuido; // y = m*x
	//Modifico y para intentar remover el ruido
	eliminarRuidoMetodo1(*y);
	//Vuelvo para atrás resolviendo M * Xreconstruido =y'
	//cout << "y = m*x" << endl;
	//y->print();
	Matriz *u = MatrizM(Xoriginal->filas(), Xoriginal->max());
	pair<Matriz*, Matriz*> pl = u->factorizacionPLU();
	//cout << "Matriz P: " << endl;
	//pl.first->print();
	//cout << "Matriz L: " << endl;
	//pl.second->print();
	//Hago Lj = Py
	(*pl.first)*(*y); //Py
	//cout << "P*y" << endl;
	//pl.first->print();
	Matriz *j = pl.second->forwardSubstitution(pl.first); //Lj = Py
	//Hago Ux = j
	Matriz *XSinRuido = u->backwardsSubstitution(j);
	grabarSonido(XSinRuido, (char*) "dopp512SinRuido.txt");
	//cout << "Matriz devuelta" << endl;
	//XSinRuido->print();
	cout << "Resultado PSNR: " << PSNR(Xoriginal, XSinRuido, Xoriginal->max()) << endl;
	delete y;
	delete u;
	delete pl.first;
	delete pl.second;
	delete j;
	delete XSinRuido;
	*/
}
