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
			if(m.columnas() == 1) {
				m.elem(i,j) += distribution(generator);
			} else {
				m.elem(i,j) += floor(distribution(generator));
			}
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
			else if(randNum >= 1 - p) {
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

void atenuarImagen(Matriz &m, int coefInicial, int coefFinal, double k) {
	// El par (x0, y0) indica el primer elemento de la diagonal actual
	int x0 = 0;
	int y0 = 0;

	// El par (x, y) indica el coeficiente actual
	int x = x0;
	int y = y0;

	for(int i = 0; i < m.filas() * m.columnas(); i++) {
		// Atenúo el coeficiente actual
		if(coefInicial <= i && i <= coefFinal) m.elem(y, x) = k * m.elem(y, x);

		// Avanzo al siguiente elemento de la diagonal
		x--;
		y++;

		// Verifico si llegué al final de la diagonal actual
		if(x < 0 || y >= m.filas()) {
			// Avanzo a la siguiente diagonal
			if(x0 < m.columnas() - 1) x0++;
			else y0++;

			// Avanzo al primer elemento de la nueva diagonal
			x = x0;
			y = y0;
		}
	}
}

void umbralizarIntervaloSonido(Matriz &m, const int coefInicial, const int coefFinal, const double k) {
	for(int i = coefInicial; i <= coefFinal; i++) {
		if(abs(m.elem(i,0)) < k) m.elem(i,0) = 0;
	}
}

void umbralizarImagen(Matriz &m, int coefInicial, int coefFinal, double umbral) {
	// El par (x0, y0) indica el primer elemento de la diagonal actual
	int x0 = 0;
	int y0 = 0;

	// El par (x, y) indica el coeficiente actual
	int x = x0;
	int y = y0;

	for(int i = 0; i < m.filas() * m.columnas(); i++) {
		// Umbralizo el coeficiente actual
		if(coefInicial <= i && i <= coefFinal) {
			if(abs(m.elem(y, x)) < umbral) m.elem(y, x) = 0;
		}

		// Avanzo al siguiente elemento de la diagonal
		x--;
		y++;

		// Verifico si llegué al final de la diagonal actual
		if(x < 0 || y >= m.filas()) {
			// Avanzo a la siguiente diagonal
			if(x0 < m.columnas() - 1) x0++;
			else y0++;

			// Avanzo al primer elemento de la nueva diagonal
			x = x0;
			y = y0;
		}
	}
}
