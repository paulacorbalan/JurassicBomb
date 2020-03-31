#include <SFML/Graphics.hpp>
#include <iostream>
#include "ia.h"

#include "include/config.h"
#include "dinosaurio/dinosaurio.h"

void meteDinosaurio(int tipo){
    bool hecho = false;
    while (hecho == false)
    {
        if(tipo == 0){ //T-Rex
            Dinosaurio dino(0, 2, (int) 0.15*0.85);
            dino.movimiento();
            hecho = true;
        }
        else if(tipo == 1){ //Velociraptor
            Dinosaurio dino(1, 1, (int) 0.15*1.15);
            dino.movimiento();
            hecho = true;
        }
        else if(tipo == 2){ //Pterodactilo
            Dinosaurio dino(2, 1, (int) 0.15);
            dino.movimiento();
            hecho = true;
        }
        else if(tipo == 3){ //Triceratops
            Dinosaurio dino(3, 1, (int) 0.15);
            dino.movimiento;
            hecho = true;
        }
        else
        {
            Dinosaurio dino();
        }
        
    }
}