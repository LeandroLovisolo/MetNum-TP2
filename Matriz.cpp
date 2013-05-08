#include "Matriz.h"
#include <iostream>
#include <cmath>
using namespace std;

Matriz::Matriz(const int filas, const int columnas) {
	vectorMatriz = new double[filas*columnas];
	this->filas = filas;
	this->columnas = columnas;
}

Matriz::~Matriz() {
	delete vectorMatriz;
}

double &Matriz::elem(const int x, const int y) {
	//cout << "(" << x << "," << y << ") Posicion en vector: " << y*columnas + x << endl;
	return vectorMatriz[y*columnas + x];
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
				nuevaMatriz[i*mat.columnas + h] += this->elem(j,i)*mat.elem(h,j);
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
			cout << this->elem(j,i) << " ";
		}
		cout << endl;
	}
}

void Matriz::intercambiarFilas(const int i, const int j) {
	for(int x=0;x<columnas;x++) {
		double elemento = this->elem(x,i);
		this->elem(x,i) = this->elem(x,j);
		this->elem(x,j) = elemento;
	}
}

const int Matriz::filaConMayorAbsEnCol(const int col) {
	int filaMayor = 0;
	int mayor = this->elem(col,0);
	for(int y=1;y<filas;y++) {
		if(abs(this->elem(col,y)) > mayor) {
			mayor = abs(this->elem(col,y));
			filaMayor = y;
		}
	}
	return filaMayor;
}
