#pragma once
#include "contexto.h"
#include <string>
#include "SFML/Graphics.hpp"

using namespace std;
class States {
public:
	virtual void Init() = 0;
	virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvents(Contexto* game) = 0;
	virtual void Update(Contexto* game) = 0;
	virtual void Draw(Contexto* game) = 0;


	/*void cambio(Contexto* game, States* state) {
		game->
	}*/
};

