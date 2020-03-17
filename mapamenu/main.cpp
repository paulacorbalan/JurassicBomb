#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/config.h"
#include "ej_modulos/Tile.h"
#include "mapa/Map.h"
#include "menu/menu.h"

#define kVel 5

int main() {
  Map *mod2 = new Map("resources/mapa1.tmx");
  Menu menu;
  //Creamos una ventana
  sf::RenderWindow window(sf::VideoMode(width, height), "P0. Fundamentos de los Videojuegos. DCCIA");

   /* //////////PRUEBA IMAGE
            sf::Texture tiletex;
            sf::Sprite tileimage; 
        if ( !tiletex.loadFromFile( "resources/tilebase.png" ) )
            std::cout << "Error: Could not display pausa image" << std::endl;

            tileimage.setTexture( tiletex );
            tileimage.setOrigin(tiletex.getSize().x*0.25, tiletex.getSize().y*0.5);
            tileimage.setTextureRect(sf::IntRect(0, 0, 32, 32));
            tileimage.setPosition(width-64, height-64);  


*/
          Tile *tile=new Tile();
            
  //Bucle del juego
  while (window.isOpen()) {
    //Bucle de obtención de eventos
    sf::Event event;
    tile->Update();
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
//limpieza
    window.clear();

    //dibujar
    mod2->draw(window);
    //window.draw(tileimage);
    tile->draw(window);
    //menu.Draw(window);

//display
    window.display();
  }

  return 0;
}