#include "../include/game.h"
#include <iostream>

using namespace std;

Vector white(0, -60);
Vector movement[16];
struct golyo golyok[16];
bool disabled[16];
bool isMovement = false;
Game game;

char* player1="Player1";
char* player2="Player2";
bool p1Balls[16] = {false, false, true, true, false, false, false, true, true, false, true, false, true, false, true, false};
bool p2Balls[16] = {false, true, false, false, true, false, true, false, false, true, false, true, false, true, false, true};
int p1Score = 0;
int p2Score = 0;
bool p1Turn=true;
bool p2Turn=false;
int stepNum = 1; //hanyszor kovetkezik az adott jatekos meg
bool end = false; //vege van-e a jateknak
int winner = 0; //ki a nyertes
bool isRoundOver = true;
//milyen esemény történt egy ütés során
bool blackHole = false; //lement a fekete
bool whiteHole = false; //lement a feher
bool p1Ball = false; //ment le tomor golyo 
bool p2Ball = false; //ment le csikos golyo
bool firstTouchP1Ball = false; //elso erintett golyo tomor volt
bool firstTouchP2Ball = false; //elso erintett golyo csikos volt
bool firstTouchBlack = false; //elso erintett golyo fekete volt



float holes[6][2] = {{25.549, -50},{27.564, 0},{25.549, 51},
                     {-25.549, 51},{-27.564, 0},{-25.549, -50.275}
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
        isRoundOver = false;
    }
}

void Game::updateBalls(){
    state->updateBalls();
}

Game::~Game(){
    delete state;
}

void Game::init(){
    state->init();
}

bool Game::getP1Turn(){
    return p1Turn;
}
bool Game::getEnd(){
    return end;
}
void Game::setEnd(bool e){
    end = e;
}
int Game::getP1Score(){
    return p1Score;
}
int Game::getP2Score(){
    return p2Score;
}

void Game::roundOver(){
    isRoundOver = true;
    if(p1Turn){
       if(blackHole){
           if(p1Score == 7){
               winner = 1;
               end = true;
           }else{
               winner = 2;
               end = true;
           }
       }
       if(p1Ball && !p2Ball){
           stepNum = 1;
       }
       if(!p1Ball && p2Ball){
           stepNum = 1;
           p2Turn = true; p1Turn = false;
       }
       if(!p1Ball && !p2Ball){
           if(stepNum==2){stepNum--;}
           else{p2Turn = true; p1Turn = false;}
       }
       if(p1Ball && p2Ball){
           stepNum = 1;
           p2Turn = true;
           p1Turn = false;
       }
       if(whiteHole){
           p2Turn = true;
           p1Turn = false;
           stepNum = 2;
       }
    }else{
       if(blackHole){
           if(p2Score == 7){
               winner = 2;
               end = true;
           }else{
               winner = 1;
               end = true;
           }
       }
       if(!p1Ball && p2Ball){
           stepNum = 1;
       }
       if(p1Ball && !p2Ball){
           stepNum = 1;
           p2Turn = false; p1Turn = true;
       }
       if(!p1Ball && !p2Ball){
           if(stepNum==2){stepNum--;}
           else{p2Turn = false; p1Turn = true;}
       }
       if(p1Ball && p2Ball){
           stepNum = 1;
           p2Turn = false;
           p1Turn = true;
       }
       if(whiteHole){
           p2Turn = false;
           p1Turn = true;
           stepNum = 2;
       }
    }
    p1Ball = false;
    p2Ball = false;
    whiteHole = false;    
    blackHole = false;
    if(end){
        p1Turn = 1;
        p1Score = 0;
        p2Score = 0;
        stepNum = 1;   
    }
}

GameState::GameState(b2Vec2 gravity, bool doSleep) : world(gravity, doSleep){
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

GameState::~GameState(){
    for(int i = 0; i <= 15; i++){
        if(balls[i]){
            world.DestroyBody(balls[i]);
        }
    }
    for(int i = 0; i < 4; i++){
        world.DestroyBody(sides[i]);
    }
}

void GameState::init(){
    if(initDone == true){
        //return;
    }
    for(int i = 0; i <= 15; i++){
        if(balls[i])world.DestroyBody(balls[i]);
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

    for(int i = 0; i <= 15; i++){
        for(int j = 0; j < 6; j++){
            int x = holes[j][0];
            int y = holes[j][1];
            int px = golyok[i].x;
            int py = golyok[i].y;
            if((x-px)*(x-px) + (y-py)*(y-py) < 30){
                if(i != 0 && !disabled[i]){
                    disabled[i] = true;
                    removeBall(i);
	            if(p1Balls[i]) {p1Score++;p1Ball=true;} //lemenet egy tomor golyo
	            if(p2Balls[i]) {p2Score++;p2Ball=true;} //lemenet egy csikos golyo
		    if(i==5) blackHole=true; //lement a fekete
                }else if(i==0){ // Reset the ball
//                    cout << "reset" << endl;
                    whiteHole=true; //lement a fehér
                    world.DestroyBody(balls[0]);

                    ballDef.position.Set(0, 25); // TODO
                    lastpos[0].Set(golyok[0].x, golyok[0].y);
                    balls[0] = world.CreateBody(&ballDef);
                    balls[0]->CreateFixture(&ballFixture);
                    balls[0]->SetBullet(true); // For greater precision
                }
                // TODO:  8-ball, etc.
            }
        }
    }


    world.Step(timeStep, velocityIterations, positionIterations);
    world.ClearForces();
    isMovement = false;
    for(int i = 0; i <= 15; i++){
        if(!balls[i]){
            continue;
        }
        b2Vec2 position = balls[i]->GetPosition();
        golyok[i].x = position.x;
        golyok[i].y = position.y;
        // TODO: angle
        float32 diff = (lastpos[i] - position).Length();
        lastpos[i] = position;
        if(diff > 0.01){ // TODO
           isMovement = true;
        }
    }
    if(!isMovement && !isRoundOver){
        game.roundOver();
    }
}


void GameState::removeBall(int id){
    if(id == 0){
//        balls[id].SetPosition(10, 10);
    }else if(balls[id]){
        world.DestroyBody(balls[id]);
        balls[id] = NULL;
    }
    // TODO
}

