#ifndef MATRIZ_H_
#define MATRIZ_H_
#include <utility>

class Matriz {
private:
	double *vectorMatriz;
	int filas;
	int columnas;
public:
	Matriz(const int filas, const int columnas); //Crea una matriz de tantas filas y columnas
	~Matriz();
	double &elem(const int fila, const int columna); //Me devuelve el elemento en las coordenadas x, y; x < cols , y < filas
	void operator*(Matriz &mat); //Multiplicación matricial
	void operator*(const double cst); //Multiplicación por escalar
	void operator+(Matriz &mat); //Suma matricial
	const double max(); //Devuelve el máximo elemento de la matriz
	const double min(); //Devuelve el mínimo elemento de la matriz
	const double rango(); //Devuelve el rango (Q) = max - min de la señal
	const int filaConMayorAbsEnCol(const int col, const int desde); //Devuelve la fila con el mayor número absoluto en una columna
	const int fils() const;
	const int cols() const;
	void intercambiarFilas(const int i, const int j); //Filas van de 0 a n-1
	void transformarEnIdent();
	std::pair <Matriz*,Matriz*> factorizacionPLU();
	Matriz* factorizacionLU();
	Matriz* backwardsSubstitution(Matriz *b);
	Matriz* forwardSubstitution(Matriz *b);
	//Teniendo la DST, pone en 0 los elementos menores a (max-min)/2
	void eliminarRuidoMetodo1();
	void print();
};



#endif
