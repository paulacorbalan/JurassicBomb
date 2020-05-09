#pragma once
#include <SFML/Graphics.hpp>
#include "sprite.h"
#include "jugador.h"

class Bomba{
    
 public:
	Bomba(float x,float y);
	std::vector<Sprite*> GenerarExplosion();
	float getCoordenadaX();
	float getCoordenadaY();
	Sprite* getBomba();
	void setExplosion(std::vector<Sprite*>);
	int getPropietario();
	bool getColision();
	bool setColision();
	void setPropietario(int identificador);

	void draw(sf::RenderWindow &window);
	static void update(sf::Clock &clock,Jugador &jugador,std::vector<Bomba> &bomb,std::vector<Sprite*> &explo,std::vector<float> &tbomb,std::vector<float> &texplo);

 private:
	sf::Texture tbomba;
	sf::Texture texplosiones;
	Sprite* sbomba;
	std::vector<Sprite*> explosiones;
	bool activarColision;
	int propietario;
	float coordenadaX;
	float coordenadaY;	
	
};
