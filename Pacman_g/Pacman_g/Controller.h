#pragma once
#include "Boton.h"
#include "Pantalla_Lvl.h"
#include "SFML/Graphics.hpp"
#include "Pantalla_Jugador.h"
#include "fstream"
class Controller
{
private:

	int rx, ry, fps;
	RenderWindow* rw;
	Pantalla_Lvl* pantallaLvl ;
	Pantalla_Jugador* pantallaJugador;
	int puntajeMaximo;


	Sprite* logo;
	Boton* botones[];


public:
	Controller();

	void setRX(int rx);
	void setRY(int ry);
	void setfps(int fps);
	void setPuntajeManximo(int puntajeMaximo);
	void setRenderWindow(int x, int y);




	void selector(int posX, int posY);

	void verInicio();
	void verPantallaJugador();
	void verConfiguracion();
	void verSelecNiveles();

	void controllerLoop();
	void showItems();
};