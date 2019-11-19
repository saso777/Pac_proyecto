#pragma once
#include "Boton.h"
#include "fstream"
#include "sstream"
#include "SFML/Graphics.hpp"
using namespace sf;
class Pantalla_GameOver
{
private:

	RenderWindow* rw;
	Sprite* backGround, * mensaje;
	Boton* botones[7];
	Sprite* vecVidas[6];
	Text* textPtjTotal;


	int nivel, vidas, vidasPerdidas, fantasmasMuertos, ptsTotal, tiempo;
	bool finalBueno, continuarPartida;

public:

	Pantalla_GameOver(bool final, int nivel, int& vidas, int vidasPerdidas, int fantasmasMuertos, int& ptsTotal, int tiempo);

	void setNivel(int nivel);
	void setVidas(int vidas);
	void setVidasPerdidas(int vidasPerdidas);
	void setFatnasmasMuertos(int fantasmasMuertos);
	void setPtsTotal(int ptsTotal);
	void setTiempo(int tiempo);
	void setFinalBueno(bool finalBueno);
	void setContinuarPartida(bool continuarPartida);

	int getNivel();
	int getVidas();
	int getVidasPerdidas();
	int getFatnasmasMuertos();
	int getPtsTotal();
	int getTiempo();
	bool isFinalBueno();
	bool getContinuarPartida();



	void overLoop();
	void showEnd();
	void mostrarVecVidas();
	void mostrarTextPtsTotal();
	void actualizarVecVidas();
	void actualizarTextPtsTotal();


	void selecOption(int x, int y);
	bool evaluarPosicionMouseBoton(int x, int y, Boton* boton);
	void mostrarVista();//decidir si mostrar informacion buena o mala (simular vistas en java, pero mal hecho) XD

	void vistaBuena();
	void vistaMala();//si se compra una vida si muestran los puntos que se gastan y el total que equedan Xd

	void guardarInformacionPartida();//abrir txts y almacenar la info de la partdia.
	//para guardar los diferentes datos
	void guardarVidas(string ruta);
	void guardarVidasPerdidas(string ruta);
	void guardarFantasmasMuertos(string ruta);
	void guardarPtsTotal(string ruta);
	void guardarPtsEnPosecion(string ruta);
	void guardarPtsPorInmunidad(string ruta);
	void guardarPtsEnNivel(string ruta);
	void guardarTiempo(string ruta);
	void guardarMejorTiempoPorNivel(string ruta);
	void guardarCantidadVecesJugado(string ruta);
	//para guardar los diferentes datos


	void setLine(string line, string ruta, int posicion);

};
