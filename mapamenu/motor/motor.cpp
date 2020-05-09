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
void Motor::estableceFPS(sf::RenderWindow& w,int n ){//ajusta los FPS

    w.setFramerateLimit(n);
}
sf::Vector2i capturaPosicionRaton(sf::RenderWindow& w){//recoge la posicion del puntero del raton
    sf::Vector2i respuesta;
    respuesta=sf::Mouse::getPosition(w);
    return respuesta;
}
sf::Time Motor::obtenerInstante(sf::Clock& c){//recoge el instante actual del reloj
    sf::Time respuesta;

    respuesta=c.getElapsedTime();

    return respuesta;
}
bool Motor::compruebaVentana(sf::RenderWindow& w){ //comprueba si la ventana esta abierta

    bool respuesta=false;

    respuesta=w.isOpen();

    return respuesta;
}
bool Motor::compruebaEvento(sf::RenderWindow&w, sf::Event& e){ //comprueba el evento

    bool respuesta=false;

    respuesta=w.pollEvent(e);

    return respuesta;
}
void Motor::cierraVentana(sf::RenderWindow& w){ //cierra la ventana del ejecutable

    w.close();
}
void Motor::estableceCadena(sf::Text& t, string s){ //actualiza el valor de la cadena

    t.setString(s);
}
void Motor::escalaTamanyoLetra(sf::Text& t,int n){//establece el tamaño de la letra

    t.setCharacterSize(n);
}
void Motor::seleccionaFuente(sf::Text& t,sf::Font f){//adjudica la fuente del texto

    t.setFont(f);
}
void Motor::seleccionaColor(sf::Text& t,sf::Color c){ //establece el color del texto

    t.setColor(c);
}
void Motor::posicionaTexto(sf::Text& t,int x,int y){//posiciona el texto en la pantallaW

    t.setPosition(x,y);
}


