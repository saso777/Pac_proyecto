#include "Boton.h"

Boton::Boton(string accion, string texto, int x, int y, string url, float tx, float ty)
{
	this->x = 0; this->y = 0;
	this->accion = accion;//para poder evaluar en los condicionales del controller;
	this->texto = texto;//para agregarle al boton

	texture = new Texture();

	if (texture->loadFromFile(url)) {

		alto = texture->getSize().y; ancho = texture->getSize().x;

		sprite = new Sprite(*texture);

		sprite->setOrigin(sprite->getPosition().x + ancho / 2, sprite->getPosition().y + alto / 2);

		sprite->setPosition(x, y);

		this->x = sprite->getPosition().x;
		this->y = sprite->getPosition().y;
	}
	else {
		texture = NULL;
		sprite = NULL;
	}



	Font* font = new Font();
	text = new Text();
	this->tx = tx;	this->ty = ty;//aqui va el codigo para posicionar el texto en el lugar deseado;

	if (font->loadFromFile("Game_Files/Fonts/CotrellCFExtraBold-Regular.ttf")) {

		text->setString(texto);
		text->setFont(*font);
		text->setOrigin(text->getPosition().x + text->getGlobalBounds().width / 2, text->getPosition().y + text->getGlobalBounds().height / 2);
		text->setPosition(tx, ty);

	}
}

Boton::Boton(string accion, string texto, int x, int y, string url, float tx, float ty, float scaleX, float scaleY)
{
	this->x = 0; this->y = 0; this->alto = 0; this->ancho = 0; this->tx = 0; this->ty = 0;
	this->accion = accion;
	this->texto = texto;
	texture = new Texture();
	if (texture->loadFromFile(url)) {
		this->alto = texture->getSize().y * scaleY;
		this->ancho = texture->getSize().x * scaleX;
		sprite = new Sprite(*texture);
		sprite->setScale(scaleX, scaleY);
		sprite->setOrigin(sprite->getPosition().x + texture->getSize().x / 2, sprite->getPosition().y + texture->getSize().y / 2);
		sprite->setPosition(x, y);
	}
	else {
		texture = NULL;
		sprite = NULL;
	}

	Font* font = new Font();
	text = new Text();
	this->tx = tx;	this->ty = ty;

	if (font->loadFromFile("Game_Files/Fonts/CotrellCFExtraBold-Regular.ttf")) {

		text->setFont(*font);
		text->setString(texto);
		text->setOrigin(text->getPosition().x + text->getGlobalBounds().width / 2, (text->getPosition().y + text->getGlobalBounds().height / 2));
		text->setPosition(tx, ty);

	}
}


Boton::Boton(string accion, string texto, int x, int y, string url, float tx, float ty, float scaleX, float scaleY, float orX, float orY)
{
	this->x = 0; this->y = 0; this->alto = 0; this->ancho = 0; this->tx = 0; this->ty = 0;
	this->accion = accion;
	this->texto = texto;
	texture = new Texture();
	if (texture->loadFromFile(url)) {
		this->alto = texture->getSize().y * scaleY;
		this->ancho = texture->getSize().x * scaleX;
		sprite = new Sprite(*texture);
		sprite->setScale(scaleX, scaleY);
		if (orX != 0 && orY != 0) {
			sprite->setOrigin(sprite->getPosition().x + sprite->getGlobalBounds().width / 2, sprite->getPosition().y + sprite->getGlobalBounds().width / 2);
		}
		sprite->setPosition(x, y);
	}
	else {
		texture = NULL;
		sprite = NULL;
	}

	Font* font = new Font();
	text = new Text();
	this->tx = tx;	this->ty = ty;

	if (font->loadFromFile("Game_Files/Fonts/CotrellCFExtraBold-Regular.ttf")) {
		text->setFont(*font);
		text->setString(texto);
		text->setOrigin(text->getPosition().x + text->getGlobalBounds().width / 2, (text->getPosition().y + text->getGlobalBounds().height / 2) + 5);
		text->setPosition(tx, ty);


	}
}

Boton::Boton(string accion, int x, int y, string url, float scaleX, float scaleY)
{
	this->accion = accion;
	texture = new Texture();

	if (texture->loadFromFile(url)) {
		texture->loadFromFile(url);	alto = (texture->getSize().y) * scaleY; ancho = (texture->getSize().x) * scaleX;

		sprite = new Sprite(*texture);

		sprite->setOrigin(sprite->getPosition().x + ancho / 2, sprite->getPosition().y + alto / 2);

		sprite->setPosition(x, y);

		this->x = sprite->getPosition().x;
		this->y = sprite->getPosition().y;
		sprite->setScale(scaleX, scaleY);
	}
	else {
		texture = NULL;
		sprite = NULL;
	}

}


Boton::Boton(string accion, int x, int y, string url, float scaleX, float scaleY, float orX, float orY)
{
	this->accion = accion;
	texture = new Texture();

	if (texture->loadFromFile(url)) {
		texture->loadFromFile(url);

		sprite = new Sprite(*texture);


		if (orX != 0 && orY != 0) {

			orX = sprite->getPosition().x + sprite->getGlobalBounds().width / 2;
			orY = sprite->getPosition().y + sprite->getGlobalBounds().height / 2;

			x = x + (800 / 19) / 2;
			y = y + (720 / 21) / 2;

		}
		sprite->setScale(scaleX, scaleY);

		sprite->setOrigin(orX, orY);

		sprite->setPosition(x, y);

		alto = sprite->getGlobalBounds().height; ancho = sprite->getGlobalBounds().width;
		this->x = sprite->getPosition().x;
		this->y = sprite->getPosition().y;

	}
	else {

		this->x = x + ((800 / 19) / 2);
		this->y = y + ((720 / 21) / 2);
		texture = NULL;
		sprite = NULL;
		alto = 720 / 21;
		ancho = 800 / 19;

	}

}



void Boton::setX(int x)
{
	this->x = x;

	if (sprite != NULL) {
		if (sprite != NULL) {
			sprite->setPosition(x, y);
		}
	}
}

void Boton::setY(int y)
{
	this->y = y;
	if (sprite != NULL) {
		if (sprite != NULL) {
			sprite->setPosition(x, y);
		}
	}

}

void Boton::setAlto(int alto)
{
	this->alto = alto;
	if (sprite != NULL) {
		sprite->setScale(alto, ancho);
	}
}

void Boton::setAncho(int ancho)
{
	this->ancho = ancho;
	if (sprite != NULL) {
		sprite->setScale(alto, ancho);
	}
}

void Boton::setTX(float tx)
{
	if (text != NULL) {
		this->tx = tx;
		text->setPosition(tx, ty);
	}
}

void Boton::setTY(float ty)
{
	if (text != NULL) {
		this->ty = ty;
		text->setPosition(tx, ty);
	}
}

void Boton::setAccion(string accion)
{
	this->accion = accion;
}

void Boton::setTexto(string texto)
{
	if (text != NULL) {
		this->texto = texto;
		text->setString(texto);
	}

}

void Boton::setTexture(string url)
{
	texture = new Texture();
	texture->loadFromFile(url);
}

void Boton::setSprite(string url)
{
	texture = new Texture();
	if (texture->loadFromFile(url)) {
		texture->loadFromFile(url);
		sprite = new Sprite(*texture);

		sprite->setOrigin(sprite->getPosition().x + ancho / 2, sprite->getPosition().y + alto / 2);

		sprite->setPosition(x, y);
	}
	else {
		sprite = NULL;
		texture = NULL;
	}

}

void Boton::setText(string texto)
{
	//inecesario
	if (text != NULL) {
		text->setString(texto);
	}

}

void Boton::setColorJPG(int a, int b, int c)
{
	Color* color = new Color(a, b, c);//255 es el valor maximo para lo parametros si se pone algo mayor, quedara igual
	if (sprite != NULL) {
		sprite->setColor(*color);
	}
}

void Boton::setColorPNG(int a, int b, int c, int d)
{
	Color* color = new Color(a, b, c, d);
	if (sprite != NULL) {
		sprite->setColor(*color);
	}
}

void Boton::setPosicionSprite(float x, float y)
{
	this->setX(x);
	this->setY(y);
}

void Boton::setPosicionTexto(float tx, float ty)
{
	this->setTX(tx);
	this->setTY(ty);
}

int Boton::getX()
{
	return x;
}

int Boton::getY()
{
	return y;
}

int Boton::getAlto()
{
	return alto;
}

int Boton::getAncho()
{
	return ancho;
}

float Boton::getTX()
{
	return tx;
}

float Boton::getTY()
{
	return ty;
}

Texture*& Boton::getTexture()
{
	return texture;
}

Sprite*& Boton::getSprite()
{
	return sprite;
}

Text*& Boton::getText()
{
	return text;
}

string Boton::getAccion()
{
	return accion;
}

bool Boton::ajustarBtnTexto()
{
	if (sprite != NULL) {
		if (text->getFont() != NULL) {
			float w1 = 0, h1 = 0;
			float w2 = 0, h2 = 0;
			w1 = text->getGlobalBounds().width/* + 20*/;
			h1 = text->getGlobalBounds().height/* + 20*/;

			w2 = texture->getSize().x;
			h2 = texture->getSize().y;

			sprite->setScale((w1 / w2) + 0.2, (h1 / h2) + 0.2);

			return true;
		}
		else {
			return true;
		}
	}
	else {
		return false;
	}
}
