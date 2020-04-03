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
      nueva=true;
      std::cout<<"mundoiniciado\n";
      //crear mundo
      //modo=Menu::Instance()->GetModo();
      dif=Menu::Instance()->GetDif(); //dificultad
      lvls=Menu::Instance()->GetLvls(); //numero de niveles
      play=Menu::Instance()->GetPlayers();//numero de jugadores
      
      std::cout<<dif<<lvls<<lvlactual<<"\n";
      
      hud=new Tile();

      for(int a=0;a<lvls;a++){//cargar los mapas dependiendo del nombre
        string s="resources/mapas/"+to_string(dif)+"mapa"+to_string(a)+".tmx";
        std::cout<<s<<endl;
        std::cout<<"premap";
        Map* m=new Map(s,dif+3);//NUMERO A AJUSTAR POR DIFICULTAD
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
              }//Cualquier tecla desconocida se imprime por pantalla su código
          default:
            std::cout << " code " << event.key.code << std::endl;
          break;
        }
      }

}

void Mundo::Update(sf::RenderWindow &window) {//COSAS DEL MUNDO QUE SE ACTUALIZAN SIEMPRE

  if(hud->getTerminada()){

    std::cout<<"terminado el tiempo"<<endl;
    //HAS PERDIDO

  }

  /*if(mapas[lvlactual]->getpuntos()==JUGADORPUNTOS){ ///SI LOS PUNTOS DEL MAPA SON IGUALES A LOS DEL JUGADOR HA TERMINADO EL MAPA 

       mapas[lvlactual]->terminar();

  }*/

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
        std::cout<<"fin"<<endl;
        //RENICIAR MUNDO
        this->renicio();
        //MENU INICIAL
        Menu::Instance()->reinicio();
        ChangeState(Contexto::Instance(),Menu::Instance());

}
 void Mundo::renicio(){ //reiniciar el mundo
      nueva=false;
      std::cout<<dif<<lvls<<lvlactual<<"\n";
      dif=0;
      lvls=0;
      lvlactual=0;
      play=0;
      std::cout<< mapas.size()<<endl;
      for(unsigned int i=0;i<mapas.size();i++){
        mapas[i]=NULL;
        delete mapas[i];
      }
      mapas.clear();
      for(unsigned int i=0;i<adns.size();i++){
        adns[i]=NULL;
        delete adns[i];
      }
      adns.clear();
      std::cout<< mapas.size()<<endl;

      std::cout<<dif<<lvls<<lvlactual<<"\n";

 }

 void Mundo::Draw(sf::RenderWindow &window){//dibujar mapa y hud
    if(lvlactual<mapas.size()){
      mapas[lvlactual]->draw(window);
      hud->draw(window);
    }

    //ARRAY DE ADNS  se recorre y se dibuja 
    for(unsigned int l=0; l<adns.size();l++){
      window.draw(*(adns[l]));
    }
 }

 bool Mundo::saleADN(){
  int ***_tilemap=mapas[lvlactual]->gettilemap();
  int _numlayers=mapas[lvlactual]->getnumlayers();
  int _height=mapas[lvlactual]->getnumlayers();
  int _width=mapas[lvlactual]->getnumlayers();

  int cont=0;
      for(unsigned int l=0; l<_numlayers;l++){
        for( unsigned int y=0; y<_height;y++){
          for(unsigned int x=0; x<_width;x++){
            int gid=_tilemap [l][y][x]-1;
            if(gid==2){//GID = PIEDRAS
              cont++;
            }
          }
        }
      }
   if(cont==(mapas[lvlactual]->getpuntos()-0/*PUNTOSDELJUGADOR*/)){
     return true;
   }
  return false;
 }