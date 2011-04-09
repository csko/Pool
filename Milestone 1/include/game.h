#ifndef _JATEKLOGIKA_
#define _JATEKLOGIKA_
#include "vector.h"
#include <GL/glut.h> // GLfloat
#include <Box2D/Box2D.h>

struct golyo {
   GLfloat x;
   GLfloat y;
   GLfloat xRot, yRot;
}; // TODO: két vectorra bontani

class GameState {
    public:
        GameState(b2Vec2 gravity, bool doSleep);
        ~GameState();

        void init();
        void hit(float x, float y);
        void updateBalls();
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

class Game {
    public:
        Game();
        ~Game();

        void hit();
        void init();
        void updateBalls();
    private:
        GameState* state;
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
