#ifndef ECUACIONES_H_
#define ECUACIONES_H_
#include "Matriz.h"

Matriz* MatrizG(const int n);
Matriz* MatrizSt(const int n);
double C(const int k, const int n);
Matriz* MatrizT(const int n);
Matriz* MatrizM(const int n, const int rango);
Matriz* MatrizMsombrero(const int n);
Matriz* aplicarDCT(Matriz& x);
Matriz* revertirDCT(Matriz& x, const int rango);

double PSNR(Matriz& matOriginal, Matriz& matPerturbada, const int rangoMax);
double ECM(Matriz& matOriginal, Matriz& matPerturbada);

#endif /* ECUACIONES_H_ */
