#ifndef MOTOR_H
#define MOTOR_H

#include "SFML/Graphics.hpp"
#include <string>
using namespace std;
class Motor{

    private:    

           static Motor* minstance;

    public:
            Motor* Instance();
           // sf::RenderWindow creaVentana(int x,int y,string titulo);
            void estableceFPS(sf::RenderWindow& w,int n );
            sf::Time obtenerInstante(sf::Clock& c);
            bool compruebaVentana(sf::RenderWindow& w);
            bool compruebaEvento(sf::RenderWindow& w,sf::Event& e);
            void cierraVentana(sf::RenderWindow& w);
            void estableceCadena(sf::Text& t, string s);
            void escalaTamanyoLetra(sf::Text& t,int n);
            void seleccionaFuente(sf::Text& t,sf::Font f);
            void seleccionaColor(sf::Text& t,sf::Color c);
            sf::Vector2i capturaPosicionRaton(sf::RenderWindow& w);
            void posicionaTexto(sf::Text& t,int x,int y);


};
















#endif