#ifndef MENU_H
#define MENU_H

#pragma once
#include <string>
#include <iostream>
#include "states.h"

using namespace std;
#define width 640
#define height 480

class Menu : public States {
  private:
  sf::Texture background;
  sf::Sprite backgroundImage;
    sf::Texture titulo;
  sf::Sprite tituloImage;
  sf::Texture ganar;
  sf::Sprite ganarImage;
  sf::Texture perder;
  sf::Sprite perderImage;
  sf::Texture pausa;
  sf::Sprite pausaImage;
  sf::Sprite playImage;
  sf::Texture play;
  sf::Sprite atrasImage;
  sf::Texture atras;
  sf::Sprite nivelesImage;
  sf::Texture niveles;
  sf::Texture menos;
  sf::Sprite menosImage;
  sf::Texture plus;
  sf::Sprite plusImage;
  sf::Font fuente;
  sf::String cadena;
  sf::Text texto;
  sf::Texture facil;
  sf::Sprite facilImage;
  sf::Texture normal;
  sf::Sprite normalImage;
  sf::Texture dificil;
  sf::Sprite dificilImage;
  sf::Texture splayer;
  sf::Sprite splayerImage;
  sf::Texture mplayer;
  sf::Sprite mplayerImage;
  sf::Texture exit;
  sf::Sprite exitImage;                
  sf::Sprite sprite;

    sf::Texture controles;
  sf::Sprite controlesImage;   

    bool gpause=false;
    bool jugando=false;
    int players=0;
    int lvls=0;
    int dificulty=0;//0 facil 1 normal 2 dificil
    int menus=5;//0 principal, 1 un jugador, 2 multijugador, 3 opciones
    
    static Menu* pinstance;

  public:
    void Inicializar();
    void reinicio(int a);
    static Menu* Instance();
    void Event(sf::Event event,sf::RenderWindow &window, float time);
    void Update(sf::RenderWindow &window, float time);
    void Draw(sf::RenderWindow &window);
    int GetLvls();
    int GetDif();
    int GetPlayers(){return players;}
    void lvltxt();
  protected:
    void Cargarecursos();


};

#endif