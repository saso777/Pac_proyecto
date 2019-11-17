#include "Pantalla_Jugador.h"

Pantalla_Jugador::Pantalla_Jugador()
{
	rw = new RenderWindow(VideoMode(800, 600), "Datos de Jugador");
	rw->setFramerateLimit(20);
	loop();
}

void Pantalla_Jugador::loop()
{
	Event* evento = new Event();
	while (rw->isOpen()) {

		draw();
		while (rw->pollEvent(*evento)) {

			if (evento->type == Event::Closed) {
				rw->close();
			}

		}

	}
}

void Pantalla_Jugador::draw()
{
	rw->clear();



	rw->display();
}

void Pantalla_Jugador::verTrofeos()
{
	ifstream f;
	tam = 2;
	f.open("");
	//veo el txt veo cuales son diferentes de - y aumento el tamaño y despues agrego los botones
	//correspondientes a nombre ,los trofeos y el boton de reiniciar
	//continuar despues de finalizar seccion de ganar trofeos

}