#include "Tile.h"
#include <iostream>
Motor* moto=Motor::Instance();
Tile::Tile() {
Cargarecursos();
}

void Tile::Cargarecursos(){

  //Cargo la imagen donde reside la textura del sprite

  
  vida1=new Sprite("resources/corazon rojo.png");
  vida2=new Sprite("resources/corazon rojo.png");
  vida3=new Sprite("resources/corazon rojo.png");

  letranumero=new Sprite("resources/letrasnumeros.png");

  contador=new Sprite("resources/contador.png");
     
  //Y creo el spritesheet a partir de la imagen anterior
            if (!fuente.loadFromFile("resources/arial.ttf"))
            {              
                  std::cout << "Error: Could not display font" << std::endl;
            }    
            // Damos un valor a la cadena
            cadena = "0"+std::to_string(min)+":"+std::to_string(seg);
            // Asignamos la cadena al 
            moto->estableceCadena(texto,cadena);
           
            // Asignamos la fuente que hemos cargado al texto
             moto->estableceFuente(texto,fuente);
            // Tamaño de la fuente
            moto->escalaTamanyoLetra(texto,20);
            // Posición del texto
            moto->posicionaTexto(texto,295,20);
            moto->seleccionaColor(texto,sf::Color::Red);
  
  //Le pongo el centroide donde corresponde
  vida1->estableceOrigen(16,16);
  vida2->estableceOrigen(16,16);
  vida3->estableceOrigen(16,16);
  

   /*
    //sf::Sprite gameover(tex3);
    gameover.setOrigin(8 / 2,15 / 2);
    */
  //barra de vida
  vida1->recortaSprite(0,3,16,16);
  vida2->recortaSprite(0,3,16,16);
  vida3->recortaSprite(0,3,16,16);

 vida2->escalaSprite(2,2);
 vida3->escalaSprite(2,2);
 vida1->escalaSprite(2,2);

  

  // Lo dispongo en el centro de la panta
  vida1->posiciona(40,40);
  vida2->posiciona(71,40);
  vida3->posiciona(102,40);

 
}
void Tile::draw(sf::RenderWindow &window){
  if(vidas==1){
    vida1->dibujaSprite(window);
  }else if(vidas==2){
    vida1->dibujaSprite(window);
    vida2->dibujaSprite(window);
  }else if(vidas==3){
    vida1->dibujaSprite(window);
    vida2->dibujaSprite(window);
    vida3->dibujaSprite(window);
  }else if(vidas==0)
  {
    /* GAMEOVER HABER ESTUDIAO */
  }
    moto->dibujaText(texto,window);
}
void Tile::Update(Jugador* j){
    vidas=j->getVidas();
    if(!terminada){
        int s2=segundero;
        segundero=moto->obtentiempoensegundos(temporizador);
        if(s2<segundero){             
            seg-=1;
                std::cout<<seg<<"\n";
                if(seg<10){
                    texto.setString("0"+std::to_string(min)+":0"+std::to_string(seg));
                }else{
                     texto.setString("0"+std::to_string(min)+":"+std::to_string(seg));
                }
            if(seg<=0){
                if(min==0){
                    terminada=true;
                }
                min--;
                seg=59;
            }
        }
    }
}