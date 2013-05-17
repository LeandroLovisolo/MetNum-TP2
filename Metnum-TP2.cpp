#include <iostream>
#include <fstream>
#include <utility>
#include "Matriz.h"
#include "Ecuaciones.h"
#include "Metodos.h"
#include "Tests.h"
#include <string>
#include <string.h>
#include <ctype.h>


using namespace std;

void Ayuda(string ejecutable) {
    cout << "Uso: " << ejecutable << "<tipo de muestra> <archivo> <tipo de ruido>"
    	 << "<parametro del ruido> <metodo de eliminacion de ruido> <parametro del metodo> " << endl
         << endl
         << "  <tipo de muestra> <archivo> imagen / sonido lena.pgm / signals/dopp512.txt"
         << "  Tipo de archivo presentado en la entrada" << endl
         << "  <tipo de ruido> <parametro del ruido>"
         << "  Tipo de ruido a aplicar a la entrada: --aditivo / --impulsivo , con k y p parámetros respectivamente" << endl
         << "  <tipo de metodo de eliminacion de ruido> <parametro del metodo>"
         << "  Metodo de eliminacion de ruido a aplicar: --umbralizar / -- atenuar con k parametro" << endl << endl
         << "Ejemplo: ./metnum sonido signals/dopp512.txt aditivo 2 atenuar 0.5" << endl;
    exit(-1);
}

int main(int argc, char *argv[]) {
	Matriz* muestra = 0;
	Matriz* muestraConRuido = 0;
	if(argc != 7) Ayuda(argv[0]);
	//Preparo los argumentos
	char* tipo_muestra = argv[1];
	char* archivo = argv[2];
	char* tipo_ruido = argv[3];
	char* param_ruido = argv[4];
	char* metodo_eliminacion = argv[5];
	char* param_metodo = argv[6];

	//Veo los parámetros sobre la muestra
	if(strcmp(tipo_muestra,"imagen") == 0) {
		muestra = cargarMatriz(archivo);
		muestraConRuido = new Matriz(*muestra);
		if(muestra == 0) Ayuda(argv[0]);
	}
	else if(strcmp(tipo_muestra,"sonido") == 0) {
		muestra = cargarSonido(archivo);
		muestraConRuido = new Matriz(*muestra);
		if(muestra == 0) Ayuda(argv[0]);
	}
	else {
		Ayuda(argv[0]);
	}

	//Le corto a archivo su extension
	char *punto = strrchr(archivo, '.');
	*punto = '\0';

	//Veo los parámetros sobre el ruido
	if(strcmp(tipo_ruido, "aditivo") == 0 && isdigit(param_ruido[0])) {
		agregarRuidoAditivo(*muestraConRuido, 0, atof(param_ruido));

	}
	else if(strcmp(tipo_ruido, "impulsivo") == 0 && isdigit(param_ruido[0])) {
		agregarRuidoImpulsivo(*muestraConRuido, atof(param_ruido));
	}
	else {
		Ayuda(argv[0]);
	}
	//Imprimo el PSNR del ruido agregado
	cout << "PSNR de la muestra con ruido agregado: " << PSNR(*muestra, *muestraConRuido, muestra->max()) << endl;

	//Se preparan las matrices para calcular su DCT
	Matriz* dctOriginal = aplicarDCT(*muestra); //DCT del dato original
	Matriz* dctRuido = aplicarDCT(*muestraConRuido); //DCT del dato con ruido
	//Copia de dctRuido para luego grabar dctRuido
	Matriz dctRuidoEliminado(*dctRuido);

	//Buffers para los nombres de los archivos
	char dctOriginalFileName[60];
	char dctRuidoFileName[60];
	char muestraConRuidoFileName[60];
	char resFileName[60];

	//Escritura de nombres de archivos
	//[base].dct.[extension]
	sprintf(dctOriginalFileName, "%s.dct.txt", archivo); 
	 //[base].dct.[tipo de ruido].[parametro del ruido].[extension]
	sprintf(dctRuidoFileName, "%s.dct.%s.%s.txt", archivo, 
	tipo_ruido, param_ruido);

	if(strcmp(tipo_muestra,"sonido") == 0) {
		//[base].[tipo de ruido].[parametro del ruido].[extension]
		sprintf(muestraConRuidoFileName, "%s.%s.%s.txt", archivo, tipo_ruido, param_ruido); 
	}
	else {
		sprintf(muestraConRuidoFileName, "%s.%s.%s.pgm", archivo, tipo_ruido, param_ruido);
	}

	//Checkeo de metodos, aplicación y grabado

	if(strcmp(tipo_muestra,"sonido") == 0) {
		//Veo los metodos de eliminacion
		if(strcmp(metodo_eliminacion, "atenuar") == 0 && isdigit(param_metodo[0])) {
			atenuarIntervaloSonido(dctRuidoEliminado,
					               dctRuidoEliminado.filas() / 2,
					               dctRuidoEliminado.filas() - 1,
					               atof(param_metodo));
		}
		else if(strcmp(metodo_eliminacion, "umbralizar") == 0 && isdigit(param_metodo[0])) {
			umbralizarIntervaloSonido(dctRuidoEliminado,
					                  dctRuidoEliminado.filas() / 2,
					                  dctRuidoEliminado.filas() - 1,
					                  dctRuidoEliminado.rango() * atof(param_metodo));
		}
		else {
			Ayuda(argv[0]);
		}
		//Consigo los resultados de la aplicación de los métodos
		Matriz* res = revertirDCT(dctRuidoEliminado, muestraConRuido->rango());
		//Imprimo el PSNR del resultado del metodo
		cout << "PSNR de la muestra luego de aplicar el método: " << PSNR(*muestra, *res, muestra->max()) << endl;
		
		sprintf(resFileName, "%s.%s.%s.%s.%s.txt", archivo, tipo_ruido,
		param_ruido, metodo_eliminacion, param_metodo);

		char dctRuidoEliminadoFileName[60];
		//[base].dct.[tipo de ruido].[parametro del ruido].[metodo de eliminacion].[param metodo].[extension]
		sprintf(dctRuidoEliminadoFileName, "%s.dct.%s.%s.%s.%s.txt", archivo, tipo_ruido,
		param_ruido, metodo_eliminacion, param_metodo);
		//Grabo todo
		grabarSonido(*muestraConRuido, muestraConRuidoFileName); //Muestra con ruido
		grabarSonido(*dctOriginal, dctOriginalFileName); //DCT original
		grabarSonido(*dctRuido, dctRuidoFileName); //DCT con ruido
		grabarSonido(dctRuidoEliminado, dctRuidoEliminadoFileName); //DCT atenuar
		grabarSonido(*res, resFileName); //Resultado
		delete res;
	}
	else {
		//Veo los metodos de eliminacion
		if(strcmp(metodo_eliminacion, "atenuar") == 0 && isdigit(param_metodo[0])) {
			atenuarImagen(dctRuidoEliminado,
					      dctRuidoEliminado.filas() * dctRuidoEliminado.columnas() * 0.3447,
					      dctRuidoEliminado.filas() * dctRuidoEliminado.columnas() - 1,
					      atof(param_metodo));
		}
		else if(strcmp(metodo_eliminacion, "umbralizar") == 0 && isdigit(param_metodo[0])) {
			atenuarImagen(dctRuidoEliminado,
					      dctRuidoEliminado.filas() * dctRuidoEliminado.columnas() * 0.3,
					      dctRuidoEliminado.filas() * dctRuidoEliminado.columnas() - 1,
					      dctRuidoEliminado.rango() * atof(param_metodo));
		}
		else {
			Ayuda(argv[0]);
		}
		//Consigo los resultados de la aplicación de los métodos
		Matriz* res = revertirDCT(dctRuidoEliminado, muestraConRuido->rango());
		//Imprimo el PSNR del resultado del metodo
		cout << "PSNR de la muestra luego de aplicar el método: " << PSNR(*muestra, *res, muestra->max()) << endl;

		sprintf(resFileName, "%s.%s.%s.%s.%s.pgm", archivo, tipo_ruido,
		param_ruido, metodo_eliminacion, param_metodo);

		char dctRuidoEliminadoFileName[60];
		//[base].dct.[tipo de ruido].[parametro del ruido].[metodo de eliminacion].[param metodo].[extension]
		sprintf(dctRuidoEliminadoFileName, "%s.dct.%s.%s.%s.%s.txt", archivo, tipo_ruido,
		param_ruido, metodo_eliminacion, param_metodo);

		//Grabo todo
		grabarMatriz(*muestraConRuido, muestraConRuidoFileName); //Muestra con ruido

		Matriz* vectorDCTOriginal = convertirImagenAVector(*dctOriginal);
		grabarSonido(*vectorDCTOriginal, dctOriginalFileName);
		Matriz* vectorDCTRuido = convertirImagenAVector(*dctRuido);
		grabarSonido(*vectorDCTRuido, dctRuidoFileName);
		Matriz* vectorDctRuidoEliminado = convertirImagenAVector(dctRuidoEliminado);
		grabarSonido(*vectorDctRuidoEliminado, dctRuidoEliminadoFileName);

		grabarMatriz(*res, resFileName); //Resultado
		delete res;
	}
	delete dctOriginal;
	delete dctRuido;
	delete muestra;
	delete muestraConRuido;
	return 0;
}
