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

      //CREAR JUGADORES
      //Sustituir numJugadores por el id que le corresponde a este jugador.
      jugador = new Jugador(numjugadores);
    
      for(int a=0;a<lvls;a++){//cargar los mapas dependiendo del nombre
        string s="resources/mapas/"+to_string(dif)+"mapa"+to_string(a)+".tmx";
        std::cout<<s<<endl;
        std::cout<<"premap";
        Map* m=new Map(s);
        //Anadimos piedras y paredes del mapa.
        m->anadirVector(todoSprites);
        std::cout<<"prepush"<<endl;
        std::cout<< mapas.size()<<endl;
        mapas.push_back(m);//meter los mapas en el vector de mapas
        std::cout<< mapas.size()<<endl;
        std::cout<<"postpush"<<endl;
      }

      //CREAR DINOSAURIOS O QUIZA EN MAPA JUSTO ARRIBA
      // Textura por defecto del dinosaurio
      sf::Texture dino_abajo;
      if(!dino_abajo.loadFromFile("resources/dino_abajo.png")){
        std::cerr << "Error cargando dino_abajo.png";
        exit(0);
      }

      /* Generacion de los dos dinosaurios del nivel.
       * Se pueden generar mas en funcion del nivel, pero hay dos para este nivel
       * El tipo de dinosario es: 0: T-Rex | 1: Velociraptor | 2: Pterodactilo | 3: Triceratops 
       */

      Dinosaurio *dino1 = new Dinosaurio(); // Constructor del dinosaurio
      dino1->modifyTexture(dino_abajo); // Cambia la textura del dinosaurio
      dino1->setTipodino(0); // Establece el tipo de dinosario, la vida y la velocidad en funcion de su tipo
      dino1->modifyPosition(225,132); // Punto de spawn. Debe estar dentro del mapa
      dinosaurios.push_back(dino1); // Guardar en el vector de dinosaurios
      todoSprites.push_back(dino1->getSprite()); //Lo añadimos al vector de colisiones.

      Dinosaurio *dino2 = new Dinosaurio(); // Constructor del dinosaurio
      dino2->modifyTexture(dino_abajo); // Cambia la textura del dinosaurio
      dino2->setTipodino(1); // Establece el tipo de dinosario, la vida y la velocidad en funcion de su tipo
      dino2->modifyPosition(218,232); // Punto de spawn. Debe estar dentro del mapa
      dinosaurios.push_back(dino2); // Guardar en el vector de dinosaurios
      todoSprites.push_back(dino2->getSprite()); //Lo añadimos al vector de colisiones.
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
                Bomba bomba(jugador->getSprite()->getPosition().x, jugador->getSprite()->getPosition().y);
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
              Colisiones::crearColisiones(*jugador->getSprite(),todoSprites,0,jugador->getVelocidad());
              Colisiones::colisionesBombas(*jugador,totalBombas,0);
              break;
            //Abajo
            case 74:
              jugador->mover(1);
              Colisiones::crearColisiones(*jugador->getSprite(),todoSprites,1,jugador->getVelocidad());
              Colisiones::colisionesBombas(*jugador,totalBombas,1);
              break;
            //Derecha
            case 72:
              jugador->mover(2);
              Colisiones::crearColisiones(*jugador->getSprite(),todoSprites,2,jugador->getVelocidad());
              Colisiones::colisionesBombas(*jugador,totalBombas,2);
              break;
            //Izquierda
            case 71:
              jugador->mover(3);
              Colisiones::crearColisiones(*jugador->getSprite(),todoSprites,3,jugador->getVelocidad());
              Colisiones::colisionesBombas(*jugador,totalBombas,3);
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
    // Mover los dinosaurios con la IA
    IA ia; // Genera una ia con cada iteracion
    ia.movimientoDinos(dinosaurios, _cont,todoSprites); // Permite mover a los dinosaurios
      _cont++; // Contador de iteraciones del programa
    
    //Detecta si le tiene que quitar vida a jugadores y dinosaurios si colisionan con una explosion.
    //Colisiones::update(dinosaurios,*jugador,totalExplosiones); //EN DESARROLLO

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
      for(unsigned int i = 0;i < totalBombas.size();i++)
      {
        totalBombas[i].draw(window);
      }
      for(unsigned int i = 0;i < totalExplosiones.size();i++)
      {
        window.draw(totalExplosiones[i]);
      }
      for(unsigned int i=0; i < dinosaurios.size(); i++)
      {
        window.draw(*dinosaurios[i]->getSprite());
      }
      jugador->draw(window);
    }
 }