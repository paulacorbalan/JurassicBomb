#ifndef MAPA_H
#define MAPA_H
#pragma once
#include "tinyxml.h"
#include <string>
#include "SFML/Graphics.hpp"

using namespace std;
class Map {

public:
  Map(string s);
  ~Map();
  void Update(sf::Event event,sf::RenderWindow &window);
  void draw(sf::RenderWindow &window);
  void setactivelayer(int layer);
  TiXmlElement* cambio(int l, TiXmlElement &d);
  bool fin(){return finalizado;};
  void terminar(){ std::cout<<"terminado";finalizado=true;};
  void Update();
  void reservarMemoria(int num);
  void anadirVector(std::vector<sf::Sprite*> &vectorS);

private:
  bool finalizado;
  int _width;
  int _height;
  int _tilewidth;
  int _tileheigh;
  int _numlayers;
  int ***_tilemap;
  int _activelayer;
  string _nombremapa;
  sf::Font fuente;
  sf::Text texto;
  sf::VertexArray m_vertices;
  sf::Texture _tilesettexture;
  sf::Sprite ****_tilemapSprite;

};

#endif