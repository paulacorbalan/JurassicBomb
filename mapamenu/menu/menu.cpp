#include "menu.h"


Menu* Menu::pinstance=0;

  Menu* Menu::Instance() {
    if(pinstance==0){
      pinstance=new Menu;
        std::cout<<"menuinstance"; 
    }
    return pinstance;
  }

void Menu::Inicializar() {
  std::cout<<"menuiniciado\n";
  Cargarecursos(); 
}


void Menu::Update(sf::Event event,sf::RenderWindow &window) {

  std::cout<<"menuupdate\n";
    switch (event.type) {
    ///////////////Scroll
          case sf::Event::MouseWheelScrolled:
            std::cout << event.mouseWheelScroll.delta << std::endl;
          break;
              //////////////Clic del raton
          case sf::Event::MouseButtonPressed:


            if(sf::Mouse::Left == event.key.code){
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

              if(menus==0 && !jugando){
                //posicion raton respecto ventana

                    //comprobacion encima de que sprite esta          
                          if(splayerImage.getGlobalBounds().contains(mousePos.x,mousePos.y)){
                            menus=1;
                            players=1;
                            std::cout << "un jugador" << std::endl;
                          }
                          if(mplayerImage.getGlobalBounds().contains(mousePos.x,mousePos.y)){
                            menus=1;
                            players=2;
                            std::cout << "players=2;" << std::endl;
                          }
                          if(exitImage.getGlobalBounds().contains(mousePos.x,mousePos.y)){
                            window.close();
                            std::cout << "exit" << std::endl;
                          }

              }else if(menus==1 && !jugando){
                                                                                  //ChangeState(Contexto::Instance(),Menu::Instance()); CAMBIAR ESTADOS
                    //comprobacion encima de que sprite esta          
                          if(facilImage.getGlobalBounds().contains(mousePos.x,mousePos.y)){
                          dificulty=0;
                            std::cout << "facil" << std::endl;
                          }
                          if(normalImage.getGlobalBounds().contains(mousePos.x,mousePos.y)){
                            dificulty=1;
                            std::cout << "normal" << std::endl;
                          }
                          if(dificilImage.getGlobalBounds().contains(mousePos.x,mousePos.y)){
                            dificulty=2;
                            std::cout << "dificil" << std::endl;
                          }
                          if(atrasImage.getGlobalBounds().contains(mousePos.x,mousePos.y)){
                            menus=0;
                            std::cout << "atras" << std::endl;
                          }
                          if(playImage.getGlobalBounds().contains(mousePos.x,mousePos.y)){
                            jugando=true;
                            std::cout << "jugar" << std::endl;
                          }
                          if(menosImage.getGlobalBounds().contains(mousePos.x,mousePos.y)){
                            if(lvls<10 && lvls>1){
                            lvls--;
                            }
                            std::cout << "-1 " << lvls << std::endl;
                              cadena = std::to_string(lvls);
                                texto.setString(cadena);
                          }
                          if(plusImage.getGlobalBounds().contains(mousePos.x,mousePos.y)){
                            if(lvls<9 && lvls>0){
                            lvls++;
                            }
                            std::cout << "+1 "<< lvls << std::endl;
                              cadena = std::to_string(lvls);
                                texto.setString(cadena);
                          }

              }else if(jugando && gpause){
                          if(pausaImage.getGlobalBounds().contains(mousePos.x,mousePos.y)){
                          gpause=false;
                            std::cout << "quita pausa" << std::endl;
                          }
                          if(exitImage.getGlobalBounds().contains(mousePos.x,mousePos.y)){
                            window.close();
                            std::cout << "exit" << std::endl;
                          }
              }
                  std::cout << "clic izq" << std::endl;
            }
          //////////Se pulsó una tecla, imprimo su codigo
          case sf::Event::KeyPressed:

            ///Verifico si se pulsa alguna tecla de movimiento
            switch (event.key.code) {

            //Mapeo del cursor
          
              case sf::Keyboard::Right:
              if(!gpause && jugando){
                sprite.setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
                //Escala por defecto
                sprite.setScale(1, 1);
                sprite.move(kVel, 0);
              }
                break;

              case sf::Keyboard::Left:
              if(!gpause && jugando){
                sprite.setTextureRect(sf::IntRect(0 * 75, 2 * 75, 75, 75));
                //Reflejo vertical
                sprite.setScale(-1, 1);
                sprite.move(-kVel, 0);
              }
                break;

              case sf::Keyboard::Up:
              if(!gpause && jugando){
                sprite.setTextureRect(sf::IntRect(0 * 75, 3 * 75, 75, 75));
                sprite.move(0, -kVel);           
                }
                break;

              case sf::Keyboard::Down:
              if(!gpause && jugando){
                sprite.setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));
                sprite.move(0, kVel);
              }
                break;

            //PAUSA
            case sf::Keyboard::Return:
            if(gpause && jugando){
              std::cout << "quita pausa" << std::endl;
              gpause=false;
              }else if(!gpause && jugando){
                std::cout << "pon pausa" << std::endl;
              gpause=true;
              }
              break;

            //Cualquier tecla desconocida se imprime por pantalla su código
            default:
              std::cout << " menu " << menus << " players " << players << " dificultad "<< dificulty << " jugando " << jugando << " code " << event.key.code << std::endl;
              break;
            }
          }

}

void Menu::Draw(sf::RenderWindow &window) {

    //dibujar cosas
      if (jugando && !gpause){
              window.draw(sprite);
      }else if(jugando && gpause){
              window.draw(pausaImage);
              window.draw(exitImage);
      }

      if (menus==1 && !jugando){
              window.draw(facilImage);
              window.draw(normalImage);
              window.draw(dificilImage);
              window.draw(atrasImage);
              window.draw(playImage);
              window.draw(plusImage);
              window.draw(menosImage);
              window.draw(nivelesImage);
              window.draw(texto);
      }
        if(menus==0 && !jugando){
              window.draw(splayerImage);
              window.draw(mplayerImage);
              window.draw(exitImage);

  //std::cout<<"menudraw\n";
        }

}


void Menu::Cargarecursos(){
   //background
   std::cout<<"menucargados";
            if ( !background.loadFromFile( "resources/background.jpg" ) )
              std::cout << "Error: Could not display background image" << std::endl;
            backgroundImage.setTexture( background );

          //Cargo la imagen donde reside la textura del sprite
           //Y creo el spritesheet a partir de la imagen anterior
              sf::Texture tex;
              if (!tex.loadFromFile("resources/sprites.png")) {
                std::cerr << "Error cargando la imagen sprites.png";
              }

            sf::Sprite aux(tex);
            //Le pongo el centroide donde corresponde
            aux.setOrigin(75 / 2, 75 / 2);
            //Cojo el sprite que me interesa por defecto del sheet
            aux.setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));

            // Lo dispongo en el centro de la pantalla
            aux.setPosition(320, 240);

            sprite=aux;

                  //pausa
                  if ( !pausa.loadFromFile( "resources/pausa.png" ) )
                  std::cout << "Error: Could not display pausa image" << std::endl;

                  pausaImage.setTexture( pausa );
                  pausaImage.setOrigin(pausa.getSize().x*0.5, pausa.getSize().y*0.5);
                  pausaImage.setPosition(width*1/2, height*2/6);  

                  //play
                  if ( !play.loadFromFile( "resources/play.png" ) )
                  std::cout << "Error: Could not display play image" << std::endl;

                  playImage.setTexture( play );
                  playImage.setOrigin(play.getSize().x*0.5, play.getSize().y*0.5);
                  playImage.setPosition(width*3/4, height*4/6); 

                  //atras
                  if ( !atras.loadFromFile( "resources/atras.png" ) )
                  std::cout << "Error: Could not display atras image" << std::endl;

                  atrasImage.setTexture( atras );
                  atrasImage.setOrigin(atras.getSize().x*0.5, atras.getSize().y*0.5);
                  atrasImage.setPosition(width/2, height*5/6);
                  //niveles
                  
                  

                  if ( !niveles.loadFromFile( "resources/niveles.png" ) )
                  std::cout << "Error: Could not display niveles image" << std::endl;

                  nivelesImage.setTexture( niveles );
                  nivelesImage.setOrigin(niveles.getSize().x*0.5, niveles.getSize().y*0.5);
                  nivelesImage.setPosition(width*6/8, height*2/6);
                  //menos
                  if ( !menos.loadFromFile( "resources/menos.png" ) )
                  std::cout << "Error: Could not display menos image" << std::endl;

                  menosImage.setTexture( menos );
                  menosImage.setOrigin(menos.getSize().x*0.5, menos.getSize().y*0.5);
                  menosImage.setPosition(width*5/8, height*3/6);
                  //mas
                  if ( !plus.loadFromFile( "resources/plus.png" ) )
                  std::cout << "Error: Could not display plus image" << std::endl;

                  plusImage.setTexture( plus );
                  plusImage.setOrigin(plus.getSize().x*0.5, plus.getSize().y*0.5);
                  plusImage.setPosition(width*7/8, height*3/6);

          //texto niveles
            // Creamos un objeto fuente
            
            // Intentamos cargarla
            if (!fuente.loadFromFile("resources/arial.ttf"))
            {
              
                  std::cout << "Error: Could not display font" << std::endl;
            }
            // Creamos un objeto texto
            
            // Creamos un objeto String
            
            // Damos un valor a la cadena
            cadena = std::to_string(3);
            // Asignamos la cadena al texto
            texto.setString(cadena);
            // Asignamos la fuente que hemos cargado al texto
            texto.setFont(fuente);
            // Tamaño de la fuente
            texto.setCharacterSize(75);
            // Posición del texto
            texto.setPosition(-15+(plusImage.getPosition().x+menosImage.getPosition().x)/2,-50+(plusImage.getPosition().y+menosImage.getPosition().y)/2);
            texto.setColor(sf::Color::Red);


                  //facil
                  if ( !facil.loadFromFile( "resources/facil.png" ) )
                  std::cout << "Error: Could not display facil image" << std::endl;

                  facilImage.setTexture( facil );
                  facilImage.setOrigin(facil.getSize().x*0.5, facil.getSize().y*0.5);
                  facilImage.setPosition(width*1/3, height*2/6);

                  //normal


                  if ( !normal.loadFromFile( "resources/normal.png" ) )
                  std::cout << "Error: Could not display normal image" << std::endl;

                  normalImage.setTexture( normal );
                  normalImage.setOrigin(normal.getSize().x*0.5, normal.getSize().y*0.5);
                  normalImage.setPosition(width*1/3, height*3/6);
                  //dificil
                  if ( !dificil.loadFromFile( "resources/dificil.png" ) )
                  std::cout << "Error: Could not display dificil image" << std::endl;

                  dificilImage.setTexture( dificil );
                  dificilImage.setOrigin(dificil.getSize().x*0.5, dificil.getSize().y*0.5);
                  dificilImage.setPosition(width*1/3, height*4/6);
                  //un jugador
                  if ( !splayer.loadFromFile( "resources/splayer.png" ) )
                  std::cout << "Error: Could not display splayer image" << std::endl;

                  splayerImage.setTexture( splayer );
                  splayerImage.setOrigin(splayer.getSize().x*0.5, splayer.getSize().y*0.5);
                  splayerImage.setPosition(width/2, height*2/6);
                  //multijugador
                  if ( !mplayer.loadFromFile( "resources/mplayer.png" ) )
                  std::cout << "Error: Could not display mplayer image" << std::endl;

                  mplayerImage.setTexture( mplayer );
                  mplayerImage.setOrigin(mplayer.getSize().x*0.5, mplayer.getSize().y*0.5);
                  mplayerImage.setPosition(width/2, height*3/6);
                  //salir


                  if ( !exit.loadFromFile( "resources/exit.png" ) )
                  std::cout << "Error: Could not display exit image" << std::endl;
                  
                  exitImage.setTexture( exit );
                  exitImage.setOrigin(exit.getSize().x*0.5, exit.getSize().y*0.5);
                  exitImage.setPosition(width/2, height*4/6);


}





