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

    float RestTime = timeStep;
    float lambda;
    float accel = 1.0f;
    Vector oldPos[16];

    //Compute velocity for next timestep using Euler equations
    for (i=0; i <= 15; i++)
      movement[i] += accel*RestTime;

    //While timestep not over
    while (RestTime > eps){
       lambda=10000;   //initialize to very large value

       //For all the balls find closest intersection between balls and planes
        for (int i=0; i <= 15; i++){
            //compute new position and distance
            oldPos[i]=balls[i];
            uveloc = movement[i];
            uveloc.normalize();
            balls[i] += movement[i] * RestTime;
            rt2 = oldPos[i].dist(balls[i]); // TODO: dist

            //Test if collision occured between ball and all 5 planes
            if (TestIntersionPlane(pl1, oldPos[i], uveloc, rt, norm)) {
                //Find intersection time
                rt4=rt*RestTime/rt2;

                //if smaller than the one already stored replace and in timestep
                if (rt4<=lamda and rt4<=RestTime+ZERO){
                    if (! ((rt<=ZERO)&&(uveloc.dot(norm)>ZERO)) ){
                        normal=norm;
                        point=OldPos[i]+uveloc*rt;
                        lamda=rt4;
                        BallNr=i;
                    }
                }
            }
/*
			  if (TestIntersionPlane(pl2,OldPos[i],uveloc,rt,norm))
			  {
				   rt4=rt*RestTime/rt2;

				  if (rt4<=lamda)
				  { 
				    if (rt4<=RestTime+ZERO)
						if (! ((rt<=ZERO)&&(uveloc.dot(norm)>ZERO)) )
						 {
							normal=norm;
							point=OldPos[i]+uveloc*rt;
							lamda=rt4;
							BallNr=i;
							dummy=1;
						 }
				  }
				 
			  }
*/
 // 3 more planes...
       // After all balls have been tested with planes, test for collision
       // between them and replace if collision time smaller


       if (FindBallCol(Pos2,BallTime,RestTime,BallColNr1,BallColNr2)){
            if ( (lamda==10000) || (lamda>BallTime) ) {
                RestTime=RestTime-BallTime;

                TVector pb1,pb2,xaxis,U1x,U1y,U2x,U2y,V1x,V1y,V2x,V2y;
                double a,b;

                pb1=OldPos[BallColNr1]+ArrayVel[BallColNr1]*BallTime;
                pb2=OldPos[BallColNr2]+ArrayVel[BallColNr2]*BallTime;
                xaxis=(pb2-pb1).unit();

                a=xaxis.dot(ArrayVel[BallColNr1]);
                U1x=xaxis*a;
                U1y=ArrayVel[BallColNr1]-U1x;

                xaxis=(pb1-pb2).unit();
                b=xaxis.dot(ArrayVel[BallColNr2]);
                U2x=xaxis*b;
                U2y=ArrayVel[BallColNr2]-U2x;

                V1x=(U1x+U2x-(U1x-U2x))*0.5;
                V2x=(U1x+U2x-(U2x-U1x))*0.5;
                V1y=U1y;
                V2y=U2y;

                for (j=0;j<NrOfBalls;j++)
                    ArrayPos[j]=OldPos[j]+ArrayVel[j]*BallTime;

                    ArrayVel[BallColNr1]=V1x+V1y;
                    ArrayVel[BallColNr2]=V2x+V2y;

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
			if (lamda!=10000)
			{		 
				      RestTime-=lamda;

					  for (j=0;j<NrOfBalls;j++)
					  ArrayPos[j]=OldPos[j]+ArrayVel[j]*lamda;

					  rt2=ArrayVel[BallNr].mag();
					  ArrayVel[BallNr].unit();
					  ArrayVel[BallNr]=TVector::unit( (normal*(2*normal.dot(-ArrayVel[BallNr]))) + ArrayVel[BallNr] );
					  ArrayVel[BallNr]=ArrayVel[BallNr]*rt2;
							
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
			}
			else RestTime=0;

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

bool TestIntersionPlane(const Plane& plane, const Vector& position, const Vector& direction, double& lamda, TVector& pNormal) {

    double DotProduct = dot(direction, plane.normal);
    double l2;

    // determine if ray parallel to plane
    if (DotProduct < ZERO  && DotProduct > -ZERO){
        return false;
    }

    l2 = dot(plane.normal, plane.position - position) / DotProduct;

    if (l2 < -ZERO) {
        return false;
    }

    pNormal = plane.normal;
    lamda = l2;

    return true;
}
/*
int FindBallCol(TVector& point, double& TimePoint, double Time2, int& BallNr1, int& BallNr2)

{

	TVector RelativeV;

	TRay rays;

	double MyTime=0.0, Add=Time2/150.0, Timedummy=10000, Timedummy2=-1;

	TVector posi;

	

	//Test all balls against eachother in 150 small steps

	for (int i=0;i<NrOfBalls-1;i++)

	{

	 for (int j=i+1;j<NrOfBalls;j++)

	 {	

		    RelativeV=ArrayVel[i]-ArrayVel[j];

			rays=TRay(OldPos[i],TVector::unit(RelativeV));

			MyTime=0.0;



			if ( (rays.dist(OldPos[j])) > 40) continue; 



			while (MyTime<Time2)

			{

			   MyTime+=Add;

			   posi=OldPos[i]+RelativeV*MyTime;

			   if (posi.dist(OldPos[j])<=40) {

										   point=posi;

										   if (Timedummy>(MyTime-Add)) Timedummy=MyTime-Add;

										   BallNr1=i;

										   BallNr2=j;

										   break;

										}

			

			}

	 }



	}



	if (Timedummy!=10000) { TimePoint=Timedummy;

	                        return 1;

	}



	return 0;

}

*/