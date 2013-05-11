#include "Tests.h"
#include "Metodos.h"
#include "Ecuaciones.h"
#include <iostream>
#include <fstream>

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

void grabarSonido(Matriz& mat, char* fileName) {
	ofstream file(fileName);
	if(file.is_open()) {
		for(int i = 0; i < mat.filas(); i++) {
			for(int j = 0; j < mat.columnas(); j++) {
				file << mat.elem(i,j) << " ";
			}
		}
		file.close();
	}
}

//Anda pal orto
void pruebaMetodoSimpleEliminacion() {
	Matriz *Xoriginal = cargarSonido((char*) "signals/dopp512.txt");
	Matriz Xruido(*Xoriginal);
	agregarRuidoAditivo(Xruido,2,2);
	cout << "Ruido agregado PSNR: " << PSNR(*Xoriginal, Xruido, Xoriginal->max()) << endl;
	//grabarSonido(Xruido, (char*) "dopp512ConRuido.txt");

	Matriz *DCT = aplicarDCT(Xruido);
	//grabarSonido(*DCT, (char*) "dopp512DCTConRuido.txt");

	//Pongo en 0 todas las frecuencias de un poco más del medio hasta el final
	for(int i=0;i<Xruido.filas();i++) {
		if(Xruido.elem(i,0) < 0) {
			Xruido.elem(i,0) = Xruido.elem(i,0) - Xruido.elem(i,0)/1000;
		}
		else {
			Xruido.elem(i,0) = Xruido.elem(i,0) + Xruido.elem(i,0)/1000;
		}
	}
	//grabarSonido(*DCT, (char*) "dopp512DCTSinRuido.txt");
	Matriz *res = revertirDCT(*DCT, Xoriginal->rango());
	//grabarSonido(*res, (char*) "dopp512SinRuido.txt");
	
	cout << "PSNR final: " << PSNR(*Xoriginal, *res, Xoriginal->max()) << endl;
	delete Xoriginal;
	delete DCT;
	delete res;
}

void pruebaMetodo1() {
	Matriz *Xoriginal = cargarSonido((char*) "signals/dopp512.txt");
	Matriz *DCTOr = aplicarDCT(*Xoriginal);
	grabarSonido(*DCTOr, (char*) "dopp512DCTOriginal.txt");
	Matriz Xruido(*Xoriginal);
	agregarRuidoAditivo(Xruido,0,0.5);
	cout << "Ruido agregado PSNR: " << PSNR(*Xoriginal, Xruido, Xoriginal->max()) << endl;

	grabarSonido(Xruido, (char*) "dopp512ConRuido.txt");

	Matriz *DCT = aplicarDCT(Xruido);
	grabarSonido(*DCT, (char*) "dopp512DCTConRuido.txt");
	eliminarRuidoUmbral(*DCT, 1);
	grabarSonido(*DCT, (char*) "dopp512DCTSinRuido.txt");
	Matriz *res = revertirDCT(*DCT, Xoriginal->rango());
	grabarSonido(*res, (char*) "dopp512SinRuido.txt");
	
	cout << "PSNR final: " << PSNR(*Xoriginal, *res, Xoriginal->max()) << endl;
	delete Xoriginal;
	delete DCT;
	delete res;
}

void pruebaSubmatriz() {
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
	delete sub;
}

void aplicarYrevertirDCT() {
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

	Matriz* x0 = revertirDCT(*d, x.rango());

	cout << "Matriz x0:" << endl;
	x0->print();
	delete d;
	delete x0;
}

void aplicarYrevertirDCTMatrices() {
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

	Matriz* d = aplicarDCT(A);

	cout << "Matriz d:" << endl;
	d->print();

	Matriz* x0 = revertirDCT(*d, A.rango());

	cout << "Matriz x0:" << endl;
	x0->print();
	delete d;
	delete x0;
}
