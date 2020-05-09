#ifndef MENU_H
#define MENU_H

#pragma once
#include <string>
#include <iostream>
#include "states.h"
#include "sprite.h"

//

using namespace std;
#define width 640
#define height 480

class Menu : public States {
  private:
  sf::Texture background;
  Sprite* backgroundImage;
  sf::Texture pausa;
  Sprite* pausaImage;
  Sprite* playImage;
  sf::Texture play;
  Sprite* atrasImage;
  sf::Texture atras;
  Sprite* nivelesImage;
  sf::Texture niveles;
  sf::Texture menos;
  Sprite* menosImage;
  sf::Texture plus;
  Sprite* plusImage;
  sf::Font fuente;
  sf::String cadena;
  sf::Text texto;
  sf::Texture facil;
  Sprite* facilImage;
  sf::Texture normal;
  Sprite* normalImage;
  sf::Texture dificil;
  Sprite* dificilImage;
  sf::Texture splayer;
  Sprite* splayerImage;
  sf::Texture mplayer;
  Sprite* mplayerImage;
  sf::Texture exit;
  Sprite* exitImage;                
  Sprite* sprite;

    bool gpause=false;
    bool jugando=false;
    int players=0;
    int lvls=1;
    int dificulty=0;//0 facil 1 normal 2 dificil
    int menus=0;//0 principal, 1 un jugador, 2 multijugador, 3 opciones
    
    static Menu* pinstance;

  public:
    void Inicializar();
    void reinicio();
    static Menu* Instance();
    void Event(sf::Event event,sf::RenderWindow &window);
    void Update(sf::RenderWindow &window);
    void Draw(sf::RenderWindow &window);
    int GetLvls();
    int GetDif();
    int GetPlayers(){return players;}
    void lvltxt();
  protected:
    void Cargarecursos();


};

#endif