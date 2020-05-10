#include "menu.h"
#include "juego.h"
#include "motor.h"



Menu* Menu::pinstance=0;
Motor* m=Motor::Instance();
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


void Menu::Update(sf::RenderWindow &window) {


    
}
void Menu::Event(sf::Event event,sf::RenderWindow &window){
      switch (event.type) {
        case sf::Event::Closed:
          Contexto::Instance()->Quit();
          m->cierraVentana(window);
        break;
      ///////////////Scroll
            case sf::Event::MouseWheelScrolled:
              std::cout << event.mouseWheelScroll.delta << std::endl;
            break;
                //////////////Clic del raton
            case sf::Event::MouseButtonPressed:

              if(sf::Mouse::Left == event.key.code){
                      sf::Vector2i mousePos=sf::Mouse::getPosition(window);
                      //sf::Vector2i mousePos = m->capturaPosicionRaton(window);

                if(menus==0 && !jugando){
                  //posicion raton respecto ventana

                      //comprobacion encima de que sprite esta          
                            if(splayerImage->contiene(mousePos.x,mousePos.y)){
                              menus=1;
                              players=1;
                              std::cout << "un jugador" << std::endl;
                            }
                            if(mplayerImage->contiene(mousePos.x,mousePos.y)){
                              menus=1;
                              players=2;
                              std::cout << "players=2;" << std::endl;
                            }
                            if(exitImage->contiene(mousePos.x,mousePos.y)){
                              m->cierraVentana(window);
                              std::cout << "exit" << std::endl;
                            }

                }else if(menus==1 && !jugando){
                                                                                    //ChangeState(Contexto::Instance(),Menu::Instance()); CAMBIAR ESTADOS
                      //comprobacion encima de que sprite esta          
                            if(facilImage->contiene(mousePos.x,mousePos.y)){
                            dificulty=0;
                              std::cout << "facil" << std::endl;
                            }
                            if(normalImage->contiene(mousePos.x,mousePos.y)){
                              dificulty=1;
                              std::cout << "normal" << std::endl;
                            }
                            if(dificilImage->contiene(mousePos.x,mousePos.y)){
                              dificulty=2;
                              std::cout << "dificil" << std::endl;
                            }
                            if(atrasImage->contiene(mousePos.x,mousePos.y)){
                              menus=0;
                              std::cout << "atras" << std::endl;
                            }
                            if(playImage->contiene(mousePos.x,mousePos.y)){
                              //jugando=true; juego stado             CAMBIAR ESTADO
                            std::cout << "jugar" << std::endl;
                           
                            ChangeState(Contexto::Instance(),Juego::Instance());
                            }
                            if(menosImage->contiene(mousePos.x,mousePos.y)){
                              if(lvls<10 && lvls>1){
                                lvls--;
                              }
                              std::cout << "-1 " << lvls << std::endl;
                                cadena = std::to_string(lvls);
                                m->estableceCadena(texto,cadena);
                                  
                            }
                            if(plusImage->contiene(mousePos.x,mousePos.y)){
                              if(lvls<9 && lvls>0){
                              lvls++;
                              }
                              std::cout << "+1 "<< lvls << std::endl;
                                cadena = std::to_string(lvls);
                                m->estableceCadena(texto,cadena);
                                 
                            }

                } 
                else if(menus==3 && !jugando){	
	                  //GANADO	108	                }
	                  std::cout<<"has ganado"<<std::endl;		
	                  menus=0;		
	                  lvls=1;		
                }
                    std::cout << "clic izq" << std::endl;
              }
            //////////Se pulsó una tecla, imprimo su codigo
            case sf::Event::KeyPressed:
              ///Verifico si se pulsa alguna tecla de movimiento
              switch (event.key.code) {

                
              //Cualquier tecla desconocida se imprime por pantalla su código
              default:
                std::cout << " menu " << menus << " players " << players << " dificultad "<< dificulty << " jugando " << jugando << " code " << event.key.code << std::endl;
                break;
              }
            }
      



}
void Menu::Draw(sf::RenderWindow &window) {
    //dibujar cosas
    backgroundImage->dibujaSprite(window);
      if (jugando && !gpause){
        sprite->dibujaSprite(window);
      }else if(jugando && gpause){
        pausaImage->dibujaSprite(window);
        exitImage->dibujaSprite(window);
      }

      if (menus==1 && !jugando){
            facilImage->dibujaSprite(window);
            normalImage->dibujaSprite(window);
            dificilImage->dibujaSprite(window);
            atrasImage->dibujaSprite(window);
            playImage->dibujaSprite(window);
            plusImage->dibujaSprite(window);
            menosImage->dibujaSprite(window);
            nivelesImage->dibujaSprite(window);
            m->dibujaText(texto,window);
            
             
      }
        if(menus==0 && !jugando){
          splayerImage->dibujaSprite(window);
          mplayerImage->dibujaSprite(window);
          exitImage->dibujaSprite(window);
             

  
        }
        if(menus==3 && !jugando){
          ganarImage->dibujaSprite(window);
          }
}
void Menu::lvltxt(){

            // Damos un valor a la cadena
            cadena = std::to_string(1);
            // Asignamos la cadena al texto
            m->estableceCadena(texto,cadena);
            // Asignamos la fuente que hemos cargado al texto
            m->estableceFuente(texto,fuente);
            // Tamaño de la fuente
            m->escalaTamanyoLetra(texto,75);
            // Posición del texto
            m->posicionaTexto(texto,-15+(plusImage->getPosX()+menosImage->getPosX())/2,-50+(plusImage->getPosY()+menosImage->getPosY())/2);
//            texto.setPosition(-15+(plusImage.getPosition().x+menosImage.getPosition().x)/2,-50+(plusImage.getPosition().y+menosImage.getPosition().y)/2);
            m->seleccionaColor(texto,sf::Color::Red);
}
void Menu::reinicio(){
lvls=1;
menus=3;//PONER EN 3 PARA LA PANTALLA DE VICTORIA
dificulty=0;

lvltxt();
}

void Menu::Cargarecursos(){
   //background
   std::cout<<"menucargados";
  // backgroundImage->cargaTextura(background,"resources/fondo2.png");
            backgroundImage=new Sprite("resources/fondo2.png");
            backgroundImage->estableceOrigen(backgroundImage->texturaX(background)*0.5,backgroundImage->texturaY(background)*0.5);
            backgroundImage->posiciona(width/2,height/2);
          //Cargo la imagen donde reside la textura del sprite
           //Y creo el spritesheet a partir de la imagen anterior
              //ganarImage->cargaTextura(ganar,"resources/ganar2.png");
             // ganarImage->estableceTextura(ganar);
             ganarImage=new Sprite("resources/ganar2.png");
              ganarImage->estableceOrigen(ganarImage->texturaX(ganar)*0.5,ganarImage->texturaY(ganar)*0.5);
              ganarImage->posiciona(width/2,height/2);
            Sprite* aux=new Sprite("resources/sprites.png");
            //Le pongo el centroide donde corresponde
            aux->estableceOrigen(75,75);
            //Cojo el sprite que me interesa por defecto del sheet
            aux->recortaSprite(0,0,75,75);

            // Lo dispongo en el centro de la pantalla
            aux->posiciona(320,240);

            sprite=aux;

                  //pausa
                  
                  pausaImage->cargaTextura(pausa,"resources/pausa.png");
                  pausaImage->estableceTextura(pausa);
                  pausaImage->estableceOrigen(pausaImage->texturaX(pausa) *0.5,pausaImage->texturaY(pausa)*0.5);
                  pausaImage->posiciona(width*1/2,height*2/6);
                

                  //play
                  
                  playImage->cargaTextura(play,"resources/play.png");
                  playImage->estableceTextura(play);
                  playImage->estableceOrigen(playImage->texturaX(play) *0.5,playImage->texturaY(play)*0.5);
                  playImage->posiciona(width*3/4,height*4/6);
                 

                  //atras
                  atrasImage->cargaTextura(atras,"resources/atras.png");
                  atrasImage->estableceTextura(atras);
                  atrasImage->estableceOrigen(atrasImage->texturaX(atras) *0.5,atrasImage->texturaY(atras)*0.5);
                  atrasImage->posiciona(width/2,height*5/6);

                
                  //niveles
                  
                  

                  nivelesImage->cargaTextura(niveles,"resources/niveles.png");
                  nivelesImage->estableceTextura(niveles);
                  nivelesImage->estableceOrigen(nivelesImage->texturaX(niveles) *0.5,nivelesImage->texturaY(niveles)*0.5);
                  nivelesImage->posiciona(width*6/8,height*2/6);


                  //menos
                  menosImage->cargaTextura(menos,"resources/menos.png");
                  menosImage->estableceTextura(menos);
                  menosImage->estableceOrigen(menosImage->texturaX(menos) *0.5,menosImage->texturaY(menos)*0.5);
                  menosImage->posiciona(width*5/8,height*3/6);
                  //mas
                  plusImage->cargaTextura(plus,"resources/plus.png");
                  plusImage->estableceTextura(plus);
                  plusImage->estableceOrigen(plusImage->texturaX(plus) *0.5,plusImage->texturaY(plus)*0.5);
                  plusImage->posiciona(width*7/8,height*3/6);

              

          //texto niveles
            // Creamos un objeto fuente
            
            // Intentamos cargarla
            
                  m->cargaFuente(fuente,"resources/arial.ttf");
                  lvltxt();
                  //facil
                  
                  facilImage->cargaTextura(facil,"resources/facil.png");
                  facilImage->estableceTextura(facil);
                  facilImage->estableceOrigen(facilImage->texturaX(facil) *0.5,facilImage->texturaY(facil)*0.5);
                  
                  facilImage->posiciona(width*1/3,height*2/6);

                 

                  //normal


                  normalImage->cargaTextura(normal,"resources/normal.png");
                  normalImage->estableceTextura(normal);
                  normalImage->estableceOrigen(normalImage->texturaX(normal) *0.5,normalImage->texturaY(normal)*0.5);
                  normalImage->posiciona(width*1/3,height*3/6);
                
                  //dificil
                  
                  dificilImage->cargaTextura(dificil,"resources/dificil.png");
                  dificilImage->estableceTextura(dificil);
                  dificilImage->estableceOrigen(dificilImage->texturaX(dificil) *0.5,dificilImage->texturaY(dificil)*0.5);
                  dificilImage->posiciona(width*1/3,height*4/6);

                  
                  //un jugador
                 
                  splayerImage->cargaTextura(splayer,"resources/splayer.png");
                  splayerImage->estableceTextura(splayer);
                  splayerImage->estableceOrigen(splayerImage->texturaX(splayer) *0.5,splayerImage->texturaY(splayer)*0.5);
                  splayerImage->posiciona(width/2,height*2/6);

                  
                  //multijugador
                
                  mplayerImage->cargaTextura(mplayer,"resources/mplayer.png");
                  mplayerImage->estableceTextura(mplayer);
                  mplayerImage->estableceOrigen(mplayerImage->texturaX(mplayer) *0.5,mplayerImage->texturaY(mplayer)*0.5);
                  mplayerImage->posiciona(width/2,height*3/6);

               
                  //salir


                  
                  exitImage->cargaTextura(exit,"resources/exit.png");
                  exitImage->estableceTextura(exit);
                  exitImage->estableceOrigen(exitImage->texturaX(exit) *0.5,exitImage->texturaY(exit)*0.5);
                  exitImage->posiciona(width/2,height*4/6);
                 
}
int Menu::GetLvls(){
  return lvls;
}

int Menu::GetDif(){
  return dificulty;
}




