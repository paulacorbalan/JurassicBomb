#include "adn.h"
#include <iostream>


Adn::Adn(int p,int x, int y) {
  puntos=p;
  visible=true;//comenzaria en falso
  posx=x;
  posy=y;
  adnsprite=new Sprite("resources/adn.png");
  adnsprite->posiciona(112+(x*32),64+(y*32));
}


Adn::~Adn(){
  visible=false;
  std::cout<<"eliminar sprite"<<endl;
  adnsprite=NULL;
  delete adnsprite; 
  std::cout<<"tras eliminar sprite"<<endl;
}

void Adn::draw(sf::RenderWindow& window){

  if(visible){
    adnsprite->dibujaSprite(window);
  }
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


