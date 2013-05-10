#include <iostream>
#include <fstream>
#include <utility>
#include "Matriz.h"
#include "Ecuaciones.h"
using namespace std;

Matriz *cargarSonido(char *fileName) {
	Matriz *mat;
	ifstream file(fileName);
	if(file.is_open()) {
		int longitud;
		file >> longitud;
		mat = new Matriz(longitud, 1);
		for(int i=0;i<longitud;i++) {
			file >> mat->elem(i,0);
		}
		file.close();
	}
	return mat;
}

int main() {
	Matriz A(4,4);
	A.elem(0,0) = 1;
	A.elem(0,1) = 1;
	A.elem(0,2) = 0;
	A.elem(0,3) = 3;

	A.elem(1,0) = 2;
	A.elem(1,1) = 1;
	A.elem(1,2) = -1;
	A.elem(1,3) = 1;

	A.elem(2,0) = 3;
	A.elem(2,1) = -1;
	A.elem(2,2) = -1;
	A.elem(2,3) = 2;

	A.elem(3,0) = -1;
	A.elem(3,1) = 2;
	A.elem(3,2) = 3;
	A.elem(3,3) = -1;

	cout << "Matriz A:" << endl;
	A.print();

	tuple<Matriz*, Matriz*, Matriz*> plu = A.factorizacionPLU();

	cout << "P*A:" << endl;
	(*(get<0>(plu)) * A)->print();

	cout << "L*U:" << endl;
	(*(get<1>(plu)) * *(get<2>(plu)))->print();

	return 0;
}
