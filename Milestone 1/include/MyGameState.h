#ifndef _MYGAMESTATE_
#define _MYGAMESTATE_
#include "vector.h"
#include "../include/tvector.h"
#include "../include/game.h"

struct Plane{
    TVector position;
    TVector normal;
};

class MyGameState : public GameState {
    public:
        MyGameState(Game* game);
        ~MyGameState();

        void init();
        void hit(float x, float y);
        void updateBalls();
        void removeBall(int id);
        void moveBall(int id, float x, float y);
    private:
        bool FindBallCol(TVector& point, double& TimePoint, double Time2, int& BallNr1, int& BallNr2);
        float  timeStep;
        TVector balls[16];
        Vector lastpos[16];
        TVector movement[16];
        TVector oldPos[16];

        bool initDone;
        Game* game;
};

#endif
