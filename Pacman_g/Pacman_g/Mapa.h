#pragma once
#include "Nodo.h"
#include<iostream>
#include<fstream>
#include <sstream>
using namespace std;
class Mapa
{
private:
	int lvl;
	string ruta;
	char letras[21][19];
	int tamGrafo;
	Nodo** grafo;
	Nodo* listaAdyacencia;
public:
	Mapa(int lvl);

	void setTamGrafo(int tamGrafo);

	int getTamGrafo();
	char getLetras(int fil, int col);
	Nodo** getGrafo();
	Nodo* getGrafo(int indice);
	Nodo* getListaAdyacencia();

	bool verificarTam();
	void inicializarMatLetras();
	void inicializarGrafo();
	void clcPsNd(Nodo*& nodo, int x, int y);
	int** generaMatrizDeAdyacencia();
	int getGrafo(int x,int y);
	void generarListasAdyacencia(int** matriz);

};
