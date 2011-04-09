#ifndef _JATEKLOGIKA_
#define _JATEKLOGIKA_
#include "vector.h"
#include <GL/glut.h> // GLfloat

struct golyo {
   GLfloat x;
   GLfloat y;
   GLfloat xRot, yRot;
}; // TODO: két vectorra bontani

const float eps = 0.000000000001;

const float erosit_a = 1.2;
const float gyengit_a = 1.2;
const float balra_a = 0.1;
const float jobbra_a = 0.1;
const float friction = 0.5;

void hit();
void balraIrany();
void jobbraIrany();
void erosit();
void gyengit();
#endif