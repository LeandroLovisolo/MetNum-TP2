#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "Tests.h"
#include "Metodos.h"
#include "Ecuaciones.h"
#include "Matriz.h"

using namespace std;

Matriz *cargarVector(char *fileName) {
	Matriz *mat = 0;
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

Matriz *cargarMatriz(char *fileName) {
	Matriz *mat = 0;
	ifstream file(fileName);
	if(file.is_open()) {
		string temp;
		file >> temp; //Leo el P2
		int crap;
		int longitud;
		int altura;
		file >> longitud;
		file >> altura;
		file >> crap; //Leo la porqueria del rango
		mat = new Matriz(altura, longitud);
		for(int i=0;i<altura;i++) {
			for(int j=0;j<longitud;j++) {
				file >> mat->elem(i,j);
			}
		}
		file.close();
	}
	return mat;
}

void grabarMatriz(Matriz& mat, char* fileName) {
	ofstream file(fileName);
	if(file.is_open()) {
		file << "P2" << endl;
		file << mat.columnas() << " " << mat.filas() << endl;
		file << "255" << endl;
		for(int i = 0; i < mat.filas(); i++) {
			for(int j = 0; j < mat.columnas(); j++) {
				int valor = (unsigned char) mat.elem(i,j);
				file << valor << endl;
			}
		}
		file.close();
	}
}

void grabarVector(Matriz& mat, char* fileName) {
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
	Matriz *Xoriginal = cargarVector((char*) "signals/dopp512.txt");
	Matriz Xruido(*Xoriginal);
	agregarRuidoAditivo(Xruido,2,2);
	cout << "Ruido agregado PSNR: " << PSNR(*Xoriginal, Xruido, Xoriginal->max()) << endl;
	//grabarVector(Xruido, (char*) "dopp512ConRuido.txt");

	Matriz *DCT = aplicarDCT(Xruido);
	//grabarVector(*DCT, (char*) "dopp512DCTConRuido.txt");

	//Pongo en 0 todas las frecuencias de un poco más del medio hasta el final
	for(int i=0;i<Xruido.filas();i++) {
		if(Xruido.elem(i,0) < 0) {
			Xruido.elem(i,0) = Xruido.elem(i,0) - Xruido.elem(i,0)/1000;
		}
		else {
			Xruido.elem(i,0) = Xruido.elem(i,0) + Xruido.elem(i,0)/1000;
		}
	}
	//grabarVector(*DCT, (char*) "dopp512DCTSinRuido.txt");
	Matriz *res = revertirDCT(*DCT, Xoriginal->rango());
	//grabarVector(*res, (char*) "dopp512SinRuido.txt");
	
	cout << "PSNR final: " << PSNR(*Xoriginal, *res, Xoriginal->max()) << endl;
	delete Xoriginal;
	delete DCT;
	delete res;
}

//cout << "PSNR final: " << PSNR(*Xoriginal, *res, Xoriginal->max()) << endl;

void pruebaSonidoRuidoAditivo() {
	Matriz* Xoriginal = cargarVector((char*) "signals/dopp512.txt");
	Matriz Xruido(*Xoriginal);
	agregarRuidoAditivo(Xruido, 0, 2);
	cout << "PSNR ruido agregado: " << PSNR(*Xoriginal, Xruido, Xoriginal->max()) << endl;
	Matriz* DCT = aplicarDCT(Xruido);
	atenuarIntervaloSonido(*DCT, DCT->filas()/2 + DCT->filas()/4 , DCT->filas()-1, 0.8);
	Matriz* res = revertirDCT(*DCT, Xruido.rango());
	cout << "PSNR ruido final: " << PSNR(*Xoriginal, *res, Xoriginal->max()) << endl;
	delete Xoriginal;
	delete DCT;
	delete res;
}

void pruebaSonidoRuidoImpulsivo() {
	Matriz* Xoriginal = cargarVector((char*) "signals/dopp512.txt");
	Matriz Xruido(*Xoriginal);
	agregarRuidoImpulsivo(Xruido, 0.1);
	cout << "PSNR ruido agregado: " << PSNR(*Xoriginal, Xruido, Xoriginal->max()) << endl;
	Matriz* DCT = aplicarDCT(Xruido);
	grabarVector(*DCT, (char*) "DCTRuidoImpulsivo.txt");
	atenuarIntervaloSonido(*DCT, DCT->filas()/2 + DCT->filas()/4 , DCT->filas()-1, 0.1);
	Matriz* res = revertirDCT(*DCT, Xruido.rango());
	cout << "PSNR ruido final: " << PSNR(*Xoriginal, *res, Xoriginal->max()) << endl;
	delete Xoriginal;
	delete DCT;
	delete res;
}
void pruebaConversionImagenAVector() {
	Matriz A(4,4);
	A.elem(0,0) = 1;
	A.elem(0,1) = 2;
	A.elem(0,2) = 3;
	A.elem(0,3) = 4;

	A.elem(1,0) = 5;
	A.elem(1,1) = 6;
	A.elem(1,2) = 7;
	A.elem(1,3) = 8;

	A.elem(2,0) = 9;
	A.elem(2,1) = 10;
	A.elem(2,2) = 11;
	A.elem(2,3) = 12;

	A.elem(3,0) = 13;
	A.elem(3,1) = 14;
	A.elem(3,2) = 15;
	A.elem(3,3) = 16;
	cout << "Matriz" << endl;
	A.print();
	cout << "Vector" << endl;
	Matriz* vector = convertirImagenAVector(A);
	vector->print();
	delete vector;

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
	x.elem(0,0) = 4.279999;
	x.elem(1,0) = 0.849378;
	x.elem(2,0) = -7.298978;
	x.elem(3,0) = 7.497067;

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

void pruebaCargarYGrabarMatriz() {
	Matriz *imagen = cargarMatriz((char*) "lena.pgm");
	Matriz Xruido(*imagen);
	agregarRuidoAditivo(Xruido,0,1);
	cout << "Ruido agregado PSNR: " << PSNR(*imagen, Xruido, imagen->max()) << endl;
	Matriz *DCT = aplicarDCT(Xruido);
	//eliminarRuidoUmbral(*DCT, 10000); Funcion a cambiar para eliminar ruido
	Matriz *sinRuido = revertirDCT(*DCT,imagen->rango());
	grabarMatriz(*sinRuido, (char*) "lena2.pgm");
	cout << "PSNR final: " << PSNR(*imagen, *sinRuido, imagen->max()) << endl;
	delete DCT;
	delete sinRuido;
	delete imagen;
}

void pruebaAtenuar() {
	Matriz *imagen = cargarMatriz((char*) "lena.pgm");
	Matriz Xruido(*imagen);
	agregarRuidoAditivo(Xruido,0,10);
	cout << "Ruido agregado PSNR: " << PSNR(*imagen, Xruido, imagen->rango()) << endl;
	Matriz *DCT = aplicarDCT(Xruido);

	atenuarImagen(*DCT, int(DCT->filas() * DCT->columnas() * 0.05), DCT->filas() * DCT->columnas(), 0.1);

	Matriz *sinRuido = revertirDCT(*DCT,imagen->rango());
	grabarMatriz(*sinRuido, (char*) "lena2.pgm");
	cout << "PSNR final: " << PSNR(*imagen, *sinRuido, imagen->rango()) << endl;
	delete DCT;
	delete sinRuido;
	delete imagen;
}








