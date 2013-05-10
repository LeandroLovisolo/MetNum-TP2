#ifndef METODOS_H_
#define METODOS_H_

#include "Matriz.h"

void agregarRuidoAditivo(Matriz &m);
void eliminarRuidoMetodo1(Matriz &m); // Teniendo la DST, pone en 0 los elementos menores a (max - min) /2
void PruebaMetodo1(Matriz *Xoriginal);

#endif /* METODOS_H_ */
