#pragma once
#include <SFML/Graphics.hpp>


class Tile{

   
    public:
    Tile();
    Tile(int gid,int layer,int x, int y);
    void Draw(sf::RenderWindow &window);

    int layer;
    int posx;
    int posy;
    int gid;
    int tamano=32;
    int heigth=480;
    int width=640;
    
    sf::Texture tiletex;
    sf::Sprite tileimage;     



};