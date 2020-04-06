#pragma once
#include <SFML/Graphics.hpp>

class Jugador{
    
 public:
    Jugador(int num);
    sf::Sprite* getSprite(){return sprite;};
    int getIdentificador(){return identificador;};
    bool getPuesta(){return bomba;};
    int getVelocidad(){return kVel;}
    int getVidas(){return vidas;}
    float getInvencibilidad(){return invencibilidad;}
    
    void setPuesta(bool estado){bomba = estado;}
    void setVelocidad(int velocidad){kVel = velocidad;}
    void setVidas(int v){vidas = v;}
    void setInvencibilidad(float f){invencibilidad = f;}

    void mover(int direccion);
    void quitarVidas(){if(vidas > 0)vidas--;}

    void draw(sf::RenderWindow &window);

 private:
    sf::Texture* textura;
    sf::Sprite* sprite;
    int identificador;
    bool bomba;
    int kVel;
    int vidas = 3;
    float invencibilidad = -1;
};
