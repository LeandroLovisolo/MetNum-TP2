#include <random>
#include <chrono>

#include "Metodos.h"

using namespace std;

void agregarRuidoAditivo(Matriz &m) {
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	default_random_engine generator(seed);
  	normal_distribution<double> distribution(7.0,30);
	for(int i = 0; i < m.filas(); i++) {
		for(int j = 0; j < m.columnas(); j++) {
			//cout << "Que larga: " << distribution(generator) << endl;
			m.elem(i,j) += distribution(generator);
		}
	}
}

void eliminarRuidoMetodo1(Matriz &m) {
	double umbral = (m.max() - m.min())/2;
	for(int i = 0; i < m.filas(); i++) {
		for(int j = 0; j < m.columnas(); j++) {
			if(abs(m.elem(i, j)) < umbral) m.elem(i, j) = 0;
		}
	}
}

void PruebaMetodo1(Matriz *Xoriginal) {
	/*
	//Creo 'y' y x
	//cout << "Matriz original: " << endl;
	//Xoriginal->print();

	//Matriz XconRuido = Matriz(Xoriginal->filas(),Xoriginal->columnas());
	Matriz XconRuido(*Xoriginal);

	//Uso como rango max, pongo en y y la matriz M para hacer y = m*x'
	Matriz *y = MatrizM(Xoriginal->filas(), Xoriginal->max());
	XconRuido = (*Xoriginal); //La copio de la original
	//Agrego ruido a x (señal original)
	agregarRuidoAditivo(XconRuido); //Le agrego ruido
	grabarSonido(&XconRuido, (char*) "dopp512ConRuido.txt");
	cout << "Ruido agregado PSNR: " << PSNR(Xoriginal, &XconRuido, Xoriginal->max()) << endl;
	(*y)*XconRuido; // y = m*x
	//Modifico y para intentar remover el ruido
	eliminarRuidoMetodo1(*y);
	//Vuelvo para atrás resolviendo M * Xreconstruido =y'
	//cout << "y = m*x" << endl;
	//y->print();
	Matriz *u = MatrizM(Xoriginal->filas(), Xoriginal->max());
	pair<Matriz*, Matriz*> pl = u->factorizacionPLU();
	//cout << "Matriz P: " << endl;
	//pl.first->print();
	//cout << "Matriz L: " << endl;
	//pl.second->print();
	//Hago Lj = Py
	(*pl.first)*(*y); //Py
	//cout << "P*y" << endl;
	//pl.first->print();
	Matriz *j = pl.second->forwardSubstitution(pl.first); //Lj = Py
	//Hago Ux = j
	Matriz *XSinRuido = u->backwardsSubstitution(j);
	grabarSonido(XSinRuido, (char*) "dopp512SinRuido.txt");
	//cout << "Matriz devuelta" << endl;
	//XSinRuido->print();
	cout << "Resultado PSNR: " << PSNR(Xoriginal, XSinRuido, Xoriginal->max()) << endl;
	delete y;
	delete u;
	delete pl.first;
	delete pl.second;
	delete j;
	delete XSinRuido;
	*/
}

