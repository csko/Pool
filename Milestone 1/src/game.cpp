#include "../include/game.h"

Vector white(0, 20);
Vector movement[16];
struct golyo golyok[16];
bool isMovement = false;

void hit(){ 
    // A fehér golyót el kell indítani
    movement[0] += white;
}

void balraIrany(){
    white.rotate(balra_a);
}
void jobbraIrany(){
    white.rotate(-jobbra_a);
}
void erosit(){
    white *= erosit_a;
    /* TODO: max érték
    if(white.len() >= MAX){
        white.normalize();
        white *= MAX;
    }
    */
}
void gyengit(){
    white /= erosit_a;
    /* TODO: min érték
    if(white.len() <= MIN){
        white.normalize();
        white *= MIN;
    }
    */
}


