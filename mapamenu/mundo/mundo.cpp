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
              }//Cualquier tecla desconocida se imprime por pantalla su código
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

 void Mundo::Draw(sf::RenderWindow &window){//dibujar mapa y hud
    if(lvlactual<mapas.size()){
      mapas[lvlactual]->draw(window);
      hud->draw(window);
    }
 }