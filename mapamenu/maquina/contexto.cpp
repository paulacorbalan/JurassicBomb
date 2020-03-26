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
		this->m_running=true;
		    std::cout<<"contextoinicia";
	}

	void Contexto::ChangeState(States* state){ //guarda en nuevo estado
		// cleanup the current state
		/*if ( !states.empty() ) {
			states.back()->Cleanup();
			states.pop_back();
		}*/

		// store and init the new state
	

		std::cout<<states.size();

		states.push_back(state);
		std::cout<<"changestate";
		states.back()->Inicializar();
	
		std::cout<<states.size()<<"\n";

	}

	void Contexto::Update(sf::Event event,sf::RenderWindow &window){
		// let the state update the game
	  std::cout<<"contextoupdate\n";
      states.back()->Update(event,window);


	}
	void Contexto::Draw(sf::RenderWindow &window){
		// let the state draw the screen
		states.back()->Draw(window);
	}
