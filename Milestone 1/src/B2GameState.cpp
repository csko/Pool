#include "../include/B2GameState.h"
#include "../include/game.h"
#include <iostream>

using namespace std;

// src/game.cpp
class golyo;

B2GameState::B2GameState(Game* _game, b2Vec2 gravity, bool doSleep) : world(gravity, doSleep){
    game = _game;
    timeStep = 1.0f / 60.0f;
    velocityIterations = 6;
    positionIterations = 2;

    // Ball definition

    ballShape.m_radius = 1.5f;

    ballFixture.shape = &ballShape;
    ballFixture.density = 10.0f;
    ballFixture.friction = 0.8f;
    ballFixture.restitution = 0.8f;
    ballDef.type = b2_dynamicBody;
    ballDef.linearDamping = 0.7f; // TODO: angular damping

    // Side definition
    b2PolygonShape sideShape;

    b2BodyDef sideDef;
    sideDef.type = b2_staticBody;

    // Create the 4 sides

    sideDef.position.Set(-25.0f, -49.0f);
    sideShape.SetAsBox(500.0f, 0.1f);
    sides[0] = world.CreateBody(&sideDef);
    sides[0]->CreateFixture(&sideShape, 0.0f);

    sideDef.position.Set(-25.0f, -49.0f);
    sideShape.SetAsBox(0.1f, 500.0f);
    sides[1] = world.CreateBody(&sideDef);
    sides[1]->CreateFixture(&sideShape, 0.0f);

    sideDef.position.Set(25.0f, 49.0f);
    sideShape.SetAsBox(0.1f, 500.0f);
    sides[2] = world.CreateBody(&sideDef);
    sides[2]->CreateFixture(&sideShape, 0.0f);

    sideDef.position.Set(25.0f, 49.0f);
    sideShape.SetAsBox(500.0f, 0.1f);
    sides[3] = world.CreateBody(&sideDef);
    sides[3]->CreateFixture(&sideShape, 0.0f);

    initDone = false;
}

B2GameState::~B2GameState(){
    for(int i = 0; i <= 15; i++){
        if(balls[i]){
            world.DestroyBody(balls[i]);
        }
    }
    for(int i = 0; i < 4; i++){
        world.DestroyBody(sides[i]);
    }
}

void B2GameState::init(){
    if(initDone == true){
        //return;
    }
    for(int i = 0; i <= 15; i++){
        if(balls[i])world.DestroyBody(balls[i]);
        ballDef.position.Set(game->golyok[i].x, game->golyok[i].y);
        lastpos[i].Set(game->golyok[i].x, game->golyok[i].y);
        balls[i] = world.CreateBody(&ballDef);
        balls[i]->CreateFixture(&ballFixture);
        balls[i]->SetBullet(true); // For greater precision
    }
    initDone = true;
}

void B2GameState::hit(float x, float y){
    const float mult = 30;
    balls[0]->ApplyLinearImpulse(b2Vec2(x * mult * balls[0]->GetMass(), y * mult * balls[0]->GetMass()), balls[0]->GetWorldCenter());
    // TODO: angle
}

void B2GameState::updateBalls(){
    if(initDone == false){
        return;
    }

    world.Step(timeStep, velocityIterations, positionIterations);
    world.ClearForces();
    game->setMovement(false);
    for(int i = 0; i <= 15; i++){
        if(!balls[i]){
            continue;
        }
        b2Vec2 position = balls[i]->GetPosition();
        game->golyok[i].x = position.x;
        game->golyok[i].y = position.y;
        // TODO: angle
        float32 diff = (lastpos[i] - position).Length();
        lastpos[i] = position;
        if(diff > 0.01){ // TODO
           game->setMovement(true);
        }
    }
}


void B2GameState::removeBall(int id){
    if(id == 0){
    }else if(balls[id]){
        world.DestroyBody(balls[id]);
        balls[id] = NULL;
    }
    // TODO
}

void B2GameState::moveBall(int id, float x, float y){
    world.DestroyBody(balls[id]);

    ballDef.position.Set(x, y);
    lastpos[id].Set(game->golyok[id].x, game->golyok[id].y);
    balls[id] = world.CreateBody(&ballDef);
    balls[id]->CreateFixture(&ballFixture);
    balls[id]->SetBullet(true); // For greater precision
}
