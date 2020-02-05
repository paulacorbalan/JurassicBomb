#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/config.h"
#include "ej_modulos/mimodulo.h"
#include "ejemplo2/mimodulo2.h"
#include "menu/menu.h"

#define kVel 5

int main() {

  MiModulo *mod = new MiModulo();
    MiModulo2 *mod2 = new MiModulo2("resources/mapa1.tmx");

   Menu menu;
  //Creamos una ventana
  sf::RenderWindow window(sf::VideoMode(640, 480), "P0. Fundamentos de los Videojuegos. DCCIA");
 
  //Bucle del juego
  while (window.isOpen()) {
    //Bucle de obtención de eventos
    sf::Event event;
    while (window.pollEvent(event)) {
      //MENU UPDATE
      menu.Update(event,window);
      
          switch (event.type) {
          //Si se recibe el evento de cerrar la ventana la cierro
          case sf::Event::Closed:
            window.close();
            break;
          //Se pulsó una tecla, imprimo su codigo
          case sf::Event::KeyPressed:
            //Verifico si se pulsa alguna tecla de movimiento
            switch (event.key.code) {
            //Tecla ESC para salir
            case sf::Keyboard::Escape:
              window.close();
              break;
            //Cualquier tecla desconocida se imprime por pantalla su código
            default:
              std::cout << event.key.code << std::endl;
              break;
            }
          }
    }

    window.clear();
    menu.Draw(window);
    window.display();
  }

  return 0;
}