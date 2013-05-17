#ifndef TESTS_H_
#define TESTS_H_

#include "Matriz.h"

void pruebaSonidoRuidoAditivo();
void pruebaSonidoRuidoImpulsivo();
void aplicarYrevertirDCT();
void pruebaSubmatriz();
void pruebaMetodoSimpleEliminacion();
void aplicarYrevertirDCTMatrices();
void pruebaCargarYGrabarMatriz();
void pruebaAtenuar();
void pruebaConversionImagenAVector();
Matriz *cargarVector(char *fileName);
Matriz *cargarMatriz(char *fileName);
void grabarMatriz(Matriz& mat, char* fileName);
void grabarVector(Matriz& mat, char* fileName);

#endif
