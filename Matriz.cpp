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

const int Matriz::filaConMayorAbsEnCol(const int col) {
	int filaMayor = 0;
	int mayor = this->elem(col,0);
	for(int y=1;y<filas;y++) {
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

void Matriz::factorizacionPLU() {
	Matriz *L = new Matriz(this->filas, this->columnas);
	Matriz *P = new Matriz(this->filas, this->columnas);
	L->transformarEnIdent();
	P->transformarEnIdent();
	cout << "Matriz original" << endl;
	this->print();
	for(int j=0;j<this->columnas-1;j++) { //Me voy moviendo por las columnas
		for(int i=j+1;i<this->filas;i++) { //Voy recorriendo todas las filas poniendolas en 0
			//this->intercambiarFilas(this->filaConMayorAbsEnCol(i),i); //Intercambio la fila con el máximo absoluto por la actual
			//P->intercambiarFilas(this->filaConMayorAbsEnCol(i),i); //Intercambio las filas en la matriz identidad para tener P
			L->elem(j,i) = this->elem(j,i)/this->elem(j,j); //Pongo en L Mij
			//cout << "this->elem(j,i)=" << this->elem(j,i+1) << endl;
			//cout << "is->elem(j,i-1)=" << this->elem(j,i) << endl;
			//cout << "Elemento L ("<<j<<","<<i+1<<") = " << L->elem(j,i+1) << endl;
			for(int x=i;x<this->filas;x++) { //Hago la resta de las filas debajo de las ya trianguladas anteriormente
				//cout << "X=" << x << endl;
				for(int h=0;h<this->columnas;h++) { //Resto elemento a elemento
					//cout << "H=" << h << endl;
					if(x == 1) {
						cout << "H="<<h<<" this->elem(h,x) =" << this->elem(h,x) <<" - L->elem(j,i) =" << L->elem(j,i) <<" * this->elem(h,i) = " << this->elem(h,i) << endl;
					}
					if(j != h) {
						//cout << "x!=h " << "this->elem(h,x)=" << this->elem(h,x) << " this->elem(h,i)=" << this->elem(h,i) << endl;
						this->elem(h,x) = this->elem(h,x) - L->elem(j,i)*this->elem(h,i-1);
					}
					else {
						//cout << "Cayo en h == x" << endl;
						this->elem(h,x) = 0;
					}
				}
			}
		}
	}
	cout << "Matriz P" << endl;
	P->print();
	cout << "Matri< L" << endl;
	L->print();
	cout << "Matriz U" << endl;
	this->print();
}