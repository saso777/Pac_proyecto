#include "Mapa.h"

Mapa::Mapa(int lvl)
{
	this->lvl = lvl;
	tamGrafo = 0;
	listaAdyacencia = NULL;
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
			if (letras[i][j] == '#' || letras[i][j] == '4' || letras[i][j] == '$' || letras[i][j] == 'f') {
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
			if (letras[i][j] == '#' || letras[i][j] == '4' || letras[i][j] == '$' || letras[i][j] == 'f') {
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
				listaAdyacencia->insertarNodo(listaAdyacencia, nodo);
			}
		}
	}


	tamGrafo = contNodos;
	/*for (int i = 0; i < tamGrafo; i++) {
		cout << "nodo numero " << i << endl;
		cout << "  x = " << grafo[i]->getX() << endl;
		cout << "  Y = " << grafo[i]->getY() << endl;
		cout << "  peso arriba = " << grafo[i]->getPesoAr() << endl;
		cout << "  peso abajo = " << grafo[i]->getPesoAb() << endl;
		cout << "  peso izquierda= " << grafo[i]->getPesoIzq() << endl;
		cout << "  peso derecha = " << grafo[i]->getPesoDer() << endl;
		cout << grafo[i]->getX()<< " " << grafo[i]->getY() << " " << grafo[i]->getPesoDer() << " " << grafo[i]->getId() << endl;

	}*/
}
int Mapa::getGrafo(int x, int y) {
	for (int i = 0; i < tamGrafo; i++) {
		if (grafo[i]->getX() == x) {
			if (grafo[i]->getY() == y) {
				return i;
			}
		}
	}
	return 0;
}
void Mapa::generarListasAdyacencia(int** matriz)
{
	Nodo* aux = listaAdyacencia;
	for (int i = 0; i < tamGrafo; i++) {
		Vertice* v = aux->getVertices();
		for (int j = 0; j < tamGrafo; j++) {
			if (matriz[i][j] != 0) {
				Nodo* nodo = grafo[j];
				aux->getVertices()->insertar(v, nodo->getId(), matriz[i][j]);
			}
		}
		aux->setVertices(v);
		aux = aux->getSiguiente();
	}
}

int** Mapa::generaMatrizDeAdyacencia() {
	//inicia varinantes
	int fix;
	int **matriz = new int*[tamGrafo];

	for (int i = 0; i <tamGrafo;i++) {
		matriz[i] = new int[tamGrafo];
	}
	for (int i = 0; i < tamGrafo; i++) {
		for (int j = 0; j < tamGrafo; j++) {
			matriz[i][j] = 0;
		}
		
	}
	

	//aca se setean todos los datos
	for (int i = 0; i <tamGrafo; i++) {
		
		if(grafo[i]->getPesoAr() != 0&& grafo[i]->getPesoAr() != 1000) {
			fix = getGrafo(grafo[i]->getX(), grafo[i]->getY() - grafo[i]->getPesoAr());
			matriz[i][fix]=grafo[i]->getPesoAr();
		}
		if (grafo[i]->getPesoAb() != 0&& grafo[i]->getPesoAb() != 1000) {
			fix = getGrafo(grafo[i]->getX(), grafo[i]->getY() + grafo[i]->getPesoAb());
			matriz[i][fix] = grafo[i]->getPesoAb();
		}
		if (grafo[i]->getPesoDer() != 0&& grafo[i]->getPesoDer() != 1000) {
			if (grafo[i]->getX() + grafo[i]->getPesoDer() < 19) {
				fix = getGrafo(grafo[i]->getX() + grafo[i]->getPesoDer(), grafo[i]->getY());
			}else {
				fix = getGrafo((grafo[i]->getX() + grafo[i]->getPesoDer()) - 19, grafo[i]->getY());
			}
			matriz[i][fix] = grafo[i]->getPesoDer();
		}
		if (grafo[i]->getPesoIzq() != 0&& grafo[i]->getPesoIzq() != 1000) {
			if (grafo[i]->getX() - grafo[i]->getPesoIzq() > 0) {
				fix = getGrafo(grafo[i]->getX() - grafo[i]->getPesoIzq(), grafo[i]->getY());
			}else {
				fix = getGrafo((grafo[i]->getX() - grafo[i]->getPesoIzq()) + 19, grafo[i]->getY());
			}
			int temporal = grafo[i]->getPesoIzq();
			matriz[i][fix] = temporal;
		}
		
	}
	for (int i = 0; i < tamGrafo; i++) {
		for (int j = 0; j < tamGrafo; j++) {
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}

	generarListasAdyacencia(matriz);

	return matriz;
	

}



/*void Mapa::clcPsNd(Nodo*& nodo, int x, int y)
{

	int cont, xx = x, yy = y;
	//verificar si tiene nodo a la izquierda
	cont = 0;
	if (xx > 0) {
		xx = xx - 1;
		while (letras[yy][xx] != 'x') {
			if (letras[yy][xx] == ' ') {

				cont = 0;
				break;

			}
			else if (letras[yy][xx] != '#' && letras[yy][xx] != '4' && letras[yy][xx] != '$' ) {
				xx--;
				if (xx < 0) {
					xx = 18;
					cout << "PASO:" << xx << endl;
					//cont = 0;
				}
				//else {
					cont++;
				//}
					cout << "SIGUE:" << xx << endl;
			}
			else {
				xx--;
				if (xx < 0) {
					xx = 18;

					//cont = 0;
				}
				//else {
					cont++;
				//}

				cout << "NODO ENCONTRADO EN X:" << xx << endl;
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
			if (letras[yy][xx] == ' ') {

				cont = 0;
				break;

			}
			else if (letras[yy][xx] != '#' && letras[yy][xx] != '4' && letras[yy][xx] != '$' && letras[yy][xx] != ' ') {
				xx++; 
				if (xx > 18) {
					xx = 0;
					cout << "PASO:" << xx << endl;
					//cont = 0;
				}
				//else {
					cont++;
				//}
					cout << "SIGUE:" << xx << endl;
			}
			else {
				xx++;
				if (xx > 18) {
					xx = 0;
					//cont = 0;
				}
				//else {
					cont++;
					cout << "NODO ENCONTRADO EN X:" << xx << endl;
				//}
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

			if (letras[yy][xx] == ' ') {

				cont = 0;
				break;

			}
			else if (letras[yy][xx] == ' ') {

				break;

			}
			else if (letras[yy][xx] != '#' && letras[yy][xx] != '4' && letras[yy][xx] != '$' && letras[yy][xx] != ' ') {
				yy--;
				if (yy < 0) {
					yy = 20;
					cout << "PASO:" << yy << endl;
					//cont = 0;
				}
				//else {
					cont++;
				//}
				cout << "SIGUE:" << yy << endl;
				
			}
			else {
				yy--;
				if (yy < 0) {
					yy = 20;
					//cont = 0;
				}
				//else {
					cont++;
					cout << "NODO ENCONTRADO EN Y:" << yy << endl;
				//}
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

			if (letras[yy][xx] == ' ') {

				cont = 0;
				break;

			}
			else if(letras[yy][xx] != '#' && letras[yy][xx] != '4' && letras[yy][xx] != '$' && letras[yy][xx] != ' ') {
				yy++;
				if (yy > 20	) {
					yy = 0;
					cout << "PASO:" << yy << endl;
					//cont = 0;
				}
				//else {
					cont++;
				//}
					cout << "SIGUE:" << yy << endl;
			}
			else {
				yy++;
				if (yy > 21) {
					yy = 0;
					//cont = 0;
				}
				//else {
					cont++;
					cout << "NODO ENCONTRADO EN Y:" << yy << endl;
				//}
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
/*}*/



void Mapa::clcPsNd(Nodo*& nodo, int x, int y)
{

	int cont, xx = x, yy = y;
	//verificar si tiene nodo a la izquierda
	cont = 0;
	if (xx > 0) {
		xx = xx - 1;
		while (letras[yy][xx] != 'x') {
			if (letras[yy][xx] == ' ') {

				cont = 0;
				break;

			}
			else if (letras[yy][xx] != '#' && letras[yy][xx] != '4' && letras[yy][xx] != '$') {
				xx--;
				cont++;
				cout << "SIGUE:" << xx << endl;
			}
			else {
				xx--;
				cont++;
				cout << "NODO ENCONTRADO EN X:" << xx << endl;
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
			if (letras[yy][xx] == ' ') {

				cont = 0;
				break;

			}
			else if (letras[yy][xx] != '#' && letras[yy][xx] != '4' && letras[yy][xx] != '$' && letras[yy][xx] != ' ') {
				xx++;
				cont++;
				cout << "SIGUE:" << xx << endl;
			}
			else {
				xx++;
				cont++;
				cout << "NODO ENCONTRADO EN X:" << xx << endl;
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

			if (letras[yy][xx] == ' ') {

				cont = 0;
				break;

			}
			else if (letras[yy][xx] == ' ') {

				break;

			}
			else if (letras[yy][xx] != '#' && letras[yy][xx] != '4' && letras[yy][xx] != '$' && letras[yy][xx] != ' ') {
				yy--;
				cont++;
				cout << "SIGUE:" << yy << endl;
			}
			else {
				yy--;
				cont++;
				cout << "NODO ENCONTRADO EN Y:" << yy << endl;
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

			if (letras[yy][xx] == ' ') {

				cont = 0;
				break;

			}
			else if (letras[yy][xx] != '#' && letras[yy][xx] != '4' && letras[yy][xx] != '$' && letras[yy][xx] != ' ') {
				yy++;
				cont++;
				cout << "SIGUE:" << yy << endl;
			}
			else {
				yy++;
				cont++;
				cout << "NODO ENCONTRADO EN Y:" << yy << endl;
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





Nodo* Mapa::getListaAdyacencia() {
	return listaAdyacencia;
}