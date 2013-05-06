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
	const int fils();
	const int cols();
	void print();
};



#endif
