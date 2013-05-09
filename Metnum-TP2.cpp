#include <iostream>
#include <fstream>
#include "Matriz.h"
#include "Ecuaciones.h"
using namespace std;

Matriz *cargarSonido(char *fileName) {
	Matriz *mat;
	ifstream file(fileName);
	if(file.is_open()) {
		cout << "Abrio el archivo" << endl;
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
	char fileName[] = "signals/s64.txt";
	Matriz *mat = cargarSonido(fileName);
	delete mat;
	Matriz plu(4,4);
	plu.elem(0,0) = 1;
	plu.elem(0,1) = 2;
	plu.elem(0,2) = 3;
	plu.elem(0,3) = -1;

	plu.elem(1,0) = 1;
	plu.elem(1,1) = 1;
	plu.elem(1,2) = -1;
	plu.elem(1,3) = 2;

	plu.elem(2,0) = 0;
	plu.elem(2,1) = -1;
	plu.elem(2,2) = -1;
	plu.elem(2,3) = 3;

	plu.elem(3,0) = 3;
	plu.elem(3,1) = 1;
	plu.elem(3,2) = 2;
	plu.elem(3,3) = -1;
	plu.factorizacionPLU();
	return 0;
}
