#pragma once
#include <SFML/Graphics.hpp>

class Bomba{
    
 public:
	Bomba(float x,float y);
	std::vector<sf::Sprite> GenerarExplosion();
	float getCoordenadaX();
	float getCoordenadaY();
	sf::Sprite getBomba();
	void setExplosion(std::vector<sf::Sprite>);
	int getPropietario();
	bool getColision();
	bool setColision();
	void setPropietario(int identificador);

 private:
	sf::Texture* tbomba;
	sf::Texture* texplosiones;
	sf::Sprite sbomba;
	std::vector<sf::Sprite> explosiones;
	bool activarColision;
	int propietario;
	float coordenadaX;
	float coordenadaY;	
	
};
