#pragma once
#include <SFML/Graphics.hpp>
#include "bombas.h"

class Colisiones {

public:
  Colisiones(){};
  void crearColisiones(sf::Sprite &jugador,std::vector<sf::Sprite> objetos,int direccion, int velocidad);
  void colisionesBombas(sf::Sprite &jugador,std::vector<Bomba> &bombas,int direccion, int velocidad);

};