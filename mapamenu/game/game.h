#ifndef GAME_H
#define GAME_H
#pragma once
#include <string>
#include "SFML/Graphics.hpp"

using namespace std;
class Game {

  public:

    static Game* Instance();
    
protected:
    Game();
    void draw(sf::RenderWindow &window);
    void update();
    void run();

private:

  static Game* pinstance;


};

#endif