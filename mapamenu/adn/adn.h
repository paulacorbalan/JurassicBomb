#ifndef ADN_H
#define ADN_H
#pragma once
#include "tinyxml.h"
#include <string>
#include "SFML/Graphics.hpp"

using namespace std;
class Adn {

public:
  Adn(int puntos);
  ~Adn();
  void Update(sf::Event event,sf::RenderWindow &window);
  void draw(sf::RenderWindow &window);
  void Update();
  int getpuntos(){return puntos;}


private:
  int puntos;
  sf::Texture adntext;
  sf::Sprite *adnsprite;

};

#endif