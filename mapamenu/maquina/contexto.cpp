#include "contexto.h"
#include "states.h"


	Contexto* Contexto::pinstance=0;

  	Contexto* Contexto::Instance() {
		if(pinstance==0){
		pinstance=new Contexto;
		}
		return pinstance;
  	}

	void Contexto::Inicializar(){
		m_running=true;
	}

	void Contexto::ChangeState(States* state){ //guarda en nuevo estado
		// cleanup the current state
		/*if ( !states.empty() ) {
			states.back()->Cleanup();
			states.pop_back();
		}*/

		// store and init the new state
		states.push_back(state);
		states.back()->Inicializar();
	}

	void Contexto::Update(sf::Event event,sf::RenderWindow &window){
		// let the state update the game

      states.back()->Update(event,window);


	}
	void Contexto::Draw(sf::RenderWindow &window){
		// let the state draw the screen
		states.back()->Draw(window);
	}
