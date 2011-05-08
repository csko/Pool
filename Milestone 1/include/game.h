#ifndef _JATEKLOGIKA_
#define _JATEKLOGIKA_
#include "vector.h"
#include <GL/glut.h> // GLfloat
#include <Box2D/Box2D.h>
#include "../include/B2GameState.h"


struct golyo {
   GLfloat x;
   GLfloat y;
   GLfloat xRot, yRot;
}; // TODO: két vectorra bontani
/*
class GameState {
    public:
        virtual void init() = 0;
        virtual void hit(float x, float y) = 0;
        virtual void updateBalls() = 0;
        virtual void removeBall(int id) = 0;
};

class B2GameState : public GameState {
    public:
        B2GameState(b2Vec2 gravity, bool doSleep);
        ~B2GameState();

        void init();
        void hit(float x, float y);
        void updateBalls();
        void removeBall(int id);
    private:
        float32 timeStep;
        int32 velocityIterations;
        int32 positionIterations;

        b2World world;
        b2CircleShape ballShape;
        b2FixtureDef ballFixture;
        b2BodyDef ballDef;

        b2Body* balls[16];
        b2Body* sides[4];

        b2Vec2 lastpos[16];

        bool initDone;
};
*/
class Game {
    public:
        Game();
        ~Game();

        void hit();
        void init();
        void updateBalls();
        void roundOver();
        bool getP1Turn();
        bool getEnd();
        void setEnd(bool e);
	int getP1Score();
	int getP2Score();
    private:
        B2GameState* state;
};

const float eps = 0.000000000001;

const float erosit_a = 1.2;
const float gyengit_a = 1.2;
const float balra_a = 0.05;
const float jobbra_a = 0.05;

void hit();
void balraIrany();
void jobbraIrany();
void erosit();
void gyengit();
#endif
