#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/config.h"
#include "ej_modulos/Tile.h"
#include "mapa/Map.h"
#include "menu/menu.h"
#include "bomba/bombas.h"
#include "motor/motor.h"
#include "bomba/colisiones.h"
#include "maquina/contexto.h"
#include "SFML/Graphics.hpp"
#include <time.h>

int main() {

  Motor* m=Motor::Instance();

  sf::RenderWindow window(sf::VideoMode(640, 480),"P0. Fundjjjgos. DCCIA");
  m->estableceFPS(window,60);
  //Creamos una ventana
    std::cout<<"window";
    Contexto* game=Contexto::Instance();
    std::cout<<"game";
    game->Inicializar();
    game->ChangeState(Menu::Instance());   

    sf::Clock clock;
    std::cout<<"clock";
    sf::Time timeStartUpdate=m->obtenerInstante(clock);
    std::cout<<"timestart\n";
     
    //Bucle del juego
      while (m->compruebaVentana(window)) {
          while (game->Running()){
                      sf::Event event;
                        while(m->compruebaEvento(window,event)){
                          game->Event(event,window);
                        }
                      game->Update(window);  
                      game->Draw(window);              
            if(!m->compruebaVentana(window))game->Quit();
            }
          
      }
    return 0;
}