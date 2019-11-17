#include "Nodo.h"

Nodo::Nodo()
{
	id = 0;
	x = 0;
	y = 0;
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