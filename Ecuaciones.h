#ifndef ECUACIONES_H_
#define ECUACIONES_H_
#include "Matriz.h"

Matriz *MatrizG(const int n);
Matriz *MatrizSt(const int n);
double C(const int k, const int n);
Matriz *MatrizT(const int n);
Matriz *MatrizM(const int n, const int rango);
Matriz *MatrizMsombrero(const int n);
double PSNRSonido(Matriz &matOriginal, Matriz &matPerturbada, const int rango);
double ECMSonido(Matriz &matOriginal, Matriz &matPerturbada);

#endif /* ECUACIONES_H_ */
