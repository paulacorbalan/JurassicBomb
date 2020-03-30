#pragma once
#include <SFML/Graphics.hpp>

class Jugador{
    
 public:
    Jugador(int num);
    sf::Sprite getSprite();
    int getIdentificador();

 private:
    sf::Texture* textura;
    sf::Sprite sprite;
	int identificador;
};
