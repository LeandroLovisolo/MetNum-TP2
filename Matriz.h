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

	int filas() const;
	int columnas() const;
	double &elem(const int fila, const int columna);

	double max(); // Máximo elemento de la matriz
	double min(); // Mínimo elemento de la matriz
	double rango(); // max() - min()

	Matriz* operator+(Matriz &m);
	Matriz* operator*(Matriz &m);
	Matriz* operator*(double k);

	std::pair <Matriz*, Matriz*> factorizacionPLU();
	Matriz* backwardsSubstitution(Matriz *b);
	Matriz* forwardSubstitution(Matriz *b);
	void print();

private:
	void intercambiarFilas(const int i, const int j);
	void intercambiarFilas(const int i, const int j, const int hasta);
	void transformarEnIdent();
	int filaConMayorAbsEnCol(const int col, const int desde);
};

#endif
