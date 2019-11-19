#pragma once
#include<cstdlib>
#include "Boton.h"
#include "SFML/Graphics.hpp"
using namespace sf;
class Pantalla_Carga
{
private:
	int tiempo, progreso;

	RenderWindow* rw;
	int mH, mV;
	Boton* personaje;
	Boton* vecPer[];

public:
	Pantalla_Carga();
	int getRanNum(int i, int f);

	void loadLoop();
	void show();

	void evaluarPos();
	void selectAnim();
	void showPer();
	void doAnim();
	void anim1();
	void anim2();
	void anim3();
	void anim4();
};
