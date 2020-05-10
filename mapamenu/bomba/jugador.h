#pragma once
#include <SFML/Graphics.hpp>
class Mundo;
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
    void setInicio(int a){    
       matando=false;
       if(a==1){sprite->setPosition(160, 113); }else{sprite->setPosition(160+(32*10), 113+(32*8)); }
       
   }
    void mover(int direccion,float times);
    void quitarVidas(){if(vidas > 0)vidas--;}

    void draw(sf::RenderWindow &window);
       void setmatando(bool a){matando=a;}
       bool getmatando(){return matando;}
 private:
    sf::Texture* textura;
    sf::Sprite* sprite;
    int identificador;
    bool bomba;
    int kVel;
    int vidas = 3;
    float invencibilidad = -1;
    bool matando;
};
