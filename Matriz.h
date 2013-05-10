#ifndef MATRIZ_H_
#define MATRIZ_H_

#include <utility>

class Matriz {
private:
	double *vectorMatriz;
	int _filas;
	int _columnas;

public:
	Matriz(const int filas, const int columnas);
	Matriz(Matriz& otra);
	~Matriz();

	void operator+(Matriz &mat);
	Matriz* operator*(Matriz &m);
	void operator*(const double cst);
	double &elem(const int fila, const int columna);

	double max(); //Devuelve el máximo elemento de la matriz
	double min(); //Devuelve el mínimo elemento de la matriz
	double rango(); //Devuelve el rango (Q) = max - min de la señal
	int filas() const;
	int columnas() const;

	std::pair <Matriz*,Matriz*> factorizacionPLU();
	Matriz* backwardsSubstitution(Matriz *b);
	Matriz* forwardSubstitution(Matriz *b);
	void print();

private:
	void intercambiarFilas(const int i, const int j); //Filas van de 0 a n-1
	void intercambiarFilas(const int i, const int j, const int hasta);
	void transformarEnIdent();
	int filaConMayorAbsEnCol(const int col, const int desde); //Devuelve la fila con el mayor número absoluto en una columna

};



#endif
