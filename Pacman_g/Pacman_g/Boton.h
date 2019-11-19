#pragma once
#include<iostream>
using namespace std;
#include "SFML/Graphics.hpp"
using namespace sf;
class Boton
{
private:
	float x, y, tx, ty;
	int alto, ancho;
	string accion;
	string texto;
	Texture* texture;
	Sprite* sprite;
	Text* text;

public:
	Boton(string accion, string texto, int x, int y, string url, float tx, float ty);
	Boton(string accion, string texto, int x, int y, string url, float tx, float ty, float scaleX, float scaleY);
	Boton(string accion, string texto, int x, int y, string url, float tx, float ty, float scaleX, float scaleY, float orX, float orY);
	Boton(string accion, int x, int y, string url, float scaleX, float scaleY);
	Boton(string accion, int x, int y, string url, float scaleX, float scaleY, float orX, float orY);

	void setX(int x);
	void setY(int y);
	void setAlto(int alto);
	void setAncho(int ancho);
	void setTX(float tx);
	void setTY(float ty);
	void setAccion(string accion);
	void setTexto(string texto);
	void setTexture(string url);
	void setSprite(string url);
	void setText(string texto);
	void setColorJPG(int a, int b, int c);
	void setColorPNG(int a, int b, int c, int d);

	void setPosicionSprite(float x, float y);
	void setPosicionTexto(float tx, float ty);



	int getX();
	int getY();
	int getAlto();
	int getAncho();
	float getTX();
	float getTY();
	Texture*& getTexture();
	Sprite*& getSprite();
	Text*& getText();
	string getAccion();



	bool ajustarBtnTexto();//
};