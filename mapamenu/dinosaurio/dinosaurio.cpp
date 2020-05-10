
#include <iostream>
#include "dinosaurio.h"

// Velocidades
float velocidad_normal = 0.0015;
float velocidad_trex = 0.00075;
float velocidad_velociraptor = 0.00225;



Dinosaurio::Dinosaurio(){ // Constructor por defecto
    // Texturas de todos los movimientos del dinosaurio.
    // Se crean aqui porque asi, nada mas llamar al constructor, estan dentro de la clase 
    sf::Texture dino_abajo, dino_derecha, dino_izquierda, dino_arriba,camino,bloque;
    _Sprite= new Sprite("resources/dino_abajo.png");
    _Sprite->escala(0.5,0.5);
    _Sprite->cargaTextura(dino_abajo,"resources/dino_abajo.png");    
    _Sprite->cargaTextura(dino_derecha,"resources/dino_derecha.png");    
      _Sprite->cargaTextura(dino_izquierda,"resources/dino_izquierda.png");    
     _Sprite->cargaTextura(dino_arriba,"resources/dino_arriba.png");  
     _Sprite->cargaTextura(bloque,"resources/bloque.png"); 
     _Sprite->cargaTextura(camino,"resources/camino.png"); 
            

    _dino_texture_abajo=dino_abajo;
    _dino_texture_arriba=dino_arriba;
    _dino_texture_derecha=dino_derecha;
    _dino_texture_izquierda=dino_izquierda;     
    srand (time(NULL));    
    _posdino = rand() % 5; // Posicion inicial por defecto hacia abajo
    _Direccion = _Tipodino;
    _bloque=bloque;
    _camino=camino;
}

Dinosaurio::~Dinosaurio(){ // Destructor
  
  delete _Sprite; 
}

Dinosaurio::Dinosaurio(sf::Texture& textura_dino){ // Constructor con textura (no se usa)
    _Sprite->estableceTextura(textura_dino);
    _Sprite->escala(0.5,0.5);
    _Sprite->posiciona(320, 320);
}

void Dinosaurio::setTipodino(int tipodino){ // Tipo dinosaurio
    _Tipodino = tipodino; // 0: T-Rex | 1: Velociraptor | 2: Pterodactilo | 3: Triceratops
    _Direccion = _Tipodino; 

    setSpeed(); // Poner velocidad del dinosaurio
    setVida(); // Poner vida del dinosaurio
}

void Dinosaurio::modifyTexture(sf::Texture& textura){ // Establecer textura del dinosaurio
    _Sprite->estableceTextura(textura);
    
}

void Dinosaurio::modifyVida(){ // Quitar un punto de vida si toca la bomba
    if(_Vida >= 1){
        _Vida =_Vida - 1;
    }
}

int Dinosaurio::getTipodino(){ // Devuelve tipo de dinosaurio
    return _Tipodino;
}

Sprite* Dinosaurio::getSprite() { // Devuelve el sprite
    /* En caso de que el Sprite visible se haya perdido, se reestablece usando la posion
     * a la que mira el dinosaurio. Aunque se haya perdido, sus propiedades siguen 
     * estando ahi.
     */
    if(_posdino==0){
        _Sprite->estableceTextura(_dino_texture_arriba);
    }
    if(_posdino==1){
        _Sprite->estableceTextura(_dino_texture_abajo);
    }   
    if(_posdino==2){
        _Sprite->estableceTextura(_dino_texture_derecha);
    }
    if(_posdino==3){
        _Sprite->estableceTextura(_dino_texture_izquierda);
    }
    return _Sprite;
}

void Dinosaurio::modifyPosition(int x, int y){ // Cambiar posicion del dinosaurio
    _Sprite->posiciona(x, y);
}

void Dinosaurio::setSpeed(){ // Cambiar la velocidad
    if(_Tipodino == 0){ // T-rex
        _Speed = velocidad_trex;
    }
    if(_Tipodino == 1){ // Velociraptor
        _Speed = velocidad_velociraptor; 
    }
    if(_Tipodino == 2 || _Tipodino == 3){ // Resto de dinosaurios
        _Speed = velocidad_normal; 
    }
}

void Dinosaurio::setVida(){ // Cambiar vida
    if(_Tipodino == 0){ // T-rex tiene 2 de vida
        _Vida = 2; 
    }
    else{ // El resto de dinosaurios tiene 1 de vida
        _Vida = 1;
    }
}

int Dinosaurio::getVida(){ // Devolver vida
    return _Vida;
}

int Dinosaurio::getSpeed(){ // Devolver velocidad
    return _Speed;
}

sf::FloatRect Dinosaurio::getHitbox(){ // FloatRect devuelve coordenada superior izq
    return _Sprite->getHitbox(); // Coordenadas de entorno de Sprite
}

// Funciones de movimiento (salto y movimientos)
int Dinosaurio::marriba(std::vector<Sprite*> &todo,int numlayers, int height_map, int width_map,Sprite**** tilemapSprite, Map &mapas){ // Movimiento arriba
    _Sprite->estableceTextura(_dino_texture_arriba);
    bool colision=false;
    Sprite clon("resources/dino_arriba.png");
    for(int i = 0; i < 160; i++){
        for(unsigned int j = 0;j < todo.size();j++)
        {
            if(_Sprite->colisiona(todo[j]) && _Sprite!=todo[j])
            {
                std::cout<<"dino no mueve arriba"<<std::endl;
                _posdino = 0;
                 _Sprite->mueve(0, _Speed);
                   if(_Tipodino==2){
                    srand (time(NULL));
                    int probabilidad = rand()%4; // 25% de posibilidades de saltar
                    if(probabilidad==1){ 
                        sf::FloatRect posicion_bloque = todo[j]->getHitbox();
                        clon.posiciona(_Sprite->getPosX(), _Sprite->getPosY() - posicion_bloque.height);
                        colision = true;
                    }
                }
                
            }
        }

         // Recorre los posibles saltos
        for(unsigned int j=0; j < todo.size() && colision; j++){
            int clon_left = ceil(clon.getHitboxLeft());
            
            int clon_top = ceil(clon.getHitboxTop()); 
            if(!(clon.colisiona(todo[j])) && clon_top>105){ // Comprueba que no se sale por la pantalla y el camino esta despejado
                _Sprite->posiciona(clon.getHitboxLeft(),clon.getHitboxTop()-20);
                return 0;
            }
                
        }
        _Sprite->mueve(0, -(_Speed));
    }
    _posdino = 0;
    return 0; // Posicion arriba
}

int Dinosaurio::mabajo(std::vector<Sprite*> &todo,int numlayers, int height_map, int width_map,Sprite**** tilemapSprite, Map &mapas){ // Movimiento abajo
    _Sprite->estableceTextura(_dino_texture_arriba);
   bool colision = false; // Comprueba si ha habido choque. Si ha habido, se intenta salto
    bool test = false;
    Sprite clon("resources/dino_abajo.png");
    for(int i = 0; i < 160; i++){
        for(unsigned int j = 0;j < todo.size();j++)
        {
            if(_Sprite->colisiona(todo[j]) && _Sprite!=todo[j])
            {
                std::cout<<"dino no mueve abajo"<<std::endl;
                _posdino = 1;
                 _Sprite->mueve(0,-(_Speed));
                   if(_Tipodino==2){
                    srand (time(NULL));
                    int probabilidad = rand()%4; // 25% de posibilidades de saltar
                    if(probabilidad==1){ 
                        sf::FloatRect posicion_bloque = todo[j]->getHitbox();
                        clon.posiciona(_Sprite->getPosX(), _Sprite->getPosY() + posicion_bloque.height);
                        colision = true;
                    }
                }
                
            }
        }

         // Recorre los posibles saltos
        for(unsigned int j=0; j < todo.size() && colision; j++){
            int clon_left = ceil(clon.getHitboxLeft());
            
            int clon_top = ceil(clon.getHitboxTop()); 
            if(!(clon.colisiona(todo[j])) && clon_top<360){ // Comprueba que no se sale por la pantalla y el camino esta despejado
                _Sprite->posiciona(clon.getHitboxLeft(),clon.getHitboxTop()+20);
                return 1;
            }
                
        }
        _Sprite->mueve(0, _Speed);
    }
    _posdino = 1;
    return 1; // Posicion abajo
}

int Dinosaurio::mderecha(std::vector<Sprite*> &todo,int numlayers, int height_map, int width_map,Sprite**** tilemapSprite, Map &mapas){ // Movimiento derecha
    _Sprite->estableceTextura(_dino_texture_arriba);
   bool colision = false; // Comprueba si ha habido choque. Si ha habido, se intenta salto
   
    Sprite clon("resources/dino_derecha.png");
    for(int i = 0; i < 160; i++){
        for(unsigned int j = 0;j < todo.size();j++)
        {
            if(_Sprite->colisiona(todo[j]) && _Sprite!=todo[j])
            {
                std::cout<<"dino no mueve derecha"<<std::endl;
                _posdino = 2;
                 _Sprite->mueve(-(_Speed),0);
                   if(_Tipodino==2){
                    srand (time(NULL));
                    int probabilidad = rand()%4; // 25% de posibilidades de saltar
                    if(probabilidad==1){ 
                        sf::FloatRect posicion_bloque = todo[j]->getHitbox();
                        clon.posiciona(_Sprite->getPosX()+posicion_bloque.width, _Sprite->getPosY());
                        colision = true;
                    }
                }
                
            }
        }

         // Recorre los posibles saltos
        for(unsigned int j=0; j < todo.size() && colision; j++){
            int clon_left = ceil(clon.getHitboxLeft());
            
            int clon_top = ceil(clon.getHitboxTop()); 
            if(!(clon.colisiona(todo[j])) && clon_left<470){ // Comprueba que no se sale por la pantalla y el camino esta despejado
                _Sprite->posiciona(clon.getHitboxLeft()+20,clon.getHitboxTop());
                return 2;
            }
                
        }
        _Sprite->mueve(_Speed,0);
    }
    _posdino = 2;
    return 2; // Posicion derecha
}


int Dinosaurio::mizquierda(std::vector<Sprite*> &todo,int numlayers, int height_map, int width_map,Sprite**** tilemapSprite, Map &mapas){ // Movimiento izquierda
    _Sprite->estableceTextura(_dino_texture_arriba);
   bool colision = false; // Comprueba si ha habido choque. Si ha habido, se intenta salto
   
    Sprite clon("resources/dino_izquierda.png");
    for(int i = 0; i < 160; i++){
        for(unsigned int j = 0;j < todo.size();j++)
        {
            if(_Sprite->colisiona(todo[j]) && _Sprite!=todo[j])
            {
                std::cout<<"dino no mueve izq"<<std::endl;
                _posdino = 3;
                 _Sprite->mueve(-(_Speed),0);
                   if(_Tipodino==2){
                    srand (time(NULL));
                    int probabilidad = rand()%4; // 25% de posibilidades de saltar
                    if(probabilidad==1){ 
                        sf::FloatRect posicion_bloque = todo[j]->getHitbox();
                        clon.posiciona(_Sprite->getPosX()-posicion_bloque.width, _Sprite->getPosY());
                        colision = true;
                    }
                }
                
            }
        }

         // Recorre los posibles saltos
        for(unsigned int j=0; j < todo.size() && colision; j++){
            int clon_left = ceil(clon.getHitboxLeft());
            
            int clon_top = ceil(clon.getHitboxTop()); 
            if(!(clon.colisiona(todo[j])) && clon_left>150){ // Comprueba que no se sale por la pantalla y el camino esta despejado
                _Sprite->posiciona(clon.getHitboxLeft()-20,clon.getHitboxTop());
                return 2;
            }
                
        }
        _Sprite->mueve(-(_Speed),0);
    }
    _posdino = 3;
    return 3; // Posicion derecha
}

void Dinosaurio::sumaPasos(){
    int pasos;
    for(int i = 0; i < 160; i++){
        pasos++;
    }
};

void Dinosaurio::setDireccion(int i){
    _Direccion = i;
}

int Dinosaurio::getDireccion(){
    return _Direccion;
}

// Hacer que el dinosaurio salte
void Dinosaurio::salto(int pos_mirando){
    if(_Tipodino == 2){ // Solo puede saltar el pterodactilo
        switch (pos_mirando){
        case 0: // Mirando arriba
            _Sprite->mueve(0, -(_Speed)*800);
            break;
        case 1: // Mirando abajo
            _Sprite->mueve(0, (_Speed)*800);
            break;
        case 2: // Mirando derecha
            _Sprite->mueve((_Speed)*800,0);
            break;
        case 3: // Mirando izquierda
            _Sprite->mueve((-_Speed)*800,0);
        default:
            break;
        }
    }
}



