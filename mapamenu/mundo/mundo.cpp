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

      //CREAR JUGADORES
      //Sustituir numJugadores por el id que le corresponde a este jugador.
      if(play==1){
      hud1=new Tile();
      jugador1=new Jugador(1);
      jugador1->quitarVidas();
      }else if(play==2)
      {
        jugador1=new Jugador(1);
        hud1=new Tile();
        jugador2=new Jugador(2);
        hud2=new Tile(); 
      }else
      {
        std::cout<<"numero de jugadores mal"<<endl;
      }
    
      for(int a=0;a<lvls;a++){//cargar los mapas dependiendo del nombre
        string s="resources/mapas/"+to_string(dif)+"mapa"+to_string(a)+".tmx";
        std::cout<<s<<endl;
        std::cout<<"premap";
        Map* m=new Map(s,dif+3);
        //Anadimos piedras y paredes del mapa.
        std::cout<<"prepush"<<endl;
        std::cout<< mapas.size()<<endl;
        mapas.push_back(m);//meter los mapas en el vector de mapas
        std::cout<< mapas.size()<<endl;
        std::cout<<"postpush"<<endl;
      }


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
              v1 = rand() % 600;
              std::cout<<m->getnumlayers()<<m->getheight()<<m->getwidth()<<" "<<v1<<endl;
            if(gid==2 && v1<150){//GID = PIEDRAS
              std::cout<<v1<<endl;
              Adn* prueba=new Adn(1,x,y);
              adns.push_back(prueba);
              adnSprites.push_back(prueba->getSprite());
              cont++;
              if (tot==cont) { todos=true; } //CONTROLA QUE NO FALTEN ADNS
            }
          }
        }
     }   
}
void Mundo::crearDinos(Map* m,int tot){

      // Textura por defecto del dinosaurio
      sf::Texture dino_abajo;
      if(!dino_abajo.loadFromFile("resources/dino_abajo.png")){
        std::cerr << "Error cargando dino_abajo.png";
        exit(0);
      }
      /* Generacion de los dos dinosaurios del nivel.
       * Se pueden generar mas en funcion del nivel
       * El tipo de dinosario es: 0: T-Rex | 1: Velociraptor | 2: Pterodactilo | 3: Triceratops 
       */
  int v1=1;
  int cont=0;
  bool todos=false;
  std::cout<<m->getnumlayers()<<m->getheight()<<m->getwidth()<<endl;
        for( unsigned int y=2; y<m->getheight() && !todos;y++){
          for(unsigned int x=2; x<m->getwidth() && !todos;x++){
            int gid=m->gettilemap()[0][y][x]-1;
            int gid2=m->gettilemap()[1][y][x]-1;
              v1 = rand() % 999;
              std::cout<<m->getnumlayers()<<m->getheight()<<m->getwidth()<<" "<<v1<<endl;
              if(gid==1 && gid2==-1 && v1<100){//GID = camino
              Dinosaurio *dino1 = new Dinosaurio(); // Constructor del dinosaurio
              dino1->modifyTexture(dino_abajo); // Cambia la textura del dinosaurio
              dino1->setTipodino(cont%4); // Establece el tipo de dinosario, la vida y la velocidad en funcion de su tipo
              dino1->modifyPosition(117+(x*32),69+(y*32)); // Punto de spawn. Debe estar dentro del mapa
              dinosaurios.push_back(dino1); // Guardar en el vector de dinosaurios
              if (cont<2)//los dos primeros snow bees los crea activos
              {
                dino1->setactivo(true);
                todoSprites.push_back(dino1->getSprite()); //Lo añadimos al vector de colisiones.
              }
              cont++;
              if (tot==cont) { todos=true; } //CONTROLA QUE NO FALTEN ADNS
            }
          }
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
              }
              //Colocacion de una bomba pulsando tecla ESPACIO.
            case 57:
            {
              //Si el jugador no tiene una bomba ya puesta, le permitimos poner una.
              if(jugador1->getPuesta() == false)
              {
                //Nos guardamos el segundo exacto en el que se pone la bomba.
                tiemposBomba.push_back(temporizador.getElapsedTime().asSeconds());
                //Creamos una instancia de bomba.
                Bomba bomba(jugador1->getSprite()->getPosition().x, jugador1->getSprite()->getPosition().y);
                bomba.setPropietario(jugador1->getIdentificador());
                //Lo añadimos al vector de bombas.
                totalBombas.push_back(bomba);

                jugador1->setPuesta(true);
              }
              break;
            }
            case 15://p matar un dino
                if(dinosaurios.size()>0){
                    dinosaurios[0]->modifyVida();
                    if(dinosaurios[0]->getVida() == 0){
                      for(unsigned int a = 0;a < todoSprites.size();a++){
                        if(todoSprites[a]==dinosaurios[0]->getSprite()){
                          todoSprites.erase(todoSprites.begin() + a);
                        }
                      }
                    dinosaurios.erase(dinosaurios.begin() + 0);
                    //jugador1->sumaPuntos();
                    jugador1->setmatando(true);
                    }
            }
             case 16:// q eliminar un adn
                if(adns.size()>0){
                      for(unsigned int a = 0;a < adnSprites.size();a++){
                        if(adnSprites[a]==adns[0]->getSprite()){
                          adnSprites.erase(adnSprites.begin() + a);
                        }
                      }
                    adns.erase(adns.begin() + 0);
                    //jugador1->sumaPuntos();                    
            }
            //Arriba
            case 73:
              jugador1->mover(0);
              Colisiones::crearColisiones(*jugador1->getSprite(),todoSprites,0,jugador1->getVelocidad());
              Colisiones::colisionesBombas(*jugador1,totalBombas,0);
              break;
            //Abajo
            case 74:
              jugador1->mover(1);
              Colisiones::crearColisiones(*jugador1->getSprite(),todoSprites,1,jugador1->getVelocidad());
              Colisiones::colisionesBombas(*jugador1,totalBombas,1);
              break;
            //Derecha
            case 72:
              jugador1->mover(2);
              Colisiones::crearColisiones(*jugador1->getSprite(),todoSprites,2,jugador1->getVelocidad());
              Colisiones::colisionesBombas(*jugador1,totalBombas,2);
              break;
            //Izquierda
            case 71:
              jugador1->mover(3);
              Colisiones::crearColisiones(*jugador1->getSprite(),todoSprites,3,jugador1->getVelocidad());
              Colisiones::colisionesBombas(*jugador1,totalBombas,3);
              break;

          //Cualquier tecla desconocida se imprime por pantalla su código
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
      if (mapas[lvlactual]->fin()){
            std::cout<<"cambiar mapa\n";
            adnscreados=false;//DESTRuiR ADNS//
            dinoscreados=false;
            colisiones=false;
            borrarcolisiones();
            borraradns();
            borrardinos();
            lvlactual++;
            //Reiniciar contador
            hud1->reiniciocrono();
            hud2->reiniciocrono();
            if(play==1){
              jugador1->setInicio();
            }else if(play==2){
              jugador1->setInicio();
              jugador2->setInicio();
            }       
      }
      if(!(lvlactual<mapas.size())){//TERMINAR Y VOLVER A MENU FIN DEL JUEGO   
          finjuego();
          std::cout<<"tras findejuego"<<endl;
        }else{
          if(!adnscreados){//CREAR ADNS ESTO PUEDE DAR LAS PROBLEMAS
            crearAdns(mapas[lvlactual],2);
            adnscreados=true;
          }
          if(!dinoscreados){//CREAR DINOS ESTO PUEDE DAR LAS PROBLEMAS
            crearDinos(mapas[lvlactual],5);
            dinoscreados=true;
          }
          if(!colisiones){
            mapas[lvlactual]->anadirVector(todoSprites);
            colisiones=true;
          }
        }
  if(adns.size()==0){
    std::cout<<"no quedan adns por recoger"<<std::endl;
    if(lvlactual<mapas.size()){
      mapas[lvlactual]->terminar();
    }
  }
  if (jugador1->getmatando())//comprueba los enemigos muertos y los reemplaza
  {
    std::cout<<"matao"<<std::endl;
    todosno(0.015);//METER TIME
    //todosno(time);
  }
    if(play==1){// UN JUGADOR O DOS JUGADORES UPDATEAN ELLOS Y SUS HUDS
      hud1->Update(jugador1);
          Bomba::update(temporizador,*jugador1,totalBombas,totalExplosiones,tiemposBomba,tiemposExplosiones);
          Colisiones::update(temporizador,dinosaurios,*jugador1,totalExplosiones,*mapas[lvlactual],todoSprites,adnSprites,adns); 
      if(jugador1->getVidas()==0){finjuego();std::cout<<"pierdes"<<endl;}
    }else if(play==2)
    {
      hud1->Update(jugador1);
          Bomba::update(temporizador,*jugador1,totalBombas,totalExplosiones,tiemposBomba,tiemposExplosiones);
          Colisiones::update(temporizador,dinosaurios,*jugador1,totalExplosiones,*mapas[lvlactual],todoSprites,adnSprites,adns); 
      if(jugador1->getVidas()==0){finjuego();std::cout<<"pierdes1"<<endl;}
      hud2->Update(jugador2);          
          Bomba::update(temporizador,*jugador2,totalBombas,totalExplosiones,tiemposBomba,tiemposExplosiones);
          Colisiones::update(temporizador,dinosaurios,*jugador2,totalExplosiones,*mapas[lvlactual], todoSprites,adnSprites,adns);
      if(jugador2->getVidas()==0){finjuego();std::cout<<"pierdes2"<<endl;}
    }
    
    // Mover los dinosaurios con la IA
    IA ia; // Genera una ia con cada iteracion
    ia.movimientoDinos(dinosaurios, _cont,todoSprites); // Permite mover a los dinosaurios
      _cont++; // Contador de iteraciones del programa
    //Detecta si le tiene que quitar vida a jugadores y dinosaurios si colisionan con una explosion.


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
      
    //ARRAY DE ADNS  se recorre y se dibuja 
    for(unsigned int l=0; l<adns.size();l++){
      if(adns[l]!=NULL){
        if(adns[l]->getvisible())adns[l]->draw(window);
      }
    }  
    //DIBUJAR BOMBAS
      for(unsigned int i = 0;i < totalBombas.size();i++)
      {
        totalBombas[i].draw(window);
      }
      //DIBUJAR EXPLOSIONES
      for(unsigned int i = 0;i < totalExplosiones.size();i++)
      {
        window.draw(totalExplosiones[i]);
      }
      //DIBUJAR DINOSAURIOS
      for(unsigned int i=0; i < dinosaurios.size(); i++)
      {
        if(dinosaurios[i]->getactivo())window.draw(*dinosaurios[i]->getSprite());
      }
       if(play==1){
        hud1->draw(window);
        jugador1->draw(window);  
      }else if(play==2)
      {
        jugador1->draw(window);  
        hud1->draw(window);
        jugador2->draw(window);  
        hud2->draw(window);
      }
  }
}
 /*bool Mundo::saleADN(){
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
   if(cont==(mapas[lvlactual]->getpuntos()-0PUNTOSDELJUGADOR)){
     return true;
   }
  return false;
 }*/