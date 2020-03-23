#include "contexto.h"

class Contexto{


  void Contexto::Init(){
        sf::RenderWindow window(sf::VideoMode(640, 480), 
        "P0. Fundamentos de los Videojuegos. DCCIA");
  }

  void Cleanup();

  void ChangeState(States* state);
  void PushState(States* state);
  void PopState();

  void HandleEvents();
  void Update();
  void Draw();

};