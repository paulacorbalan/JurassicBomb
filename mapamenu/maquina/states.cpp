

#include "states.h"
#include "contexto.h"


	 void States::Inicializar(){}
	 void States::Update(sf::Event event,sf::RenderWindow &window) {}
	 void States::Draw(sf::RenderWindow &window){std::cout<<"state";}


	void States::ChangeState(Contexto* game, States* state) {
		game->ChangeState(state);
	}

