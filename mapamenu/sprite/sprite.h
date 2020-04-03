#ifndef SPRITE_H
#define SPRITE_H

#include "SFML/Graphics.hpp"
#include <string>

using namespace std;
class Sprite{

    private: 
            sf::Sprite spr;
            sf::Texture t;

    public:
            Sprite(string s);
            ~Sprite();
            void dibujaSprite(sf::RenderWindow& w);
            void recortaSprite(int n1,int n2,int x,int y);
            void posiciona(int x,int y);
            void estableceOrigen(int x,int y);
            bool compruebaSiRatonEstaEncima(sf::Vector2i& m);
            
};



















#endif