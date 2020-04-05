#include <iostream>
#include "ia.h"
#include "colisiones.h"

/* Genera numeros aleatorios entre el 0 y el 4 para ver en que direccion se mueve.
 * Usa un contador de iteraciones del programa para que no dependa del tiempo
 */

void IA::movimientoDinos(vector<Dinosaurio*> dinosaurios, int _cont,std::vector<sf::Sprite*> todosObjetos){
    int tam_dinos = dinosaurios.size();
    if(_cont%50==0){ // Contador de iteraciones del programa
        for(int i=0; i < tam_dinos; i++){
            int seed = rand()%5; // Numero entre 0 y 4 (el 4 no hace nada)
            if(seed==0){ // Arriba
                dinosaurios[i]->marriba();
                Colisiones::crearColisiones(*dinosaurios[i]->getSprite(),todosObjetos,0,dinosaurios[i]->getSpeed());
            }
            if(seed==1){ // Abajo
                dinosaurios[i]->mabajo();
                Colisiones::crearColisiones(*dinosaurios[i]->getSprite(),todosObjetos,1,dinosaurios[i]->getSpeed()); 
            }
            if(seed==2){ // Derecha
                dinosaurios[i]->mderecha();
                Colisiones::crearColisiones(*dinosaurios[i]->getSprite(),todosObjetos,2,dinosaurios[i]->getSpeed()); 
            }
            if(seed==3){ // Izquierda
                dinosaurios[i]->mizquierda();
                Colisiones::crearColisiones(*dinosaurios[i]->getSprite(),todosObjetos,3,dinosaurios[i]->getSpeed());
            }            
        }
    }
}