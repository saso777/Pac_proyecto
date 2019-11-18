#include "Juego.h"
Juego::Juego(Mapa* mapa, int lvl, string tema)
{
	cout << "Inicia Juego" << endl;
	juegoIniciado = false;

	pantalla_gameOver = NULL;

	//datos
	nivel = lvl;
	vidas = obtenerVidas();
	//para visualizar las vidas, tiempo y el puntaje en pantalla por primera vez...

	actualizarTextTiempo();
	evaluarVidas();
	actualizaTextPtjTotal();

	//para visualizar las vidas, tiempo y el puntajeen pantalla por primera vez...
	//para visualizar los puntos por primera vez;

	//para visualizar los puntos por primera vez;


	//inicializar Datos
	fantasmasMuertos = 0;
	ptsTotal = 0;
	tiempo = 0;

	pacDots = 0;


	tiempo_de_poder = 0;
	//inicializar Datos
//Datos


//referente a personajes
	pacman = NULL;
	for (int i = 0; i < 4; i++) {
		fantasmas[i] = NULL;
	}
	//referente a personajes



	//referente al escenario

	Texture texture;
	texture.loadFromFile("Game_Files/Textures/Backgrounds/Lvl" + to_string(lvl) + "/" + tema + ".jpg");
	background = new Sprite(texture);
	background->setPosition(0, 0);
	////////rectangulo para resaltar mapa
	backBanckground = new Sprite();
	Texture texture1;
	if (texture1.loadFromFile("Game_Files/Textures/UI/Buttons/grey_panel.png")) {
		backBanckground->setTexture(texture1);
		backBanckground->setPosition(0, 0);
		backBanckground->setScale(10.24, 7.2);
		Color* color = new Color(300, 300, 300, 120);
		backBanckground->setColor(*color);
	}
	////////rectangulo para resaltar mapa
	nombre = "NIVEL" + to_string(lvl) + ": " + tema;
	rx = 1024;
	ry = 720;
	fps = 60;
	rw = new RenderWindow(VideoMode(rx, ry), nombre);
	rw->setFramerateLimit(60);
	this->mapa = mapa;
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 19; j++) {
			letras[i][j] = mapa->getLetras(i, j);
		}
	}
	cargarMapaVisual();
	//referente al escenario


	cout << "Posicion X: " << scenario[0][0]->getSprite()->getPosition().x << endl;
	cout << "Pacdots Totales Restantes: " << pacDots << endl;
	cout << "Pts Optenidos: " << ptsTotal << endl;
	mapa->generaMatrizDeAdyacencia(); //Matriz de adyacencia
	gameLoop();

	cout << "**************************************" << endl;
	cout << "Pacdots Totales Restantes: " << pacDots << endl;
	cout << "Pts Optenidos: " << ptsTotal << endl;
	//borrar estos cout<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
}



void Juego::setJuegoIniciado(bool juegoIniciado)
{
	this->juegoIniciado = juegoIniciado;
}

void Juego::setNivel(int nivel)
{
	this->nivel = nivel;
}

void Juego::setNombre(string nombre)
{
	this->nombre = nombre;
	rw->setTitle(nombre);
}

void Juego::setRX(int rx)
{
	this->rx = rx;
	this->rw = new RenderWindow(VideoMode(rx, ry), nombre);
}

void Juego::setRY(int ry)
{
	this->ry = ry;
	this->rw = new RenderWindow(VideoMode(rx, ry), nombre);
}

void Juego::setRW(int x, int y)
{
	this->rw = new RenderWindow(VideoMode(rx, ry), nombre);
}

void Juego::setFps(int fps)
{
	this->fps = fps;
	this->rw->setFramerateLimit(fps);
}

bool Juego::getJuegoIniciado()
{
	return juegoIniciado;
}

int Juego::getNivel()
{
	return nivel;
}

string Juego::getNombre()
{
	return nombre;
}

int Juego::getRX()
{
	return rx;
}

int Juego::getRY()
{
	return ry;
}

RenderWindow* Juego::getRW()
{
	return rw;
}

int Juego::getFps()
{
	return fps;
}

int Juego::getPtsTotal()
{
	return ptsTotal;
}

int Juego::getPacdots()
{
	return pacDots;
}


void Juego::gameLoop()
{
	Event* evento = new Event();
	int mitadPacDots = pacDots / 2;
	int frames = 0;

	while (rw->isOpen()) {

		if (frames == 60) {
			frames = 0;

			if (juegoIniciado == true) {

				tiempo++;

			}
			if (pacman->getComer() == true) {

				tiempo_de_poder++;//el problemita aqui es que el tiempo no se reinicia si se come otro power pellet
				//sino que continua solamente
				//ademas como esta con base a la cantidad de frames entonces puede durar 9.5 segundos o similar

			}
		}

		while (rw->pollEvent(*evento)) {
			if (evento->type == Event::KeyPressed) {
				pacman->guardarTecla(evento);

				juegoIniciado = true;
			}
			else if (evento->type == Event::Closed) {
				rw->close();
				cout << "Su Tiempo Fue de: " << tiempo << "  Adios..." << endl;
			}
			//aquqi eventos para gameplay
		}
		/*
		cout << "POSITION X: " << pacman->getSprite()->getPosition().x << " POSITION Y: " << pacman->getSprite()->getPosition().y << endl;
		cout << "ORIGEN X: " << pacman->getSprite()->getOrigin().x << " ORIGIN Y: " << pacman->getSprite()->getOrigin().y << endl;
		//meter esto en asuntos pacman XD
		*/

		//ver se hay alguna colicion en la direccion a la que se le habia dicho al pacman que fuera
		pacman->verFutColision(scenario, ptsTotal, pacDots, fantasmasMuertos, vidas, vidasPerdidas, fantasmas);
		pacman->moverPersonaje(scenario, ptsTotal, pacDots, fantasmasMuertos, vidas, vidasPerdidas, fantasmas);
		//ver se hay alguna colicion en la direccion a la que se le habia dicho al pacman que fuera


		//cuando se vayan a mover a los fantasmas se deve hacer con el ondicional de juegoIniciado;
		if (juegoIniciado == true) {

			//moverFantasmas

		}


		//para poder saber en que Vertice del grafo esta pacman(aun falta hacer nmetodo para saber el futuro nodo al que puede ir
		convertirPosPacMat(pacman->getSprite()->getPosition().x, pacman->getSprite()->getPosition().y);
		//para poder saber en que Vertice del grafo esta pacman(aun falta hacer nmetodo para saber el futuro nodo al que puede ir



		//evaluar los Diferentes eventos que pueden suceder con respecto a los puntajes y tiempos...
		verificarTiempo_de_comida();
		verificarPts(mitadPacDots);
		evaluarVidas();
		//evaluar los Diferentes eventos que pueden suceder con respecto a los puntajes y tiempos...
		//Dibujar las cosas y sumar frames
		drawer();
		frames++;
		//Dibujar las cosas y sumar frames
	}

}

void Juego::drawer()
{
	rw->clear();

	mostrarEscenario();
	mostrarPersonajes();
	mostrarUI();

	rw->display();
}

void Juego::evaluarVidas()
{
	for (int i = 0; i < 6; i++) {
		//si el indice del vector es mayor a el numero de vidas que poseeentonces se procede a hacer las evaluaciones
		//y si resultan ser adecuadas para la situcacion entonces se cambia el color
		if (vecVidas[i] != NULL) {

			if (vecVidas[i]->getSprite() != NULL) {



				if (i >= vidas) {


					Color* c = new Color(126, 126, 126, 200);

					vecVidas[i]->getSprite()->setColor(*c);

				}
				else {

					Color* c = new Color(255, 255, 255, 255);

					vecVidas[i]->getSprite()->setColor(*c);

				}
			}

		}
		else {

			for (int i = 0; i < 6; i++) {
				vecVidas[i] = new Boton("Visualizar_Vidas_Activas", 800 + (18 * (2 * i)), 200, "Game_Files/Textures/Personajes/Pacman/PacMan_Ini.png", 0.06, 0.06);
				if (i >= vidas) {

					Color* c = new Color(126, 126, 126, 200);//si es mayor a las vidas que posee entonces se poen oscuras y tranparentes
					vecVidas[i]->getSprite()->setColor(*c);
					vecVidas[i]->setAccion("Visualizar_Vidas_Inactivas");

				}
			}

		}

	}
}

void Juego::verificarTiempo_de_comida()
{

	if (pacman->getComer() == true) {

		if (tiempo_de_poder > 10) {

			//ya que el color de los fantasmas se cambiaria desde la clase personaje en el metodo de 
			//verificar posicion entonces aqui solo se vuelven a poner normales y se anula el poder de pacman
			pacman->setComer(false);
			tiempo_de_poder = 0;
			Texture* t = new Texture();
			if (t->loadFromFile("Game_Files/Textures/Personajes/Pacman/PacMan_Ini.png")) {
				pacman->getSprite()->setTexture(*t);
			}

			Color* c = new Color(255, 255, 255, 255);
			for (int i = 0; i < 4; i++) {
				fantasmas[i]->getSprite()->setColor(*c);
			}
			c = NULL;

			//HACER COLOR DE LOS FANTASMAS NORMALES COMO ANTES

		}
		else {
			//cout << "Tiempo: " << tiempo_de_poder << endl;
		}

	}

}

void Juego::verificarPts(int mitadPacDots)
{

	if (mitadPacDots == ptsTotal / 10) {

		//aumentar la velocidad de los fantasmas
		cout << "PUNTOS******************************************************************************" << endl;

	}
	if (pacDots == 0) {

		cout << "Todos los pacdots comidos" << endl;
		ptsTotal = ptsTotal + (100 * nivel);
		gamePassed();
		rw->close();
		//se muestran cuantas vidas quedaron, cuantos puntos hizo, cual es el puntaje total, cauntos fantasmas murieron,
		//tiempo que duro la partida y si murio  no en la partida

	}
	else if (vidas == 0) {
		cout << "Sin Vidas" << endl;
		if (gameOver() == false) {
			rw->close();
		}
		else {
			vidas = obtenerVidas();
			pacman->setVidas(vidas);
		}

		//verificar el puntaje global total para asi poder ver si se pueden comprar algunos juegos

	}

}

void Juego::terminarJuego()//pequeña incongruensa .....
{
	//si vidas = a 0 y faltan pacdots entocnes game over
	//sino si vidas != 0 y pacdots = 0 entonces pantalla pasada y mostrar datos de partida.
}

bool Juego::gameOver()
{
	pantalla_gameOver = new Pantalla_GameOver(false, nivel, vidas, vidasPerdidas, fantasmasMuertos, ptsTotal, tiempo);
	//llamar a la pantalla de game over para asi poder decidir si comprar mas vidas o abandonar la partida.
	//cuando se cierre la ventana se pide una variable que muestra si decide cerrar por completo la partida o si se continua
	//una variable booleana
	return pantalla_gameOver->getContinuarPartida();//aqui cambiar la vara dependiendode lo que arroje la clase pantalla_Game_Over

}

void Juego::gamePassed()
{

	pantalla_gameOver = new Pantalla_GameOver(true, nivel, vidas, vidasPerdidas, fantasmasMuertos, ptsTotal, tiempo);//true para mostr
	//mostrar una ventana para mostrar puntos e ir a la pantalla de lvls

}

void Juego::actualizarTextTiempo()
{
	if (textTiempo != NULL) {

		textTiempo->setString("Tiempo:  " + to_string(tiempo));

	}
	else {
		Font* f = new Font();
		if (f->loadFromFile("Game_Files/Fonts/CotrellCFExtraBold-Regular.ttf")) {

			textTiempo = new Text();

			textTiempo->setFont(*f);

			textTiempo->setString("Tiempo:  " + tiempo);

			textTiempo->setOrigin(textTiempo->getPosition().x /*+ textTiempo->getGlobalBounds().width / 2*/, textTiempo->getPosition().y + textTiempo->getGlobalBounds().height / 2);

			textTiempo->setPosition(805, 100);

		}
		else {

			textTiempo = NULL;

		}

	}

}

void Juego::actualizaTextPtjTotal()
{
	if (textPtjTotal != NULL) {
		textPtjTotal->setString("Puntos: " + to_string(ptsTotal));
	}
	else {

		Font* f = new Font();
		if (f->loadFromFile("Game_Files/Fonts/CotrellCFExtraBold-Regular.ttf")) {

			textPtjTotal = new Text();	textPtjTotal->setString("Puntos:\n0");	textPtjTotal->setPosition(805, 300);
			textPtjTotal->setFont(*f);

		}
		f = NULL;

	}

}

void Juego::cargarMapaVisual()
{

	for (int y = 0; y < 21; y++) {

		for (int x = 0; x < 19; x++) {

			scenario[y][x] = elegirRutaTextura(letras[y][x], x, y);

		}

	}

}

Boton* Juego::elegirRutaTextura(char letra, int x, int y)
{
	if (letra == 'x' || letra == 'X') {//paredes

		return elegirTextura("Tapar Camino", "Game_Files/Textures/Gameplay/Blue_Panel1.png", x, y, 0.42f, 0.34f, -10, -10);

	}
	else if (letra == '1' || letra == '#' || letra == '$' || letra == '0') {//puntos comestibles
		if (letra == '0' || letra == '$') {

			pacDots++;
			return elegirTextura("Empoderante_Comer", "Game_Files/Textures/Gameplay/yellow_circle.png", x, y, 0.6f, 0.6f, -10, -10);

		}
		else {

			pacDots++;
			return elegirTextura("Comestible", "Game_Files/Textures/Gameplay/yellow_circle.png", x, y, 0.2f, 0.2f, -10, -10);

		}

	}
	else if (letra == 'p') {

		//agregar aqui el nombre del jugador
		//cambiar la velocidad para la defensa
		pacman = new Personaje(vidas, 6, "Mr. Pacman", (800 / 19) * (x), (720 / 21) * (y), "Game_Files/Textures/Personajes/Pacman/PacMan_Ini.png", 0.05f, 0.05f, false);
		//si la velocidad es mayor o igual a 7 entonces no pasa por lo slaberintos......
		return elegirTextura("Nada", "", x, y, 0, 0, -10, -10);

	}
	else if (letra == 'f') {

		string r = "", n = "";
		int v = 0;
		for (int i = 0; i < 4; i++) {
			if (i == 0) {
				n = "Blinky";
				v = 3;
				r = "Game_Files/Textures/Personajes/Fantasmas/Blinky.png";
			}
			else if (i == 1) {
				v = 2;
				n = "Pinky";
				r = "Game_Files/Textures/Personajes/Fantasmas/Pinky.png";
			}
			else if (i == 2) {
				v = 2;
				n = "Inky";
				r = "Game_Files/Textures/Personajes/Fantasmas/Inky.png";
			}
			else if (i == 3) {
				v = 2;
				n = "Clyde";
				r = "Game_Files/Textures/Personajes/Fantasmas/Clyde.png";
			}
			fantasmas[i] = new Personaje(0, v, n, (800 / 19) * x, (720 / 21) * y, r, 0.06, 0.06, true);
		}
		return elegirTextura("Nada", "", x, y, 0, 0, -10, -10);//podria retornar aqui un null para ahorrarme el tener que revisar esa una, dos o tres casillas en las que se encuentran los fantasmas
		//pero por cuestiones de validacions no...
	}
	else {

		return elegirTextura("Nada", "", x, y, 0, 0, -10, -10);

	}

}

Boton* Juego::elegirTextura(string accion, string ruta, int x, int y, float sclX, float sclY, float orX, float orY)
{

	Boton* btn = new Boton(accion, (800 / 19) * (x), (720 / 21) * (y), ruta, sclX, sclY, orX, orY);

	return btn;

}

void Juego::mostrarEscenario()
{

	rw->draw(*background);
	rw->draw(*backBanckground);
	mostrarScenarioAutomatico();

}

void Juego::mostrarUI()
{

	mostrarVecVidas();
	actualizaTextPtjTotal();	mostrarTextPtjTotal();
	actualizarTextTiempo();		mostrarTextTiempo();


}

void Juego::mostrarPersonajes()
{

	mostrarPacman();
	mostrarFantasmas();

}

void Juego::mostrarScenarioAutomatico()
{
	for (int i = 0; i < 19; i++) {

		for (int j = 0; j < 21; j++) {

			if (scenario[j][i]->getSprite() != NULL) {

				rw->draw(*scenario[j][i]->getSprite());

			}

		}

	}
}

void Juego::mostrarTextTiempo()
{
	if (textTiempo != NULL) {

		rw->draw(*textTiempo);

	}
}

void Juego::mostrarVecVidas()
{
	for (int i = 0; i < 6; i++) {
		if (vecVidas[i] != NULL) {
			if (vecVidas[i]->getSprite() != NULL) {
				rw->draw(*vecVidas[i]->getSprite());
			}
		}
	}
}

void Juego::mostrarTextPtjTotal()
{
	if (textPtjTotal != NULL) {

		rw->draw(*textPtjTotal);

	}
}

void Juego::mostrarPoderesDisp()
{

	for (int i = 0; i < 3; i++) {



	}

}


void Juego::mostrarPacman() {

	if (pacman != NULL) {

		rw->draw(*pacman->getSprite());

	}

}

void Juego::mostrarFantasmas()
{

	for (int i = 0; i < 4; i++) {

		if (fantasmas[i] != NULL) {

			if (fantasmas[i]->getSprite() != NULL) {

				rw->draw(*fantasmas[i]->getSprite());

			}

		}

	}

}

int Juego::obtenerVidas()
{
	int num = -1;
	string n = "";
	ifstream f;
	f.open("Game_Files/Data/Total_Vidas.txt");
	if (!f.fail()) {
		getline(f, n);
		stringstream x(n);
		x >> num;
	}
	return num;
}

void Juego::convertirPosPacMat(int px, int py)
{

	for (int f = 0; f < 21; f++) {

		for (int c = 0; c < 19; c++) {

			if (scenario[f][c] != NULL) {

				if ((px < scenario[f][c]->getX() + (scenario[f][c]->getAncho() / 2))
					&& px > scenario[f][c]->getX() - (scenario[f][c]->getAncho() / 2)
					&& py < scenario[f][c]->getY() + (scenario[f][c]->getAlto() / 2)
					&& py > scenario[f][c]->getY() - (scenario[f][c]->getAlto() / 2)) {

					buscarVertice(c, f);

					/*cout << "BLOQUE: " << endl;
					cout << "( " << c << " , " << f << " );" << endl;*/

				}
			}

		}

	}

}

void Juego::buscarVertice(int x, int y)
{

	for (int i = 0; i < mapa->getTamGrafo(); i++) {

		if (mapa->getGrafo(i)->getX() == x && mapa->getGrafo(i)->getY() == y) {

			//cout << "ESTAAA EN UN VERTICE DEL GRAFO" << endl;
			mapa->getGrafo(i)->setHayPacman(true);
		}
		else {
			mapa->getGrafo(i)->setHayPacman(false);
		}

	}

}