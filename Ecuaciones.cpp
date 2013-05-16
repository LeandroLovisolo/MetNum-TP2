#include <cmath>
#include <iostream> //Para algunos cout, borrar si no estan

#include "Ecuaciones.h"
#include "Metodos.h"

using namespace std;

Matriz* MatrizG(const int n) {
	Matriz* mat = new Matriz(n,1);
	for(int i = 0; i < n; i++) {
		mat->elem(i, 0) = i;
	}
	return mat;
}

Matriz* MatrizSt(const int n) {
	Matriz m(1, n);
	for(int j = 0; j < n; j++) {
		m.elem(0, j) = j + (1 / 2.0); // (n-1) + 1/2, Como empieza en i = 0, ((n+1)-1) + 1/2 = n + 1/2
	}
	return m * (M_PI / n);
}

double C(const int k, const int n) {
	if(k == 1) return sqrt(1.0 / n);
	return sqrt(2.0 / n);
}

Matriz* MatrizT(const int n) {
	Matriz* st = MatrizSt(n);
	Matriz* g = MatrizG(n);
	Matriz* t = (*g) * (*st);
	for(int j = 0; j < t->columnas(); j++) {
		for(int i = 0; i < t->filas(); i++) {
			t->elem(i, j) = cos(t->elem(i, j)); // Aplico coseno a todos los elementos
		}
	}
	delete st;
	delete g;
	return t;
}

Matriz* MatrizMsombrero(const int n) {
	Matriz* t = MatrizT(n);
	for(int j = 0; j < t->columnas(); j++) {
		for(int i = 0; i < t->filas(); i++) {
			t->elem(i, j) = C(i + 1, n) * t->elem(i, j); // Mutiplico por la función C. (i+1) porque empieza en 0
		}
	}
	return t;
}

Matriz* MatrizM(const int n, const int rango) { //Rango es Q = max - min de la señal
	Matriz* Msombrero = MatrizMsombrero(n);
	for(int j = 0; j < Msombrero->columnas(); j++) {
		for(int i = 0; i < Msombrero->filas(); i++) {
			Msombrero->elem(i, j) = floor((rango * Msombrero->elem(i ,j) + 1) / 2.0);
		}
	}
	return Msombrero;
}

// PSNR para ondas de sonido
double PSNR(Matriz& matOriginal, Matriz& matPerturbada, const int rangoMax) {
	//10 * log10( rango^2 / ECM)
	double ecm = ECM(matOriginal, matPerturbada);
	//cout << "error cuadratico: " << ecm << endl;

	return 10 * log10( pow(rangoMax, 2) / ecm);
}

//Error cuadrático medio para ondas de sonido
double ECM(Matriz& matOriginal, Matriz& matPerturbada) {
	double acum = 0;
	for(int i = 0; i < matOriginal.filas(); i++) {
		for(int j = 0; j < matOriginal.columnas(); j++) {
			acum += pow(matOriginal.elem(i, j) - matPerturbada.elem(i, j) , 2);
		}
	}
	return acum / (matOriginal.filas() * matOriginal.columnas());
}

Matriz* aplicarDCT(Matriz& x) {
	Matriz* resultado;
	if(x.columnas() == 1) {
		Matriz* M = MatrizM(x.filas(), x.rango());
		resultado = (*M) * x;
		delete M;
	}
	else {
		//255 para el rango de imagenes
		Matriz* M = MatrizM(x.filas(), 255);
		Matriz *temp = (*M) * x;
		M->transponer();
		resultado = (*temp) * (*M);
		delete temp;
		delete M;
	}
	return resultado;
}

Matriz* revertirDCT(Matriz& xTransformada, const int rango) {
	Matriz* x = new Matriz(xTransformada);
	if(x->columnas() == 1) {
		Matriz* M = MatrizM(x->filas(), rango);
		//Hago M^(-1) * xTransformada, donde xTransformada es M*x
		Matriz *j = xTransformada.multiplicarPorInversa(*M);
		delete M;
		delete x;
		return j;
	}
	else {
		//Rango 255 para imagenes
		Matriz* M = MatrizM(x->filas(), 255);
		//Hago M^(-1) * cada columna
		for(int i = 0; i < x->columnas(); i++) {
			Matriz* columna = x->submatriz(0, x->filas()-1 ,i ,i);
			Matriz* j = columna->multiplicarPorInversa(*M);
			x->cambiarColumna(*j, i);
			delete j;
		}
		//Me queda x*Mt , hago (x*Mt)t = M*xt
		x->transponer();
		for(int i = 0; i < x->columnas(); i++) {
			Matriz* columna = x->submatriz(0, x->filas()-1 ,i ,i);
			Matriz* j = columna->multiplicarPorInversa(*M);
			x->cambiarColumna(*j, i);
			delete j;
		}
		//Me dá xt
		x->transponer();
		delete M;
		return x;
	}
}
 
Matriz* convertirImagenAVector(Matriz& imagen) {
	Matriz* vector = new Matriz(pow(imagen.filas(),2), 1);
	int x0 = 0;
	int y0 = 0;
	int x = x0;
	int y = y0;
	cout << "Filas del vector " << vector->filas() << endl; 
	for(int i = 0;i < vector->filas(); i++) {
		cout << "indice ("<<y << ","<<x<<")" << endl;
		cout << "Voy metiendo " << imagen.elem(y,x) << endl;
		vector->elem(i,0) = imagen.elem(y,x);

		x--;
		y++;

		if(x < 0 || y >= imagen.filas()) {
			if(x0 < imagen.filas()-1) {
				x0++;
			}
			else {
				y0++;
			}
			x = x0; y = y0;
		}
	}
	return vector;
}