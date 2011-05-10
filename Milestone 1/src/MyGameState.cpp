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
    // TODO: Put balls in their correct position.
    // TODO: Reset movement vectors.
    initDone = true;
}

void MyGameState::hit(float x, float y){
    // TODO: adjust movement vector of the white ball
    // TODO: angle
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
    // TODO: remove ball
}

void MyGameState::moveBall(int id, float x, float y){
    // TODO: move ball
}
