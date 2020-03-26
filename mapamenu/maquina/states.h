#ifndef STATES_H
#define STATES_H

#pragma once
#include <iostream>
#include <string>
#include "SFML/Graphics.hpp"

class Contexto;

class States {
public:
	 void Inicializar();
	 void Update(sf::Event event,sf::RenderWindow &window) ;
	 void Draw(sf::RenderWindow &window);


	void ChangeState(Contexto* game, States* state);
};

#endif