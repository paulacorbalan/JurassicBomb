#pragma once
#include "tinyxml.h"
#include "Tile.h"
#include <string>
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

sf::VertexArray m_vertices;
  sf::Texture _tilesettexture;

  sf::Sprite ****_tilemapSprite;




};