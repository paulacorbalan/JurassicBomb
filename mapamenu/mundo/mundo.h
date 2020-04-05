#ifndef MUNDO_H
#define MUNDO_H

#pragma once
#include <string>
#include <iostream>
#include "states.h"
#include "Map.h"
#include "menu.h"
#include "Tile.h"
#include "jugador.h"
#include "bombas.h"
#include "dinosaurio.h"
#include "colisiones.h"
#include "../IA/ia.h"

using namespace std;

class Mundo : public States {

  private:    
    static Mundo* jinstance;
    int dif=0;
    int lvls=0;
    int lvlactual=0;
    int play=0;
    int numjugadores = 1;
    std::vector<Map*> mapas;
    std::vector<Dinosaurio*> dinosaurios;
    Tile* hud;
    sf::Clock temporizador;
    //Jugador//
    Jugador* jugador;
    /////Control de las bombas y explosiones/////
    std::vector<Bomba> totalBombas;
    std::vector<sf::Sprite> totalExplosiones;
    std::vector<float> tiemposBomba;
    std::vector<float> tiemposExplosiones;
    //Vector que almacena todos los sprites para comprobar las colisiones.
    std::vector<sf::Sprite*> todoSprites;

    int _cont = 0; // Contador de iteraciones del juego


  public:
    void Inicializar();
    static Mundo* Instance();
    void Event(sf::Event event,sf::RenderWindow &window);
    void Update(sf::RenderWindow &window);
    void Draw(sf::RenderWindow &window);
    void renicio();
    void finjuego();
    void move_dinos();



};

#endif