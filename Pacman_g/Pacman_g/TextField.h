#pragma once
#include "SFML/Graphics.hpp"
#include<iostream>
using namespace std;
using namespace sf;
class TextField
{

private:

	int tamMax, x, y;	float alto, ancho;//tamaño que no exeda, posicion y escala o tamaño
	bool lleno;//por si no hay nada escrito entonces pone un texto provisional y cuando se toca se borra para que escriba
	Sprite* sprite;//la imagen que puede que tenga de fondo
	Text* text;//texto y ademas tengo que agregar una fuente por defecto

public:

	TextField(string txt, int tamMax, int x, int y, float alto, float ancho, bool lleno, string  urlSprt);
	
	void setTamMax(int tamMax);
	void setX(int x);
	void setY(int y);
	void setAlto(float alto);
	void setAncho(float ancho);
	void setLleno(bool lleno);
	void setSprite(string url);
	void setStringText(string txt);

	int getTamMax();
	int getX();
	int getY();
	float getAlto();
	float getAncho();
	bool isLleno();
	Sprite*& getSprite();
	Text*& getText();

	void ajustarSpriteTexto();//para que cuando escriba el sprite se ajuste al tamaño, parecido a como funciona en boton.
	


};

