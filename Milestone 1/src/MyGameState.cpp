#include "../include/MyGameState.h"
#include "../include/game.h"
#include <iostream>

using namespace std;

// src/game.cpp
class golyo;
class Game;

MyGameState::MyGameState(Game* _game) {
    game = _game;
    timeStep = 1.0f / 60.0f;

    // Create the 4 sides
    /*
    sideDef.position.Set(-25.0f, -49.0f);
    sideDef.position.Set(-25.0f, -49.0f);
    sideDef.position.Set(25.0f, 49.0f);
    sideDef.position.Set(25.0f, 49.0f);
    */
    

    initDone = false;
}

MyGameState::~MyGameState(){
}

void MyGameState::init(){
    if(initDone == true){
        //return;
    }
    for(int i = 0; i <= 15; i++){
        lastpos[i].setX(game->golyok[i].x);
        lastpos[i].setY(game->golyok[i].y);

        moveBall(i, game->golyok[i].x, game->golyok[i].y);

        movement[i].setX(0);
        movement[i].setY(0);
    }
    initDone = true;
}

void MyGameState::hit(float x, float y){
    movement[0].setX(x);
    movement[0].setY(y);
    // TODO: angle?
}

void MyGameState::updateBalls(){
    if(initDone == false){
        return;
    }

    // TODO: Do the collision detection, response.
    // TODO: game->setMovement() accordingly
    // TODO: change game->golyok[i]
}

void MyGameState::removeBall(int id){
    moveBall(id, -50000, -50000); // Hack :)
}

void MyGameState::moveBall(int id, float x, float y){
    balls[id].setX(x);
    balls[id].setY(y);
}
