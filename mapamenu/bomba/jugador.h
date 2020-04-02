#pragma once
#include <SFML/Graphics.hpp>

class Jugador{
    
 public:
    Jugador(int num);
    sf::Sprite getSprite(){return sprite;};
    int getIdentificador(){return identificador;};
    bool getPuesta(){return bomba;};
    int getVelocidad(){return kVel;}
    void setPuesta(bool estado){bomba = estado;}
    void setVelocidad(int velocidad){kVel = velocidad;}
    void mover(int direccion);

    void draw(sf::RenderWindow &window);

 private:
    sf::Texture* textura;
    sf::Sprite sprite;
    int identificador;
    bool bomba;
    int kVel;
};
