#pragma once
#include "sprite.h"
#include "motor.h"
#include "bombas.h"
#include "adn.h"
#include "Map.h"
#include "../dinosaurio/dinosaurio.h"

class Colisiones {

public:
  Colisiones(){};
  static void crearColisiones(Sprite* jugador,std::vector<Sprite*> objetos,int direccion,int velocidad);
  static void colisionesBombas(Jugador &jugador,std::vector<Bomba> &bombas,int direccion);
  static void update(sf::Clock &temporizador,std::vector<Dinosaurio*> &dinosaurios,Jugador &jugador,std::vector<Sprite*> &totalExplosiones,Map &mapa, std::vector<Sprite*> &todoSprites, std::vector<Sprite*> &adnSprites,std::vector<Adn*> &adns);

};