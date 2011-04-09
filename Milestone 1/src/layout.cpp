#include <GL/glut.h>
#include "../include/billiard.h"
#include "../include/3dstexture.h"
#include "../include/3dsloader.h"
#include "../include/texture.h"
#include "../include/game.h"

#include <iostream>
using namespace std;

GLuint textures[16];
static int gInit = 0;

obj_type object1, object2, object3;

static GLfloat golyoSugar = 2.0f;

// src/game.cpp
extern struct golyo golyok[16];
extern Vector white;
extern bool isMovement;

void golyokInit(){
  golyok[0].x = -25;
  golyok[0].y = -50;

  gInit = 1;
  int i;
//  int par = 0;
  GLfloat x = -25;
  GLfloat y = 0;
  golyok[1].x = x;
  golyok[1].y = y;
  x-=golyoSugar;
  y+=1.6*golyoSugar;
  int hanyadik = 1;
  for(i = 1; i<=2;i++){  
    hanyadik++;
    golyok[hanyadik].x = x;
    golyok[hanyadik].y = y;
    x+=2*golyoSugar;
  }
  x-=golyoSugar;
  y+=1.6*golyoSugar;
  for(i = 1; i<=3;i++){  
    hanyadik++;
    golyok[hanyadik].x = x;
    golyok[hanyadik].y = y;
    x-=2*golyoSugar;
  }
  x+=golyoSugar;
  y+=1.6*golyoSugar;
  for(i = 1; i<=4;i++){  
    hanyadik++;
    golyok[hanyadik].x = x;
    golyok[hanyadik].y = y;
    x+=2*golyoSugar;
  }
  x-=golyoSugar;
  y+=1.6*golyoSugar;
  for(i = 1; i<=5;i++){  
    hanyadik++;
    golyok[hanyadik].x = x;
    golyok[hanyadik].y = y;
    x-=2*golyoSugar;
  }
  for(i=1;i<=15;i++){
    golyok[i].xRot = -90;
  }
}

void DrawGolyok(){
  if(gInit == 0) golyokInit();
  glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(golyok[0].x, golyok[0].y, 0);

    if(!isMovement){
        glBegin(GL_LINES); // A fehér golyó irányának vektora
            glVertex3f(0,0,0);
            glVertex3f(white.getX(), white.getY(), 0);
        glEnd();
    }

    GLUquadric *qobj = gluNewQuadric();
    gluQuadricTexture(qobj,GL_TRUE);
    gluSphere(qobj,golyoSugar,15,15);
    gluDeleteQuadric(qobj);
  glPopMatrix();
  int i;
  for(i=1;i<=15;i++){
    glColor3f(1,1,1);
    glPushMatrix();
      glTranslatef(golyok[i].x, golyok[i].y, 0);
      glRotatef(golyok[i].xRot, 1, 0, 0);
      glRotatef(golyok[i].yRot, 0, 1, 0);
      GLUquadric *qobj = gluNewQuadric();
      gluQuadricTexture(qobj,GL_TRUE);
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D,textures[i]);
      gluSphere(qobj,golyoSugar,15,15);
      gluDeleteQuadric(qobj);
      glDisable(GL_TEXTURE_2D);
    glPopMatrix();
  }
}

void axes(){
float ORG[3] = {0,0,0};

float XP[3] = {1,0,0},
YP[3] = {0,1,0},
ZP[3] = {0,0,1};

glPushMatrix ();

//glTranslatef (-2.4, -1.5, -5);
//glRotatef (tip , 1,0,0);
//glRotatef (turn, 0,1,0);
glScalef (50, 50, 50);

glLineWidth (2.0);

glBegin (GL_LINES);
glColor3f (1,0,0); // X axis is red.
glVertex3fv (ORG);
glVertex3fv (XP );
glColor3f (0,1,0); // Y axis is green.
glVertex3fv (ORG);
glVertex3fv (YP );
glColor3f (0,0,1); // z axis is blue.
glVertex3fv (ORG);
glVertex3fv (ZP );
glEnd();

glPopMatrix ();
}

void texturazas(obj_type object1){
    glColor3f(1,1,1);
    int l_index = 0;
    glClear(GL_DEPTH_BUFFER_BIT); // This clear the background color to dark blue
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, object1.id_texture); // We set the active texture 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBegin(GL_TRIANGLES); // glBegin and glEnd delimit the vertices that define a primitive (in our case triangles)
    for (l_index=0;l_index<object1.polygons_qty;l_index++)
    {
        //----------------- FIRST VERTEX -----------------
        // Texture coordinates of the first vertex
        glTexCoord2f( object1.mapcoord[ object1.polygon[l_index].a ].u,
                      object1.mapcoord[ object1.polygon[l_index].a ].v);
        // Coordinates of the first vertex
        glVertex3f( object1.vertex[ object1.polygon[l_index].a ].x,
                    object1.vertex[ object1.polygon[l_index].a ].y,
                    object1.vertex[ object1.polygon[l_index].a ].z); //Vertex definition

        //----------------- SECOND VERTEX -----------------
        // Texture coordinates of the second vertex
        glTexCoord2f( object1.mapcoord[ object1.polygon[l_index].b ].u,
                      object1.mapcoord[ object1.polygon[l_index].b ].v);
        // Coordinates of the second vertex
        glVertex3f( object1.vertex[ object1.polygon[l_index].b ].x,
                    object1.vertex[ object1.polygon[l_index].b ].y,
                    object1.vertex[ object1.polygon[l_index].b ].z);
        
        //----------------- THIRD VERTEX -----------------
        // Texture coordinates of the third vertex
        glTexCoord2f( object1.mapcoord[ object1.polygon[l_index].c ].u,
                      object1.mapcoord[ object1.polygon[l_index].c ].v);
        // Coordinates of the Third vertex
        glVertex3f( object1.vertex[ object1.polygon[l_index].c ].x,
                    object1.vertex[ object1.polygon[l_index].c ].y,
                    object1.vertex[ object1.polygon[l_index].c ].z);
    }
      glDisable(GL_TEXTURE_2D);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
