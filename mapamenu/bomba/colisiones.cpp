#include "colisiones.h"
#include <iostream>

void Colisiones::crearColisiones(sf::Sprite &jugador,std::vector<sf::Sprite> objetos, int direccion, int velocidad)
{
      for(unsigned int i = 0;i < objetos.size();i++)
      {
        //Ha encontrado un objeto del vector con el que esta colisionando actualmente.
        if(jugador.getGlobalBounds().intersects(objetos[i].getGlobalBounds()))
            {
              //Contrarestar velocidad en la direccion en la que esta yendo.
                switch (direccion)
                {
                  //Derecha
                  case 0:
                    jugador.move(-velocidad, 0);
                    break;
                  //Izquierda
                  case 1:
                    jugador.move(velocidad, 0);
                    break;
                  //Arriba
                  case 2:
                    jugador.move(0,velocidad);
                    break;
                  //Abajo
                  case 3:
                    jugador.move(0,-velocidad);
                    break;
                }
            }
      }
}

void Colisiones::colisionesBombas(sf::Sprite &jugador,std::vector<Bomba> &bombas, int direccion, int velocidad)
{
  for(unsigned int i = 0;i < bombas.size();i++)
  {
    //Ha encontrado la bomba con la que esta colisionando.
    if(bombas[i].getBomba().getGlobalBounds().intersects(jugador.getGlobalBounds()))
    {
      std::cout << "He entrado 1" << std::endl;
      if(bombas[i].getColision() == true)
      {
        std::cout << "He entrado 2" << std::endl;
      switch (direccion)
              {
                //Derecha
                case 0:
                  jugador.move(-velocidad, 0);
                  break;
                //Izquierda
                case 1:
                  jugador.move(velocidad, 0);
                  break;
                //Arriba
                case 2:
                  jugador.move(0,velocidad);
                  break;
                //Abajo
                case 3:
                  jugador.move(0,-velocidad);
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

/*
    if(bombas[i].getBomba().getGlobalBounds().intersects(jugador.getGlobalBounds()))
    {
      //Contrarestar velocidad en la direccion en la que esta yendo.
              switch (direccion)
              {
                //Derecha
                case 0:
                  jugador.move(-velocidad, 0);
                  break;
                //Izquierda
                case 1:
                  jugador.move(velocidad, 0);
                  break;
                //Arriba
                case 2:
                  jugador.move(0,velocidad);
                  break;
                //Abajo
                case 3:
                  jugador.move(0,-velocidad);
                  break;
              }
    }
    */