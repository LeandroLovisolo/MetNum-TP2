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
	Matriz x(4, 1);
	x.elem(0,0) = 1;
	x.elem(1,0) = 2;
	x.elem(2,0) = 4;
	x.elem(3,0) = 8;

	cout << "Matriz x:" << endl;
	x.print();

	Matriz* d = aplicarDCT(x);

	cout << "Matriz d:" << endl;
	d->print();

	Matriz* x0 = revertirDCT(*d, x.max());

	cout << "Matriz x0:" << endl;
	x0->print();


	//Matriz A = *MatrizM(x.filas(), x.rango());

	
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
	cout << "Matriz A" << endl;
	A.print();
	cout << "Submatriz " << endl;
	Matriz *sub = A.submatriz(0,1,0,1);
	sub->print();
	/*
	cout << "Matriz A:" << endl;
	A.print();

	Matriz* x1 = A*x;

	cout << "Matriz x1 = A * x:" << endl;
	x1->print();

	tuple<Matriz*, Matriz*, Matriz*> plu = A.factorizacionPLU();

	// [P, L, U] = lu_con_pivoteo(A);
	// y = forward_substitution(L, P * x1);
	// x0 = backward_substitution(U, y);

	Matriz* P_x1 = *get<0>(plu) * (*x1);
	Matriz* y = get<1>(plu)->forwardSubstitution(*P_x1);
	Matriz* x0 = get<2>(plu)->backwardSubstitution(*y);

	cout << "P_x1:" << endl;
	P_x1->print();

	cout << "Matriz y:" << endl;
	y->print();

	cout << "Matriz x = (A^-1) * x1:" << endl;
	x0->print();

	*/

	/*
	cout << "P*A:" << endl;
	(*(get<0>(plu)) * A)->print();

	cout << "L*U:" << endl;
	(*(get<1>(plu)) * *(get<2>(plu)))->print();
	*/



	/*
	// Matriz simple para probar en PruebaMetodo1, sacandole
	// el ruido y su eliminacion, que se puede convertir y volver
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
	*/
	
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
