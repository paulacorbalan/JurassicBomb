#include <SFML/Graphics.hpp>
#include <iostream>
#include "include/config.h"
#include "ej_modulos/Tile.h"
#include "mapa/Map.h"
#include "menu/menu.h"
#include "maquina/contexto.h"

#define kVel 5

int main() {
  Map *mod2 = new Map("resources/mapa1.tmx");
  Menu *menu=Menu::Instance();
  Tile *tile=new Tile();
  //Creamos una ventana

Contexto game;
            
  //Bucle del juego
  while (game.Running()) {
 
		game.HandleEvents();
		game.Update();
		game.Draw();
 
  }

  game.Cleanup();

  return 0;
}