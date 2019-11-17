#pragma once
#include "SFML/Graphics.hpp"
#include "Boton.h"
#include <iostream>
#include <fstream>
using namespace std;
using namespace sf;

class Pantalla_Jugador
{
private:

	RenderWindow* rw;
	Boton** datos;
	int tam;

public:
	Pantalla_Jugador();

	void loop();
	void draw();


	void verTrofeos();

};
