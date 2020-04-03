#include "motor.h"

Motor* Motor::minstance=0;
 Motor* Motor::Instance(){

     if(minstance==0){
         minstance=new Motor;

     }

     return minstance;
 }
/*sf::RenderWindow Motor::creaVentana(int x,int y,string titulo){

     sf::RenderWindow w(sf::VideoMode(x,y),titulo);
     
    return w;

    
}*/
void Motor::estableceFPS(sf::RenderWindow& w,int n ){

    w.setFramerateLimit(n);
}
sf::Vector2i capturaPosicionRaton(sf::RenderWindow& w){
    sf::Vector2i respuesta;
    respuesta=sf::Mouse::getPosition(w);
    return respuesta;
}
sf::Time Motor::obtenerInstante(sf::Clock& c){
    sf::Time respuesta;

    respuesta=c.getElapsedTime();

    return respuesta;
}
bool Motor::compruebaVentana(sf::RenderWindow& w){

    bool respuesta=false;

    respuesta=w.isOpen();

    return respuesta;
}
bool Motor::compruebaEvento(sf::RenderWindow&w, sf::Event& e){

    bool respuesta=false;

    respuesta=w.pollEvent(e);

    return respuesta;
}
void Motor::cierraVentana(sf::RenderWindow& w){

    w.close();
}
void Motor::estableceCadena(sf::Text& t, string s){

    t.setString(s);
}
void Motor::escalaTamanyoLetra(sf::Text& t,int n){

    t.setCharacterSize(n);
}
void Motor::seleccionaFuente(sf::Text& t,sf::Font f){

    t.setFont(f);
}
void Motor::seleccionaColor(sf::Text& t,sf::Color c){

    t.setColor(c);
}
void Motor::posicionaTexto(sf::Text& t,int x,int y){

    t.setPosition(x,y);
}
