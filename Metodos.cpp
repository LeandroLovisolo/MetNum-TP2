#include <random>
#include <chrono>

#include "Metodos.h"

using namespace std;

void agregarRuidoAditivo(Matriz &m) {
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
  	normal_distribution<double> distribution(7.0,30);
	for(int i = 0; i < m.filas(); i++) {
		for(int j = 0; j < m.columnas(); j++) {
			//cout << "Que larga: " << distribution(generator) << endl;
			m.elem(i,j) += distribution(generator);
		}
	}
}

void eliminarRuidoMetodo1(Matriz &m) {
	double umbral = (m.max() - m.min())/2;
	for(int i = 0; i < m.filas(); i++) {
		for(int j = 0; j < m.columnas(); j++) {
			if(abs(m.elem(i, j)) < umbral) m.elem(i, j) = 0;
		}
	}
}
