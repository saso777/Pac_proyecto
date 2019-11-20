#pragma once
#include "SFML/Graphics.hpp"
#include "Boton.h"
#include <iostream>
#include <fstream>
#include<stdlib.h>
using namespace std;
using namespace sf;

class Pantalla_Jugador
{//
private:

	RenderWindow* rw;
	Boton* datos[6];
	string datos_tiempo_jugado;
	string fatasmas_comidos;
	string total_vidas;
	string jugador;
	string data_cap;
public:
	Pantalla_Jugador();

	void loop();
	void draw();
	void mostrarTofeos();

	void verTrofeos();
	void ajustarSigPosicionXYTrofeo(int &x, int &y, int i);
	void guardarLineaTrofeo(int posicion, int ubicacionVec, int& x, int& y);
	void obtener_datos_de_jugador();
	void mostrar_datos();
};