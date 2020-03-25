#include "contexto.h"


class Contexto{

	void Contexto::Init(){
			sf::RenderWindow window(sf::VideoMode(640, 480), 
			"P0. Fundamentos de los Videojuegos. DCCIA");
	}

	void Contexto::Cleanup(){

		while ( !states.empty() ) {
			states.back()->Cleanup();
			states.pop_back();
		}

	}

	void Contexto::ChangeState(States* state) 
	{
		// cleanup the current state
		if ( !states.empty() ) {
			states.back()->Cleanup();
			states.pop_back();
		}

		// store and init the new state
		states.push_back(state);
		states.back()->Init();
	}

	void Contexto::PushState(States* state)
	{
		// pause current state
		if ( !states.empty() ) {
			states.back()->Pause();
		}

		// store and init the new state
		states.push_back(state);
		states.back()->Init();
	}

	void Contexto::PopState()
	{
		// cleanup the current state
		if ( !states.empty() ) {
			states.back()->Cleanup();
			states.pop_back();
		}

		// resume previous state
		if ( !states.empty() ) {
			states.back()->Resume();
		}
	}

	void Contexto::HandleEvents() 
	{
		// let the state handle events
		states.back()->HandleEvents(this);
	}

	void Contexto::Update() 
	{
		// let the state update the game
		states.back()->Update(this);
	}

	void Contexto::Draw() 
	{
		
		// let the state draw the screen
		states.back()->Draw(this);
	}


};