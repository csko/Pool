#include "../include/game.h"
#include <iostream>

using namespace std;

Vector white(0, -60);
Vector movement[16];
struct golyo golyok[16];
bool disabled[16];
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

    b2Vec2 gravity(0.0f, 0.0f);
    bool doSleep = false;
    state = new B2GameState(this, gravity, doSleep);
}

bool Game::getMovement(){
    return isMovement;
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
