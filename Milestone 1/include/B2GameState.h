#ifndef _B2GAMESTATE_
#define _B2GAMESTATE_
#include <GL/glut.h> // GLfloat
#include <Box2D/Box2D.h>

#include "../include/game.h"
#include "vector.h"

class Game; // forward declaration
class GameState; // forward declaration

class B2GameState : public GameState {
    public:
        B2GameState(Game* game, b2Vec2 gravity, bool doSleep);
        ~B2GameState();

        void init();
        void hit(float x, float y);
        void updateBalls();
        void removeBall(int id);
        void moveBall(int id, float x, float y);
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
        Game* game;
};
#endif
