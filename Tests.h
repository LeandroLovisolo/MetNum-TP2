#ifndef TESTS_H_
#define TESTS_H_

void pruebaSonidoRuidoAditivo();
void pruebaSonidoRuidoImpulsivo();
void aplicarYrevertirDCT();
void pruebaSubmatriz();
void pruebaMetodoSimpleEliminacion();
void aplicarYrevertirDCTMatrices();
void pruebaCargarYGrabarMatriz();
void pruebaAtenuar();
void pruebaConversionImagenAVector();
Matriz *cargarSonido(char *fileName);
Matriz *cargarMatriz(char *fileName);
void grabarMatriz(Matriz& mat, char* fileName);
void grabarSonido(Matriz& mat, char* fileName);

#endif
