#include "../include/game.h"

using namespace std;

Vector white(0, 60);
Vector movement[16];
struct golyo golyok[16];
bool disabled[16];
bool isMovement = false;
Game game;

float holes[6][2] = {{8.18, 24.89},{7.88, -27.43},{8.2, -2.11},
                     {-57.68, -27.42},{-58, 24.89},{-58, -81.03}
                     };

void balraIrany(){
    if(!isMovement){
        white.rotate(balra_a);
    }
}
void jobbraIrany(){
    if(!isMovement){
        white.rotate(-jobbra_a);
    }
}
void erosit(){
    if(!isMovement){
        white *= erosit_a;
        const float maxlen = 200;
        if(white.length() >= maxlen){
            white.normalize();
            white *= maxlen;
        }
    }
}
void gyengit(){
    if(!isMovement){
        white /= erosit_a;
        const float minlen = 1;
        if(white.length() <= minlen){
            white.normalize();
            white *= minlen;
        }
    }
}

Game::Game(){
    b2Vec2 gravity(0.0f, 0.0f);
    bool doSleep = false;
    state = new GameState(gravity, doSleep);
}

void Game::hit(){
    if(!isMovement){
        state->hit(white.getX(), white.getY());
    }
}

void Game::updateBalls(){
    state->updateBalls();
    for(int i = 0; i <= 15; i++){
        for(int j = 0; j < 6; j++){
            int x = holes[j][0];
            int y = holes[j][1];
            int px = golyok[i].x;
            int py = golyok[i].y;
            if((x-px)*(x-px) + (y-py)*(y-py) < 20){
                disabled[i] = true;
                state->removeBall(i);
                // TODO: remove from state
                // TODO: cue ball reset, 8-ball, etc.
            }
        }
    }
}

Game::~Game(){
    delete state;
}

void Game::init(){
    state->init();
}

GameState::GameState(b2Vec2 gravity, bool doSleep) : world(gravity, doSleep){
    timeStep = 1.0f / 60.0f;
    velocityIterations = 6;
    positionIterations = 2;

    // Ball definition

    ballShape.m_radius = 2.0f;

    ballFixture.shape = &ballShape;
    ballFixture.density = 10.0f;
    ballFixture.friction = 0.8f;
    ballFixture.restitution = 0.8f;
    ballDef.type = b2_dynamicBody;
    ballDef.linearDamping = 0.5f; // TODO: angular damping

    // Side definition
    b2PolygonShape sideShape;

    b2BodyDef sideDef;
    sideDef.type = b2_staticBody;

    // Create the 4 sides

    sideDef.position.Set(-60.4f, -84.29f);
    sideShape.SetAsBox(500.0f, 0.1f);
    sides[0] = world.CreateBody(&sideDef);
    sides[0]->CreateFixture(&sideShape, 0.0f);

    sideDef.position.Set(-60.4f, -84.29f);
    sideShape.SetAsBox(0.1f, 500.0f);
    sides[1] = world.CreateBody(&sideDef);
    sides[1]->CreateFixture(&sideShape, 0.0f);

    sideDef.position.Set(10.6f, 28.14f);
    sideShape.SetAsBox(0.1f, 500.0f);
    sides[2] = world.CreateBody(&sideDef);
    sides[2]->CreateFixture(&sideShape, 0.0f);

    sideDef.position.Set(10.6f, 28.14f);
    sideShape.SetAsBox(500.0f, 0.1f);
    sides[3] = world.CreateBody(&sideDef);
    sides[3]->CreateFixture(&sideShape, 0.0f);

    initDone = false;
}

GameState::~GameState(){
    for(int i = 0; i <= 15; i++){
        world.DestroyBody(balls[i]);
    }
    for(int i = 0; i < 4; i++){
        world.DestroyBody(sides[i]);
    }
}

void GameState::init(){
    if(initDone == true){
        return;
    }
    for(int i = 0; i <= 15; i++){
        ballDef.position.Set(golyok[i].x, golyok[i].y);
        lastpos[i].Set(golyok[i].x, golyok[i].y);
        balls[i] = world.CreateBody(&ballDef);
        balls[i]->CreateFixture(&ballFixture);
        balls[i]->SetBullet(true); // For greater precision
    }
    initDone = true;
}

void GameState::hit(float x, float y){
    const float mult = 30;
    balls[0]->ApplyLinearImpulse(b2Vec2(x * mult * balls[0]->GetMass(), y * mult * balls[0]->GetMass()), balls[0]->GetWorldCenter());
    // TODO: angle
}

void GameState::updateBalls(){
    if(initDone == false){
        return;
    }
    world.Step(timeStep, velocityIterations, positionIterations);
    world.ClearForces();
    isMovement = false;
    float32 diff = 0;
    for(int i = 0; i <= 15; i++){
        b2Vec2 position = balls[i]->GetPosition();
        golyok[i].x = position.x;
        golyok[i].y = position.y;
        // TODO: angle

        diff += (lastpos[i] - position).Length();
        lastpos[i] = position;

    }
    if(diff > 0.1){ // TODO
        isMovement = true;
    }
}

void GameState::removeBall(int id){
    // TODO
}
