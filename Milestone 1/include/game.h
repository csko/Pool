#ifndef _JATEKLOGIKA_
#define _JATEKLOGIKA_
#include "vector.h"
#include <GL/glut.h> // GLfloat
#include <Box2D/Box2D.h>
#include "../include/B2GameState.h"

class B2GameState; // forward declaration

struct golyo {
   GLfloat x;
   GLfloat y;
   GLfloat xRot, yRot;
}; // TODO: két vectorra bontani
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
    private:
        B2GameState* state;
        bool isMovement;
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
