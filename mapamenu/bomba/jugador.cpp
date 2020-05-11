#include "jugador.h"
#include <iostream>

Jugador::Jugador(int numero)
{
    textura = new sf::Texture();
    if (!textura->loadFromFile("resources/jugadores.png")) {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }

    sprite = new sf::Sprite();
    sprite->setTexture(*textura);
    sprite->setOrigin(32 / 2, 32 / 2);
    sprite->setScale(0.9,0.9);
    if (numero==1)
    {
            sprite->setPosition(160, 113);

    sprite->setTextureRect(sf::IntRect(0 * 32, 0 * 32, 32, 32));
    }else
    {
            sprite->setPosition(192, 177);

    sprite->setTextureRect(sf::IntRect(0 * 32, 1 * 32, 32, 32));
    }

    setInicio(numero);
    identificador = numero;
    kVel = 100;
}


void Jugador::draw(sf::RenderWindow &window)
{
    window.draw(*sprite);
}

void Jugador::mover(int direccion,float times)
{
    switch (direccion)
    {

    //Arriba
    case 0:
        sprite->setTextureRect(sf::IntRect(3 * 32, (identificador-1) * 32, 32, 32));
        sprite->move(0, -kVel*times);
        break;
    //Abajo
    case 1:
        sprite->setTextureRect(sf::IntRect(0 * 32, (identificador-1) * 32, 32, 32));
        sprite->move(0, kVel*times);
        break;
    //Derecha
    case 2:
        sprite->setTextureRect(sf::IntRect(2 * 32, (identificador-1) * 32, 32, 32));
        //Escala por defecto
        sprite->move(kVel*times, 0);
        break;
    //Izquierda
    case 3:
        sprite->setTextureRect(sf::IntRect(1 * 32, (identificador-1) * 32, 32, 32));
        //Reflejo vertical
        sprite->move(-kVel*times, 0);
        break;
    }

}


