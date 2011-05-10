#include "../include/game.h"
#include "../include/B2GameState.h"
#include "../include/MyGameState.h"
#include <iostream>

using namespace std;

Vector white(0, -10);
Vector movement[16];
Game game;

// TODO: ezeket bele kell rakni Game osztályba
//milyen esemény történt egy ütés során
bool firstTouchP1Ball = false; //elso erintett golyo tomor volt
bool firstTouchP2Ball = false; //elso erintett golyo csikos volt
bool firstTouchBlack = false; //elso erintett golyo fekete volt


void balraIrany(){
    if(!game.getMovement()){
        white.rotate(balra_a);
    }
}
void jobbraIrany(){
    if(!game.getMovement()){
        white.rotate(-jobbra_a);
    }
}
void erosit(){
    if(!game.getMovement()){
        white *= erosit_a;
        const float maxlen = 200;
        if(white.length() >= maxlen){
            white.normalize();
            white *= maxlen;
        }
    }
}
void gyengit(){
    if(!game.getMovement()){
        white /= erosit_a;
        const float minlen = 1;
        if(white.length() <= minlen){
            white.normalize();
            white *= minlen;
        }
    }
}

Game::Game(){
    isMovement = false;
    isRoundOver = true;
    p1Score = p2Score = 0;
    p1Turn = true;
    p2Turn = false;
    winner = 0;
    blackHole = whiteHole = false;
    p1Ball = p2Ball = false;
    end = false;
    stepNum = 1;

    b2Vec2 gravity(0.0f, 0.0f);
    bool doSleep = false;
//    state = new B2GameState(this, gravity, doSleep);
    state = new MyGameState(this);
}

bool Game::getMovement(){
    return isMovement;
}

bool Game::getRoundOver(){
    return isRoundOver;
}

void Game::setMovement(bool m){
    isMovement = m;
}

void Game::hit(){
    if(!isMovement){
        state->hit(white.getX(), white.getY());
        isRoundOver = false;
    }
}

void Game::updateBalls(){
    state->updateBalls(); // Update the position of the balls

    if(!getMovement() && !getRoundOver()){
       roundOver();
    }

    // Handle balls falling in the holes
    for(int i = 0; i <= 15; i++){
        for(int j = 0; j < 6; j++){
            int x = holes[j][0];
            int y = holes[j][1];
            int px = golyok[i].x;
            int py = golyok[i].y;
            if((x-px)*(x-px) + (y-py)*(y-py) < 30){ // TODO: 30 jo ertek?
                if(i != 0 && !disabled[i]){
                    disabled[i] = true;
                    state->removeBall(i);

                    if(p1Balls[i]){
                        p1Score++;
                        p1Ball=true;
                    } //lement egy tomor golyo

                    if(p2Balls[i]){
                    p2Score++;
                    p2Ball=true;
                    } //lement egy csikos golyo

                if(i==5) blackHole=true; //lement a fekete
                }else if(i==0){ // Reset the ball
                    whiteHole=true; //lement a fehér
                    state->moveBall(0, 0, 25); // TODO: jo pozicio?
                }
                // TODO:  8-ball, etc.
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
void Game::collision(int a, int b){ // Balls a and b have collided
    cout << "collision " << a << " " << b << endl;
    // TODO
}
void hole(int a, int h){ // Ball a has fallen into hole h
    // TODO
}
