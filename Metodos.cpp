#include <iostream>
#include <random>
#include <cmath>
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

void agregarRuidoImpulsivo(Matriz &m, const double p) {
	int max, min;
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::uniform_real_distribution<double> distribution(0.0,1.0);
	if(m.columnas() == 1) {
		max = m.max();
		min = m.min();
	}
	else {
		max = 255;
		min = 0;
	}
	for(int i = 0;i < m.filas(); i++) {
		for(int j = 0;j < m.columnas(); j++) {
			double randNum = distribution(generator);
			if(randNum < p) {
				m.elem(i,j) = max;
			}
			else if(randNum >= p) {
				m.elem(i,j) = min;
			}
		}
	}
}

void atenuarIntervaloSonido(Matriz &m, const int coefInicial, const int coefFinal, const double k) {
	for(int i = coefInicial; i <= coefFinal; i++) {
		m.elem(i,0) *= k;
	}
}

void umbralizarIntervaloSonido(Matriz &m, const int coefInicial, const int coefFinal, const double k) {
	for(int i = coefInicial; i <= coefFinal; i++) {
		if(abs(m.elem(i,0)) < k) m.elem(i,0) = 0;
	}
}