#ifndef _MYGAMESTATE_
#define _MYGAMESTATE_
#include "vector.h"
#include "../include/game.h"

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
        float  timeStep;
        Vector balls[16];
        Vector lastpos[16];

        bool initDone;
        Game* game;
};
#endif
