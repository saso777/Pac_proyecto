#pragma once
#include "SFML/Graphics.hpp"
#include "Boton.h"
#include <iostream>
#include <fstream>
using namespace std;
using namespace sf;

class Pantalla_Jugador
{//
private:

	RenderWindow* rw;
	Boton* datos[6];

public:
	Pantalla_Jugador();

	void loop();
	void draw();
	void mostrarTofeos();

	void verTrofeos();
	void ajustarSigPosicionXYTrofeo(int &x, int &y, int i);
	void guardarLineaTrofeo(int posicion, int ubicacionVec, int& x, int& y);
};