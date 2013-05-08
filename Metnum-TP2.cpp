#include <iostream>
#include "Matriz.h"
#include "Ecuaciones.h"
using namespace std;

int main() {
	Matriz *mat = MatrizM(5, 10);
	mat->print();
	return 0;
}
