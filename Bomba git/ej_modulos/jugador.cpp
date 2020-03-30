#include "jugador.h"
#include <iostream>

Jugador::Jugador(int numero)
{
    textura = new sf::Texture();
    if (!textura->loadFromFile("resources/sprites.png")) {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }

    sprite.setTexture(*textura);
    sprite.setOrigin(75 / 2, 75 / 2);
    sprite.setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));
    sprite.setScale(0.5,0.5);
    sprite.setPosition(320, 240);

    identificador = numero;
}

sf::Sprite Jugador::getSprite()
{
    return sprite;
}

int Jugador::getIdentificador()
{
    return identificador;
}
