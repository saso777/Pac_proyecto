#pragma once
class Nodo
{
private:
	int id;
	int x, y, pesoIzq, pesoDer, pesoAr, pesoAb;
	float px, py;

	bool hayPacman, ocupado;
public:
	Nodo();
	Nodo(int id, int x, int y, float peso);

	void setId(int id);
	void setX(int x);
	void setY(int y);
	void setPx(float px);
	void setPy(float py);
	void setPesoIzq(int cont);
	void setPesoAr(int cont);
	void setPesoDer(int cont);
	void setPesoAb(int cont);
	void setHayPacman(bool hayPacman);
	void setOcupado(bool ocupado);

	int getId();
	int getX();
	int getY();
	float getPx();
	float getPy();
	int getPesoAr();
	int getPesoAb();
	int getPesoIzq();
	int getPesoDer();
	bool getHayPacman();
	bool isOcupado();

};
