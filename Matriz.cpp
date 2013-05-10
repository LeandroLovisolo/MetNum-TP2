#include "Matriz.h"
#include <iostream>
#include <cmath>
#include <utility>

#include <iomanip>
using namespace std;

Matriz::Matriz(const int filas, const int columnas) {
	_filas = filas;
	_columnas = columnas;
	vectorMatriz = new double[filas * columnas];
}

Matriz::Matriz(Matriz& otra) {
	_filas = otra._filas;
	_columnas = otra._columnas;
	vectorMatriz = new double[_filas * _columnas];
	for(int i = 0; i < _filas * _columnas; i++) vectorMatriz[i] = otra.vectorMatriz[i];
}

Matriz::~Matriz() {
	delete vectorMatriz;
}

double &Matriz::elem(const int fila, const int columna) {
	return vectorMatriz[fila*this->_columnas + columna];
}

int Matriz::filas() const {
	return _filas;
}

int Matriz::columnas() const {
	return _columnas;
}

void Matriz::operator=(Matriz &mat) {
	for(int i=0;i<this->_filas;i++) { //Me muevo fila a fila en A
		for(int j=0;j<this->_columnas;j++) { //Me muevo en cada columna de B
			this->elem(i,j) = mat.elem(i,j);
		}
	}
}

void Matriz::operator*(Matriz &mat) {
	//A*B donde this = A y B mat
	double *nuevaMatriz = new double[mat._columnas*this->_filas];
	for(int i=0;i<_filas;i++) { //Me muevo fila a fila en A
		for(int h=0;h<mat._columnas;h++) { //Me muevo en cada columna de B
			nuevaMatriz[i*mat._columnas + h] = 0;
			for(int j=0;j<_columnas;j++) { //Me muevo entre cada fila de B = columnas A, multiplico y sumo
				nuevaMatriz[i*mat._columnas + h] += this->elem(i,j)*mat.elem(j,h);
			}
		}
	}
	this->_columnas = mat._columnas;
	delete this->vectorMatriz;
	vectorMatriz = nuevaMatriz;
}

void Matriz::operator*(const double cst) {
	for(int i=0;i<_filas;i++) {
		for(int j=0;j<_columnas;j++) {
			this->elem(i,j) = this->elem(i,j)*cst;
		}
	}
}

void Matriz::operator+(Matriz &mat) {
	for(int i=0;i<_filas;i++) {
		for(int j=0;j<_columnas;j++) {
			this->elem(i,j) += mat.elem(i,j);
		}
	}
}

void Matriz::print(){
	for(int i=0;i<_filas;i++) {
		for(int j=0;j<_columnas;j++) {
			cout << this->elem(i,j) << '\t';
		}
		cout << endl;
	}
}

void Matriz::intercambiarFilas(const int i, const int j) {
	intercambiarFilas(i, j, _columnas);
}

void Matriz::intercambiarFilas(const int i, const int j, const int hasta) {
	if(i == j) return;
	for(int x=0;x<hasta;x++) {
		double elemento = this->elem(i,x);
		this->elem(i,x) = this->elem(j,x);
		this->elem(j,x) = elemento;
	}
}

int Matriz::filaConMayorAbsEnCol(const int col, const int desde) {
	int filaMayor = desde;
	int mayor = this->elem(desde,col);
	for(int y=desde+1;y<_filas;y++) {
		if(abs(this->elem(y,col)) > mayor) {
			mayor = abs(this->elem(y,col));
			filaMayor = y;
		}
	}
	return filaMayor;
}

void Matriz::transformarEnIdent() {
	for(int y=0;y<_filas;y++) {
		for(int x=0;x<_columnas;x++) {
			this->elem(y,x) = (y == x ? 1 : 0);
		}
	}
}

//Devuelve en la primera posición a P, en la segunda a L y deja a A como U
pair <Matriz*,Matriz*> Matriz::factorizacionPLU() {
	Matriz *L = new Matriz(this->_filas, this->_columnas);
	Matriz *P = new Matriz(this->_filas, this->_columnas);
	pair <Matriz*,Matriz*> resultado;
	resultado = make_pair(P,L);
	L->transformarEnIdent();
	P->transformarEnIdent();
	for(int j=0;j<this->_columnas-1;j++) { //Me voy moviendo por las columnas
		//Intercambio la fila con el máximo absoluto por la actual
		//Tener en cuenta que las columnas también determinan la fila a la cual intecambiar el mayor
		//ya que vamos moviendonos diagonalmente, (j,j) va a tener siempre el maximo
		int jp = this->filaConMayorAbsEnCol(j,j);
		this->intercambiarFilas(jp,j);
		P->intercambiarFilas(jp,j); //Intercambio las filas en la matriz identidad para tener P
		L->intercambiarFilas(jp, j, j);
		for(int i=j+1;i<this->_filas;i++) { //Voy recorriendo todas las filas poniendolas en 0
			L->elem(i,j) = this->elem(i,j)/this->elem(j,j); //Pongo en L Mij
			this->elem(i,j) = 0; //Pongo en 0 el elemento eliminado
			for(int x=j+1;x<_columnas;x++) {
				this->elem(i,x) = this->elem(i,x) - L->elem(i,j)*this->elem(j,x);
			}
		}
	}
	return resultado;
}

//Ax = b resuelvo sistema (Solo matrices trianguladas) devuelvo X
Matriz* Matriz::backwardsSubstitution(Matriz *b) {
	Matriz *x = new Matriz(this->_columnas,1);
	for(int i=this->_filas-1;i>=0;i--) { //Voy de la fila de abajo para arriba
		//Me armo un acumulador del nuevo valor Xi, voy construyendo el X de abajo hacia arriba
		//Utilizo Xi = (Bi - sum(Aij, Xj)/Aii j=i+1 hasta n (cols))
		double valorX = b->elem(i,0);
		//Hago Xi = (Bi - sum(Aij, Xj)
		//Recorro las columnas de la posición+1 en que tengo mi incognita
		for(int j=i+1;j<this->_columnas;j++) {
			valorX -= this->elem(i,j) * x->elem(j,0);
		}
		//Xi/Aii para terminar
		x->elem(i,0) = valorX/this->elem(i,i);
	}
	return x;
}

//Ax = b resuelvo sistema (Solo matrices trianguladas) devuelvo X
Matriz* Matriz::forwardSubstitution(Matriz *b) {
	Matriz *x = new Matriz(this->_columnas,1);
	//Recorro las columnas de la posición 0 hasta la posición-1 en que tengo mi incognita
	for(int i=0;i<this->_filas;i++) { //Recorro filas de arriba a abajo
		//Me armo un acumulador del nuevo valor Xi, voy construyendo el X de arriba hacia abajo
		//Utilizo Xi = (Bi - sum(Aij, Xj)/Aii j=i+1 hasta n (cols))
		double valorX = b->elem(i,0);
		//Hago Xi = (Bi - sum(Aij, Xj)
		for(int j=0;j<i;j++) {
			valorX -= this->elem(i,j) * x->elem(j,0);
		}
		//Xi/Aii para terminar
		x->elem(i,0) = valorX/this->elem(i,i);
	}
	return x;
}

double Matriz::max() {
	double max = this->elem(0,0);
	for(int i=0;i<this->_filas;i++) {
		for(int j=0;j<this->_columnas;j++) {
			if(this->elem(i,j) > max) {
				max = this->elem(i,j);
			}
		}
	}
	return max;
}

double Matriz::min() {
	double min = this->elem(0,0);
	for(int i=0;i<this->_filas;i++) {
		for(int j=0;j<this->_columnas;j++) {
			if(this->elem(i,j) < min) {
				min = this->elem(i,j);
			}
		}
	}
	return min;
}

double Matriz::rango() {
	return this->max()-this->min();
}
