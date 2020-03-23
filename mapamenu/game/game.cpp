#include "game.h"


Game* Game::pinstance=0;

Game* Game::Instance() {
  if(pinstance==0){
    pinstance=new Game;
  }
  return pinstance;
}

Game::Game(){
}


void Game::draw(sf::RenderWindow &window) {
}

void Game::update() {
}
