#include "contexto.h"
#include "states.h"


	void Contexto::Inicializar(){
		m_running=true;
	}

	void Contexto::ChangeState(States* state){
		// cleanup the current state
		/*if ( !states.empty() ) {
			states.back()->Cleanup();
			states.pop_back();
		}*/

		// store and init the new state
		states.push_back(state);
		states.back()->Inicializar();
	}
	void Contexto::PushState(States* state){
		// pause current state
		/*if ( !states.empty() ) {
			states.back()->Pause();
		}*/

		// store and init the new state
		states.push_back(state);
		states.back()->Inicializar();
	}
	void Contexto::PopState(){
		// cleanup the current state
		/*if ( !states.empty() ) {
			states.back()->Cleanup();
			states.pop_back();
		}*/

		// resume previous state
		/*if ( !states.empty() ) {
			states.back()->Resume();
		}*/
	}
	void Contexto::Update(sf::Event event,sf::RenderWindow &window){
		// let the state update the game

      states.back()->Update(event,window);


	}
	void Contexto::Draw(sf::RenderWindow &window){
		// let the state draw the screen
		states.back()->Draw(window);
	}
