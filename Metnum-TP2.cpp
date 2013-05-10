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
	char fileName[] = "signals/dopp512.txt";
	Matriz *mat = cargarSonido(fileName);
	Matriz plu(4,4);
	plu.elem(0,0) = 1;
	plu.elem(0,1) = 1;
	plu.elem(0,2) = 0;
	plu.elem(0,3) = 3;

	plu.elem(1,0) = 2;
	plu.elem(1,1) = 1;
	plu.elem(1,2) = -1;
	plu.elem(1,3) = 1;

	plu.elem(2,0) = 3;
	plu.elem(2,1) = -1;
	plu.elem(2,2) = -1;
	plu.elem(2,3) = 2;

	plu.elem(3,0) = -1;
	plu.elem(3,1) = 2;
	plu.elem(3,2) = 3;
	plu.elem(3,3) = -1;

	Matriz b(4,1);
	b.elem(0,0) = 1;
	b.elem(1,0) = 2;
	b.elem(2,0) = 3;
	b.elem(3,0) = 4;

/* Matriz simple para probar en PruebaMetodo1, sacandole
	el ruido y su eliminacion, que se puede convertir y volver */
	Matriz sonidoTest(4,1);
	sonidoTest.elem(0,0) = 1;
	sonidoTest.elem(1,0) = 2;
	sonidoTest.elem(2,0) = 3;
	sonidoTest.elem(3,0) = 4;
	Matriz *DCT = aplicarDCT(&sonidoTest);
	DCT->print();
	cout << "Devuelta" << endl;
	Matriz *devuelta = revertirDCT(DCT);
	devuelta->print();
	//delete DCT;
	//delete devuelta;
	//PruebaMetodo1(mat);
	delete mat;
	
	/*
	cout << "Matriz Original: " << endl;
	Matriz *L = plu.factorizacionLU();
	cout << "Matriz L: " << endl;
	L->print();
	cout << "Matriz U: " << endl;
	plu.print();
	cout << "Tratando de re-contruir A = L.U" << endl;
	(*L)*plu; //Multiplico L por U
	L->print();*/
	return 0;
}
