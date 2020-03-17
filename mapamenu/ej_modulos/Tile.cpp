#include "Tile.h"
#include <iostream>

Tile::Tile(int i,int l, int x, int y) {
    gid=i;
    layer=l;
    posx=x;
    posy=y;

    if ( !tiletex.loadFromFile( "resources/tilebase.png" ) )
    std::cout << "Error: Could not display pausa image" << std::endl;

    tileimage.setTexture( tiletex );
    tileimage.setOrigin(tiletex.getSize().x*0.25, tiletex.getSize().y*0.5);
    tileimage.setTextureRect(sf::IntRect((gid-1) * tamano, (gid-1) * tamano, tamano, tamano));
    tileimage.setPosition((width/13/2)+(tamano*x), (heigth/11/2)+(tamano*y));
}
void Tile::Draw(sf::RenderWindow &window){
    window.draw(tileimage);
}

