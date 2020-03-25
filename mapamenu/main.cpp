#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/config.h"
#include "ej_modulos/Tile.h"
#include "mapa/Map.h"
#include "menu/menu.h"
#include "maquina/contexto.h"
#include "SFML/Graphics.hpp"
#include <time.h>

#define kVel 5

int main() {
  /*Map *mod2 = new Map("resources/mapa1.tmx");
  Menu *menu=Menu::Instance();
  Tile *tile=new Tile();*/

  sf::RenderWindow window(sf::VideoMode(640, 480),"P0. Fundamentos de los Videojuegos. DCCIA");

  //Creamos una ventana

  Contexto game;
  game.ChangeState(Menu::Instance());       
  sf::Clock clock;
  sf::Time timeStartUpdate=clock.getElapsedTime();
     
    //Bucle del juego
    while (game.Running()) {
  
          if(clock.getElapsedTime().asMilliseconds()-timeStartUpdate.asMilliseconds()>15){
          sf::Event event;
                while (window.pollEvent(event)) {           
                        
                      game.Update(event,window);
                                            
                      timeStartUpdate = clock.getElapsedTime();
                    }
                }

          game.Draw(window);
      }

    return 0;
}