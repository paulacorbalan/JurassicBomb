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
#include "adn.h"

using namespace std;

class Mundo : public States {

  private:    
    static Mundo* jinstance;
    int dif=0;//dificultad
    int lvls=0;//numero de niveles
    int lvlactual=0;//nivel en el que estamos
    int play=0;//numero de jugadores
    int modo=0;//modo de juego
    std::vector<Map*> mapas;//vector de mapas para jugar
    Tile* hud1;//el hud
    Tile* hud2;//el hud
    //JUGADOR1 j1
    //JUGADOR2 j2
    bool nueva=false;//controla la nueva partida
    std::vector<Adn*> adns;//array de adns(seguramente modificcable)


    bool adnscreados=false;
   

  public:
    void Inicializar();
    static Mundo* Instance();
    void Event(sf::Event event,sf::RenderWindow &window);
    void Update(sf::RenderWindow &window);
    void Draw(sf::RenderWindow &window);
    void renicio();
    void finjuego();
    bool saleADN(int *** _tilemap,int _numlayers, int _height,int  _width);
    void crearAdns(Map* m,int tot);
    void borraradns(){
        for(unsigned int i=0;i<adns.size();i++){
          std::cout<<"adn delete"<<endl;
          delete adns[i];
          adns[i]=NULL;
        }
        adns.clear();
    }
    void borrarmapas(){
      for(unsigned int i=0;i<mapas.size();i++){
        delete mapas[i];
        mapas[i]=NULL;
      }
      mapas.clear();
    }




};

#endif