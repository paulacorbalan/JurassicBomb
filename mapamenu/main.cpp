#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/config.h"
#include "ej_modulos/Tile.h"
#include "mapa/Map.h"
#include "menu/menu.h"
#include "bomba/bombas.h"
#include "bomba/colisiones.h"
#include "maquina/contexto.h"
#include "SFML/Graphics.hpp"
#include <time.h>
#include "motor.h"
#define UPDATETIME 1000/30
int main() {

    Motor* motor=Motor::Instance();


  sf::RenderWindow window(sf::VideoMode(640, 480),"Jurassic Bomb");
  motor->estableceFPS(window,60);

  //Creamos una ventana
    Contexto* game=Contexto::Instance();
    //Iniciamos el juego
    game->Inicializar();
    //Empezamos en el stado menu
    game->ChangeState(Menu::Instance());   

    sf::Clock clock;
    sf::Clock clock2;
    sf::Time timeStartUpdate=motor->obtenerInstante(clock);

     
    //Bucle del juego
      while (motor->compruebaVentana(window)) {
        if((motor->obtenerInstante(clock).asMilliseconds()-timeStartUpdate.asMilliseconds())>UPDATETIME){
          while (game->Running()){
                      sf::Event event;
                        while(motor->compruebaEvento(window,event)){
                          game->Event(event,window, clock2.restart().asSeconds());
                        }
                      game->Update(window, clock2.restart().asSeconds());  
                      game->Draw(window);              
            if(!motor->compruebaVentana(window))game->Quit();
          }
          timeStartUpdate=motor->obtenerInstante(clock);
        }  
      }
    return 0;
}