#include "bombas.h"
#include <iostream>

//Esto es un comentariazo.
Bomba::Bomba(float x, float y)
{
    coordenadaX = x;
    coordenadaY = y;
    activarColision = false;

    //Cargo la textura de las explosiones para usarlas posteriormente.
    texplosiones = new sf::Texture();

    if (!texplosiones->loadFromFile("resources/explosion.png")) {
        std::cerr << "Error cargando la imagen explosion.png";
        exit(0);
    }

    //Cargo la textura y creo el sprite de la bomba.
    tbomba = new sf::Texture();
    if (!tbomba->loadFromFile("resources/bomba.png")) {
        std::cerr << "Error cargando la imagen bomba.png";
        exit(0);
    }

    sbomba.setTexture(*tbomba);
    sbomba.setTextureRect(sf::IntRect(0, 0, 410, 370));
    sbomba.setOrigin(410/2,370/2);
    sbomba.setPosition(x,y);
    sbomba.scale(0.15,0.15);
}

std::vector<sf::Sprite> Bomba::GenerarExplosion()
{
    std::vector<sf::Sprite> sprites;
    float x = getCoordenadaX();
    float y = getCoordenadaY();
    //Escala.
    float sc = 0.05;
    //Distancia separacion entre explosiones.
    int dsExp = 45;

    //Explosion central.
    sf::Sprite explosionCen(*texplosiones);
    explosionCen.setOrigin(840/2, 840/2);
    explosionCen.setTextureRect(sf::IntRect(0, 0, 900, 900));
    explosionCen.setPosition(x,y);
    explosionCen.setScale(sc,sc);
    sprites.push_back(explosionCen);

    //Explosion izquierda.
    sf::Sprite explosionIzq(*texplosiones);
    explosionIzq.setOrigin(840/2, 840/2);
    explosionIzq.setTextureRect(sf::IntRect(0, 0, 900, 900));
    explosionIzq.setPosition(x-dsExp,y);
    explosionIzq.setScale(sc,sc);
    sprites.push_back(explosionIzq);

    //Explosion derecha.
    sf::Sprite explosionDer(*texplosiones);
    explosionDer.setOrigin(840/2, 840/2);
    explosionDer.setTextureRect(sf::IntRect(0, 0, 900, 900));
    explosionDer.setPosition(x+dsExp,y);
    explosionDer.setScale(sc,sc);
    sprites.push_back(explosionDer);

    //Explosion arriba.
    sf::Sprite explosionAr(*texplosiones);
    explosionAr.setOrigin(840/2, 840/2);
    explosionAr.setTextureRect(sf::IntRect(0, 0, 900, 900));
    explosionAr.setPosition(x,y+dsExp);
    explosionAr.setScale(sc,sc);
    sprites.push_back(explosionAr);

    //Explosion abajo.
    sf::Sprite explosionAb(*texplosiones);
    explosionAb.setOrigin(840/2, 840/2);
    explosionAb.setTextureRect(sf::IntRect(0, 0, 900, 900));
    explosionAb.setPosition(x,y-dsExp);
    explosionAb.setScale(sc,sc);
    sprites.push_back(explosionAb);

    //Rellenamos la variable explosiones.
    setExplosion(sprites);

    return sprites;
}

//GETTERS

sf::Sprite Bomba::getBomba()
{
    return sbomba;
}

bool Bomba::getColision()
{
  return activarColision;
}

float Bomba::getCoordenadaX()
{
    return coordenadaX;
}

float Bomba::getCoordenadaY()
{
    return coordenadaY;
}

int Bomba::getPropietario()
{
    return propietario;
}

//SETTERS

bool Bomba::setColision()
{
  return activarColision = true;
}

void Bomba::setExplosion(std::vector<sf::Sprite> exp)
{
    for(int i = 0;i < 5; i++)
    {
        explosiones.push_back(exp[i]);
    }
}

void Bomba::setPropietario(int identificador)
{
    propietario = identificador;
}

