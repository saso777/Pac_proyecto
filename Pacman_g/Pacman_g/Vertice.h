#pragma once
#include <iostream>

using namespace std;

class Vertice {//
	private:
		Vertice* sig;
		bool visitado;
		int peso;
		int id;
	public:
		Vertice();
		Vertice* getSiguiente();
		void setSiguiente(Vertice* sig);
		bool getVisitado();
		void setVisitado(bool v);
		int getPeso();
		void setPeso(int p);
		int getDato();
		void setDato(int id);
		void insertar(Vertice*& lista, int dato, int peso);
		void mostrarVertices(Vertice*& vertices);
};