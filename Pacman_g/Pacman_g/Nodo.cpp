#include "Nodo.h"

Nodo::Nodo()
{//
	id = 0;
	x = 0;
	y = 0;
	px = 0;
	py = 0;
	pesoAcumulado = 0;
	iteraciones = 0;
	vertices = NULL;
	sig = NULL;
	predecesor = NULL;
	hayPacman = false;
	ocupado = false;
	pesoIzq = 0;
}

Nodo::Nodo(int id, int x, int y, float peso)
{
	this->ocupado = false;
	this->hayPacman = false;
	this->id = id;
	this->x = x;
	this->y = y;
	this->pesoIzq = peso;
}

Nodo::Nodo(Nodo* nodo) {
	id = nodo->getId();
	pesoAcumulado = nodo->getPesoAcumulado();
	iteraciones = nodo->getIteraciones();
	vertices = nodo->getVertices();
	sig = NULL;
	predecesor = nodo->getPredecesor();
	x = nodo->getX();
	y = nodo->getY();
	px = nodo->getPx();
	py = nodo->getPy();
	hayPacman = nodo->getHayPacman();
	ocupado = nodo->isOcupado();
}

void Nodo::setPesoAcumulado(int pesoA)
{
	pesoAcumulado = pesoA;
}

void Nodo::setIteraciones(int ite)
{
	iteraciones = ite;
}

void Nodo::setSiguiente(Nodo* sig)
{
	this->sig = sig;
}

void Nodo::setPredecesor(Nodo* pred)
{
	predecesor = pred;
}

void Nodo::setVertices(Vertice* v)
{
	this->vertices = v;
}

void Nodo::setId(int id)
{
	this->id = id;
}

void Nodo::setX(int x)
{
	this->x = x;
}

void Nodo::setY(int y)
{
	this->y = y;
}

void Nodo::setPx(float px)
{
	this->px = px;
}

void Nodo::setPy(float py)
{
	this->py = py;
}

void Nodo::setPesoIzq(int cont)
{
	this->pesoIzq = cont;
}

void Nodo::setPesoAr(int cont)
{
	this->pesoAr = cont;
}

void Nodo::setPesoDer(int cont)
{
	this->pesoDer = cont;
}

void Nodo::setPesoAb(int cont)
{
	this->pesoAb = cont;
}

void Nodo::setHayPacman(bool hayPacman)
{
	this->hayPacman = hayPacman;
}

void Nodo::setOcupado(bool ocupado)
{
	this->ocupado = ocupado;
}

int Nodo::getPesoAcumulado()
{
	return pesoAcumulado;
}

int Nodo::getIteraciones()
{
	return iteraciones;
}

Nodo* Nodo::getSiguiente()
{
	return sig;
}

Nodo* Nodo::getPredecesor()
{
	return predecesor;
}

Vertice* Nodo::getVertices()
{
	return vertices;
}

int Nodo::getId()
{
	return id;
}

int Nodo::getX()
{
	return x;
}

int Nodo::getY()
{
	return y;
}

float Nodo::getPx()
{
	return px;
}

float Nodo::getPy()
{
	return py;
}

int Nodo::getPesoAr()
{
	return pesoAr;
}

int Nodo::getPesoAb()
{
	return pesoAb;
}

int Nodo::getPesoIzq()
{
	return pesoIzq;
}

int Nodo::getPesoDer()
{
	return pesoDer;
}

bool Nodo::getHayPacman()
{
	return hayPacman;
}

bool Nodo::isOcupado()
{
	return ocupado;
}

void Nodo::insertar(Nodo*& lista, int dato) {
	Nodo* aux = lista;
	if (aux == NULL) {
		lista = new Nodo();
		lista->setId(dato);
	}
	else {
		if (aux->getSiguiente() == NULL) {
			Nodo* nodo = new Nodo();
			nodo->setId(dato);
			lista->setSiguiente(nodo);
		}
		else {
			aux = aux->getSiguiente();
			insertar(aux, dato);
		}
	}
}

void Nodo::insertarNodo(Nodo*& lista, Nodo* nodo) {
	Nodo* aux = lista;
	Nodo* nuevo = new Nodo(nodo);
	if (aux == NULL) {
		lista = nuevo;
	}
	else {
		if (aux->getSiguiente() == NULL) {
			aux->setSiguiente(nuevo);
		}
		else {
			aux = aux->getSiguiente();
			insertarNodo(aux, nuevo);
		}
	}
}

Nodo* Nodo::eliminar(Nodo*& lista, int dato) {
	Nodo* eliminado = NULL;
	if (lista != NULL) {
		Nodo* aux = lista;
		if (aux->getSiguiente() == NULL) {
			if (aux->getId() == dato) {
				eliminado = aux;
				lista = NULL;
			}
		}
		else {
			if (aux->getId() == dato) {
				eliminado = aux;
				lista = aux->sig;
			}
			else {
				bool deleted = false;
				while (aux->getSiguiente() != NULL && !deleted) {
					if (aux->getSiguiente()->getId() == dato) {
						eliminado = aux->getSiguiente();
						deleted = true;
						if (aux->getSiguiente()->getSiguiente() != NULL) {
							aux->setSiguiente(aux->getSiguiente()->getSiguiente());
						}
						else {
							aux->setSiguiente(NULL);
						}
					}
					else {
						aux = aux->getSiguiente();
					}
				}
			}
		}
	}

	return eliminado;
}

int Nodo::menor(Nodo*& lista) {
	Nodo* aux = lista;
	int menor = -1;
	if (aux != NULL) {
		menor = aux->getId();
		if (aux->getSiguiente() != NULL) {
			while (aux->getSiguiente()!= NULL) {
				if (aux->getPesoAcumulado() > aux->getSiguiente()->getPesoAcumulado()) {
					menor = aux->getSiguiente()->getId();
				}
				aux = aux->getSiguiente();
			}
		}
	}
	return menor;
}

bool Nodo::existe(Nodo*& lista, int dato) {
	bool encontrado = false;
	if (lista != NULL) {
		Nodo* aux = lista;
		while (aux != NULL && !encontrado) {
			if (aux->getId() == dato) {
				encontrado = true;
			}
			aux = aux->getSiguiente();
		}
	}
	return encontrado;
}

void Nodo::cambiarVisitados(Nodo*& lista) {
	Nodo* aux = lista;
	while (aux != NULL) {
		Vertice* vertices = aux->getVertices();
		while (vertices != NULL) {
			if (vertices->getVisitado()) {
				//cout << vertices->getDato() << endl;
				vertices->setVisitado(false);
			}
			vertices = vertices->getSiguiente();

		}
		//cout << endl;
		aux = aux->getSiguiente();
	}
}

void Nodo::setVisitado(Nodo*& lista, int dato) {
	Nodo* aux = lista;
	while (aux != NULL) {
		Vertice* vertices = aux->getVertices();
		while (vertices != NULL) {
			if (vertices->getDato() == dato && !vertices->getVisitado()) {
				vertices->setVisitado(true);
			}
			vertices = vertices->getSiguiente();
		}
		aux = aux->getSiguiente();
	}
}

Nodo* Nodo::getNodoDato(Nodo*& lista, int dato) {
	Nodo* nodo = NULL;
	Nodo* aux = lista;
	while (aux != NULL) {
		if (aux->getId() == dato) {
			nodo = aux;
			break;
		}
		else {
			aux = aux->getSiguiente();
		}
	}
	return nodo;
}

void Nodo::mostrarLista(Nodo*& lista) {
	Nodo* aux = lista;
	Vertice* v = new Vertice();
	if (aux != NULL) {
		if (aux->getSiguiente() != NULL) {
			cout << aux->getId();
			v = aux->getVertices();
			v->mostrarVertices(v);
			cout << "\n|\n";
			aux = aux->getSiguiente();
			mostrarLista(aux);
		}
		else {
			cout << aux->getId();
			v = aux->getVertices();
			v->mostrarVertices(v);
		}
	}
}
