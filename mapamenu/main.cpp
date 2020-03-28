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


  sf::RenderWindow window(sf::VideoMode(640, 480),"P0. Fundamentos de los Videojuegos. DCCIA");
  //Creamos una ventana
    std::cout<<"window";
    Contexto* game=Contexto::Instance();
    std::cout<<"game";
    game->Inicializar();
    game->ChangeState(Menu::Instance());      
    sf::Clock clock;
    std::cout<<"clock";
    sf::Time timeStartUpdate=clock.getElapsedTime();
    std::cout<<"timestart\n";
     
    //Bucle del juego
      while (window.isOpen()) {
          while (game->Running()) {
                      sf::Event event;
                        while(window.pollEvent(event)){
                          game->Event(event,window);
                        }
                      game->Update(window);  






                      game->Draw(window);
                   

            if(!window.isOpen())game->Quit();
            }
          
      }
    return 0;
}