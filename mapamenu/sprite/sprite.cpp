#include "sprite.h"

Sprite::Sprite(string s){
   
        t.loadFromFile(s);
        spr.setTexture(t);
    
}
Sprite::~Sprite(){

    delete this;
}
void Sprite::dibujaSprite(sf::RenderWindow& w){

    w.draw(spr);
}
void Sprite::recortaSprite(int n1,int n2,int x,int y){

    spr.setTextureRect(sf::IntRect(n1*x,n2*y,x,y));
}
void Sprite::posiciona(int x,int y){

        spr.setPosition(x,y);
}
void Sprite::estableceOrigen(int x,int y){

    spr.setOrigin(x/2,y/2);
}
bool Sprite::compruebaSiRatonEstaEncima(sf::Vector2i& m){

    bool respuesta=false;

    respuesta=spr.getGlobalBounds().contains(m.x,m.y);

    return respuesta;
}