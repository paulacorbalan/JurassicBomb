#include <iostream>
#include "ia.h"

/* Genera numeros aleatorios entre el 0 y el 4 para ver en que direccion se mueve.
 * Usa un contador de iteraciones del programa para que no dependa del tiempo
 */

void IA::movimientoDinos(vector<Dinosaurio*> dinosaurios, int _cont,std::vector<sf::Sprite*> &todoSprite, Map &mapas){
    int tam_dinos = dinosaurios.size();

    sf::Sprite**** tilemapSprite = mapas.gettilemapSprite();
    int numlayers, height_map, width_map, ***tilemap;
    tilemap = mapas.gettilemap();
    numlayers = mapas.getnumlayers();
    height_map = mapas.getheight();
    width_map = mapas.getwidth();


    if(_cont%50==0){ // Contador de iteraciones del programa
        for(int i=0; i < tam_dinos; i++){
            int cosas [5] = { 0, 1, 2, 3, 4 };
            int meh = cosas[i];
            dinosaurios[i]->setDireccion(meh);
            
            srand (time(NULL));
            int num1 = dinosaurios[i]->getDireccion();
            int num2 = rand() % 5;
            int dir = abs(num1 - num2);
            //dir = 1;

            if(dir == 0){
                dinosaurios[i]->marriba(todoSprite, numlayers, height_map, width_map, tilemapSprite, mapas);
                dinosaurios[i]->marriba(todoSprite, numlayers, height_map, width_map, tilemapSprite, mapas);
            }
            if(dir == 1){
                dinosaurios[i]->mabajo(todoSprite, numlayers, height_map, width_map, tilemapSprite, mapas);
                dinosaurios[i]->mabajo(todoSprite, numlayers, height_map, width_map, tilemapSprite, mapas);
            }
            if(dir == 2){
                dinosaurios[i]->mderecha(todoSprite, numlayers, height_map, width_map, tilemapSprite, mapas);
                dinosaurios[i]->mderecha(todoSprite, numlayers, height_map, width_map, tilemapSprite, mapas);
            }
            if(dir == 3){
                dinosaurios[i]->mizquierda(todoSprite, numlayers, height_map, width_map, tilemapSprite, mapas);
                dinosaurios[i]->mizquierda(todoSprite, numlayers, height_map, width_map, tilemapSprite, mapas);
            }
            else{
                dinosaurios[i]->sumaPasos();
                dinosaurios[i]->sumaPasos();
            }
        }
    }
    else{ // Contador de iteraciones del programa
        for(int i=0; i < tam_dinos; i++){
            int cosas [5] = { 0, 1, 2, 3, 4 };
            int meh = cosas[i];
            dinosaurios[i]->setDireccion(meh);
            
            srand (time(NULL));
            int num1 = dinosaurios[i]->getDireccion();
            int num2 = rand() % 5;
            int dir = abs(num1 - num2);
            //dir = 1;

            if(dir == 0){
                dinosaurios[i]->marriba(todoSprite, numlayers, height_map, width_map, tilemapSprite, mapas);
                dinosaurios[i]->marriba(todoSprite, numlayers, height_map, width_map, tilemapSprite, mapas);
            }
            if(dir == 1){
                dinosaurios[i]->mabajo(todoSprite, numlayers, height_map, width_map, tilemapSprite, mapas);
                dinosaurios[i]->mabajo(todoSprite, numlayers, height_map, width_map, tilemapSprite, mapas);
            }
            if(dir == 2){
                dinosaurios[i]->mderecha(todoSprite, numlayers, height_map, width_map, tilemapSprite, mapas);
                dinosaurios[i]->mderecha(todoSprite, numlayers, height_map, width_map, tilemapSprite, mapas);
            }
            if(dir == 3){
                dinosaurios[i]->mizquierda(todoSprite, numlayers, height_map, width_map, tilemapSprite, mapas);
                dinosaurios[i]->mizquierda(todoSprite, numlayers, height_map, width_map, tilemapSprite, mapas);
            }
            else{
                dinosaurios[i]->sumaPasos();
                dinosaurios[i]->sumaPasos();
            }
        }
    }
}