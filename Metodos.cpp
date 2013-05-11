#include <iostream>
#include <random>
#include <chrono>
#include "Ecuaciones.h"
#include "Metodos.h"

using namespace std;

void agregarRuidoAditivo(Matriz &m, const double mu, const double sigma) {
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
  	normal_distribution<double> distribution(mu,sigma);
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
