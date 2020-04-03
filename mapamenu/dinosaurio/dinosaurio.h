#ifndef DINOSAURIO_H
#define DINOSAURIO_H

class Dinosaurio
{
    public:
      Dinosaurio(); // Constructor por defecto
      Dinosaurio(int tipo, int vida, int velocidad); // Constructor con parametros
      Dinosaurio(sf::Texture&); // Constructor con textura
      ~Dinosaurio(); // Destructor

      // Movimiento
      int movimiento();
      void salto(int pos_mirando);

      // Devolver sprite
      sf::Sprite getSprite() const;

      // Cambiar vida
      void setVida();

      // Devolver vida
      int getVida();

      // Devolver velocidad
      int getSpeed();

      // Devolver hitbox
      sf::FloatRect getHitbox();

      // Devolver tipo dinosaurio
      int getTipodino();

      // Modificar vida del dinosaurio en el caso de que toque la bomba
      void modifyVida();

      int generaRandom(int max);

    private:
      float _Speed; // Velocidad
      sf::Sprite _Sprite; // Sprite
      int _Vida; // Vida del dino
      int _Tipodino; // Indica el tipo de dinosaurio. 0: T-Rex | 1: Velociraptor | 2: Pterodactilo | 3: Triceratops
};

#endif
