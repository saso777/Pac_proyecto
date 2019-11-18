#pragma once
#include"Boton.h"
#include "Pantalla_Carga.h"
#include "Juego.h"
#include "Mapa.h"
using namespace std;
using namespace sf;
class Pantalla_Lvl
{
private:
	int nivelesObtenidos;
	RenderWindow* rw;
	string nombreTema;
	string ruta;

	Pantalla_Carga* pantallaCarga;
	Juego* juego;
	Mapa* mapa;
	Boton* lvl;	int focusedLvl;

	// Textos de Informacion de Nivel

	Boton* txts[4];

	// Textos de Informacion de Nivel

public:
	Pantalla_Lvl();

	RenderWindow* getRW();

	void verPuntuacion();
	void swapLvl(Event* evento);
	void selecLvl();

	void screenLoop();
	void show();

	void mostrarLvls();
	void mostrarDatosLvl();
	void selecDatos();
};
