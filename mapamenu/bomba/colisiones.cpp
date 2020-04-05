#include "colisiones.h"
#include <iostream>

void Colisiones::crearColisiones(sf::Sprite &jugador,std::vector<sf::Sprite*> objetos, int direccion, int velocidad)
{
      for(unsigned int i = 0;i < objetos.size();i++)
      {
        //Ha encontrado un objeto del vector con el que esta colisionando actualmente.
        if(jugador.getGlobalBounds().intersects(objetos[i]->getGlobalBounds()))
            {
              //Contrarestar velocidad en la direccion en la que esta yendo.
                switch (direccion)
                {
                  //Arriba
                  case 0:
                    jugador.move(0,velocidad);
                    break;
                  //Abajo
                  case 1:
                    jugador.move(0,-velocidad);
                    break;
                  //Derecha
                  case 2:
                    jugador.move(-velocidad, 0);
                    break;
                  //Izquierda
                  case 3:
                  jugador.move(velocidad, 0);
                    break;
                }
            }
      }
}

void Colisiones::colisionesBombas(Jugador &jugador,std::vector<Bomba> &bombas, int direccion)
{
  for(unsigned int i = 0;i < bombas.size();i++)
  {
    //Ha encontrado la bomba con la que esta colisionando.
    if(bombas[i].getBomba().getGlobalBounds().intersects(jugador.getSprite()->getGlobalBounds()))
    {
      std::cout << "He entrado 1" << std::endl;
      if(bombas[i].getColision() == true)
      {
        std::cout << "He entrado 2" << std::endl;
      switch (direccion)
              {
                //Arriba
                case 0:
                  jugador.mover(1);
                  break;
                //Abajo
                case 1:
                  jugador.mover(0);
                  break;
                //Izquierda
                case 2:
                  jugador.mover(3);
                  break;
                //Derecha
                case 3:
                  jugador.mover(2);
                  break;
              }
      }
    }
    else
    {
      //Si no colisiona con una bomba pero esa bomba es suya y aun no tiene colision, se la activamos.
      if(bombas[i].getPropietario() == 1 && bombas[i].getColision() == false)
      {
        std::cout << bombas[i].getColision() << std::endl;
        std::cout << "Acabo de activar una colision" << std::endl;
        std::cout << bombas[i].setColision() << std::endl;
      }
    }
  }
}


void Colisiones::update(std::vector<Dinosaurio*> &dinosaurios,Jugador &jugador,std::vector<sf::Sprite> &totalExplosiones)
{
  for(unsigned int i = 0;i < totalExplosiones.size();i++)
  {
    for(unsigned int j = 0;j < dinosaurios.size();j++)
    {
      //Si el dinosaurio actual ha chocado con un explosion, debemos quitarle una vida.
      if(dinosaurios[j]->getSprite()->getGlobalBounds().intersects(totalExplosiones[i].getGlobalBounds()))
      {
        dinosaurios[j]->modifyVida();
        if(dinosaurios[j]->getVida() == 0)
        {
          dinosaurios.erase(dinosaurios.begin() + j-1);
        }
      }
    }
    if(jugador.getSprite()->getGlobalBounds().intersects(totalExplosiones[i].getGlobalBounds()))
    {
      jugador.quitarVidas();
      std::cout << jugador.getVidas() << std::endl;
      
    }
  }
}
