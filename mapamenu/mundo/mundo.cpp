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
      hud1=new Tile(1);
      jugador1=new Jugador(1);
      }else if(play==2)//CREA JUGADORES SEGUN SEA MULTIJUGADOR O UN JUGADOR
      {
        jugador1=new Jugador(1);
        hud1=new Tile(1);
        jugador2=new Jugador(2);
        hud2=new Tile(2); 
      }else
      {
        std::cout<<"numero de jugadores mal"<<endl;
      }
    
      for(int a=0;a<lvls;a++){//cargar los mapas dependiendo del nombre
        string s="resources/mapas/"+to_string(dif)+"mapa"+to_string(a)+".tmx";
        Map* m=new Map(s,dif+3);
        mapas.push_back(m);//meter los mapas en el vector de mapas
      }

                    if ( !background.loadFromFile( "resources/fondo2.png" ) )
                      std::cout << "Error: Could not display background image" << std::endl;
                    backgroundImage.setTexture( background );
                    backgroundImage.setOrigin(background.getSize().x*0.5, background.getSize().y*0.5);
                    backgroundImage.setPosition(width/2, height/2); 


}
void Mundo::crearAdns(Map* m,int tot){//CREA LOS ADNS A RECOGER
  int v1=1;
  int cont=0;
  bool todos=false;
    for(unsigned int l=0; l<m->getnumlayers() && !todos;l++){
        for( unsigned int y=0; y<m->getheight() && !todos;y++){
          for(unsigned int x=0; x<m->getwidth() && !todos;x++){ //ELIGE POSICION
            int gid=m->gettilemap()[l][y][x]-1;
              v1 = rand() % 600;
            if(gid==2 && v1<150){//COMPRUEBA QUE ES GID = PIEDRAS
              Adn* prueba=new Adn(1,x,y);
              adns.push_back(prueba);//AÑADE AL VECTOR ADNS
              adnSprites.push_back(prueba->getSprite());//AÑADE AL VECTOR DE SPRITES ADNS
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
        for( unsigned int y=2; y<m->getheight() && !todos;y++){//RECORRO LA MATRIZ DEL MAPA
          for(unsigned int x=2; x<m->getwidth() && !todos;x++){
            int gid=m->gettilemap()[0][y][x]-1;
            int gid2=m->gettilemap()[1][y][x]-1;
              v1 = rand() % 999;
              if(gid==1 && gid2==-1 && v1<400){//COMPRUEBO QUE LA POSICION SEA CORRECTA
              Dinosaurio *dino1 = new Dinosaurio(); // Constructor del dinosaurio
              dino1->modifyTexture(dino_abajo); // Cambia la textura del dinosaurio
              dino1->setTipodino(1); // Establece el tipo de dinosario, la vida y la velocidad en funcion de su tipo
              dino1->modifyPosition(117+(x*32),69+(y*32)); // Punto de spawn. Debe estar dentro del mapa
              dinosaurios.push_back(dino1);
              std::cout<<"DINO METIDO"<<std::endl; // Guardar en el vector de dinosaurios
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
        //if(!todos){crearDinos(m,tot-cont);} 
}

void Mundo::Event(sf::Event event,sf::RenderWindow &window, float time){ //COSAS DEL MUNDO CUANDO PULSAS ALGO
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
              if(lvlactual<mapas.size()){//TERMINAR EL MAPA ACTUAL
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
              jugador1->mover(0);//MOVER
              Colisiones::crearColisiones(*jugador1->getSprite(),todoSprites,0,jugador1->getVelocidad());//CREAR NUEVA COLISION
              Colisiones::colisionesBombas(*jugador1,totalBombas,0);//COMPROBAR COLISION CON BOMBAS COLOCADAS
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

void Mundo::Update(sf::RenderWindow &window, float time) {//COSAS DEL MUNDO QUE SE ACTUALIZAN SIEMPRE

  if(hud1->getTerminada()){
    std::cout<<"terminado el tiempo"<<endl;//HAS PERDIDO
    finjuego(4);
  }else{

      if (mapas[lvlactual]->fin()){//CUANDO TERMINA EL MAPA
            std::cout<<"cambiar mapa\n";
            adnscreados=false;
            dinoscreados=false;
            colisiones=false;
            borrarcolisiones();//DESTRUYE COLISIONES
            borraradns();//DESTRUYE ADNS
            borrardinos();//DESTRUYE DINOS
            lvlactual++;//CAMBIA EL NIVEL
            if(play==1){
              jugador1->setInicio(1);//COLOCAR EN CONDICIONES INICIALES
              hud1->reiniciocrono();//Reiniciar contador
            }else if(play==2){
              jugador1->setInicio(1);
              hud1->reiniciocrono();
              jugador2->setInicio(2);
              hud2->reiniciocrono();
            }       
      }
      if(!(lvlactual<mapas.size())){//TERMINAR Y VOLVER A MENU FIN DEL JUEGO   
          finjuego(3);
          std::cout<<"tras findejuego"<<endl;
        }else{
          if(!adnscreados){//CREAR ADNS 
            crearAdns(mapas[lvlactual],2);
            adnscreados=true;
          }
          if(!dinoscreados){//CREAR DINOS 
            crearDinos(mapas[lvlactual],10);
            dinoscreados=true;
          }
          if(!colisiones){//CREAR COLISIONES
            mapas[lvlactual]->anadirVector(todoSprites);
            colisiones=true;
          }   
// UN JUGADOR O DOS JUGADORES UPDATEAN ELLOS SUS COLISIONES Y SUS HUDS
              if(play==1){
                if (jugador1->getmatando())//comprueba los enemigos muertos y los reemplaza
                {
                  std::cout<<"matao"<<std::endl;
                  todosno(0.015);//METER TIME
                }
                hud1->Update(jugador1);
                    Bomba::update(temporizador,*jugador1,totalBombas,totalExplosiones,tiemposBomba,tiemposExplosiones);
                    Colisiones::update(temporizador,dinosaurios,*jugador1,totalExplosiones,*mapas[lvlactual],todoSprites,adnSprites,adns); 
                if(jugador1->getVidas()==0){//SI TIENES 0 VIDAS PIERDES 
                  finjuego(4);std::cout<<"pierdes"<<endl;
                }else{
                    // Mover los dinosaurios con la IA
                    IA ia; // Genera una ia con cada iteracion
                    ia.movimientoDinos(dinosaurios, _cont,todoSprites, *mapas[lvlactual]); // Permite mover a los dinosaurios
                      _cont++; // Contador de iteraciones del programa
                    //Detecta si le tiene que quitar vida a jugadores y dinosaurios si colisionan con una explosion.

                  if(adns.size()==0){//SI NO QUEDAN ADNS SE TERMINA EL NIVEL
                    std::cout<<"no quedan adns por recoger"<<std::endl;
                    if(lvlactual<mapas.size()){
                      mapas[lvlactual]->terminar();
                    }
                  }
                }
              }else if(play==2)
              {
                hud1->Update(jugador1);
                    Bomba::update(temporizador,*jugador1,totalBombas,totalExplosiones,tiemposBomba,tiemposExplosiones);
                    Colisiones::update(temporizador,dinosaurios,*jugador1,totalExplosiones,*mapas[lvlactual],todoSprites,adnSprites,adns); 
                hud2->Update(jugador2);          
                    Bomba::update(temporizador,*jugador2,totalBombas,totalExplosiones,tiemposBomba,tiemposExplosiones);
                    Colisiones::update(temporizador,dinosaurios,*jugador2,totalExplosiones,*mapas[lvlactual], todoSprites,adnSprites,adns);
                if(jugador1->getVidas()==0 || jugador2->getVidas()==0){
                  finjuego(4);std::cout<<"perdeis"<<endl;
                }else{
                    // Mover los dinosaurios con la IA
                    IA ia; // Genera una ia con cada iteracion
                    ia.movimientoDinos(dinosaurios, _cont,todoSprites, *mapas[lvlactual]); // Permite mover a los dinosaurios
                      _cont++; // Contador de iteraciones del programa
                    //Detecta si le tiene que quitar vida a jugadores y dinosaurios si colisionan con una explosion.
                  if(adns.size()==0){//SI NO QUEDAN ADNS SE TERMINA EL NIVEL
                    std::cout<<"no quedan adns por recoger"<<std::endl;
                    if(lvlactual<mapas.size()){
                      mapas[lvlactual]->terminar();
                    }
                  }
                }
              }
                
            }  
        }
}

 
void Mundo::finjuego(int a){//CUANDO TERMINO PRIMERO REINICIO EL MUNDO Y LUEGO ME MUEVO AL MENU INICIAL
        std::cout<<"fin"<<endl;
        //RENICIAR MUNDO
        this->renicio();
        //MENU INICIAL
        Menu::Instance()->reinicio(a);
        ChangeState(Contexto::Instance(),Menu::Instance());
}

void Mundo::renicio(){ //reiniciar el mundo, TODO A 0 Y BORRAR MAPAS
      nueva=false;
      std::cout<<"reinicio"<<dif<<lvls<<lvlactual<<"\n";
      dif=0;
      lvls=0;
      lvlactual=0;
      play=0;
      borrarmapas();
      std::cout<<"reiniciofin"<<dif<<lvls<<lvlactual<<"\n";
}

void Mundo::Draw(sf::RenderWindow &window){//dibujar mapa y hud
  window.draw(backgroundImage);
  if(lvlactual<mapas.size()){
      mapas[lvlactual]->draw(window);//DIBUJO MAPA ACTUAL
      
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
       if(play==1){//DIBUJA JUGADOR Y HUD
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