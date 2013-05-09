#include "Matriz.h"
#include <iostream>
#include <cmath>
#include <utility>
using namespace std;

Matriz::Matriz(const int filas, const int columnas) {
	vectorMatriz = new double[filas*columnas];
	this->filas = filas;
	this->columnas = columnas;
}

Matriz::~Matriz() {
	delete vectorMatriz;
}

double &Matriz::elem(const int fila, const int columna) {
	return vectorMatriz[fila*this->columnas + columna];
}

const int Matriz::fils() const {
	return filas;
}

const int Matriz::cols() const {
	return columnas;
}

void Matriz::operator*(Matriz &mat) {
	//A*B donde this = A y B mat
	double *nuevaMatriz = new double[mat.columnas*this->filas];
	for(int i=0;i<filas;i++) { //Me muevo fila a fila en A
		for(int h=0;h<mat.columnas;h++) { //Me muevo en cada columna de B
			nuevaMatriz[i*mat.columnas + h] = 0;
			for(int j=0;j<columnas;j++) { //Me muevo entre cada fila de B = columnas A, multiplico y sumo
				nuevaMatriz[i*mat.columnas + h] += this->elem(i,j)*mat.elem(j,h);
			}
		}
	}
	this->columnas = mat.columnas;
	delete this->vectorMatriz;
	vectorMatriz = nuevaMatriz;
}

void Matriz::operator*(const double cst) {
	for(int i=0;i<filas;i++) {
		for(int j=0;j<columnas;j++) {
			this->elem(i,j) = this->elem(i,j)*cst;
		}
	}
}

void Matriz::operator+(Matriz &mat) {
	for(int i=0;i<filas;i++) {
		for(int j=0;j<columnas;j++) {
			this->elem(i,j) += mat.elem(i,j);
		}
	}
}

void Matriz::print(){
	for(int i=0;i<filas;i++) {
		for(int j=0;j<columnas;j++) {
			cout << this->elem(i,j) << " ";
		}
		cout << endl;
	}
}

void Matriz::intercambiarFilas(const int i, const int j) {
	if(i == j) return;
	for(int x=0;x<columnas;x++) {
		double elemento = this->elem(i,x);
		this->elem(i,x) = this->elem(j,x);
		this->elem(j,x) = elemento;
	}
}

const int Matriz::filaConMayorAbsEnCol(const int col, const int desde) {
	int filaMayor = desde;
	int mayor = this->elem(desde,col);
	for(int y=desde+1;y<filas;y++) {
		if(abs(this->elem(y,col)) > mayor) {
			mayor = abs(this->elem(y,col));
			filaMayor = y;
		}
	}
	return filaMayor;
}

void Matriz::transformarEnIdent() {
	for(int y=0;y<filas;y++) {
		for(int x=0;x<columnas;x++) {
			this->elem(y,x) = (y == x ? 1 : 0);
		}
	}
}

//Devuelve en la primera posición a P, en la segunda a L y deja a A como U
pair <Matriz*,Matriz*> Matriz::factorizacionPLU() {
	Matriz *L = new Matriz(this->filas, this->columnas);
	Matriz *P = new Matriz(this->filas, this->columnas);
	pair <Matriz*,Matriz*> resultado;
	resultado = make_pair(P,L);
	L->transformarEnIdent();
	P->transformarEnIdent();
	this->print();
	for(int j=0;j<this->columnas-1;j++) { //Me voy moviendo por las columnas
		//Intercambio la fila con el máximo absoluto por la actual
		//Tener en cuenta que las columnas también determinan la fila a la cual intecambiar el mayor
		//ya que vamos moviendonos diagonalmente, (j,j) va a tener siempre el maximo
		this->intercambiarFilas(this->filaConMayorAbsEnCol(j,j),j);
		P->intercambiarFilas(this->filaConMayorAbsEnCol(j,j),j); //Intercambio las filas en la matriz identidad para tener P
		for(int i=j+1;i<this->filas;i++) { //Voy recorriendo todas las filas poniendolas en 0
			L->elem(i,j) = this->elem(i,j)/this->elem(j,j); //Pongo en L Mij
			this->elem(i,j) = 0; //Pongo en 0 el elemento eliminado
			for(int x=j+1;x<columnas;x++) {
				this->elem(i,x) = this->elem(i,x) - L->elem(i,j)*this->elem(j,x);
			}
		}
	}
	return resultado;
}

//Devuelve L y la matriz queda como U
Matriz* Matriz::factorizacionLU() {
	Matriz *L = new Matriz(this->filas, this->columnas);
	L->transformarEnIdent();
	this->print();
	for(int j=0;j<this->columnas-1;j++) { //Me voy moviendo por las columnas
		for(int i=j+1;i<this->filas;i++) { //Voy recorriendo todas las filas poniendolas en 0
			L->elem(i,j) = this->elem(i,j)/this->elem(j,j); //Pongo en L Mij
			this->elem(i,j) = 0; //Pongo en 0 el elemento eliminado
			for(int x=j+1;x<columnas;x++) {
				this->elem(i,x) = this->elem(i,x) - L->elem(i,j)*this->elem(j,x);
			}
		}
	}
	return L;
}

//Ax = b resuelvo sistema (Solo matrices trianguladas)
Matriz* Matriz::backwardsSubstitution(Matriz *b) {
	Matriz *x = new Matriz(this->columnas,1);
	for(int i=this->filas-1;i>=0;i--) { //Voy de la fila de abajo para arriba
		//Me armo un acumulador del nuevo valor Xi, voy construyendo el X de abajo hacia arriba
		//Utilizo Xi = (Bi - sum(Aij, Xj)/Aii j=i+1 hasta n (cols))
		double valorX = b->elem(i,0);
		//Hago Xi = (Bi - sum(Aij, Xj)
		for(int j=i+1;j<this->columnas;j++) {
			valorX -= this->elem(i,j) * this->elem(j,0);
		}
		//Xi/Aii para terminar
		x->elem(i,0) = valorX/this->elem(i,i);
	}
	return x;
}