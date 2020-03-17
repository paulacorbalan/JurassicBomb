#pragma once
#include <SFML/Graphics.hpp>


class Tile{

   
    public:
    Tile();
    void Cargarecursos();
    void Update();
    void draw(sf::RenderWindow &window);
private:

    sf::Sprite vida1;
    sf::Sprite vida2;
    sf::Sprite vida3;
    sf::Texture texvida;
    sf::Sprite letranumero;
    sf::Texture texletranumero;
    sf::Sprite contador;
    sf::Texture texcontador;
    sf::Clock temporizador;
    int segundero;
    std::vector<sf::Sprite> sprites;


    sf::Font fuente;
    sf::String cadena;
    sf::Text texto;
    int vidas=3;
    bool terminada=false;
    int min=0;
    int seg=12;



};