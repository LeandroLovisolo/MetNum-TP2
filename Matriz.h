#ifndef MATRIZ_H_
#define MATRIZ_H_
class Matriz {
private:
	double *vectorMatriz;
	int filas;
	int columnas;
public:
	Matriz(const int filas, const int columnas); //Crea una matriz de tantas filas y columnas
	~Matriz();
	double &elem(const int x, const int y); //Me devuelve el elemento en las coordenadas x, y; x < cols , y < filas
	void operator*(Matriz &mat); //Multiplicación matricial
	void operator*(const double cst); //Multiplicación por escalar
	void operator+(Matriz &mat); //Suma matricial
	void intercambiarFilas(const int i, const int j); //Filas van de 0 a n-1
	const int filaConMayorAbsEnCol(const int col); //Devuelve la fila con el mayor número absoluto en una columna
	const int fils() const;
	const int cols() const;
	void print();
};



#endif
