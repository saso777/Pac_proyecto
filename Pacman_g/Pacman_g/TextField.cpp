#include "TextField.h"

TextField::TextField(string txt, int tamMax, int x, int y, float alto, float ancho, bool lleno, string  urlSprt)
{//
	//referente al cuadro de texto
	this->lleno = lleno;
	this->tamMax = tamMax;
	Font* f = new Font();
	if (f->loadFromFile("Game_Files/Fonts/CotrellCFExtraBold-Regular.ttf")) {

		text = new Text();
		text->setFont(*f);
		text->setString(txt);
		text->setScale(ancho / text->getGlobalBounds().width, alto / text->getGlobalBounds().height);

		cout << "ScalaX: " << text->getScale().x << endl;
		cout << "ScalaY: " << text->getScale().y << endl;

		text->setOrigin(text->getPosition().x + text->getGlobalBounds().width / 2, text->getPosition().y + text->getGlobalBounds().height / 2);
		text->setPosition(x, y);


	}
	else {
		text = NULL;
	}
	//referente al cuadro de texto

	Texture* t = new Texture();
	if (t->loadFromFile(urlSprt)) {

		sprite = new Sprite(*t);
		sprite->setOrigin(sprite->getPosition().x + sprite->getGlobalBounds().width / 2, sprite->getPosition().y + sprite->getGlobalBounds().height / 2);
		sprite->setPosition(x, y);
		ajustarSpriteTexto();

	}
	else {

		sprite = NULL;

	}

	
}

void TextField::setTamMax(int tamMax)
{

	this->tamMax = tamMax;

}

void TextField::setX(int x)
{

	this->x = x;

}

void TextField::setY(int y)
{

	this->y = y;

}

void TextField::setAlto(float alto)
{

	this->alto = alto;

}

void TextField::setAncho(float ancho)
{
	this->ancho = ancho;
}

void TextField::setLleno(bool lleno)
{

	this->lleno = lleno;

}

void TextField::setSprite(string url)
{

	if (sprite != NULL) {

		Texture* t = new Texture();
		if (t->loadFromFile(url)) {

			sprite->setTexture(*t);
			if (text != NULL) {

				ajustarSpriteTexto();

			}

		}

	}
	

}

void TextField::setStringText(string txt)
{

	if (text != NULL) {

		text->setString(txt);

	}

}

int TextField::getTamMax()
{
	return tamMax;
}

int TextField::getX()
{
	return x;
}

int TextField::getY()
{
	return y;
}

float TextField::getAlto()
{
	return alto;
}

float TextField::getAncho()
{
	return ancho;
}

bool TextField::isLleno()
{
	return lleno;
}

Sprite*& TextField::getSprite()
{
	return sprite;
}

Text*& TextField::getText()
{
	return text;
}

void TextField::ajustarSpriteTexto()
{

	if ((sprite && text) != NULL) {
		
		float sclx = 0, scly = 0;

		sclx = (text->getGlobalBounds().width / sprite->getGlobalBounds().width) + 5;
		scly = (text->getGlobalBounds().height / sprite->getGlobalBounds().height) + 5;
		
		cout << "tamaño en x:   " << sclx << endl;
		cout << "tamaño en y:   " << scly << endl;

		sprite->setScale(sclx,scly);
		

	}

}

