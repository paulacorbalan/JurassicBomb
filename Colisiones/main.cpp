#include <SFML/Graphics.hpp>
#include <iostream>

#include "include/config.h"

#define kVel 5
#define anchuraVentana 640
#define altoVentana 480

int main() {
  //Creamos una ventana
  sf::RenderWindow window(sf::VideoMode(anchuraVentana,altoVentana), "P0. Fundamentos de los Videojuegos. DCCIA");
  //Creamos la textura de una roca.
  sf::Texture texturaRoca;

 if (!texturaRoca.loadFromFile("resources/roca.png")) {
    std::cerr << "Error cargando la imagen roca.png";
    exit(0);
  }

  sf::Sprite roca1;
  sf::Sprite roca2;
  sf::Sprite roca3;
  roca1.setTexture(texturaRoca);
  roca2.setTexture(texturaRoca);
  roca3.setTexture(texturaRoca);

  roca1.setOrigin(200,200);
  roca1.setTextureRect(sf::IntRect(65,65,325,245));
  roca2.setTextureRect(sf::IntRect(65,65,325,245));
  roca3.setTextureRect(sf::IntRect(65,65,325,245));
  roca1.setPosition(200, 120);
  roca2.setPosition(400, 120);
  roca3.setPosition(200, 260);
  
  roca1.scale(0.15,0.15);
  roca2.scale(0.15,0.15);
  roca3.scale(0.15,0.15);

  


  //Cargo la imagen donde reside la textura del sprite
  sf::Texture tex;
  if (!tex.loadFromFile("resources/sprites.png")) {
    std::cerr << "Error cargando la imagen sprites.png";
    exit(0);
  }

  //Y creo el spritesheet a partir de la imagen anterior
  sf::Sprite sprite(tex);

  //Le pongo el centroide donde corresponde
  sprite.setOrigin(75 / 2, 75 / 2);
  //Cojo el sprite que me interesa por defecto del sheet
  sprite.setTextureRect(sf::IntRect(0 * 75, 0 * 75, 65, 65));

  // Lo dispongo en el centro de la pantalla
  sprite.setPosition(320, 240);
  sprite.setScale(0.5, 0.5);

  //Bucle del juego
  while (window.isOpen()) {
    //Bucle de obtención de eventos
    sf::Event event;
    while (window.pollEvent(event)) {

      switch (event.type) {

      //Si se recibe el evento de cerrar la ventana la cierro
      case sf::Event::Closed:
        window.close();
        break;

      //Se pulsó una tecla, imprimo su codigo
      case sf::Event::KeyPressed:

        //Verifico si se pulsa alguna tecla de movimiento
        switch (event.key.code) {

        //Mapeo del cursor
        case sf::Keyboard::Right:
          sprite.setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
          //Escala por defecto
          sprite.setScale(0.5, 0.5);
          sprite.move(kVel, 0);

          //Comprobacion de colisiones con objetos y limites del mapa.
          if(sprite.getGlobalBounds().intersects(roca1.getGlobalBounds()) || sprite.getGlobalBounds().intersects(roca2.getGlobalBounds()) || sprite.getGlobalBounds().intersects(roca3.getGlobalBounds()))
          {
            sprite.move(-kVel, 0);
          }

          //Le sumamos a la posicion actual del centroide, una distancia media entre el y su caja de colision.
          if(sprite.getPosition().x + 18.75 > anchuraVentana)
          {
            sprite.move(-kVel, 0);
          }
          ////////Fin de las colisiones.

          break;

        case sf::Keyboard::Left:
          sprite.setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
          //Reflejo vertical
          sprite.setScale(-0.5, 0.5);
          sprite.move(-kVel, 0);

          if(sprite.getGlobalBounds().intersects(roca1.getGlobalBounds()) || sprite.getGlobalBounds().intersects(roca2.getGlobalBounds()) || sprite.getGlobalBounds().intersects(roca3.getGlobalBounds()))
          {
            sprite.move(kVel, 0);
          }

          if(sprite.getPosition().x - 18.75 < 0)
          {
            sprite.move(kVel, 0);
          }

          break;

        case sf::Keyboard::Up:
          sprite.setTextureRect(sf::IntRect(0 * 75, 3 * 75, 75, 75));
          sprite.move(0, -kVel);

          if(sprite.getGlobalBounds().intersects(roca1.getGlobalBounds()) || sprite.getGlobalBounds().intersects(roca2.getGlobalBounds()) || sprite.getGlobalBounds().intersects(roca3.getGlobalBounds()))
          {
            sprite.move(0, kVel);
          }

          if(sprite.getPosition().y - 18.75 < 0)
          {
            sprite.move(0, kVel);
          }

          break;

        case sf::Keyboard::Down:
          sprite.setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));
          sprite.move(0, kVel);

          if(sprite.getGlobalBounds().intersects(roca1.getGlobalBounds()) || sprite.getGlobalBounds().intersects(roca2.getGlobalBounds()) || sprite.getGlobalBounds().intersects(roca3.getGlobalBounds()))
          {
            sprite.move(0, -kVel);
          }

          if(sprite.getPosition().y + 18.75 > altoVentana)
          {
            sprite.move(0, -kVel);
          }

          break;

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
    window.draw(roca1);
    window.draw(roca2);
    window.draw(roca3);
    window.draw(sprite);
    window.display();
  }

  return 0;
}