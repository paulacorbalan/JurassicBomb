#include "bombas.h"
#include <iostream>

//Arriba esa fiesta
//Y todo eso
Bomba::Bomba(float x, float y)
{
    coordenadaX = x;
    coordenadaY = y;
    activarColision = false;

    //Cargo la textura de las explosiones para usarlas posteriormente.
    sbomba->cargaTextura(texplosiones,"resources/explosion.png");
    /*if (!texplosiones->loadFromFile("resources/explosion.png")) {
        std::cerr << "Error cargando la imagen explosion.png";
        exit(0);
    }*/

    //Cargo la textura y creo el sprite de la bomba.
    sbomba->cargaTextura(tbomba,"resources/bomba.png");
    /*if (!tbomba->loadFromFile("resources/bomba.png")) {
        std::cerr << "Error cargando la imagen bomba.png";
        exit(0);
    }*/

    sbomba->estableceTextura(tbomba);
    sbomba->recortaSprite(0,0,410,370);
    sbomba->estableceOrigen(410,370);
    sbomba->posiciona(x,y);
    sbomba->escala(0.10,0.10);
}

std::vector<Sprite*> Bomba::GenerarExplosion()
{
    std::vector<Sprite*> sprites;
    float x = getCoordenadaX();
    float y = getCoordenadaY();
    //Escala.
    float sc = 0.035;
    //Distancia separacion entre explosiones.
    int dsExp = 32;

    //Explosion central.
    Sprite* explosionCen=new Sprite("resources/explosion.png");
    explosionCen->estableceOrigen(840,840);
    explosionCen->recortaSprite(0,0,900,900);
    explosionCen->posiciona(x,y);
    explosionCen->escala(sc,sc);
    sprites.push_back(explosionCen);

    //Explosion izquierda.
    Sprite* explosionIzq=new Sprite("resources/explosion.png");
    explosionIzq->estableceOrigen(840,840);
     explosionIzq->recortaSprite(0,0,900,900);
     explosionIzq->posiciona(x-dsExp,y);
    explosionIzq->escala(sc,sc);
    sprites.push_back(explosionIzq);

    //Explosion derecha.
    Sprite* explosionDer=new Sprite("resources/explosion.png");
      explosionDer->estableceOrigen(840,840);
     explosionDer->recortaSprite(0,0,900,900);
     explosionDer->posiciona(x+dsExp,y);
    explosionDer->escala(sc,sc);
    sprites.push_back(explosionDer);

    //Explosion arriba.
    Sprite* explosionAr=new Sprite("resources/explosion.png");
     explosionAr->estableceOrigen(840,840);
     explosionAr->recortaSprite(0,0,900,900);
     explosionAr->posiciona(x,y+dsExp);
    explosionAr->escala(sc,sc);
    sprites.push_back(explosionAr);

    //Explosion abajo.
    Sprite* explosionAb=new Sprite("resources/explosion.png");
    explosionAb->estableceOrigen(840,840);
     explosionAb->recortaSprite(0,0,900,900);
     explosionAb->posiciona(x,y-dsExp);
    explosionAb->escala(sc,sc);
    sprites.push_back(explosionAb);

    //Rellenamos la variable explosiones.
    setExplosion(sprites);

    return sprites;
}

void Bomba::update(sf::Clock &temporizador,Jugador &jugador,std::vector<Bomba> &totalBombas,std::vector<Sprite*> &totalExplosiones,std::vector<float> &tiemposBomba,std::vector<float> &tiemposExplosiones)
{
    //Detectamos si ya ha pasado la cantidad de tiempo suficiente para que explote una bomba.
    if(tiemposBomba.size() > 0 && temporizador.getElapsedTime().asSeconds() - tiemposBomba[0] >= 3)
    {
      //Nos guardamos las explosiones generadas por la bomba que lleva mas tiempo puesta.
      std::vector<Sprite*> aux = totalBombas[0].GenerarExplosion();
      for(unsigned int i = 0;i < aux.size();i++)
      {
        totalExplosiones.push_back(aux[i]);
      }

      //Nos guardamos el tiempo en el que ha producido la explosion.
      tiemposExplosiones.push_back(temporizador.getElapsedTime().asSeconds());
      //Si la bomba que se va a borrar es del jugador actual, le habilitamos para pueda volver a poner una bomba.
      if(totalBombas[0].getPropietario() == jugador.getIdentificador())
      {
        jugador.setPuesta(false);
      }
      //Borramos la bomba que lleva mas tiempo puesta.
      totalBombas.erase(totalBombas.begin());
      //Borramos el tiempo que controla la primera bomba.
      tiemposBomba.erase(tiemposBomba.begin());
    }

    
    //Ha pasado un segundo desde que se activa la explosion.
    if(tiemposExplosiones.size() > 0 && temporizador.getElapsedTime().asSeconds() - tiemposExplosiones[0] >= 1)
    {
      //Borramos explosion mas antigua y su tiempo.
      totalExplosiones.erase(totalExplosiones.begin(),totalExplosiones.begin()+5);
      tiemposExplosiones.erase(tiemposExplosiones.begin());
    }
}

//GETTERS

Sprite* Bomba::getBomba()
{
    return sbomba;
}

bool Bomba::getColision()
{
  return activarColision;
}

float Bomba::getCoordenadaX()
{
    return coordenadaX;
}

float Bomba::getCoordenadaY()
{
    return coordenadaY;
}

int Bomba::getPropietario()
{
    return propietario;
}

//SETTERS

bool Bomba::setColision()
{
  return activarColision = true;
}

void Bomba::setExplosion(std::vector<Sprite*> exp)
{
    for(int i = 0;i < 5; i++)
    {
        explosiones.push_back(exp[i]);
    }
}

void Bomba::setPropietario(int identificador)
{
    propietario = identificador;
}

void Bomba::draw(sf::RenderWindow &window)
{
    sbomba->dibujaSprite(window);
}

