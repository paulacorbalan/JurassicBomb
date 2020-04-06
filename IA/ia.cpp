#include <iostream>
#include "ia.h"

/* Genera numeros aleatorios entre el 0 y el 4 para ver en que direccion se mueve.
 * Usa un contador de iteraciones del programa para que no dependa del tiempo
 */

void IA::movimientoDinos(vector<Dinosaurio*> dinosaurios, int _cont){
    int tam_dinos = dinosaurios.size();

    if(_cont%50==0){ // Contador de iteraciones del programa
        for(int i=0; i < tam_dinos; i++){
            int cosas [5] = { 0, 1, 2, 3, 4 };
            int meh = cosas[i];
            dinosaurios[i]->setDireccion(meh);
            
            srand (time(NULL));
            int num1 = dinosaurios[i]->getDireccion();
            int num2 = rand() % 5;
            int dir = abs(num1 - num2);

            if(dir == 0){
                dinosaurios[i]->marriba();
                dinosaurios[i]->marriba();
            }
            if(dir == 1){
                dinosaurios[i]->mabajo();
                dinosaurios[i]->mabajo();
            }
            if(dir == 2){
                dinosaurios[i]->mderecha();
                dinosaurios[i]->mderecha();
            }
            if(dir == 3){
                dinosaurios[i]->mizquierda();
                dinosaurios[i]->mizquierda();
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

            if(dir == 0){
                dinosaurios[i]->marriba();
                dinosaurios[i]->marriba();
            }
            if(dir == 1){
                dinosaurios[i]->mabajo();
                dinosaurios[i]->mabajo();
            }
            if(dir == 2){
                dinosaurios[i]->mderecha();
                dinosaurios[i]->mderecha();
            }
            if(dir == 3){
                dinosaurios[i]->mizquierda();
                dinosaurios[i]->mizquierda();
            }
            else{
                dinosaurios[i]->sumaPasos();
                dinosaurios[i]->sumaPasos();
            }
        }
    }
}