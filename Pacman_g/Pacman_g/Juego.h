#pragma once
#include "Boton.h"
#include "Mapa.h"
#include "Personaje.h"
#include "Pantalla_GameOver.h"
#include<iostream>
#include<SFML/Graphics.hpp>
#include <queue>

using namespace sf;
using namespace std;
class Juego
{//
private:
	bool juegoIniciado;


	string nombre;
	int rx, ry, fps;
	RenderWindow* rw;
	//referente al scenario
	Mapa* mapa;
	Pantalla_GameOver* pantalla_gameOver;
	char letras[21][19];
	Boton* scenario[21][19];
	Sprite* background;
	Boton* datos[6];
	Sprite* backBanckground;


	//referente a los personajes
	
	Personaje* pacman;
	Personaje* fantasmas[4];
	//referente a los personajes

	//Respecto a Dijkstra
	Nodo* camino1, *camino2, * lista1, *lista2;
	//Respecto a Dijkstra

	//Respecto a Floyd
	int** matAd;///matriz de adyacencia
	int** matFloyd; //metriz 1 del floyd
	int** matRutas; //matriz de rutas del  floyd
	//Respecto a Floyd

	//referente al UI
	Boton* poderesDisp[3];
	Boton* vecVidas[6];//el jugador podra tener un maximo de tres vidas...
	Text* textPtjTotal;
	Text* textTiempo;

	//referente al UI

	//referentes a los diferentes tipos de puntos;
	int nivel;
	int vidas;
	int vidasPerdidas;
	int fantasmasMuertos;
	int ptsTotal;
	int tiempo;

	int pacDots;
	//////////////////

	int tiempo_de_poder;//tiempo_de_comer es como un timepo de poder

public:

	Juego(Mapa* mapa, int lvl, string tema);
	//sets y gets
	void setJuegoIniciado(bool juegoIniciado);
	void setNivel(int nivel);
	void setNombre(string nombre);
	void setRX(int rx);
	void setRY(int ry);
	void setRW(int rx, int ry);
	void setFps(int fps);


	bool getJuegoIniciado();
	int getNivel();
	string getNombre();
	int getRX();
	int getRY();
	RenderWindow* getRW();
	int getFps();

	int getPtsTotal();
	int getPacdots();


	//sets y gets

	//loop
	void gameLoop();
	void drawer();
	//loop



	//durante el gameplay
	void evaluarVidas();
	void verificarTiempo_de_comida();
	void verificarPts(int mitadPacDots);
	void terminarJuego();
	bool gameOver();
	void gamePassed();
	void actualizarTextTiempo();
	void actualizaTextPtjTotal();
	//durante el gameplay


	//referente al mapa(texturas,etc)
	void cargarMapaVisual();
	Boton* elegirRutaTextura(char letra, int x, int y);
	Boton* elegirTextura(string accion, string ruta, int x, int y, float sclX, float sclY, float orX, float orY);
	//referente al mapa(texturas,etc)

	//mostradores de objetos visuales
		//Raices:
	void mostrarEscenario();
	void mostrarUI();
	void mostrarPersonajes();
	//escenario
	void mostrarScenarioAutomatico();
	//escenario
	//UI
	void mostrarTextTiempo();
	void mostrarVecVidas();
	void mostrarTextPtjTotal();
	void mostrarPoderesDisp();
	//UI
	//Personaes
	void mostrarPacman();
	void mostrarFantasmas();
	void resetearMovimientos();
	//Personaes
//Raices:

//mostradores de objetos visuales

//Referente a la carga de datos
	int obtenerVidas();
	//Referente a la carga de datos


	//buscar ubicacion de pacman con respecto a la matriz y buscar el vertice en el cual puede ser que este pacman
	void convertirPosPacMat(int px, int py);//a final de cuentas tambien se encontrar donde estan los fantasmas
	
	void buscarVertice(int x, int y);

	void falsearEstanciaPacman();
	Nodo* dijkstra(Nodo*& lista, int x, int y);
	//Nodo* dijkstra(Nodo*& lista, int px, int py, int fx, int fy);//lo mismo pero mas varato XD...mejor despues

	void cambiarRutaBlinky();//para dijkstra
	void cambiarRutaPinky();
	void cambiarRutaClyde();

	//buscar ubicacion de pacman con respecto a la matriz y buscar el vertice en el cual puede ser que este pacman

	//metodo para crear las matriz floyd 
	void crearFloyd();
	//metodo para  obtener la ruta entre 2 puntos Floyd
	Nodo* Floyd(Nodo* inicio,Nodo* final);
	//recuperar ruta 1Floyd
	void RecRutaFloyd(int i, int j, queue<Nodo>* lista);
	

};
