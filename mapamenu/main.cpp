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
  Contexto game;
      std::cout<<"game";
  game.Inicializar();
  game.ChangeState(Menu::Instance());      
  sf::Clock clock;
      std::cout<<"clock";
  sf::Time timeStartUpdate=clock.getElapsedTime();
      std::cout<<"timestart\n";
     
    //Bucle del juego
      while (window.isOpen()) {
          while (game.Running()) {
                sf::Event event;
                      while (window.pollEvent(event)) {           
                              
                                        switch (event.type) {
                                          //Si se recibe el evento de cerrar la ventana la cierro
                                          case sf::Event::Closed:
                                            game.Quit();
                                            window.close();
                                            break;
                                          case sf::Event::KeyPressed:
                                                  switch (event.key.code) {
                                                  //Tecla ESC para salir
                                                  case sf::Keyboard::Escape:
                                                    game.Quit();
                                                    window.close();
                                                    break;
                                                       default:
                                                  std::cout << event.key.code << std::endl;
                                                   break;
                                                  }
                                                
                                        }
                            game.Update(event,window);
                                                  
                            timeStartUpdate = clock.getElapsedTime();

                          }
                game.Draw(window);
              }
            }
      
    return 0;
}