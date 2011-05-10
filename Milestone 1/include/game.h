#ifndef _JATEKLOGIKA_
#define _JATEKLOGIKA_
#include "vector.h"
#include <GL/glut.h> // GLfloat
#include <Box2D/Box2D.h>
//#include "../include/B2GameState.h"

//class B2GameState; // forward declaration

const float holes[6][2] = {{25.549, -50},{27.564, 0},{25.549, 51},
                          {-25.549, 51},{-27.564, 0},{-25.549, -50.275}
                          };

const bool p1Balls[16] = {false, false, true, true, false, false, false, true, true, false, true, false, true, false, true, false};
const bool p2Balls[16] = {false, true, false, false, true, false, true, false, false, true, false, true, false, true, false, true};

//const char* player1="Player1";
//const char* player2="Player2";

struct golyo {
   GLfloat x;
   GLfloat y;
   GLfloat xRot, yRot;
}; // TODO: két vectorra bontani

class GameState {
    public:
        virtual void init() = 0;
        virtual void hit(float x, float y) = 0;
        virtual void updateBalls() = 0;
        virtual void removeBall(int id) = 0;
        virtual void moveBall(int id, float x, float y) = 0;
};

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
	    bool getMovement();
	    void setMovement(bool m);
	    bool getRoundOver();
	    struct golyo golyok[16];
        bool disabled[16];

        // Callback
        void collision(int a, int b); // Balls a and b have collided
        void hole(int a, int h); // Ball a has fallen into hole h
    private:
        GameState* state;
        bool isMovement;
        bool isRoundOver;
        int p1Score, p2Score;
        bool p1Turn, p2Turn;
        int winner; //ki a nyertes
        bool blackHole, whiteHole; //lement a fekete (feher)
        bool p1Ball, p2Ball; //ment le tomor (csikos) golyo
        bool end; //vege van-e a jateknak
        int stepNum; //hanyszor kovetkezik az adott jatekos meg
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
