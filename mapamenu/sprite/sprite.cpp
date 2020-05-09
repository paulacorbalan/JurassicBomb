#include "sprite.h"
#include <iostream>
Sprite::Sprite(string s){
   
        t.loadFromFile(s);
        spr->setTexture(t);
    
}
Sprite::~Sprite(){
    spr=NULL;
    delete spr;
   
}
void Sprite::dibujaSprite(sf::RenderWindow& w){//dibuja el sprite

    w.draw(*spr);
}
void Sprite::recortaSprite(int n1,int n2,int x,int y){//selecciona el sprite de la textura

    spr->setTextureRect(sf::IntRect(n1*x,n2*y,x,y));
}
void Sprite::posiciona(int x,int y){//establece la posicion del sprite

        spr->setPosition(x,y);
}
void Sprite::estableceOrigen(int x,int y){//establece el origen de las transformaciones del sprite

    spr->setOrigin(x/2,y/2);
}
bool Sprite::compruebaSiRatonEstaEncima(sf::Vector2i& m){//captura si el raton esta encima de algun elemento

    bool respuesta=false;

    respuesta=spr->getGlobalBounds().contains(m.x,m.y);

    return respuesta;
}