#include <SFML/Graphics.hpp>
#include <iostream>
#include "dinosaurio.h"

Dinosaurio::Dinosaurio(){ // Constructor por defecto
    _Tipodino = 1;
    _Vida = 2;
    _Speed = (int) 0.1*0.85;
}

Dinosaurio::Dinosaurio(int tipo, int vida, int velocidad){ // Constructor por defecto
    _Tipodino = tipo;
    _Vida = vida;
    _Speed = velocidad;
}

Dinosaurio::~Dinosaurio(){ // Destructor
}

Dinosaurio::Dinosaurio(sf::Texture& textura_dino){ // Constructor con textura
    _Sprite.setTexture(textura_dino);
    _Sprite.setPosition(320, 240);
    _Sprite.setOrigin(75 / 2, 75 / 2);

    // Cojo el sprite que me interesa por defecto del sheet
    _Sprite.setTextureRect(sf::IntRect(1 * 75, 0 * 75, 75, 75)); // SPrite concreto
}

void Dinosaurio::modifyVida(){ // Quitar un punto de vida si toca la bomba
    if(_Vida >= 1){
        _Vida =_Vida - 1;
    }
}

int Dinosaurio::getTipodino(){ // Devuelve tipo de dinosaurio
    return _Tipodino;
}

int generaRandom(int max){
    unsigned long j;
    srand( (unsigned)time(NULL) );

    int miRandom = (rand() % max) + 1;
    return miRandom;
}

int Dinosaurio::movimiento(){
    int direccion = 0;
    int contador = 0;
    int duracionMov = 2500;

    if(contador >= duracionMov){
        direccion = generaRandom(5);
        contador = 0;
    }

    if(direccion == 1){ // arriba
        _Sprite.setTextureRect(sf::IntRect(0 * 75, 3 * 75, 75, 75));
        _Sprite.move(0, -(_Speed));
    }
    else if(direccion == 2){ // abajo
        _Sprite.setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));
         _Sprite.move(0, _Speed);
    }
    else if(direccion == 3){ // derecha
        _Sprite.setScale(1,1);  // Sprite original
        _Sprite.setTextureRect(sf::IntRect(1 * 75, 2 * 75, 75, 75));
        _Sprite.move(_Speed, 0);
    }
    else if(direccion == 4){ // izquierda
        _Sprite.setScale(-1,1); // Sprite invertido  
        _Sprite.setTextureRect(sf::IntRect(1 * 75, 2 * 75, 75, 75));
        _Sprite.move(-(_Speed),0);
    }
    else { // no se mueve
    }

    contador ++;
}

int Dinosaurio::getVida(){ // Devolver vida
    return _Vida;
}

int Dinosaurio::getSpeed(){ // Devolver velocidad
    return _Speed;
}

// Hacer que el dinosaurio salte
void Dinosaurio::salto(int pos_mirando){
    if(_Tipodino == 2){ // Solo puede saltar el pterodactilo
        switch (pos_mirando){
        case 0: // Mirando arriba
            _Sprite.move(0, -(_Speed)*800);
            break;
        case 1: // Mirando abajo
            _Sprite.move(0, (_Speed)*800);
            break;
        case 2: // Mirando derecha
            _Sprite.move((_Speed)*800,0);
            break;
        case 3: // Mirando izquierda
            _Sprite.move((-_Speed)*800,0);
        default:
            break;
        }
    }
}

sf::FloatRect Dinosaurio::getHitbox(){ // FloatRect devuelve coordenada superior izq
    return _Sprite.getGlobalBounds(); // Coordenadas de entorno de SPrite
}