#include <SFML/Graphics.hpp>
#include <iostream>
#include "dinosaurio.h"

// Velocidades
float velocidad_normal = 0.1;
float velocidad_trex = velocidad_normal - (velocidad_normal*0.15); // -15% de la velocidad normal
float velocidad_velociraptor = velocidad_normal + (velocidad_normal*0.15); // +15% de la velocidad normal 

Dinosaurio::Dinosaurio(){ // Constructor por defecto
}

Dinosaurio::~Dinosaurio(){ // Destructor
}

Dinosaurio::Dinosaurio(sf::Texture& textura_dino){ // Constructor con textura
    _Sprite.setTexture(textura_dino);
    _Sprite.setPosition(320, 240);
    _Sprite.setOrigin(75 / 2, 75 / 2);

    // Cojo el sprite que me interesa por defecto del sheet
    _Sprite.setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75)); // SPrite concreto
}

void Dinosaurio::setTipodino(int tipodino){ // Tipo dinosaurio
    _Tipodino = tipodino; // 0: T-Rex | 1: Velociraptor | 2: Pterodactilo | 3: Triceratops 

    setSpeed(); // Poner velocidad del dinosaurio
    setVida(); // Poner vida del dinosaurio
}

void Dinosaurio::modifyVida(){ // Quitar un punto de vida si toca la bomba
    if(_Vida >= 1){
        _Vida =_Vida - 1;
    }
}

int Dinosaurio::getTipodino(){ // Devuelve tipo de dinosaurio
    return _Tipodino;
}

sf::Sprite Dinosaurio::getSprite() const{ // Devuelve el sprite
    return _Sprite;
}

void Dinosaurio::setSpeed(){ // Cambiar la velocidad
    if(_Tipodino == 0){ // T-rex
        _Speed = velocidad_trex;
    }
    if(_Tipodino == 1){ // Velociraptor
        _Speed = velocidad_velociraptor; 
    }
    if(_Tipodino == 2 || _Tipodino == 3){ // Resto de dinosaurios
        _Speed = velocidad_normal; 
    }
}

// Funciones de movimiento
int Dinosaurio::marriba(){ // Movimiento arriba
    _Sprite.setTextureRect(sf::IntRect(0 * 75, 3 * 75, 75, 75));
    _Sprite.move(0, -(_Speed));
    return 0; // Posicion arriba
}

int Dinosaurio::mabajo(){ // Movimiento abajo
    _Sprite.setTextureRect(sf::IntRect(0 * 75, 0 * 75, 75, 75));
    _Sprite.move(0, _Speed);
    return 1; // Posicion abajo
}


int Dinosaurio::mderecha(){ // Movimiento derecha
    _Sprite.setScale(1,1);  // Sprite original
    _Sprite.setTextureRect(sf::IntRect(1 * 75, 2 * 75, 75, 75));
    _Sprite.move(_Speed, 0);
    return 2; // Posicion derecha
}


int Dinosaurio::mizquierda(){ // Movimiento izquierda
    _Sprite.setScale(-1,1); // Sprite invertido  
    _Sprite.setTextureRect(sf::IntRect(1 * 75, 2 * 75, 75, 75));
    _Sprite.move(-(_Speed),0);
    
    return 3; // Posicion izquierda
}

void Dinosaurio::setVida(){ // Cambiar vida
    if(_Tipodino == 0){ // T-rex tiene 2 de vida
        _Vida = 2; 
    }
    else{ // El resto de dinosaurios tiene 1 de vida
        _Vida = 1;
    }
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