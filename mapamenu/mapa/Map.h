#pragma once
#include "tinyxml.h"
#include <string>
#include "SFML/Graphics.hpp"

using namespace std;
class Map {

public:
  Map(string s);
  void draw(sf::RenderWindow &window);
  void setactivelayer(int layer);
private:
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