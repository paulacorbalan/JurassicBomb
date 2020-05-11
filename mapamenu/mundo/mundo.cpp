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
                    
    borrarcolisiones();//DESTRUYE COLISIONES
    borraradns();//DESTRUYE ADNS
    borrardinos();//DESTRUYE DINOS
    adnscreados=false;
    dinoscreados=false;
    colisiones=false;
    /*Controles jugador 1*/
    flechaArriba = false;
    flechaAbajo = false;
     flechaIzquierda = false;
     flechaDerecha = false;
     teclaEspacio = false;
    /*Controles jugador 2*/
     teclaW = false;
     teclaS = false;
     teclaA = false;
     teclaD = false;
     teclaE = false;

}
void Mundo::crearAdns(Map* m,int tot){//CREA LOS ADNS A RECOGER
  int v1=1;
  int cont=0;
  bool todos=false;
    for(unsigned int l=0; l<m->getnumlayers() && !todos;l++){
        for( unsigned int y=0; y<m->getheight() && !todos;y++){
          for(unsigned int x=0; x<m->getwidth() && !todos;x++){ //ELIGE POSICION
            int gid=m->gettilemap()[l][y][x]-1;
              v1 = rand() % 500;
            if(gid==2 && v1<150){//COMPRUEBA QUE ES GID = PIEDRAS
              Adn* prueba=new Adn(1,x,y);
              adns.push_back(prueba);//AÑADE AL VECTOR ADNS
              adnSprites.push_back(prueba->getSprite());//AÑADE AL VECTOR DE SPRITES ADNS
              std::cout<<"adn creado"<<std::endl;
              cont++;
              if (tot==cont) { todos=true; } //CONTROLA QUE NO FALTEN ADNS
            }
          }
        }
     }   
}
void Mundo::crearDinos(Map* m,int tot){
      /* Generacion de los dos dinosaurios del nivel.
       * Se pueden generar mas en funcion del nivel
       * El tipo de dinosario es: 0: T-Rex | 1: Velociraptor | 2: Pterodactilo | 3: Triceratops 
       */
  int v1=1;
  int cont=0;
  bool todos=false;
        for( unsigned int y=2; y<m->getheight()-2 && !todos;y++){//RECORRO LA MATRIZ DEL MAPA
          for(unsigned int x=2; x<m->getwidth()-2 && !todos;x++){
            int gid=m->gettilemap()[0][y][x]-1;
            int gid2=m->gettilemap()[1][y][x]-1;
              v1 = rand() % 999;
              if(gid==1 && gid2==-1 && v1<600){//COMPRUEBO QUE LA POSICION SEA CORRECTA
              Dinosaurio *dino1 = new Dinosaurio(); // Constructor del dinosaurio
              dino1->setTipodino(cont%4); // Establece el tipo de dinosario, la vida y la velocidad en funcion de su tipo
              dino1->modifyPosition(117+(x*32),69+(y*32)); // Punto de spawn. Debe estar dentro del mapa
              dinosaurios.push_back(dino1);
              std::cout<<"DINO METIDO"<<std::endl; // Guardar en el vector de dinosaurios
              if (cont<dif+2)//los dos primeros snow bees los crea activos
              {
                dino1->setactivo(true);
              }
              cont++;
              if (tot==cont) { todos=true; } //CONTROLA QUE NO FALTEN ADNS
            }
          }
        }
}

void Mundo::Event(sf::Event event,sf::RenderWindow &window, float time){ //COSAS DEL MUNDO CUANDO PULSAS ALGO
      switch (event.type) {
        case sf::Event::Closed:
          Contexto::Instance()->Quit();
          window.close();
        break;
        //AL PULSAR LA TECLA
        case sf::Event::KeyPressed:

          if(event.key.code == 60)
          {
            if(lvlactual<mapas.size()){//TERMINAR EL MAPA ACTUAL
                  mapas[lvlactual]->terminar();
              }
          }

          if(event.key.code == 15)
          {
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
          }
          /*Controles jugador 1*/

            //Colocacion de una bomba pulsando tecla ESPACIO.
            if(event.key.code == 57)
            {
              teclaEspacio = true;
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
            }
            //Flecha arriba
            if(event.key.code == 73)
            {
              flechaArriba = true;
            }
              
            //Flecha abajo
            if(event.key.code == 74)
            {
              flechaAbajo = true;
            }
            //Flecha derecha
            if(event.key.code == 72)
            {
              flechaDerecha = true;
            }
            //Flecha izquierda
            if(event.key.code == 71)
            {
              flechaIzquierda = true;
            }
            
            /*Controles jugador 2*/
            
            if(play == 2)
            {
                //Colocacion de una bomba pulsando tecla E.
              if(event.key.code == 4)
              {
                teclaE = true;
                //Si el jugador no tiene una bomba ya puesta, le permitimos poner una.
                if(jugador2->getPuesta() == false)
                {
                  //Nos guardamos el segundo exacto en el que se pone la bomba.
                  tiemposBomba.push_back(temporizador.getElapsedTime().asSeconds());
                  //Creamos una instancia de bomba.
                  Bomba bomba(jugador2->getSprite()->getPosition().x, jugador2->getSprite()->getPosition().y);
                  bomba.setPropietario(jugador2->getIdentificador());
                  //Lo añadimos al vector de bombas.
                  totalBombas.push_back(bomba);

                  jugador2->setPuesta(true);
                }
              }
              //W arriba
              if(event.key.code == 22)
              {
                teclaW = true;
              }
              //S abajo
              if(event.key.code == 18)
              {
                teclaS = true;
              }

              //D derecha
              if(event.key.code == 3)
              {
                teclaD = true;
              }

              //A izquierda
              if(event.key.code == 0)
              {
                teclaA = true;
              }
            }

            break;
        //AL SOLTAR LA TECLA
        case sf::Event::KeyReleased:

          /*Controles jugador 1*/

            //Colocacion de una bomba pulsando tecla ESPACIO.
            if(event.key.code == 57)
            {
              teclaEspacio = false;
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
            }
            //Flecha arriba
            if(event.key.code == 73)
            {
              flechaArriba = false;
            }
              
            //Flecha abajo
            if(event.key.code == 74)
            {
              flechaAbajo = false;
            }
            //Flecha derecha
            if(event.key.code == 72)
            {
              flechaDerecha = false;
            }
            //Flecha izquierda
            if(event.key.code == 71)
            {
              flechaIzquierda = false;
            }
            
            /*Controles jugador 2*/
            
            if(play == 2)
            {
                //Colocacion de una bomba pulsando tecla E.
              if(event.key.code == 4)
              {
                teclaE = false;
                //Si el jugador no tiene una bomba ya puesta, le permitimos poner una.
                if(jugador2->getPuesta() == false)
                {
                  //Nos guardamos el segundo exacto en el que se pone la bomba.
                  tiemposBomba.push_back(temporizador.getElapsedTime().asSeconds());
                  //Creamos una instancia de bomba.
                  Bomba bomba(jugador2->getSprite()->getPosition().x, jugador2->getSprite()->getPosition().y);
                  bomba.setPropietario(jugador2->getIdentificador());
                  //Lo añadimos al vector de bombas.
                  totalBombas.push_back(bomba);

                  jugador2->setPuesta(true);
                }
              }
              //W arriba
              if(event.key.code == 22)
              {
                teclaW = false;
              }
              //S abajo
              if(event.key.code == 18)
              {
                teclaS = false;
              }

              //D derecha
              if(event.key.code == 3)
              {
                teclaD = false;
              }

              //A izquierda
              if(event.key.code == 0)
              {
                teclaA = false;
              }
            }

        break;

           
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
            crearAdns(mapas[lvlactual],dif+2);
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
            // UN JUGADOR UPDATEAN ELLOS SUS COLISIONES Y SUS HUDS
              if(play==1){
                if (jugador1->getmatando())//comprueba los enemigos muertos y los reemplaza
                {
                  std::cout<<"matao"<<std::endl;
                  todosno(time,jugador1);//CONTROLA LA APARICION DE LOS DINOSAURIOS
                }
                hud1->Update(jugador1);
                    Bomba::update(temporizador,*jugador1,totalBombas,totalExplosiones,tiemposBomba,tiemposExplosiones);
                    Colisiones::update(temporizador,dinosaurios,*jugador1,totalExplosiones,*mapas[lvlactual],todoSprites,adnSprites,adns); 
                if(jugador1->getVidas()==0){//SI TIENES 0 VIDAS PIERDES 
                  finjuego(4);std::cout<<"pierdes"<<endl;
                }else{
                    // Mover los dinosaurios con la IA
                    IA ia; // Genera una ia con cada iteracion
                    ia.movimientoDinos(dinosaurios, _cont,todoSprites, *mapas[lvlactual],time); // Permite mover a los dinosaurios
                      _cont++; // Contador de iteraciones del programa
                    //Detecta si le tiene que quitar vida a jugadores y dinosaurios si colisionan con una explosion.

                  if(adns.size()==0){//SI NO QUEDAN ADNS SE TERMINA EL NIVEL
                    std::cout<<"no quedan adns por recoger"<<std::endl;
                    if(lvlactual<mapas.size()){
                      mapas[lvlactual]->terminar();
                    }
                  }
                }
              }else if(play==2)// DOS JUGADORES UPDATEAN ELLOS SUS COLISIONES Y SUS HUDS
              {
                if (jugador1->getmatando())//comprueba los enemigos muertos y los reemplaza
                {
                  std::cout<<"matao"<<std::endl;
                  todosno(time,jugador1);//METER TIME
                }
                if (jugador2->getmatando())//comprueba los enemigos muertos y los reemplaza
                {
                  std::cout<<"matao"<<std::endl;
                  todosno(time,jugador2);//METER TIME
                }
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
                    ia.movimientoDinos(dinosaurios, _cont,todoSprites, *mapas[lvlactual],time); // Permite mover a los dinosaurios
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
        //MOVIMIENTO DE LOS PERSONAJES
        //J1
        if(flechaArriba)
        {
          jugador1->mover(0,time);
          Colisiones::crearColisiones(*jugador1->getSprite(),todoSprites,0,jugador1->getVelocidad(),time);//CREAR NUEVA COLISION
          Colisiones::colisionesBombas(*jugador1,totalBombas,0,time);//COMPROBAR COLISION CON BOMBAS COLOCADAS
        }
        if(flechaAbajo)
        {
          jugador1->mover(1,time);
          Colisiones::crearColisiones(*jugador1->getSprite(),todoSprites,1,jugador1->getVelocidad(),time);
          Colisiones::colisionesBombas(*jugador1,totalBombas,1,time);
        }
        if(flechaDerecha)
        {
          jugador1->mover(2,time);
          Colisiones::crearColisiones(*jugador1->getSprite(),todoSprites,2,jugador1->getVelocidad(),time);
          Colisiones::colisionesBombas(*jugador1,totalBombas,2,time);
        }
        if(flechaIzquierda)
        {
          jugador1->mover(3,time);
          Colisiones::crearColisiones(*jugador1->getSprite(),todoSprites,3,jugador1->getVelocidad(),time);
          Colisiones::colisionesBombas(*jugador1,totalBombas,3,time);
        }
        
        //J2
        if(teclaW)
        {
          jugador2->mover(0,time);//MOVER
          Colisiones::crearColisiones(*jugador2->getSprite(),todoSprites,0,jugador2->getVelocidad(),time);//CREAR NUEVA COLISION
          Colisiones::colisionesBombas(*jugador2,totalBombas,0,time);//COMPROBAR COLISION CON BOMBAS COLOCADAS
        }
        if(teclaS)
        {
          jugador2->mover(1,time);
          Colisiones::crearColisiones(*jugador2->getSprite(),todoSprites,1,jugador2->getVelocidad(),time);
          Colisiones::colisionesBombas(*jugador2,totalBombas,1,time);
        }
        if(teclaD)
        {
          jugador2->mover(2,time);
          Colisiones::crearColisiones(*jugador2->getSprite(),todoSprites,2,jugador2->getVelocidad(),time);
          Colisiones::colisionesBombas(*jugador2,totalBombas,2,time);
        }
        if(teclaA)
        {
          jugador2->mover(3,time);
          Colisiones::crearColisiones(*jugador2->getSprite(),todoSprites,3,jugador2->getVelocidad(),time);
          Colisiones::colisionesBombas(*jugador2,totalBombas,3,time);
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

void Mundo::renicio(){
      //reiniciar el mundo, TODO A 0 Y BORRAR MAPAS
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
        hud1->draw(window,jugador1);
        jugador1->draw(window);  
      }else if(play==2)
      {
        jugador1->draw(window);  
        hud1->draw(window,jugador1);
        jugador2->draw(window);  
        hud2->draw(window,jugador2);
      }
  }
}
