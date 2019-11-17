#include "Pantalla_Lvl.h"

Pantalla_Lvl::Pantalla_Lvl()
{

	pantallaCarga = NULL;
	mapa = NULL;
	juego = NULL;

	verPuntuacion();

	focusedLvl = nivelesObtenidos;

	selecLvl();

	for (int i = 0; i < 4; i++) {

		txts[i] = new Boton("Ninguna", "", 0, 0, "Game_Files/Textures/UI/Scenary/Rotulo1.png", 0, 0, 1, 1, 0, 0);
		txts[i]->setColorPNG(50, 80, 100, 200);

	}


	selecDatos();

	rw = new RenderWindow(VideoMode(800, 600), "Niveles");

	rw->setFramerateLimit(30);



	screenLoop();
}

RenderWindow* Pantalla_Lvl::getRW()
{
	return rw;
}

void Pantalla_Lvl::verPuntuacion()
{
	ifstream f;

	f.open("Game_Files/Data/Score/ptj_Total.txt");

	string num = "";

	if (!f.fail()) {
		getline(f, num);
		getline(f, num);

		int pts = 0;

		stringstream x(num);

		x >> pts;

		cout << pts << " + " << num << endl;
		if (pts < 1900) {
			nivelesObtenidos = 1;
		}
		else if (pts < 3800) {
			nivelesObtenidos = 2;
		}
		else if (pts < 5700) {
			nivelesObtenidos = 3;
		}
		else if (pts < 7600) {
			nivelesObtenidos = 4;
		}
		else if (pts < 9500) {
			nivelesObtenidos = 5;
		}
		else if (pts < 11400) {
			nivelesObtenidos = 6;
		}
		else if (pts < 13300) {
			nivelesObtenidos = 7;
		}
		else if (pts < 15200) {
			nivelesObtenidos = 8;
		}
		else if (pts < 17100) {
			nivelesObtenidos = 9;
		}
		else if (pts >= 17100) {
			nivelesObtenidos = 10;
		}
	}

}

void Pantalla_Lvl::swapLvl(Event* evento)
{
	cout << focusedLvl << " vs " << nivelesObtenidos << endl;
	if (evento->key.code == Keyboard::Left || evento->key.code == Keyboard::Down) {
		if (focusedLvl > 1) {
			focusedLvl--;
		}
		cout << "LEFT" << endl;
	}
	else if (evento->key.code == Keyboard::Right || evento->key.code == Keyboard::Up) {

		if (focusedLvl < nivelesObtenidos) {
			focusedLvl++;
		}
		cout << "RIGHT" << endl;
	}
	selecLvl();
	selecDatos();
}

void Pantalla_Lvl::selecLvl()
{

	if (focusedLvl == 1) {
		nombreTema = "The_Jocker";
	}
	else if (focusedLvl == 2) {
		nombreTema = "The_Simpsons";
	}
	else if (focusedLvl == 3) {
		nombreTema = "Iron_Man";
	}
	else if (focusedLvl == 4) {
		nombreTema = "Spider-man";
	}
	else if (focusedLvl == 5) {
		nombreTema = "Batman";
	}
	else if (focusedLvl == 6) {
		nombreTema = "Superman";
	}
	else if (focusedLvl == 7) {
		nombreTema = "Deadpool";
	}
	else if (focusedLvl == 8) {
		nombreTema = "One_Piece";
	}
	else if (focusedLvl == 9) {
		nombreTema = "Naruto_Shippuden";
	}
	else if (focusedLvl == 10) {
		nombreTema = "Dragon_Ball";
	}
	selecDatos();
}

void Pantalla_Lvl::screenLoop()
{
	Event* evento = new Event();
	while (rw->isOpen()) {

		show();

		while (rw->pollEvent(*evento)) {

			if (evento->type == Event::Closed) {

				rw->close();

			}
			else if (evento->type == Event::KeyReleased) {

				swapLvl(evento);

				if (evento->key.code == Keyboard::Enter) {
					//pantallaCarga = new Pantalla_Carga();
					//pantallaCarga = NULL;
					mapa = new Mapa(focusedLvl);

					if (mapa->verificarTam()) {

						juego = new Juego(mapa, focusedLvl, nombreTema);

					}
					rw->close();
					//una vez finalizada la "carga" llama a ejecutar juego

				}
				else if (evento->key.code == Keyboard::Escape) {

					rw->close();

				}
			}
		}
	}
}

void Pantalla_Lvl::show()
{
	rw->clear();
	mostrarLvls();
	mostrarDatosLvl();
	rw->display();

}

void Pantalla_Lvl::mostrarLvls()
{
	ruta = "Game_Files/Textures/Backgrounds/Lvl" + to_string(focusedLvl) + "/" + nombreTema + ".jpg";

	lvl = new Boton("", 400, 300, ruta, 1, 1);

	rw->draw(*lvl->getSprite());
}

void Pantalla_Lvl::mostrarDatosLvl()
{
	for (int i = 0; i < 4; i++) {

		if (txts[i] != NULL) {

			if (txts[i]->getSprite() != NULL) {

				rw->draw(*txts[i]->getSprite());
				rw->draw(*txts[i]->getText());

			}

		}

	}
}

void Pantalla_Lvl::selecDatos()
{
	string r = "Game_Files/Data/Score/pts_" + to_string(focusedLvl) + ".txt", texto = "";
	ifstream f;

	f.open(r);

	if (!f.fail()) {



		if (txts[0] != NULL) {
			if (txts[0]->getSprite() != NULL) {
				txts[0]->setPosicionSprite(0, 300);
				txts[0]->setPosicionTexto(5, 300);
				txts[0]->setTexto("Nivel: " + to_string(focusedLvl));
				txts[0]->ajustarBtnTexto();
			}
		}

		for (int i = 1; i < 4 && !f.eof(); i++) {
			getline(f, texto);
			getline(f, texto);
			if (i == 1) {
				texto = "Mayor Cant. Puntos: " + texto;
			}
			else if (i == 2) {
				texto = "Cant. Veces Jugado: " + texto;
			}
			else if (i == 3) {

				texto = "Mejor Tiempo: " + texto;
			}
			if (txts[i] != NULL) {

				if (txts[i]->getSprite() != NULL) {

					txts[i]->setPosicionSprite(0, 300 + (50 * i));
					txts[i]->setPosicionTexto(5, 300 + (50 * i));
					txts[i]->setTexto(texto);

					txts[i]->ajustarBtnTexto();

				}

			}


			//txts[i]->setPosition(0, 400 + (i * 50));


		}
	}

}