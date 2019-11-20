#pragma once
#include "Boton.h"
#include "Nodo.h"
#include<iostream>
#include<SFML/Graphics.hpp>
using namespace std;
using namespace sf;
class Personaje
{//
private:
	int pix, piy;//punto inicial del personaje

	int velocidad;
	int vidas;
	string nombre;
	string ruta;
	Texture* texture;
	Sprite* sprite;
	int movH, movV;
	float x, y;
	bool esperarTecla;
	bool comer;
	bool disable;

	//contadores(se pueden usar par saber cuantas veces quien mato a quien, en el caso del pacman son los fantasmas y viceversa)
	int contador;
	//contadores(se pueden usar par saber cuantas veces quien mato a quien, en el caso del pacman son los fantasmas y viceversa)

	Event* accion, * accionAnt;
public:
	Personaje(int vidas, int velocidad, string nombre, float x, float y, string ruta, float scaleX, float scaleY, bool comer);
	//sets y gets
	void setPix(int pix);
	void setPiy(int piy);
	void setVidas(int vidas);
	void setVelocidad(int velocidad);
	void setNombre(string nombre);
	void setTexture(string url);
	void setSprite(Texture* texture);
	void setMovH(int movH);
	void setMovV(int movV);
	void setX(float x);
	void setY(float y);
	void setEsperaTecla(bool esperarTecla);
	void setComer(bool comer);
	void setContador(int contador);

	int getPix();
	int getPiy();
	int getVidas();
	int getVelocidad();
	string getNombre();
	Texture*& getTexture();
	Sprite*& getSprite();
	int getMovH();
	int getMovV();
	float getX();
	float getY();
	bool getEsperaTecla();
	bool getComer();
	int getCotador();

	//sets y gets



	//en cuanto a los esprites
	float getTope();
	float getFondo();
	float getIzquierda();
	float getDerecha();
	//en cuanto a los esprites


	//metodos propios
	void guardarTecla(Event* evento);
	void selecMov(int mx, int my);
	void verFutColision(Boton* scenario[21][19], int& ptsTotal, int& pacdots, int& fantasmasMuertos, int& vidas, int& vidasPerdidas, Personaje* fantasmas[4]);
	void revisarPosicion(Boton* scenario[21][19], int x, int y, string accion, int& ptsTotal, int& pacdots, int& fantasmasMuertos, int& vidas, int& vidasPerdidas, Personaje* fantasmas[4]);
	//void adaptarPos_Person_Bloc(Boton* bloque);
	void verColisionConFantasmas(int& ptsTotal, int& fantasmasMuertos, int& vidas, int& vidasPerdidas, Personaje* fantasmas[4]);
	void moverPersonaje(Boton* scenario[21][19], int& ptsTotal, int& pacdots, int& fantasmasMuertos, int& vidas, int& vidasPerdidas, Personaje* fantasmas[4]);
	//metodos propios

	//REFERENCTE A LOS FANTASMAS
	void fElegirMovimiento(Nodo*& camino);//se recive el nodo se obtiene sus coordenadas y se madna a mover fantasma en la direccion indicada, reajsta ubicacion.
	bool fMoverFantasma(Nodo*& camino, bool cambiar);//x futura y Y futura
	bool fEvaluarPosFantasma(Nodo*& camino);//se procede a reajustar las distancia entre el fantasma y el nodo
	//REFERENTE A LOS FANTASMAS
};
