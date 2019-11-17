#include "Personaje.h"

Personaje::Personaje(int vidas, int velocidad, string nombre, float x, float y, string ruta, float scaleX, float scaleY, bool comer)
{
	this->pix = 0;
	this->piy = 0;
	this->velocidad = velocidad;
	this->vidas = vidas;
	this->nombre = nombre;
	this->comer = comer;
	this->ruta = ruta;
	this->contador = 0;
	texture = new Texture();
	if (texture->loadFromFile(ruta)) {
		sprite = new Sprite(*texture);
		cout << x << " , " << y << endl;


		sprite->setOrigin(sprite->getPosition().x + texture->getSize().x / 2, sprite->getPosition().y + texture->getSize().y / 2);
		sprite->setPosition(x + ((800 / 19) / 2), y + ((720 / 21) / 2));
		sprite->setScale(scaleX, scaleY);

		piy = sprite->getPosition().y;
		pix = sprite->getPosition().x;

	}
	else {
		sprite = NULL;
		texture = NULL;
	}
	esperarTecla = false;
	accion = new Event();
	accion->key.code = Keyboard::C;/////////////////////vericar;;;;;
	accionAnt = accion;
}

void Personaje::setPix(int pix)
{
	this->pix = pix;
}

void Personaje::setPiy(int piy)
{
	this->piy = piy;
}

void Personaje::setVidas(int vidas)
{
	this->vidas = vidas;
}

void Personaje::setVelocidad(int velocidad)
{
	this->velocidad = velocidad;
}

void Personaje::setNombre(string nombre)
{
	this->nombre = nombre;
}

void Personaje::setTexture(string url)
{
	texture = new Texture();
	texture->loadFromFile(url);
}

void Personaje::setSprite(Texture* texture)
{
	sprite = new Sprite(*texture);
}

void Personaje::setMovH(int movH)
{
	this->movH = movH;
}

void Personaje::setMovV(int movV)
{
	this->movV = movV;
}

void Personaje::setX(float x)
{
	this->x = x;
}

void Personaje::setY(float y)
{
	this->y = y;
}

void Personaje::setEsperaTecla(bool esperarTecla)
{
	this->esperarTecla = esperarTecla;
}

void Personaje::setComer(bool comer)
{
	this->comer = comer;
}

void Personaje::setContador(int contador)
{
	this->contador = contador;
}

int Personaje::getPix()
{
	return pix;
}

int Personaje::getPiy()
{
	return piy;
}

int Personaje::getVidas()
{
	return vidas;
}

int Personaje::getVelocidad()
{
	return velocidad;
}

string Personaje::getNombre()
{
	return nombre;
}

Texture*& Personaje::getTexture()
{
	return texture;
}

Sprite*& Personaje::getSprite()
{
	return sprite;
}

int Personaje::getMovH()
{
	return movH;
}

int Personaje::getMovV()
{
	return movV;
}

float Personaje::getX()
{
	return x;
}

float Personaje::getY()
{
	return y;
}

bool Personaje::getEsperaTecla()
{
	return esperarTecla;
}

bool Personaje::getComer()
{
	return comer;
}

int Personaje::getCotador()
{
	return contador;
}

float Personaje::getTope()
{
	if (sprite != NULL) {
		return sprite->getPosition().y - ((texture->getSize().y * sprite->getScale().y) / 2);
	}
	else {
		return 0;
	}

}

float Personaje::getFondo()
{
	if (sprite != NULL) {
		return sprite->getPosition().y + ((texture->getSize().y * sprite->getScale().y) / 2);
	}
	else {
		return 0;
	}

}

float Personaje::getIzquierda()
{
	if (sprite != NULL) {
		return sprite->getPosition().x - ((texture->getSize().x * sprite->getScale().x) / 2);
	}
	else {
		return 0;
	}

}

float Personaje::getDerecha()
{
	if (sprite != NULL) {
		return sprite->getPosition().x + ((texture->getSize().x * sprite->getScale().x) / 2);
	}
	else {
		return 0;
	}
}

void Personaje::guardarTecla(Event* evento)
{
	this->accion = evento;

}

void Personaje::selecMov(int mx, int my)
{
	movH = mx;
	movV = my;

}

void Personaje::verFutColision(Boton* scenario[21][19], int& ptsTotal, int& pacdots, int& fantasmasMuertos, int& vidas,
	int& vidasPerdidas, Personaje* fantasmas[4])
{
	int disX = (sprite->getTexture()->getSize().x * sprite->getScale().x) / 2, disY = (sprite->getTexture()->getSize().y * sprite->getScale().y) / 2;
	esperarTecla = false;
	if (accion->key.code == Keyboard::Up) {
		//cout << "ARRIBA" << endl;
		revisarPosicion(scenario, 0, -disY, "No hacer nada", ptsTotal, pacdots, fantasmasMuertos, vidas, vidasPerdidas, fantasmas);

		if (esperarTecla == false) {
			selecMov(0, -1);
		}
	}
	else if (accion->key.code == Keyboard::Down) {
		//cout << "ABAJO" << endl;
		revisarPosicion(scenario, 0, disY, "No hacer nada", ptsTotal, pacdots, fantasmasMuertos, vidas, vidasPerdidas, fantasmas);
		if (esperarTecla == false) {
			selecMov(0, 1);
		}
	}
	else if (accion->key.code == Keyboard::Right) {
		//cout << "DERECHA" << endl;
		revisarPosicion(scenario, disX, 0, "No hacer nada", ptsTotal, pacdots, fantasmasMuertos, vidas, vidasPerdidas, fantasmas);

		if (esperarTecla == false) {
			selecMov(1, 0);
		}
	}
	else if (accion->key.code == Keyboard::Left) {
		//cout << "IZQUIERDA" << endl;
		revisarPosicion(scenario, -disX, 0, "No hacer nada", ptsTotal, pacdots, fantasmasMuertos, vidas, vidasPerdidas, fantasmas);
		if (esperarTecla == false) {
			selecMov(-1, 0);//solo valores de 1 y -1 para que no salgan disparados los personajes
		}
	}
	accionAnt = accion;
}

//no pense bien este metodo y resulta que este es un metodo unico(para el uso del pacman)
//tendremos que hacer el de los fantasmas parecido pero con algunas diferencias
void Personaje::revisarPosicion(Boton* scenario[21][19], int x, int y, string accion, int& ptsTotal, int& pacdots,
	int& fantasmasMuertos, int& vidas, int& vidasPerdidas, Personaje* fantasmas[4])//ya Detecta y detiende al colizionar verticalmente(mas bien mas de la cuenta) falta horizontalmente...
{
	//sprite->setPosition(xx + x,yy + y);

	if (texture != NULL && sprite != NULL) {// solo si el personaje tiene textura y sprite

		//esto es para poder ver si se salio del escenario y asi redireccionarlos por donde venia pero desde el lado contrario
		int xx = x, yy = y;

		verColisionConFantasmas(ptsTotal, fantasmasMuertos, vidas, vidasPerdidas, fantasmas);//para verificar si choco contra algun fantasma o no

		if (sprite->getPosition().x - sprite->getGlobalBounds().width / 4 > 800
			&& sprite->getPosition().x + sprite->getGlobalBounds().width / 4 > 800) {

			sprite->setPosition(-5, sprite->getPosition().y);
			this->x = -5;

		}
		else if (sprite->getPosition().x + sprite->getGlobalBounds().width / 4 < 0
			&& sprite->getPosition().x - sprite->getGlobalBounds().width / 4 < 0) {

			sprite->setPosition(805, sprite->getPosition().y);
			this->x = 805;
		}
		else if (sprite->getPosition().y - sprite->getGlobalBounds().height / 4 > 720
			&& sprite->getPosition().y + sprite->getGlobalBounds().height / 4 > 720) {

			sprite->setPosition(sprite->getPosition().x, -5);
			this->y = -5;

		}
		else if (sprite->getPosition().y + sprite->getGlobalBounds().height / 4 < 0
			&& sprite->getPosition().y - sprite->getGlobalBounds().height / 4 < 0) {

			sprite->setPosition(sprite->getPosition().x, 725);
			this->y = 725;

		}

		//cout <<"Pacman X: " << sprite->getPosition().x << "Pacman Y: " << sprite->getPosition().y << endl;
		for (int i = 0; i < 21; i++) {
			for (int j = 0; j < 19; j++) {

				if (scenario[i][j] != NULL) {//solo si hay un objeto en la matriz

					if (scenario[i][j]->getAccion() != "Nada") {

						if (scenario[i][j]->getAccion() == "Comestible" || scenario[i][j]->getAccion() == "Empoderante_Comer" || scenario[i][j]->getAccion() == "Empoderante_Correr" || scenario[i][j]->getAccion() == "Empoderante_Encerrar") {

							if (x >= 0) {
								xx = 1;//esto es nada mas poder sumarle un pixel mas a la ubicacion en la direccion a la que esta yendo
							}
							else if (x < 0) {
								xx = -1;
							}
							if (y >= 0) {
								yy = 1;
							}
							else if (y < 0) {
								yy = -1;
							}

							sprite->setPosition(sprite->getPosition().x + xx, sprite->getPosition().y + yy);

							if (sprite->getGlobalBounds().intersects(scenario[i][j]->getSprite()->getGlobalBounds())) {



								if (scenario[i][j]->getAccion() == "Comestible") {
									pacdots--;
									ptsTotal = ptsTotal + 10;

									scenario[i][j] = new Boton("Nada", (800 / 19) * (j), (720 / 21) * (i), "", 0, 0, -10, -10);
									esperarTecla = false;

								}
								else if (scenario[i][j]->getAccion() == "Empoderante_Comer") {
									comer = true;
									//cambiar el color de los fantasmas 
									scenario[i][j] = new Boton("Nada", (800 / 19) * (j), (720 / 21) * (i), "", 0, 0, -10, -10);
									esperarTecla = false;

									Texture* t = new Texture();
									if (t->loadFromFile("Game_Files/Textures/Personajes/Pacman/PacMan_Comelon - copia.png")) {
										//enojar pacman
										sprite->setTexture(*t);
									}
									//asustar Fantasmas
									Color* c = new Color(20, 20, 255, 255);
									for (int i = 0; i < 4; i++) {
										fantasmas[i]->getSprite()->setColor(*c);
									}
									c = NULL;
									pacdots--;
									ptsTotal = ptsTotal + 10;
								}
								else if (scenario[i][j]->getAccion() == "Empoderante_Correr") {//por ejemplo.....

									comer = true;//cambiar velocidad
									//cambiar el color de los fantasmas 
									scenario[i][j] = new Boton("Nada", (800 / 19) * (j), (720 / 21) * (i), "", 0, 0, -10, -10);
									esperarTecla = false;

								}

							}
							sprite->setPosition(sprite->getPosition().x - xx, sprite->getPosition().y - yy);
						}
						/*else if (scenario[i][j]->getAccion() == "Empoderante") {
							//cout << "JUaz" << endl;
						}*/
						else {
							sprite->setPosition(sprite->getPosition().x + x, sprite->getPosition().y + y);
							if (sprite->getGlobalBounds().intersects(scenario[i][j]->getSprite()->getGlobalBounds())) {

								if (accion == "No hacer nada") {

									esperarTecla = true;

								}
								else if (accion == "Detener") {

									movH = 0;
									movV = 0;
									esperarTecla = true;
									//adaptarPos_Person_Bloc(scenario[i][j]);

								}


							}

							sprite->setPosition(sprite->getPosition().x - x, sprite->getPosition().y - y);


						}
					}

				}
			}
		}
		/*cout << "ESPERAR TECLA: ----->" << esperarTecla << endl;
		cout << "Izquierda: " << getIzquierda() << " a Derecha: " << getDerecha() << endl;
		cout << "De Arriba: " << getTope() << " a Abajo: " << getFondo() << endl;*/
	}
	//cout << "AQUI SALIO:     " << esperarTecla << endl;

	//sprite->setPosition(xx, yy);
}


//metodo defectuoso
/*
void Personaje::adaptarPos_Person_Bloc(Boton* bloque)
{
	int bx = bloque->getSprite()->getPosition().x, by = bloque->getSprite()->getPosition().y;
	int px = sprite->getPosition().x, py = sprite->getPosition().y;

	cout << "Bx: "<< bx + bloque->getSprite()->getGlobalBounds().width <<"  By: " << by + bloque->getSprite()->getGlobalBounds().height << endl;

	cout << "Px: " << px << "  Py: " << py << endl;

	cout << "PPPX: " << px - sprite->getGlobalBounds().width / 2 << "PPPY: " << py - sprite->getGlobalBounds().height / 2 << endl;
	if (py > by && movV < 0) {

		sprite->setPosition(px, (by + bloque->getSprite()->getGlobalBounds().height + (sprite->getGlobalBounds().height / 2)));
		//y = sprite->getPosition().y;

	}else if (py < by && movV > 0) {

		sprite->setPosition(px, (by - (sprite->getGlobalBounds().height / 2)));
		//y = sprite->getPosition().y;

	}
	else if (px > bx && movH < 0) {

		sprite->setPosition((bx + bloque->getSprite()->getGlobalBounds().width + (sprite->getGlobalBounds().width / 2)), py);
		//x = sprite->getPosition().x;

	}
	else if (px < bx && movH > 0) {

		sprite->setPosition((bx - (sprite->getGlobalBounds().width / 2)), py);
		//x = sprite->getPosition().x;

	}
}
*/
// de pacman a fantasmas, falta hacer un metodos de fantasmas a pacman.....

void Personaje::verColisionConFantasmas(int& ptsTotal, int& fantasmasMuertos, int& vidas, int& vidasPerdidas, Personaje* fantasmas[4])
{
	if (comer == false) {
		contador = 0;
	}
	for (int i = 0; i < 4; i++) {

		if (fantasmas[i] != NULL) {

			if (fantasmas[i]->getSprite() != NULL) {

				if (sprite->getGlobalBounds().intersects(fantasmas[i]->getSprite()->getGlobalBounds())) {

					if (comer == true) {
						fantasmasMuertos++;
						/*///////////////////////////////////////PONER ESTO CUANDO SE QUIERA AUMENTAR LOS PUNTOS POR COMER FANTASMAS
						ptsTotal = ptsTotal + (300 + (100 * contador));

						contador++;
						*////////////////////////////////////////PONER ESTO CUANDO SE QUIERA AUMENTAR LOS PUNTOS POR COMER FANTASMAS
						//aqui se llamaria a la animacion de regreso a casa por medio del algoritmo de dijkstra........

						fantasmas[i]->getSprite()->setPosition(fantasmas[i]->getPix(), fantasmas[i]->getPiy());

					}
					else {
						vidas--;
						vidasPerdidas++;
						cout << "Pum" << vidas << endl;
						this->movV = 0;
						this->movH = 0;
						sprite->setPosition(pix, piy);

						this->x = pix;
						this->y = piy;

						//solucionar aqui que no deja de moverse el pacman...............................................

					}

				}

			}

		}

	}

}



void Personaje::moverPersonaje(Boton* scenario[21][19], int& ptsTotal, int& pacdots, int& fantasmasMuertos, int& vidas, int& vidasPerdias, Personaje* fantasmas[4])
{
	x = x + (velocidad * movH);//asignar nueva ubicacion
	y = y + (velocidad * movV);//asignar nueva ubicacion

	if (movH < 0) {//desidir rotacion del personaje
		sprite->setRotation(180);
	}
	else if (movH > 0) {//desidir rotacion del personaje
		sprite->setRotation(0);
	}
	else if (movV < 0) {//desidir rotacion del personaje
		sprite->setRotation(270);//se vuelve al revez
	}
	else if (movV > 0) {//desidir rotacion del personaje
		sprite->setRotation(90);
	}

	//cout << "MovH = " << movH << " - MovV = " << movV << endl;
	sprite->setPosition(sprite->getPosition().x + (velocidad * movH), sprite->getPosition().y + (velocidad * movV));

	revisarPosicion(scenario, (velocidad * movH), (velocidad * movV), "Detener", ptsTotal, pacdots, fantasmasMuertos, vidas, vidasPerdias, fantasmas);

}