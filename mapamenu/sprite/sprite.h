#ifndef SPRITE_H
#define SPRITE_H

#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>

using namespace std;
class Sprite{

    private: 
            sf::Sprite* spr;
            sf::Texture t;

    public:
            Sprite(string s);
            Sprite();
            ~Sprite();
            void dibujaSprite(sf::RenderWindow& w);
            void recortaSprite(int n1,int n2,int x,int y);
            void posiciona(int x,int y);
            void estableceOrigen(int x,int y);
            void cargaTextura(sf::Texture& t,string s){ //aqui cargamos la textura pasada por parametro
                if (!t.loadFromFile(s)) {
                        std::cerr << "Error cargando la imagen explosion.png";
                         exit(0);
                }
            }
            void estableceTextura(sf::Texture& t){//actualiza la textura a utilizar
                    spr->setTexture(t);
            }
            bool compruebaSiRatonEstaEncima(sf::Vector2i& m);
            void escala(float x, float y){  //establece la escala del sprite
                    spr->scale(x,y);
                    
            }
            void mueve(float x,float y){  //mueve el sprite
                    spr->move(x,y);
            
            }
            sf::FloatRect getHitbox(){   //captura la hitbox del sprite
                    spr->getGlobalBounds();
            }
            bool colisiona(sf::Sprite* s){ //compueba si dos sprites colisionan
                    bool respuesta=false;
                    respuesta=spr->getGlobalBounds().intersects(s->getGlobalBounds());
                    return respuesta;
                    
            } 
            bool colisiona(Sprite* s){
                    bool respuesta=false;
                    respuesta=spr->getGlobalBounds().intersects(s->getSpr()->getGlobalBounds());
                    return respuesta;
                    
            } 
             bool operator!=(Sprite& s1){  //sobrecarga operador distinto
                     
                    return (spr)!=s1.getSpr();
            }

            bool contiene(float x,float y){             //comprueba si el sprite esta contenido en la posicion dadda
                    bool resultado=false;
                    resultado=spr->getGlobalBounds().contains(x,y);
                    return resultado;     
                         
                 }   
               float getPosX(){         //devuelve la posicion x del sprite
                       return spr->getPosition().x;
               } 
               float getPosY(){                 //devuele la posicion y del sprite
                       return spr->getPosition().y;
               } 
               sf::Sprite* getSpr(){  //devuelve el sprite
                       return spr;
               }
               int texturaX(sf::Texture& t){ // captura la posicion x de la textura
                     return   t.getSize().x;
               }

               int texturaY(sf::Texture& t){ //captura la posicion y de la textura
                     return   t.getSize().y;
               }
};



















#endif