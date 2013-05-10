#ifndef METODOS_H_
#define METODOS_H_

#include "Matriz.h"

void agregarRuidoAditivo(Matriz &m);

//Teniendo la DST, pone en 0 los elementos menores a (max-min)/2
void eliminarRuidoMetodo1(Matriz &m);


#endif /* METODOS_H_ */
