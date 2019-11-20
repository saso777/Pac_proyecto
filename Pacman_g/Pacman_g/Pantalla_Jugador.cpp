#include "Pantalla_Jugador.h"
#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
Pantalla_Jugador::Pantalla_Jugador()
{//
	rw = new RenderWindow(VideoMode(800, 600), "Datos de Jugador");
	rw->setFramerateLimit(20);
	verTrofeos();
	obtener_datos_de_jugador();

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
	mostrar_datos();

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
void Pantalla_Jugador::mostrar_datos()
{
	Text text1;
	Text text2;
	Text text3;
	Text text4;
	Text text5;
	//vector para imprimir
	Vector2f vector (20,400);
	Font font;

	font.loadFromFile("Game_Files/Fonts/CotrellCFExtraBold-Regular.ttf");
		
	
	text1.setString("Nombre del jugador: "+jugador);
	text2.setString("Numero del total de vidas restantes: "+total_vidas);
	text3.setString("Fantamas totales comidos: " + fatasmas_comidos);
	text4.setString("tiempo total jugado en segundos: "+datos_tiempo_jugado);
	text5.setString("Historial: \n"+data_cap);
	//datos
	text1.setFillColor(Color::White);
	text1.setCharacterSize(18);
	text1.setFont(font);
	//
	text2.setFillColor(Color::White);
	text2.setCharacterSize(18);
	text2.setFont(font);
	//
	text3.setFillColor(Color::White);
	text3.setCharacterSize(18);
	text3.setFont(font);
	//
	text4.setFillColor(Color::White);
	text4.setCharacterSize(18);
	text4.setFont(font);
	//
	text5.setFillColor(Color::White);
	text5.setCharacterSize(18);
	text5.setFont(font);
	text1.setPosition(vector);
	
	rw->draw(text1);
	vector.y = vector.y + 30;
	text2.setPosition(vector);
	vector.y = vector.y + 30;
	rw->draw(text2);
	text3.setPosition(vector);
	vector.y = vector.y + 30;
	rw->draw(text3);
	text4.setPosition(vector);
	rw->draw(text4);
	
	vector.x = (420);
	vector.y = 380;
	text5.setPosition(vector);
	rw->draw(text5);

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
	f.close(); //si no sirve este metodo mas, borran esto, es que en teoria si se abre el archivo al finalizar se debe de cerrar

}

void Pantalla_Jugador::obtener_datos_de_jugador()
{
	
	ifstream f1("Game_Files/Data/Segundos_Juego.txt");
	 
	
		
		getline(f1, datos_tiempo_jugado);
		f1.close();

	ifstream f2("Game_Files/Data/Fantasmas_Comidos.txt");
	 
	
		getline(f2, fatasmas_comidos);
		f2.close();

	ifstream f3("Game_Files/Data/Total_Vidas.txt");
	 
	
		getline(f3, total_vidas);
		f3.close();
		ifstream f4("Game_Files/Data/Jugador.txt");
	
		getline(f4, jugador);
		f4.close();
		ifstream f5("Game_Files/Data/Score/ptj_Total.txt");

		string temp;
		while (getline(f5, data_cap)) {
			temp = temp + data_cap+"\n";
		}
		
		f4.close();
		data_cap = temp;
	

	
}


