#ifndef DINOSAURIO_H
#define DINOSAURIO_H

class Dinosaurio 
{
    public:
      Dinosaurio(); // Constructor por defecto
      Dinosaurio(sf::Texture&); // Constructor con textura
      ~Dinosaurio(); // Destructor

      // Movimiento
      int marriba();
      int mabajo();
      int mderecha();
      int mizquierda();

      void salto(int pos_mirando);

      // Cambiar velocidad
      void setSpeed();

      // Devolver sprite
      sf::Sprite getSprite() ;

      // Cambiar vida
      void setVida();

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


    private:
      float _Speed; // Velocidad
      int _Direccion;
      sf::Sprite _Sprite; // Sprite
      sf::Texture _dino_texture_abajo;
      sf::Texture _dino_texture_arriba;
      sf::Texture _dino_texture_derecha;
      sf::Texture _dino_texture_izquierda;
      int _posdino; // Posicion a la que mira el dino ==> 0:Arriba | 1:Abajo | 2:Derecha | 3:Izquierda
      int _Vida; // Vida del dino
      int _Tipodino; // Indica el tipo de dinosaurio. 0: T-Rex | 1: Velociraptor | 2: Pterodactilo | 3: Triceratops 
};

#endif
