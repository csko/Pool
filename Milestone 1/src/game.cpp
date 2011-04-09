#include "../include/game.h"
#include <cstdio>
#include <iostream>

using namespace std;

Vector white(0, 20);
Vector movement[16];
struct golyo golyok[16];
bool isMovement = false;
Game game;

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

Game::Game(){
    b2Vec2 gravity(0.0f, 0.0f);
    bool doSleep = false;
    state = new GameState(gravity, doSleep);
}

void Game::hit(){
    state->hit(white.getX(), white.getY());
}

void Game::updateBalls(){
    state->updateBalls();
}

Game::~Game(){
    delete state;
}

void Game::init(){
//    cout << "Loading ball positions into engine" << endl;
    for(int i = 0; i <= 15; i++){
//        printf("%d %f %f\n", i, golyok[i].x, golyok[i].y);
    }
    state->init();
}

GameState::GameState(b2Vec2 gravity, bool doSleep) : world(gravity, doSleep){
    timeStep = 1.0f / 60.0f;
    velocityIterations = 6;
    positionIterations = 2;

    ballShape.m_radius = 2.0f;

    ballFixture.shape = &ballShape;
    ballFixture.density = 1.0f;
    ballFixture.friction = 0.3f;
    ballFixture.restitution = 1.0f;

    ballDef.type = b2_dynamicBody;

    initDone = false;
}

GameState::~GameState(){
}

void GameState::init(){
    for(int i = 0; i <= 15; i++){
        ballDef.position.Set(golyok[i].x, golyok[i].y);
        balls[i] = world.CreateBody(&ballDef);
        balls[i]->CreateFixture(&ballFixture);
    }
    initDone = true;
}

void GameState::hit(float x, float y){
    balls[0]->ApplyLinearImpulse(b2Vec2(x  * balls[0]->GetMass(), y * balls[0]->GetMass()), balls[0]->GetWorldCenter());
    // TODO: angle
}

void GameState::updateBalls(){
    if(initDone == false){
        return;
    }
    world.Step(timeStep, velocityIterations, positionIterations);
    world.ClearForces();
    for(int i = 0; i <= 15; i++){
        b2Vec2 position = balls[i]->GetPosition();
        golyok[i].x = position.x;
        golyok[i].y = position.y;
        // TODO: angle
    }

}

