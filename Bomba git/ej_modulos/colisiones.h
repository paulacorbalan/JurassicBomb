#pragma once
#include <SFML/Graphics.hpp>

class Colisiones {

public:
  Colisiones(){};
  void crearColisiones(sf::Sprite &jugador,std::vector<sf::Sprite> objetos,int direccion, int velocidad);
};