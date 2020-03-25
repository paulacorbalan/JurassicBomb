#ifndef STATES_H
#define STATES_H

#pragma once
#include "contexto.h"
#include <iostream>
#include <string>

class States {
public:
	 void Inicializar();
	 void Update(sf::Event event,sf::RenderWindow &window) ;
	 void Draw(sf::RenderWindow &window);


	void ChangeState(Contexto* game, States* state) {
		game->ChangeState(state);
	}
};

#endif