#include "jugador.h"
#include <iostream>

Jugador::Jugador(int numero)
{
    
   /* if (!textura->loadFromFile("resources/sprites.png")) {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }*/

    sprite = new Sprite("resources/sprites.png");
    sprite->cargaTextura(textura,"resources/sprites.png");
    sprite->estableceOrigen(75,75);
    sprite->recortaSprite(0,0,75,75);
    sprite->escala(0.35,0.35);
    if (numero==1)
    {
            sprite->posiciona(160,113);
            
    }else
    {
            sprite->posiciona(192,117);
    }
    
    

    identificador = numero;
    kVel = 2;
}


void Jugador::draw(sf::RenderWindow &window)
{
    sprite->dibujaSprite(window);
}

void Jugador::mover(int direccion)
{
    switch (direccion)
    {

    //Arriba
    case 0:
        sprite->recortaSprite(0,3,75,75);
        
        sprite->mueve(0, -kVel);
        break;
    //Abajo
    case 1:
        sprite->recortaSprite(0,0,75,75);
        sprite->mueve(0, kVel);
        break;
    //Derecha
    case 2:
        sprite->recortaSprite(0,2,75,75);
        //Escala por defecto
        sprite->escala(0.35,0.35);
        sprite->mueve(kVel, 0);
        break;
    //Izquierda
    case 3:
        sprite->recortaSprite(0,2,75,75);
        //Reflejo vertical
        sprite->escala(-0.35, 0.35);
        sprite->mueve(-kVel, 0);
        break;
    }

}



