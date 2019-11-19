#include "Pantalla_Carga.h"

Pantalla_Carga::Pantalla_Carga()
{//
	personaje = new Boton("", "", -200, 300, "Game_Files/Textures/Personajes/PAC_Perseguido.png", -200, 300, 0.3, 0.3);

	mV = 0;	mH = 0;
	tiempo = 0;
	progreso = 0;
	rw = new RenderWindow(VideoMode(800, 600), "");
	rw->setFramerateLimit(30);

	selectAnim();

	loadLoop();
}

int Pantalla_Carga::getRanNum(int i, int f)
{
	int valor = 0;
	srand(time(NULL));
	valor = rand() % f + i;

	return valor;
}

void Pantalla_Carga::loadLoop()
{
	int frame = 0;
	Event* evento = new Event();
	while (rw->isOpen()) {
		while (rw->pollEvent(*evento)) {
			if (evento->type == Event::Closed) {
				//rw->close();//hiba a hacer que se pudiera cancelar la carga pero por cuestiones de tiempo, para no
				//tener que hacer que se devuelva a la seleccion de nivel
			}
		}
		show();
		doAnim();
		frame++;
		if (frame >= 30) {
			tiempo++;
			frame = 0;
		}
		if (tiempo >= 10) {
			rw->close();
		}
	}
}

void Pantalla_Carga::show()
{

	rw->clear();

	showPer();

	rw->display();

}

void Pantalla_Carga::evaluarPos()/////////////////////////7arreglar esta parte////////////////////////////////////
{
	if (personaje->getSprite()->getPosition().x - personaje->getAncho() / 2 > 800 + personaje->getAncho() / 2
		|| personaje->getX() + personaje->getAncho() / 2 < 0 - personaje->getAncho() / 2
		|| personaje->getY() - personaje->getAlto() / 2 > 600 + personaje->getAlto() / 2
		|| personaje->getY() + personaje->getAlto() / 2 < 0 - personaje->getAlto() / 2) {
		selectAnim();
	}
}

void Pantalla_Carga::selectAnim()
{
	int valor = getRanNum(1, 4);
	//personaje = NULL;
	//personaje = new Boton("", -500, -500, "Game_Files/Textures/Personajes/PAC_Perseguido.png", 0.3, 0.3);
	cout << valor << endl;
	if (valor == 1) {
		anim1();
	}
	else if (valor == 2) {
		anim2();
	}
	else if (valor == 3) {
		anim3();
	}
	else if (valor == 4) {
		anim4();
	}
}

void Pantalla_Carga::showPer()
{
	rw->draw(*personaje->getSprite());
}

void Pantalla_Carga::doAnim()
{

	personaje->setX(personaje->getX() + mH);
	personaje->setY(personaje->getY() + mV);
	evaluarPos();

}


void Pantalla_Carga::anim1()
{
	personaje->setX(0 - personaje->getAncho() / 2);
	personaje->setY(300);//hay que hacer un flip aqui al sprite
	personaje->getSprite()->setRotation(180);
	mH = 75;
	mV = 0;
}

void Pantalla_Carga::anim2()
{
	personaje->setX(800 + personaje->getAncho() / 2);
	personaje->setY(300);
	personaje->getSprite()->setRotation(0);
	mH = -75;
	mV = 0;
}

void Pantalla_Carga::anim3()
{
	personaje->setX(400);
	personaje->setY(0 - personaje->getAlto() / 2);
	personaje->getSprite()->setRotation(270);
	mH = 0;
	mV = 75;
}

void Pantalla_Carga::anim4()
{
	personaje->setX(400);
	personaje->setY(600 + personaje->getAlto() / 2);
	personaje->getSprite()->setRotation(90);
	mH = 0;
	mV = -75;
}




//faltan otras animaciones en diagonal y circulos.
