#include "mundo.h"
#include <ctime>


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
      if(play==1){
      hud1=new Tile();
      //j1=new Jugador();
      }else if(play==2)
      {
        //j1=new Jugador();
        hud1=new Tile();
        //j2=new Jugador();
        hud2=new Tile(); 
      }else
      {
        std::cout<<"numero de jugadores mal"<<endl;
      }
      
      for(int a=0;a<lvls;a++){//cargar los mapas dependiendo del nombre
        string s="resources/mapas/"+to_string(dif)+"mapa"+to_string(a)+".tmx";
        std::cout<<s<<endl;
        std::cout<<"premap";
        Map* m=new Map(s,dif+3);//PUNTOS A OBTENER MODIFICABLES
        std::cout<<"prepush"<<endl;
        std::cout<< mapas.size()<<endl;
        mapas.push_back(m);//meter los mapas en el vector de mapas
        std::cout<< mapas.size()<<endl;
        std::cout<<"postpush"<<endl;
      }

      //CREAR JUGADORES
      //CREAR DINOSAURIOS O QUIZA EN MAPA JUSTO ARRIBA
}

void Mundo::crearAdns(Map* m,int tot){
  int v1=1;
  int cont=0;
  bool todos=false;
  std::cout<<m->getnumlayers()<<m->getheight()<<m->getwidth()<<endl;
    for(unsigned int l=0; l<m->getnumlayers() && !todos;l++){
        for( unsigned int y=0; y<m->getheight() && !todos;y++){
          for(unsigned int x=0; x<m->getwidth() && !todos;x++){
            int gid=m->gettilemap()[l][y][x]-1;
              v1 = rand() % 999;
              std::cout<<m->getnumlayers()<<m->getheight()<<m->getwidth()<<" "<<v1<<endl;
            if(gid==2 && (v1<180 || saleADN(m->gettilemap(),m->getnumlayers(),m->getheight(),m->getwidth()))){//GID = PIEDRAS
              std::cout<<v1<<endl;
              Adn* prueba=new Adn(1,x,y);
              adns.push_back(prueba);
              cont++;
              if (tot==cont) { todos=true; } //CONTROLA QUE NO FALTEN ADNS
            }
          }
        }
     }   
}

bool Mundo::saleADN(int *** _tilemap,int _numlayers, int _height,int  _width){
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
  if(hud1->getTerminada()){
    std::cout<<"terminado el tiempo"<<endl;//HAS PERDIDO
  }
  /*if(mapas[lvlactual]->getpuntos()==JUGADORPUNTOS){ ///SI LOS PUNTOS DEL MAPA SON IGUALES A LOS DEL JUGADOR HA TERMINADO EL MAPA 
       mapas[lvlactual]->terminar();
  }*/
   if (mapas[lvlactual]->fin()){
      std::cout<<"cambiar mapa\n";
      adnscreados=false;//DESTRuiR ADNS/////////////////////////////////////
      borraradns();
      lvlactual++;
      //Reiniciar contador
      hud1->reiniciocrono();
      hud2->reiniciocrono();
      }
      if(!(lvlactual<mapas.size())){//TERMINAR Y VOLVER A MENU FIN DEL JUEGO   
          finjuego();
          std::cout<<"tras findejuego"<<endl;
        }else{
          if(!adnscreados){//CREAR ADNS ESTO PUEDE DAR LAS PROBLEMAS
            crearAdns(mapas[lvlactual],2);
            adnscreados=true;
          }
        }
    if(play==1){
      hud1->Update(); 
    }else if(play==2)
    {
      hud1->Update(); 
      hud2->Update(); 
    }
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
      std::cout<<"reinicio"<<dif<<lvls<<lvlactual<<"\n";
      dif=0;
      lvls=0;
      lvlactual=0;
      play=0;
      std::cout<< mapas.size()<<endl;
      borrarmapas();
      std::cout<<"reiniciofin"<<dif<<lvls<<lvlactual<<"\n";
}

void Mundo::Draw(sf::RenderWindow &window){//dibujar mapa y hud
  if(lvlactual<mapas.size()){
      mapas[lvlactual]->draw(window);
      if(play==1){
        hud1->draw(window);
      }else if(play==2)
      {
       hud1->draw(window);
       hud2->draw(window);
      }
    //ARRAY DE ADNS  se recorre y se dibuja 
    for(unsigned int l=0; l<adns.size();l++){
      if(adns[l]!=NULL){
        if(adns[l]->getvisible())adns[l]->draw(window);
      }
    }     
  }


}

