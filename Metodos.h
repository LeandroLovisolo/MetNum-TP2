#ifndef METODOS_H_
#define METODOS_H_

#include "Matriz.h"

void agregarRuidoAditivo(Matriz &m, const double mu, const double sigma);
void atenuarIntervaloSonido(Matriz &m, const int coefInicial, const int coefFinal, const double k);
void agregarRuidoImpulsivo(Matriz &m, const double p);
void umbralizarIntervaloSonido(Matriz &m, const int coefInicial, const int coefFinal, const double k);

#endif /* METODOS_H_ */
