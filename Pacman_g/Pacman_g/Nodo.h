#pragma once
#include "Vertice.h"
class Nodo
{
private:
	int id;
	int x, y, pesoIzq, pesoDer, pesoAr, pesoAb, pesoAcumulado;
	int iteraciones;
	float px, py;
	bool hayPacman, ocupado;
	Vertice* vertices;
	Nodo* sig;
	Nodo* predecesor;
public:
	Nodo();
	Nodo(int id, int x, int y, float peso);
	Nodo(Nodo* nodo);
	void setPesoAcumulado(int pesoA);
	void setIteraciones(int ite);
	void setSiguiente(Nodo* sig);
	void setPredecesor(Nodo* pred);
	void setVertices(Vertice* v);
	void setId(int id);
	void setX(int x);
	void setY(int y);
	void setPx(float px);
	void setPy(float py);
	void setPesoIzq(int cont);
	void setPesoAr(int cont);
	void setPesoDer(int cont);
	void setPesoAb(int cont);
	void setHayPacman(bool hayPacman);
	void setOcupado(bool ocupado);

	int getPesoAcumulado();
	int getIteraciones();
	Nodo* getSiguiente();
	Nodo* getPredecesor();
	Vertice* getVertices();
	int getId();
	int getX();
	int getY();
	float getPx();
	float getPy();
	int getPesoAr();
	int getPesoAb();
	int getPesoIzq();
	int getPesoDer();
	bool getHayPacman();
	bool isOcupado();
	bool existe(Nodo*& lista, int dato);
	int menor(Nodo*& lista);
	void insertar(Nodo*& lista, int dato);
	Nodo* eliminar(Nodo*& lista, int dato);
	Nodo* getNodoDato(Nodo*& lista, int dato);
	void insertarNodo(Nodo*& lista, Nodo* dato);
	void cambiarVisitados(Nodo*& lista); // cambia todos los vertices visitados a no visitados para volver a aplicar el algoritmo
	void setVisitado(Nodo*& lista, int dato);
	void mostrarLista(Nodo*& lista);
};