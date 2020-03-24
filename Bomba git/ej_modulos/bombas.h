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

 private:
	sf::Texture* tbomba;
	sf::Texture* texplosiones;
	sf::Sprite sbomba;
	std::vector<sf::Sprite> explosiones;
	float coordenadaX;
	float coordenadaY;	
	
};
