#include "juego.h"


Juego* Juego::jinstance=0;

  Juego* Juego::Instance() {
    if(jinstance==0){
      jinstance=new Juego;
        std::cout<<"juegoinstance"; 
    }
    return jinstance;
  }

void Juego::Inicializar() {
  std::cout<<"juegoiniciado\n";
  //crear mundo
  m=Mundo::Instance();
  m->Inicializar();
}

void Juego::Update(sf::Event event,sf::RenderWindow &window) {

        m->Update(event,window);
}
 void Juego::Draw(sf::RenderWindow &window){

    m->Draw(window);

 }