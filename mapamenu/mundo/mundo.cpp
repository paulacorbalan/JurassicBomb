#include "mundo.h"



Mundo* Mundo::jinstance=0;

  Mundo* Mundo::Instance() {
    if(jinstance==0){
      jinstance=new Mundo;
        std::cout<<"mundooinstance"; 
    }
    return jinstance;
  }

void Mundo::Inicializar() {
      std::cout<<"mundoiniciado\n";
      //crear mundo
      dif=Menu::Instance()->GetDif(); //dificultad
      lvls=Menu::Instance()->GetLvls(); //numero de niveles
      play=Menu::Instance()->GetPlayers();//numero de jugadores
      
      hud=new Tile();

      jugador = new Jugador(numjugadores);

      for(int a=0;a<lvls;a++){//cargar los mapas dependiendo del nombre
        string s="resources/mapas/"+to_string(dif)+"mapa"+to_string(a)+".tmx";
        std::cout<<s<<endl;
        std::cout<<"premap";
        Map* m=new Map(s);
        std::cout<<"prepush"<<endl;
        std::cout<< mapas.size()<<endl;
        mapas.push_back(m);//meter los mapas en el vector de mapas
        std::cout<< mapas.size()<<endl;
        std::cout<<"postpush"<<endl;
      }
      //CREAR JUGADORES
      //CREAR DINOSAURIOS O QUIZA EN MAPA JUSTO ARRIBA
}

void Mundo::Event(sf::Event event,sf::RenderWindow &window){ //COSAS DEL MUNDO CUANDO PULSAS ALGO
      switch (event.type) {
        case sf::Event::Closed:
          Contexto::Instance()->Quit();
          window.close();
        break;
        //case sf::Event::MouseButtonPressed:
        case sf::Event::KeyPressed:
              ///Verifico si se pulsa alguna tecla de movimiento
          switch (event.key.code) {
            case 60:
              if(lvlactual<mapas.size()){
                  mapas[lvlactual]->terminar();
              }
              //Colocacion de una bomba pulsando tecla ESPACIO.
            case 57:
            {
              //Si el jugador no tiene una bomba ya puesta, le permitimos poner una.
              if(jugador->getPuesta() == false)
              {
                //Nos guardamos el segundo exacto en el que se pone la bomba.
                tiemposBomba.push_back(temporizador.getElapsedTime().asSeconds());
                //Creamos una instancia de bomba.
                Bomba bomba(jugador->getSprite().getPosition().x, jugador->getSprite().getPosition().y);
                bomba.setPropietario(numjugadores);
                //Lo añadimos al vector de bombas.
                totalBombas.push_back(bomba);

                jugador->setPuesta(true);
              }
              break;
            }
            
            //Arriba
            case 73:
              jugador->mover(0);
              break;
            //Abajo
            case 74:
              jugador->mover(1);
              break;
            //Derecha
            case 72:
              jugador->mover(2);
              break;
            //Izquierda
            case 71:
              jugador->mover(3);
              break;

          //Cualquier tecla desconocida se imprime por pantalla su código
          default:
            std::cout << " code " << event.key.code << std::endl;
          break;
        }
      }

}

void Mundo::Update(sf::RenderWindow &window) {//COSAS DEL MUNDO QUE SE ACTUALIZAN SIEMPRE

   if (mapas[lvlactual]->fin())
    {
      std::cout<<"cambiar mapa\n";

      lvlactual++;
      if (!(lvlactual<mapas.size()))
      {
      //TERMINAR Y VOLVER A MENU FIN DEL JUEGO
      finjuego();
      }
      
      //Reiniciar contador
      hud->reiniciocrono();
    }
    hud->Update();
    Bomba::update(temporizador,*jugador,totalBombas,totalExplosiones,tiemposBomba,tiemposExplosiones);

 }

 
void Mundo::finjuego(){
        //RENICIAR MUNDO
        this->renicio();
        //MENU INICIAL
        Menu::Instance()->reinicio();
       ChangeState(Contexto::Instance(),Menu::Instance());
}
 void Mundo::renicio(){ //reiniciar el mundo
      std::cout<<dif<<lvls<<lvlactual<<"\n";
      dif=0;
      lvls=0;
      lvlactual=0;
      play=0;
      //vaciar mapas TARREGLAR
      std::cout<< mapas.size()<<endl;
      mapas.clear();
      std::cout<< mapas.size()<<endl;
      std::cout<<dif<<lvls<<lvlactual<<"\n";
 }

 void Mundo::Draw(sf::RenderWindow &window){
    if(lvlactual<mapas.size()){
      mapas[lvlactual]->draw(window);
      hud->draw(window);
      jugador->draw(window);
      for(unsigned int i = 0;i < totalBombas.size();i++)
      {
        totalBombas[i].draw(window);
      }
      for(unsigned int i = 0;i < totalExplosiones.size();i++)
      {
        window.draw(totalExplosiones[i]);
      }
    }
 }