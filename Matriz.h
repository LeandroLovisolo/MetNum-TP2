#ifndef MATRIZ_H_
#define MATRIZ_H_
class Matriz {
private:
	double *vectorMatriz;
	int filas;
	int columnas;
public:
	Matriz(const int filas, const int columnas);
	~Matriz();
	double &elem(const int x, const int y);
	void operator*(Matriz &mat); //Multiplicación matricial
	void operator*(const double cst); //Multiplicación por escalar
	void operator+(Matriz &mat); //Suma matricial
	void intercambiarFilas(const int i, const int j); //Filas van de 0 a n-1
	const int filaConMayorAbsEnCol(const int col);
	const int fils() const;
	const int cols() const;
	void print();
};



#endif
