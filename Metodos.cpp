#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include "Ecuaciones.h"
#include "Metodos.h"

using namespace std;

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

void agregarRuidoAditivo(Matriz &m) {
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
  	normal_distribution<double> distribution(0,1);
	for(int i = 0; i < m.filas(); i++) {
		for(int j = 0; j < m.columnas(); j++) {
			//cout << "Que larga: " << distribution(generator) << endl;
			m.elem(i,j) += distribution(generator);
		}
	}
}

void eliminarRuidoUmbral(Matriz &m, const double umbral) {
	cout << "Rango: " << m.rango() << endl;
	for(int i = 0; i < m.filas(); i++) {
		for(int j = 0; j < m.columnas(); j++) {
			if(abs(m.elem(i, j)) < umbral) m.elem(i, j) = 0;
		}
	}
}

void PruebaMetodo1(Matriz &Xoriginal) {
	Matriz Xruido(Xoriginal);
	agregarRuidoAditivo(Xruido);
	cout << "Ruido agregado PSNR: " << PSNR(Xoriginal, Xruido, Xoriginal.max()) << endl;

	grabarSonido(Xruido, (char*) "dopp512ConRuido.txt");

	Matriz *DCT = aplicarDCT(Xruido);
	grabarSonido(*DCT, (char*) "dopp512DCTConRuido.txt");
	eliminarRuidoUmbral(*DCT, 50);
	grabarSonido(*DCT, (char*) "dopp512DCTSinRuido.txt");
	Matriz *res = revertirDCT(*DCT, Xoriginal.rango());
	grabarSonido(*res, (char*) "dopp512SinRuido.txt");
	
	cout << "PSNR final: " << PSNR(Xoriginal, *res, Xoriginal.max()) << endl;
}