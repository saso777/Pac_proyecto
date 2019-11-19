#include "Pantalla_GameOver.h"

Pantalla_GameOver::Pantalla_GameOver(bool final, int nivel, int& vidas, int vidasPerdidas, int fantasmasMuertos, int& ptsTotal, int tiempo)
{

	actualizarVecVidas();
	textPtjTotal = NULL;

	continuarPartida = !final;
	mensaje = NULL;
	backGround = NULL;
	for (int i = 0; i < 7; i++) {
		botones[i] = NULL;
	}


	this->finalBueno = final;
	rw = new RenderWindow(VideoMode(800, 600), "Fin de la Partida");
	rw->setFramerateLimit(15);
	this->nivel = nivel;
	this->vidas = vidas;
	this->vidasPerdidas = vidasPerdidas;
	this->fantasmasMuertos = fantasmasMuertos;
	this->ptsTotal = ptsTotal;
	this->tiempo = tiempo;

	if (finalBueno == true) {
		vistaBuena();//para el sistema de vistas es mejor tener listas para tener una cantidad ilimitada y controlable de botones textos y diferentes cosas
	}
	else {
		vistaMala();
	}



	overLoop();

}

void Pantalla_GameOver::setNivel(int nivel)
{
	this->nivel = nivel;
}

void Pantalla_GameOver::setVidas(int vidas)
{
	this->vidas = vidas;
}

void Pantalla_GameOver::setVidasPerdidas(int vidasPerdidas)
{
	this->vidasPerdidas = vidasPerdidas;
}

void Pantalla_GameOver::setFatnasmasMuertos(int fantasmasMuertos)
{
	this->fantasmasMuertos = fantasmasMuertos;
}

void Pantalla_GameOver::setPtsTotal(int ptsTotal)
{
	this->ptsTotal = ptsTotal;
}

void Pantalla_GameOver::setTiempo(int tiempo)
{
	this->tiempo = tiempo;
}

void Pantalla_GameOver::setFinalBueno(bool finalBueno)
{
	this->finalBueno = finalBueno;
}

void Pantalla_GameOver::setContinuarPartida(bool continuarPartida)
{
	this->continuarPartida = continuarPartida;
}

int Pantalla_GameOver::getNivel()
{
	return nivel;
}

int Pantalla_GameOver::getVidas()
{
	return vidas;
}

int Pantalla_GameOver::getVidasPerdidas()
{
	return vidasPerdidas;
}

int Pantalla_GameOver::getFatnasmasMuertos()
{
	return fantasmasMuertos;
}

int Pantalla_GameOver::getPtsTotal()
{
	return ptsTotal;
}

int Pantalla_GameOver::getTiempo()
{
	return tiempo;
}

bool Pantalla_GameOver::isFinalBueno()
{
	return finalBueno;
}

bool Pantalla_GameOver::getContinuarPartida()
{
	return continuarPartida;
}

void Pantalla_GameOver::overLoop()
{

	Event* evento = new Event();
	while (rw->isOpen()) {

		showEnd();
		actualizarVecVidas();
		while (rw->pollEvent(*evento)) {

			if (evento->type == Event::Closed || evento->key.code == Keyboard::Escape) {

				guardarInformacionPartida();
				continuarPartida = false;
				rw->close();

			}
			else if (evento->type == Event::MouseButtonReleased) {
				selecOption(Mouse::getPosition(*rw).x, Mouse::getPosition(*rw).y);
				cout << "Mouse X: " << Mouse::getPosition(*rw).x << "--> Mouse Y: " << Mouse::getPosition(*rw).y << endl;
			}

		}

	}

}



void Pantalla_GameOver::showEnd()
{
	rw->clear();

	mostrarVista();
	mostrarVecVidas();
	mostrarTextPtsTotal();


	rw->display();
}

void Pantalla_GameOver::mostrarVecVidas()
{
	for (int i = 0; i < 6; i++) {

		if (vecVidas[i] != NULL) {

			rw->draw(*vecVidas[i]);

		}

	}
}

void Pantalla_GameOver::mostrarTextPtsTotal()
{
	if (textPtjTotal != NULL) {

		rw->draw(*textPtjTotal);

	}
}

void Pantalla_GameOver::actualizarVecVidas()
{

	for (int i = 0; i < 6; i++) {

		if (vecVidas[i] != NULL) {

			if (i >= vidas) {

				if (vecVidas[i]->getColor() != Color(150, 150, 150, 200)) {

					vecVidas[i]->setColor(Color(150, 150, 150, 200));

				}

			}
			else {

				if (vecVidas[i]->getColor() != Color(255, 255, 255, 255)) {

					vecVidas[i]->setColor(Color(255, 255, 255, 255));

				}

			}

		}
		else {

			Texture* t = new Texture();
			if (t->loadFromFile("Game_Files/Textures/Personajes/Pacman/PacMan_Ini.png")) {

				for (int i = 0; i < 6; i++) {

					vecVidas[i] = new Sprite(*t);
					vecVidas[i]->setScale(0.1666666666666667, 0.1666666666666667);
					vecVidas[i]->setOrigin(vecVidas[i]->getPosition().x + vecVidas[i]->getGlobalBounds().width / 2, vecVidas[i]->getPosition().y + vecVidas[i]->getGlobalBounds().height / 2);
					vecVidas[i]->setPosition(100 + (100 * i), 300 - vecVidas[i]->getGlobalBounds().height / 2);
					//le resto la mitad de su altura por que extrañamente el origen no se me coloca en el centro a la 
					//hora de setear el origen...

					if (i >= vidas) {

						vecVidas[i]->setColor(Color(150, 150, 150, 200));

					}

				}

			}

		}

	}

}

void Pantalla_GameOver::actualizarTextPtsTotal()
{
	Font* f = new Font();
	if (f->loadFromFile("Game_Files/Fonts/CotrellCFExtraBold-Regular.ttf"))
	{

		textPtjTotal = new Text();
		textPtjTotal->setFont(*f);
		textPtjTotal->setString("Puntaje Alcanzado:  " + to_string(ptsTotal));
		textPtjTotal->setOrigin(textPtjTotal->getPosition().x + textPtjTotal->getGlobalBounds().width / 2, textPtjTotal->getOrigin().y + textPtjTotal->getGlobalBounds().height / 2);
		textPtjTotal->setPosition(400, 200);


	}
	else {
		textPtjTotal = NULL;
	}
	f = NULL;
}

void Pantalla_GameOver::selecOption(int x, int y)
{
	for (int i = 0; i < 7; i++) {
		if (botones[i] != NULL) {

			if (botones[i]->getSprite() != NULL) {

				if (evaluarPosicionMouseBoton(x, y, botones[i]) == true) {

					if (botones[i]->getAccion() == "Finalizar Partida") {

						continuarPartida = false;
						guardarInformacionPartida();
						rw->close();

					}
					else if (botones[i]->getAccion() == "Comprar Vida") {

						ifstream f;
						f.open("Game_Files/Data/Score/ptj_Total.txt");

						if (!f.fail()) {

							string p = ""; int n = 0;
							getline(f, p); getline(f, p); getline(f, p); getline(f, p);
							stringstream x(p);
							x >> n;
							n = n + ptsTotal;
							f.close();
							if (vidas < 6) {

								if (n >= 3000) {

									vidas++;//estas vidas no se pasan a las vidas en la vara de juego
									ofstream ff;
									ff.open("Game_Files/Data/Total_Vidas.txt");
									if (!ff.fail()) {

										ff << vidas;
										ff.close();

									}

									n = n - 3000;
									cout << "Vidas:        " << endl;
									setLine(to_string(n), "Game_Files/Data/Score/ptj_Total.txt", 4);

								}
								else {

									cout << "FALTAN PUNTOS PARA COMPRAR LA VIDA...POBRE!! XD" << endl;

								}

							}

						}

					}
					else if (botones[i]->getAccion() == "Continuar Partida") {

						if (vidas > 0) {

							continuarPartida = true;
							rw->close();
							
						}
						else {

							cout << "NECESITA AL MENOS UNA VIDA PARA CONTINUAR CON ESTA PARTIDA....." << endl;

						}

					}


				}
			}
		}
	}
}

bool Pantalla_GameOver::evaluarPosicionMouseBoton(int x, int y, Boton* boton)
{
	cout << "ENTRA" << endl;
	if (x <= (boton->getSprite()->getPosition().x + boton->getSprite()->getGlobalBounds().width / 2)
		&& x >= (boton->getSprite()->getPosition().x - boton->getSprite()->getGlobalBounds().width / 2)) {



		//resto 50 a la posicion del boton en Y debido a un inconveniente con el posicionamiento del mismo
		if (y <= ((boton->getSprite()->getPosition().y) + boton->getSprite()->getGlobalBounds().height / 2)
			&& y >= ((boton->getSprite()->getPosition().y) - boton->getSprite()->getGlobalBounds().height / 2)) {

			return true;

		}
		else {

			return false;

		}

	}
	else {

		return false;

	}
}


void Pantalla_GameOver::mostrarVista()
{
	if (backGround != NULL) {
		rw->draw(*backGround);
	}

	if (mensaje != NULL) {
		rw->draw(*mensaje);
	}

	for (int i = 0; i < 7; i++) {
		if (botones[i] != NULL) {

			if (botones[i]->getSprite() != NULL) {

				rw->draw(*botones[i]->getSprite());

			}
			if (botones[i]->getText() != NULL) {

				rw->draw(*botones[i]->getText());

			}
		}
	}
}

void Pantalla_GameOver::vistaBuena()
{

	for (int i = 0; i < 6; i++) {

		vecVidas[i]->setPosition(vecVidas[i]->getPosition().x, 100);

	}

	Texture* t1 = new Texture(), * t2 = new Texture();
	if (t1->loadFromFile("")) {
		backGround = new Sprite(*t1);
		backGround->setOrigin(backGround->getPosition().x + backGround->getGlobalBounds().width / 2, backGround->getPosition().y + backGround->getGlobalBounds().height / 2);
		backGround->setPosition(400, 25);
	}
	if (t2->loadFromFile("")) {
		mensaje = new Sprite(*t2);
		mensaje->setOrigin(mensaje->getPosition().x + mensaje->getGlobalBounds().width / 2, mensaje->getPosition().y + mensaje->getGlobalBounds().height / 2);
		mensaje->setPosition(400, 75);
	}

	string r = "Game_Files/Textures/UI/Scenary/Rotulo1.png";



	botones[0] = new Boton("Ninguna", "Fantasmas Muertos: " + to_string(fantasmasMuertos), 400, 230, r, 400, 225, 1, 1);
	botones[1] = new Boton("Ninguna", "Puntos Obtenidos: " + to_string(ptsTotal), 400, 280, r, 400, 275, 1, 1);
	botones[2] = new Boton("Ninguna", "Tiempo de Partida: " + to_string(tiempo) + " segundos.", 400, 330, r, 400, 325, 1, 1);
	if (vidasPerdidas != 0) {
		botones[3] = new Boton("Ninguna", "Muerte en Partida: Si", 400, 380, r, 400, 375, 1, 1);
	}
	else {
		botones[3] = new Boton("Ninguna", "Muerte en Partida: No", 400, 380, r, 400, 375, 1, 1);
	}
	r = "Game_Files/Textures/UI/Buttons/grey_button00.png";
	botones[4] = new Boton("Finalizar Partida", "Volver al Menu Principal ", 400, 530, r, 400, 525, 1, 1);
	botones[5] = NULL;
	botones[6] = NULL;

	Color* c = new Color(255, 255, 255, 100);

	for (int i = 0; i < 5; i++) {

		if (botones[i]->getSprite() != NULL) {
			botones[i]->getSprite()->setColor(*c);
			botones[i]->ajustarBtnTexto();
		}

	}

}

void Pantalla_GameOver::vistaMala()
{
	Texture* t = new Texture();
	if (t->loadFromFile("Game_Files/Textures/UI/GameOver/Bad/Game_Over.png")) {

		mensaje = new Sprite(*t);
		mensaje->setScale(1, 0.70671377809187279);
		mensaje->setOrigin(mensaje->getPosition().x + (mensaje->getGlobalBounds().width / 2), mensaje->getPosition().y + (mensaje->getGlobalBounds().height / 2));
		mensaje->setPosition(400, 0);

	}
	else {
		mensaje = NULL;
	}

	actualizarTextPtsTotal();

	string r = "Game_Files/Textures/UI/Buttons/grey_button00.png";
	botones[0] = new Boton("Finalizar Partida", "Abandonar Partida", 400, 450, r, 400, 445, 1, 1);
	botones[0]->ajustarBtnTexto();	botones[0]->getSprite()->setColor(Color(200, 200, 200, 255));

	botones[1] = new Boton("Comprar Vida", "Comprar una Vida por: 3000 pts", 400, 500, r, 400, 495, 1, 1);
	botones[1]->ajustarBtnTexto();	botones[1]->getSprite()->setColor(Color(200, 200, 200, 255));

	botones[2] = new Boton("Continuar Partida", "Continuar con la Partida", 400, 550, r, 400, 545, 1, 1);
	botones[2]->ajustarBtnTexto();	botones[2]->getSprite()->setColor(Color(200, 200, 200, 255));

	for (int i = 3; i < 7; i++) {
		botones[i] = NULL;
	}


	//hacer lo mismo que en vista buena y validar que si la parsona compro una vida entonces que que continuar partidad se haga verdadero

	///tambien se puede hacer un boton comprar vida, otro finalizar partida y otro continuar partida....

	//cuando el jugador se quede sin vidas y este en el menu principal se debera pasar a esta pantalla pero cambiando textos y 
	//sugiriendo que compre vidas...

}

void Pantalla_GameOver::guardarInformacionPartida()
{
	cout << "((((((((((((((((((((((((((((((((((((((((GUARDANDO VIDAS)))))))))))))))))))))))))))))))))))))))" << endl;
	guardarVidas("Game_Files/Data/Total_Vidas.txt");
	cout << "'" << endl;

	cout << "((((((((((((((((((((((((((((((((((((((((GUARDANDO VIDAS PERDIDAS)))))))))))))))))))))))))))))))))))))))" << endl;
	guardarVidasPerdidas("Game_Files/Data/Vidas_Perdidas.txt");
	cout << "'" << endl;

	cout << "((((((((((((((((((((((((((((((((((((((((GUARDANDO FANTASMAS COMIDOS)))))))))))))))))))))))))))))))))))))))" << endl;
	guardarFantasmasMuertos("Game_Files/Data/Fantasmas_Comidos.txt");
	cout << "'" << endl;

	cout << "((((((((((((((((((((((((((((((((((((((((GUARDANDO PUNTOS POR NIVEL)))))))))))))))))))))))))))))))))))))))" << endl;
	guardarPtsEnNivel("Game_Files/Data/Score/pts_" + to_string(nivel) + ".txt");
	cout << "'" << endl;

	cout << "((((((((((((((((((((((((((((((((((((((((GUARDANDO CANTIDAD DE VECES JUGAD)))))))))))))))))))))))))))))))))))))))" << endl;
	guardarCantidadVecesJugado("Game_Files/Data/Score/pts_" + to_string(nivel) + ".txt");
	cout << "'" << endl;

	cout << "((((((((((((((((((((((((((((((((((((((((GUARDANDO PUNTAJE TOTAL)))))))))))))))))))))))))))))))))))))))" << endl;
	guardarPtsTotal("Game_Files/Data/Score/ptj_Total.txt");//revisa las mayor cantidad de puntos alcanzados en los niveles ya que el jugador como minimo puede tener esa cantidad de puntos
	cout << "'" << endl;

	cout << "((((((((((((((((((((((((((((((((((((((((GUARDANDO PUNTOS SIN GASTAR)))))))))))))))))))))))))))))))))))))))" << endl;
	guardarPtsEnPosecion("Game_Files/Data/Score/ptj_Total.txt");
	cout << "'" << endl;

	cout << "((((((((((((((((((((((((((((((((((((((((GUARDANDO TIEMPO GLOBAL DE JUEGO)))))))))))))))))))))))))))))))))))))))" << endl;
	guardarTiempo("Game_Files/Data/Segundos_Juego.txt");
	cout << "'" << endl;


	if (vidas > 0) {

		cout << "((((((((((((((((((((((((((((((((((((((((GUARDANDO MEJOR TIEMPO DE JUEGO)))))))))))))))))))))))))))))))))))))))" << endl;
		guardarMejorTiempoPorNivel("Game_Files/Data/Score/pts_" + to_string(nivel) + ".txt");

		cout << "'" << endl;
	}



	cout << "((((((((((((((((((((((((((((((((((((((((GUARDANDO PUNTOS SEGUN INMUNIDAD)))))))))))))))))))))))))))))))))))))))" << endl;
	guardarPtsPorInmunidad("Game_Files/Data/Score/ptj_Total.txt");
	cout << "'" << endl;



	cout << "NIVELLLLLL:::::::::::" << to_string(nivel) << endl;

	/////////7777777
}

void Pantalla_GameOver::guardarVidas(string ruta)
{
	ofstream f;//para escribir
	ifstream ff;//para leer
	string pal = "";
	int num = 0;
	//aguardamos las vidas
	f.open(ruta);
	f.seekp(0);
	cout << "vidas" << vidas << endl;
	if (!f.fail()) {

		f << to_string(vidas);

	}

	f.close();
	//guardamos las vidas

}

void Pantalla_GameOver::guardarVidasPerdidas(string ruta)
{
	ifstream in; ofstream out;
	string pal = "";
	int num = 0;
	in.open(ruta);
	if (!in.fail()) {

		getline(in, pal);

		stringstream x(pal);

		x >> num;

		num = num + vidasPerdidas;

		in.close();


		cout << "VIDASPERDIDASin: " << num << endl;
		cout << "VIDASPERDIDASout: " << vidasPerdidas << endl;
		out.open(ruta);
		if (!out.fail()) {

			out << num;
			out.close();
		}

	}
}

void Pantalla_GameOver::guardarFantasmasMuertos(string ruta)
{
	ifstream ff;
	ofstream f;
	string pal = "";
	int num = 0;
	//sumamos y guardamos los fantasmas muertos
	ff.open("Game_Files/Data/Fantasmas_Comidos.txt");
	if (!ff.fail()) {
		getline(ff, pal);
		stringstream x(pal);

		x >> num;

		num = fantasmasMuertos + num;
	}

	ff.close();
	f.open("Game_Files/Data/Fantasmas_Comidos.txt");
	if (!f.fail()) {
		f << num;
	}
	f.close();
	//sumamos y guardamos los fantasmas muertos

}

void Pantalla_GameOver::guardarPtsTotal(string ruta)//cambiar esto y hacerlo mas exacto
{
	//guardar Puntaje Total Ganado
	//ahora guardamos reccorremos los puntos del todos los txts y los sumamos, finalmente se guardan, esto para evitar que se haga trampa...(no es tan efectivo pero despues de un partida con trampas, el puntaje se correjira)
	//idea anterior abortada, se decidio solamente sumar lo ganado en la partida mas lo ya anteriormente hecho************
	ifstream ff;

	/*string pal = "";
	int num = 0, multiplicador = 0;//puntaje de todos los txt(niveles) ya anteriormente jugados
	string url = "";
	int n = 0;//punteje del txt abierto actualmente(este se le sumara a num)

	for (int i = 0; i < 10; i++) {
		url = "Game_Files/Data/Score/pts_" + to_string(i + 1) + ".txt";

		ff.open(url);

		if (!ff.fail()) {

			getline(ff, pal);
			getline(ff, pal);
			stringstream x(pal);
			x >> n;


			getline(ff, pal);
			getline(ff, pal);


			stringstream xx(pal);
			xx >> multiplicador;

			cout<< "Multiplicador: " << multiplicador << endl;
			if (multiplicador != 0) {

				n = n * multiplicador;
				cout << "YA MULTIPLICADO: " << n << endl;
			}
			else {
				n = n * 1;
			}

			num = num + n;

			ff.seekg(0);
		}
		ff.close();
	}
	//num = num + ptsTotal;

	ff.close();
	*/
	//nueva agregacio para el puntaje total**********(no evita que el jugador haga trampa....)
	ff.open("Game_Files/Data/Score/ptj_Total.txt");

	int num = 0;
	string line = "";

	if (!ff.fail()) {
		getline(ff, line);
		getline(ff, line);

		stringstream x(line);
		x >> num;
		ff.close();
	}

	num = num + ptsTotal;

	cout << "PUntaje Total  ========== " << num << endl;

	setLine(to_string(num), ruta, 2);


	//guardar Puntaje Total Ganado

}

void Pantalla_GameOver::guardarPtsEnPosecion(string ruta)
{
	ifstream in;

	string pal = "";
	int num = 0;

	in.open(ruta);

	if (!in.fail()) {
		getline(in, pal);
		getline(in, pal);
		getline(in, pal);
		getline(in, pal);
		in.seekg(0);

		stringstream x(pal);

		x >> num;

		num = num + ptsTotal;

		setLine(to_string(num), ruta, 4);

		in.close();

	}
	else {
		in.close();//duda..........................................
	}


}

void Pantalla_GameOver::guardarPtsPorInmunidad(string ruta)
{
	ifstream in;

	string pal = "";
	int num = 0;
	int posicion = 0;

	in.open(ruta);

	if (!in.fail()) {

		if (vidasPerdidas != 0) {
			posicion = 6;
		}
		else {
			posicion = 8;
		}
		for (int i = 0; i < posicion; i++) {
			getline(in, pal);
		}
		//stringstream funciona de maera que si no encuentra ningun numeroen el texto su valor por defecto es 0
		//stoi daria un error si este numero se suma.....
		stringstream x(pal);
		x >> num;
		num = num + ptsTotal;
		in.seekg(0);
		in.close();
		setLine(to_string(num), ruta, posicion);

	}

}

void Pantalla_GameOver::guardarPtsEnNivel(string ruta)
{

	ifstream in;
	string pal = "";


	in.open(ruta);

	if (!in.fail()) {

		getline(in, pal);
		getline(in, pal);

		if (stoi(pal) < ptsTotal) {
			//int num = 0;
			in.close();

			setLine(to_string(ptsTotal), ruta, 2);

		}

	}
	in.close();
}

void Pantalla_GameOver::guardarTiempo(string ruta)
{
	ifstream in; ofstream out;
	string pal = "";
	int num = 0;

	in.open(ruta);


	if (!in.fail()) {

		getline(in, pal);
		num = tiempo + stoi(pal);

		in.close();
		out.open(ruta);

		if (!out.fail()) {

			out << num;

			out.close();

		}

	}


}

void Pantalla_GameOver::guardarMejorTiempoPorNivel(string ruta)
{

	ifstream in;
	string pal = "";
	int num = 0;

	in.open(ruta);

	if (!in.fail()) {

		for (int i = 0; i < 6; i++) {

			getline(in, pal);

		}

		in.close();

		stringstream x(pal);
		x >> num;
		cout << "num: " << num << endl;
		if (tiempo < num) {
			//cout << "Tiempoooooooooooooooo::::::::::::" << endl;
			setLine(to_string(tiempo), ruta, 6);

		}

	}




}

void Pantalla_GameOver::guardarCantidadVecesJugado(string ruta)
{

	ifstream in;
	string p = "";
	int num = 0;
	in.open(ruta);

	if (!in.fail()) {


		getline(in, p);
		getline(in, p);
		getline(in, p);
		getline(in, p);

		stringstream x(p);

		x >> num;

		num++;//si se hace: num = stoi(p) + 1; --> esto no sirve...

		in.close();

		setLine(to_string(num), ruta, 4);


	}



}




void Pantalla_GameOver::setLine(string line, string ruta, int posicion)
{
	ifstream ff;
	ofstream f;

	//f.open(ruta);
	ff.open(ruta);

	if (!ff.fail()) {

		string* vec;//vector dinamico con las lineas del txt(use esto ya que no se como editar explicitamente una linea del txt
		int cont = 0, tpts = 0;//para el tamaño del vector y otro para el total de puntos
		string p;

		cout << "LINEA INGRESADA::::::::::::::::::::::::: " << line << endl;
		while (!ff.eof()) {

			getline(ff, p);
			cont++;
			cout << "LINEA " << cont << ": " << p << endl;
		}

		ff.seekg(0);

		vec = new string[cont];
		for (int i = 0; i < cont; i++) {

			getline(ff, vec[i]);
			cout << "VECTOR [" << i << "] =-->  ";
			cout << vec[i] << endl;;

		}

		//para casting de string a int, entre otras: se usa: stoi(string x);

		vec[posicion - 1] = line;//se suplanta el valor anterior por el valor dado
		//se guardardan los datos

		ff.close();
		f.open(ruta);

		if (!f.fail()) {

			for (int i = 0; i < cont; i++) {

				f << vec[i];
				cout << "METIDA  " << i << endl;

				if (i < cont - 1) {
					f << endl;
				}
			}

		}
		f.close();

	}
}
