#ifndef DINOSAURIO_H
#define DINOSAURIO_H
#include "sprite.h"
#include "Map.h"
class Dinosaurio 
{
    public:
      Dinosaurio(); // Constructor por defecto
      Dinosaurio(sf::Texture&); // Constructor con textura
      ~Dinosaurio(); // Destructor

      // Movimiento
      int marriba(std::vector<Sprite*> &c,int numlayers, int height_map, int width_map,Sprite**** tilemapSprite, Map &mapas);
      int mabajo(std::vector<Sprite*> &c,int numlayers, int height_map, int width_map,Sprite**** tilemapSprite, Map &mapas);
      int mderecha(std::vector<Sprite*> &c,int numlayers, int height_map, int width_map,Sprite**** tilemapSprite, Map &mapas);
      int mizquierda(std::vector<Sprite*> &c,int numlayers, int height_map, int width_map,Sprite**** tilemapSprite, Map &mapas);

      void salto(int pos_mirando);

      // Cambiar velocidad
      void setSpeed();

      // Devolver sprite
      Sprite* getSprite() ;

      // Cambiar vida
      void setVida();

      //Otorga un segundo de invencibilidad
      void setInvencibilidad(float f){invencibilidad = f;}

      // Devolver vida
      int getVida();

      // Devolver velocidad
      int getSpeed();

      // Devolver hitbox
      sf::FloatRect getHitbox();

      // Establecer tipo dinosaurio
      void setTipodino(int tipodino);

      // Devolver tipo dinosaurio
      int getTipodino();

      //Devolver invencibilidad
      float getInvencibilidad(){return invencibilidad;}

      // Modificar vida del dinosaurio en el caso de que toque la bomba
      void modifyVida();

      // Cambiar textura
      void modifyTexture(sf::Texture&);

      // Cambiar posicion
      void modifyPosition(int x, int y);

      int generaRandom(int max);

      int movimiento();

      void sumaPasos();
      void setDireccion(int i);
      int getDireccion();
       void setactivo(bool a){activo=a;}
      bool getactivo(){return activo;}


    private:
      float _Speed; // Velocidad
      int _Direccion;
      Sprite* _Sprite; // Sprite
      sf::Texture _dino_texture_abajo;
      sf::Texture _dino_texture_arriba;
      sf::Texture _dino_texture_derecha;
      sf::Texture _dino_texture_izquierda;
      sf::Texture _bloque;
      sf::Texture _camino;
      int _posdino; // Posicion a la que mira el dino ==> 0:Arriba | 1:Abajo | 2:Derecha | 3:Izquierda
      int _Vida; // Vida del dino
      int _Tipodino; // Indica el tipo de dinosaurio. 0: T-Rex | 1: Velociraptor | 2: Pterodactilo | 3: Triceratops
      float invencibilidad = -1; 
      bool activo=false;
};

#endif
