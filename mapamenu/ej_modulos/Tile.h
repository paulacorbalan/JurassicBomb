#pragma once

#include "motor.h"
#include "jugador.h"

class Tile{

   
    public:
    Tile();
    void Cargarecursos();
    void Update(Jugador* j);
    void draw(sf::RenderWindow &window);
    void reiniciocrono(){min=5;seg=59;terminada=false;}
    bool getTerminada(){return terminada;}
private:

    Sprite* vida1;
    Sprite* vida2;
    Sprite* vida3;
    sf::Texture texvida;
    Sprite* letranumero;
    sf::Texture texletranumero;
    Sprite* contador;
    sf::Texture texcontador;
    sf::Clock temporizador;
    int segundero;
    std::vector<Sprite*> sprites;


    sf::Font fuente;
    sf::String cadena;
    sf::Text texto;
    int vidas=3;
    bool terminada=false;
    int min=2;
    int seg=12;



};