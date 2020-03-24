#include "colisiones.h"
#include <iostream>

void Colisiones::crearColisiones(sf::Sprite &jugador,std::vector<sf::Sprite> objetos, int direccion, int velocidad)
{
        switch (direccion) {

            //Derecha
        case 0:
          for(unsigned int i = 0;i < objetos.size();i++)
          {
            if(jugador.getGlobalBounds().intersects(objetos[i].getGlobalBounds()))
            {
                jugador.move(-velocidad, 0);
            }
          }
          break;

            //Izquierda
        case 1:
          for(unsigned int i = 0;i < objetos.size();i++)
          {
            if(jugador.getGlobalBounds().intersects(objetos[i].getGlobalBounds()))
            {
                std::cout << "Izquierda fuera" << std::endl;
                jugador.move(velocidad, 0);
            }
          }
          break;

            //Arriba
        case 2:
          for(unsigned int i = 0;i < objetos.size();i++)
          {
            if(jugador.getGlobalBounds().intersects(objetos[i].getGlobalBounds()))
            {
                jugador.move(0,velocidad);
            }
          }
          break;

            //Abajo
        case 3:
          for(unsigned int i = 0;i < objetos.size();i++)
          {
            if(jugador.getGlobalBounds().intersects(objetos[i].getGlobalBounds()))
            {
                jugador.move(0,-velocidad);
            }
          }
          break;
        }
}