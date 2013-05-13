#ifndef METODOS_H_
#define METODOS_H_

#include "Matriz.h"

void agregarRuidoAditivo(Matriz &m, const double mu, const double sigma);
void atenuarIntervaloSonido(Matriz &m, const int coefInicial, const int coefFinal, const double k); // Teniendo la DST, pone en 0 los elementos menores a (max - min) /2

#endif /* METODOS_H_ */
