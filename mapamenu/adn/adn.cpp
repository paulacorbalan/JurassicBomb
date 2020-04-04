#include "adn.h"
#include <iostream>


Adn::Adn(int p) {
 
puntos=p;

}


Adn::~Adn(){

 // delete[] adnsprite; NOCE

}

void Adn::draw(sf::RenderWindow& window){
 window.draw(*(adnsprite));
}

void Adn::Update(sf::Event event,sf::RenderWindow &window){

  switch (event.type) {
              case sf::Event::KeyPressed:
              ///Verifico si se pulsa alguna tecla de movimiento
              switch (event.key.code) {
              //Cualquier tecla desconocida se imprime por pantalla su código

               case sf::Keyboard::Return:
                  
                default:
                  std::cout <<  " code adn " << event.key.code << std::endl;
                break;
              }
  }

}


