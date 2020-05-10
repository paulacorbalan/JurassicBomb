#pragma once
#include <SFML/Graphics.hpp>
#include "bombas.h"
#include "Map.h"
#include "../dinosaurio/dinosaurio.h"
#include "adn.h"

class Colisiones {

public:
  Colisiones(){};
  static void crearColisiones(sf::Sprite &jugador,std::vector<sf::Sprite*> objetos,int direccion,int velocidad,float times);
  static void colisionesBombas(Jugador &jugador,std::vector<Bomba> &bombas,int direccion,float times);
  static void update(sf::Clock &temporizador,std::vector<Dinosaurio*> &dinosaurios,Jugador &jugador,std::vector<sf::Sprite> &totalExplosiones,Map &mapa, std::vector<sf::Sprite*> &todoSprites, std::vector<sf::Sprite*> &adnSprites,std::vector<Adn*> &adns);

};