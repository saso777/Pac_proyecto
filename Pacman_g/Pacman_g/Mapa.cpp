#include "Mapa.h"

Mapa::Mapa(int lvl)
{
	this->lvl = lvl;
	tamGrafo = 0;

	ruta = "Game_Files/Lvl/Maps/LVL_" + to_string(lvl) + ".txt";


	if (verificarTam()) {

		inicializarMatLetras();
		inicializarGrafo();


	}



	/*
	for (int i = 0; i < 30; i++) {
		cout << "Posicion en Grafo : " << i << endl;
		cout << "Posicion en X: " << grafo[i]->getX() <<"--> Posicion en Y: " << grafo[i]->getY() << endl;
		cout << "Peso a la Derecha: " << grafo[i]->getPesoDer() << endl;
		cout << "Peso a la Izquierda: " << grafo[i]->getPesoIzq() << endl;
		cout << "Peso a la Arriba: " << grafo[i]->getPesoAr() << endl;
		cout << "Peso a la Abajo: " << grafo[i]->getPesoAb() << endl;
		cout << "Peso a la PX: " << grafo[i]->getPx() << endl;
		cout << "Peso a la PY: " << grafo[i]->getPy() << endl;
		cout << "***********************************************************"<<endl;
		//DENNIS ACUERDESE DE BORRAR ESTO(ESTO ES SOLO PARA VERIFICAR xd) att: isaac.....
	}
	*/
}

void Mapa::setTamGrafo(int tamGrafo)
{
	this->tamGrafo = tamGrafo;
}

int Mapa::getTamGrafo()
{
	return tamGrafo;
}

char Mapa::getLetras(int fil, int col)
{
	return letras[fil][col];
}

Nodo** Mapa::getGrafo()
{
	return grafo;
}

Nodo* Mapa::getGrafo(int indice)
{
	return grafo[indice];
}






bool Mapa::verificarTam()//validacion defectuosa
{
	ifstream file;
	file.open(ruta);
	if (!file.fail()) {

		int f = 0, c = 0;
		char letra;
		file.seekg(0);
		file.get(letra);

		//medir anchura no mas ni menos de 19
		while (letra != '\n') {
			c++;
			file.get(letra);

		}
		if (c == 19) {
			//medir altura, no mas ni menos de 21
			file.seekg(0);
			file.get(letra);
			while (!file.eof()) {

				if (letra == '\n') {
					f++;
				}
				file.get(letra);
			}
			f++;
			if (f == 21) {
				file.close();
				return true;
			}
			else {
				file.close();
				return false;
			}
		}
		else {
			file.close();
			return false;
		}
	}
	else {
		file.close();
		return false;
	}
}

void Mapa::inicializarMatLetras()
{
	ifstream file;
	file.open(ruta);
	if (!file.fail()) {
		char letra;
		int f = 0, c = 0;
		file.get(letra);
		while (!file.eof()) {
			if (letra != '\n') {
				letras[f][c] = letra;
				c++;
				file.get(letra);
			}
			else {
				if (f < 21) {
					c = 0;
					f++;
					file.get(letra);
				}
			}
		}
		/*
		cout << "Mostrando" << endl;
		for (int i = 0; i < 21; i++) {
			for (int j = 0; j < 19; j++) {
				cout << letras[i][j];
			}
			cout << endl;
		}*/
	}
	file.close();


}

void Mapa::inicializarGrafo()
{
	//cuantos nodos para el grafo abran?
	int contNodos = 0;

	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 19; j++) {
			if (letras[i][j] == '#' || letras[i][j] == '4' || letras[i][j] == '$') {
				contNodos++;
			}
		}
	}
	//ahora con esos nodos hagamos la matriz para simbolizar el grafo
	grafo = new Nodo * [contNodos];
	for (int i = 0; i < contNodos; i++) {
		grafo[i] = new Nodo();
	}
	//ahora recorramos otra vez las letras y agregemos ids pesos y ubicacion;
	int id = 0;
	contNodos = 0;
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 19; j++) {
			if (letras[i][j] == '#' || letras[i][j] == '4' || letras[i][j] == '$') {
				Nodo* nodo = new Nodo();
				nodo->setId(id);
				nodo->setX(j);
				nodo->setY(i);
				nodo->setPx((800 / 19) * j + ((800 / 19) / 2));
				nodo->setPy((720 / 21) * i + ((720 / 21) / 2));
				clcPsNd(nodo, j, i);
				grafo[contNodos] = nodo;
				contNodos++;

				id++;

			}
		}
	}


	tamGrafo = contNodos;
}

void Mapa::clcPsNd(Nodo*& nodo, int x, int y)
{

	int cont, xx = x, yy = y;
	//verificar si tiene nodo a la izquierda
	cont = 0;
	if (xx > 0) {
		xx = xx - 1;
		while (letras[yy][xx] != 'x') {

			if (letras[yy][xx] != '#' && letras[yy][xx] != '4' && letras[yy][xx] != '$') {
				xx--;
				cont++;
			}
			else {
				xx--;
				cont++;
				break;
			}



		}
		nodo->setPesoIzq(cont);
	}


	//verificar si tiene nodo a la derecha
	cont = 0;
	xx = x; yy = y;
	if (xx < 19) {
		xx = xx + 1;
		while (letras[yy][xx] != 'x') {
			if (letras[yy][xx] != '#' && letras[yy][xx] != '4' && letras[yy][xx] != '$') {
				xx++;
				cont++;
			}
			else {
				xx++;
				cont++;
				break;
			}
		}
		nodo->setPesoDer(cont);
	}

	//verificar si tiene nodo arriba
	cont = 0;
	xx = x; yy = y;
	if (yy > 0) {
		yy = yy - 1;
		while (letras[yy][xx] != 'x') {

			if (letras[yy][xx] != '#' && letras[yy][xx] != '4' && letras[yy][xx] != '$') {
				yy--;
				cont++;
			}
			else {
				yy--;
				cont++;
				break;
			}


		}
		nodo->setPesoAr(cont);
	}

	//verificar si tiene nodo abajo
	cont = 0;
	xx = x; yy = y;
	if (yy < 21) {
		yy = yy + 1;
		while (letras[yy][xx] != 'x') {

			if (letras[yy][xx] != '#' && letras[yy][xx] != '4' && letras[yy][xx] != '$') {
				yy++;
				cont++;
			}
			else {
				yy++;
				cont++;
				break;
			}


		}
		nodo->setPesoAb(cont);
	}
	////////////////////////BORRAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAR/////////
	/*cout << "Ubicacion X: " << x << " - Ubicacion Y:" << y << endl;
	cout << "Ubicacion PX:" << nodo->getPx() << " - Ubicacion PY: " << nodo->getPy() << endl;
	cout << "Nodos A izquierda: " << nodo->getPesoIzq() << endl;
	cout << "Nodos A Derecha: " << nodo->getPesoDer() << endl;
	cout << "Nodos A Arriba: " << nodo->getPesoAr() << endl;
	cout << "Nodos A Abajo: " << nodo->getPesoAb() << endl;*/
}