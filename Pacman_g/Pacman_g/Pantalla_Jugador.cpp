#include "Pantalla_Jugador.h"

Pantalla_Jugador::Pantalla_Jugador()
{
	rw = new RenderWindow(VideoMode(800, 600), "Datos de Jugador");
	rw->setFramerateLimit(20);
	verTrofeos();

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
	//mostrar El textfield y poder guardar el nombre y ademas poner el boton para reiniciar y ademas el de comprar vidas si es que tiene menos de 6
	mostrarTofeos();

	rw->display();
}

void Pantalla_Jugador::mostrarTofeos()
{
	for (int i = 0; i < 6; i++) {

		if (datos[i] != NULL) {

			if (datos[i]->getSprite() != NULL) {

				rw->draw(*datos[i]->getSprite());

			}
			if (datos[i]->getText() != NULL) {

				rw->draw(*datos[i]->getText());

			}

		}

	}
}



void Pantalla_Jugador::verTrofeos()
{
	
	int posicion = 0, x = 1, y = 200;
	//leer cuales trofeos tiene y agregarlos al vector de botones
	for (int i = 2; i <= 12; i += 2) {

		guardarLineaTrofeo(i, posicion, x, y);

		posicion++;

	}

	//veo el txt veo cuales son diferentes de - y aumento el tamaño y despues agrego los botones
	//correspondientes a nombre ,los trofeos y el boton de reiniciar
	//continuar despues de finalizar seccion de ganar trofeos

}

void Pantalla_Jugador::ajustarSigPosicionXYTrofeo(int& x, int& y, int i)
{

	//cout << "ENTRANDO A CAMBIO DE POSICION" << endl;
	if (datos[i] != NULL) {

		if (datos[i]->getText() != NULL) {
			//cout << endl << "NO ES NULO" << endl;
			if (x + (datos[i]->getText()->getGlobalBounds().width) + 2 > 800) {

				x = 1;
				if (datos[i]->getSprite() != NULL) {

					y += (datos[i]->getText()->getPosition().y + (datos[i]->getText()->getGlobalBounds().height) + 2);

				}
				else {

					y += 100;

				}

				//datos[i]->getText()->setPosition(x, y);

			}
			else {

				x = (datos[i]->getText()->getPosition().x + datos[i]->getText()->getGlobalBounds().width / 2) + 10;

			}

		}

	}
	//cout << "FINALIZACION DEL CAMBIO" << endl;

}

void Pantalla_Jugador::guardarLineaTrofeo(int posicion, int ubicacionVec, int& x, int& y)
{
	ifstream f;

	f.open("Game_Files/Data/Achievements/Logros.txt");
	string pal = "";
	if (!f.fail()) {
		
		for (int i = 0; i < posicion; i++) {

			getline(f, pal);
		}
		
		string txt = "";
		if (ubicacionVec == 0) {
			txt = "Clasico";
		}
		else if(ubicacionVec == 1){
			txt = "Cazador";
		}
		else if (ubicacionVec == 2) {
			txt = "Experto";
		}
		else if (ubicacionVec == 3) {
			txt = "Encierro";
		}
		else if (ubicacionVec == 4) {
			txt = "Flash";
		}
		else if (ubicacionVec == 5) {
			txt = "Rey de la Colina";
		}
		cout << "PALABRA:::::::::::::::::::::::::----->" << pal << endl;
		if (pal != "-") {

			datos[ubicacionVec] = new Boton("Mostrar_Trofeo", txt, x, y, "Game_Files/Textures/Objetos/Trofeos/Tofeo_2.png", x, y, 0.05, 0.05);

		}
		else {

			datos[ubicacionVec] = NULL;	

		}
		
		
		//este algoritmo esta asi debido a ocmplicaciones de tiempo y no se logro optimizar de la mejor forma posible...
		if (datos[ubicacionVec] != NULL) {

			if (datos[ubicacionVec]->getSprite() != NULL) {

				if (datos[ubicacionVec]->getText() != NULL) {

					if (x + datos[ubicacionVec]->getText()->getGlobalBounds().width > 800) {

						x = 1;

						y = (datos[ubicacionVec]->getSprite()->getPosition().y + (datos[ubicacionVec]->getSprite()->getGlobalBounds().height / 2)
							+ (datos[ubicacionVec]->getText()->getGlobalBounds().height) + 50);

					}


					datos[ubicacionVec]->getSprite()->setPosition(x + datos[ubicacionVec]->getText()->getGlobalBounds().width / 2
						, y);//sumar la mitad de lo que tiene ese texto para poder asi agregarlo bien con respecto a la posicion anterior


					datos[ubicacionVec]->getText()->setPosition(datos[ubicacionVec]->getSprite()->getPosition().x
						, datos[ubicacionVec]->getSprite()->getPosition().y + (datos[ubicacionVec]->getSprite()->getGlobalBounds().height / 2));

				}

			}

		}
		

		ajustarSigPosicionXYTrofeo(x, y, ubicacionVec);//despues de ajustar la posicion se ajusta la posicion del texto



	}

}
