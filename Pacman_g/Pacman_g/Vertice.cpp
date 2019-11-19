#include "Vertice.h"

Vertice::Vertice()
{
	sig = NULL;
	visitado = false;
	peso = 0;
	id = 0;
}

Vertice* Vertice::getSiguiente()
{
	return sig;
}

void Vertice::setSiguiente(Vertice* sig)
{
	this->sig = sig;
}

bool Vertice::getVisitado()
{
	return visitado;
}

void Vertice::setVisitado(bool v)
{
	visitado = v;
}

int Vertice::getPeso()
{
	return peso;
}

void Vertice::setPeso(int p)
{
	peso = p;
}

int Vertice::getDato()
{
	return id;
}

void Vertice::setDato(int id)
{
	this->id = id;
}

void Vertice::insertar(Vertice*& lista, int dato, int peso) {
	Vertice* aux = lista;
	if (aux == NULL) {
		lista = new Vertice();
		lista->setDato(dato);
		lista->setPeso(peso);
	}
	else {
		if (aux->sig == NULL) {
			Vertice* nodo = new Vertice();
			nodo->setDato(dato);
			nodo->setPeso(peso);
			lista->setSiguiente(nodo);
		}
		else {
			aux = aux->getSiguiente();
			insertar(aux, dato, peso);
		}
	}
}

void Vertice::mostrarVertices(Vertice*& vertices) {
	Vertice* aux = vertices;
	if (aux != NULL) {
		if (aux->getSiguiente() != NULL) {
			cout << "->" << aux->getDato();
			aux = aux->getSiguiente();
			mostrarVertices(aux);
		}
		else {
			cout << "->" << aux->getDato();
		}
	}
	else {
		cout << "->null";
	}
}

