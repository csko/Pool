#include <iostream>
#include "../include/MyGameState.h"
#include "../include/game.h"
#include "../include/tvector.h"
#include "../include/tray.h"

using namespace std;

// src/game.cpp
class golyo;
class Game;

MyGameState::MyGameState(Game* _game) {
    game = _game;
    timeStep = 1.0f / 60.0f;
    timeStep = 1.0f / 10.0f; // Gyorsabb tesztelés

    // Create the 4 sides
    pl[0].position = TVector(-25.0f, -49.0f, 0); // lower left
    pl[0].normal = TVector(1, 0, 0);

    pl[1].position = TVector(-25.0f, -49.0f, 0); // lower left
    pl[1].normal = TVector(0, 1, 0);

    pl[2].position = TVector(25.0f, 49.0f, 0); // lower left
    pl[2].normal = TVector(-1, 0, 0);

    pl[3].position = TVector(25.0f, 49.0f, 0); // lower left
    pl[3].normal = TVector(0,- 1, 0);

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

        movement[i] = TVector(0, 0, 0);
    }
    initDone = true;
}

void MyGameState::hit(float x, float y){
    movement[0] = TVector(x, y, 0);
    // TODO: angle?
}

void MyGameState::updateBalls(){
    if(initDone == false){
        return;
    }

    float lambda;
    double rt,rt2,rt4;
    TVector norm,uveloc;
    TVector Pos2;
    TVector normal,point,time;
    double RestTime,BallTime;
    int BallNr=0,dummy=0,BallColNr1,BallColNr2;

    //Compute velocity for next timestep using Euler equations

    // 5% linear friction
    float friction = 1.05f;
    for (int i=0; i <= 15; i++){
        movement[i] *= 1/friction;
        if(movement[i].mag() < 0.1f){
            movement[i] = TVector(0, 0, 0);
        }
    }

    RestTime=timeStep; // timestep
    lambda=1000;

    //While timestep not over
    while (RestTime > eps){
       lambda=10000;   //initialize to very large value

       //For all the balls find closest intersection between balls and planes
        for (int i=0; i <= 15; i++){
            //compute new position and distance
            oldPos[i]=balls[i];
            TVector::unit(movement[i], uveloc);
            balls[i] += movement[i] * RestTime;
            rt2 = oldPos[i].dist(balls[i]);

            //Test if collision occured between ball and all 4 planes
            for(int wall = 0; wall < 4; wall++){
                if (TestIntersionPlane(pl[wall], oldPos[i], uveloc, rt, norm)) {
                    //Find intersection time
                    rt4=rt*RestTime/rt2;

                    //if smaller than the one already stored replace and in timestep
                    if (rt4<=lambda and rt4<=RestTime+ZERO){
                        if (! ((rt<=ZERO)&&(uveloc.dot(norm)>ZERO)) ){
                            normal=norm;
                            point=oldPos[i]+uveloc*rt;
                            lambda=rt4;
                            BallNr=i;
                        }
                    }
                }
            }

        }

       // After all balls have been tested with planes, test for collision
       // between them and replace if collision time smaller
       if (FindBallCol(Pos2,BallTime,RestTime,BallColNr1,BallColNr2)){
            if ( (lambda==10000) || (lambda>BallTime) ) {
                game->collision(BallColNr1, BallColNr2);
                RestTime = RestTime - BallTime;

                TVector pb1,pb2,xaxis,U1x,U1y,U2x,U2y,V1x,V1y,V2x,V2y;
                double a,b;

                pb1 = oldPos[BallColNr1] + movement[BallColNr1] * BallTime;
                pb2 = oldPos[BallColNr2] + movement[BallColNr2] * BallTime;

                xaxis = (pb2 - pb1).unit();
                a = xaxis.dot(movement[BallColNr1]);

                U1x = xaxis * a;
                U1y = movement[BallColNr1] - U1x;

                xaxis = (pb1 - pb2).unit();
                b = xaxis.dot(movement[BallColNr2]);

                U2x = xaxis * b;
                U2y = movement[BallColNr2] - U2x;

                V1x = (U1x + U2x - (U1x - U2x)) * 0.5;
                V2x = (U1x + U2x - (U2x - U1x)) * 0.5;
                V1y = U1y;
                V2y = U2y;

                for (int j=0; j<=15;j++){
                    balls[j] = oldPos[j] + movement[j] * BallTime;
                }

                movement[BallColNr1] = V1x + V1y;
                movement[BallColNr2] = V2x + V2y;

/*
                    //Update explosion array
                      for(j=0;j<20;j++)
					  {
						  if (ExplosionArray[j]._Alpha<=0)
						  {
							  ExplosionArray[j]._Alpha=1;
                              ExplosionArray[j]._Position=ArrayPos[BallColNr1];
							  ExplosionArray[j]._Scale=1;
							  break;
						  }
					  }
					  */



					  continue; // ????
                }
            }

            //End of tests
            //If collision occured move simulation for the correct timestep
            //and compute response for the colliding ball
            if (lambda!=10000){
                RestTime-=lambda;

                for (int j=0; j <= 15; j++){
                    balls[j] = oldPos[j] + movement[j] * lambda;
                }
                rt2 = movement[BallNr].mag();
                movement[BallNr].unit(); // TODO
                movement[BallNr] = TVector::unit( (normal*(2*normal.dot(-movement[BallNr]))) + movement[BallNr] );
                movement[BallNr] = movement[BallNr]*rt2;
/*
                    //Update explosion array
                    for(j=0;j<20;j++)
					  {
						  if (ExplosionArray[j]._Alpha<=0)
						  {
							  ExplosionArray[j]._Alpha=1;
                              ExplosionArray[j]._Position=point;
							  ExplosionArray[j]._Scale=1;
							  break;
						  }
					  }
*/
                } else {
                    RestTime=0;
                }
        }
    game->setMovement(false);
    for(int i = 0; i <= 15; i++){
        game->golyok[i].x = balls[i].X();
        game->golyok[i].y = balls[i].Y();
        if(movement[i].mag() > 0.01){
            game->setMovement(true);
        }
    }
}

void MyGameState::removeBall(int id){
    moveBall(id, -50000, -50000); // Hack :)
}

void MyGameState::moveBall(int id, float x, float y){
    balls[id] = TVector(x, y, 0);
    movement[id] = TVector(0, 0, 0);
}

bool TestIntersionPlane(const Plane& plane, const TVector& position, const TVector& direction, double& lambda, TVector& pNormal) {
    double DotProduct = direction.dot(plane.normal);
    double l2;

    // determine if ray parallel to plane
    if (DotProduct < ZERO  && DotProduct > -ZERO){
        return false;
    }

    l2 = plane.normal.dot(plane.position - position) / DotProduct;

    if (l2 < -ZERO) {
        return false;
    }

    pNormal = plane.normal;
    lambda = l2;

    return true;
}

bool MyGameState::FindBallCol(TVector& point, double& TimePoint, double Time2, int& BallNr1, int& BallNr2){
    TVector RelativeV;
    TRay rays;

    double MyTime=0.0, Add=Time2/150.0, Timedummy=10000, Timedummy2=-1;

    TVector posi;

    //Test all balls against eachother in 150 small steps

    for (int i = 0; i <= 15-1; i++){
        for (int j = i + 1; j<= 15; j++){
            RelativeV = movement[i] - movement[j];

            rays = TRay(oldPos[i],TVector::unit(RelativeV));
            MyTime=0.0;
            if ( rays.dist(oldPos[j]) > 10){
                continue;
            }
            while (MyTime < Time2){
                MyTime += Add;
                posi = oldPos[i] + RelativeV * MyTime;
                if (posi.dist(oldPos[j]) <= 3) {
                    point = posi;
                    if (Timedummy > (MyTime-Add)) {
                        Timedummy = MyTime - Add;
                    }
                    BallNr1=i;
                    BallNr2=j;
                    break;
                }
            }
        }
    }
    if (Timedummy!=10000) {
        TimePoint=Timedummy;
        return true;
    }
    return false;
}
