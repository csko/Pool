#include <GL/glut.h>
#include "../include/billiard.h"
#include "../include/texture.h"
#include "../include/layout.h"
#include "../include/output.h"
#include "../include/Camera.h"
#include "../include/texturefunctions.h"
#include "../include/B2GameState.h"
#include "../include/MyGameState.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
using namespace std;
extern Vector white;
extern Game game;
extern Camera cam;

Layout layout;
Layout::Layout(){
    sugar = 1.5f;
    gInit = 0;
    dakoRot = 0.0;
    dakoeltolas = 0;
    elso = false;
    f0 = ImageLoad("images/f0.bmp");
    f1 = ImageLoad("images/f1.bmp");
    f2 = ImageLoad("images/f2.bmp");
    wall = ImageLoad("images/w4.bmp");
    floor = ImageLoad("images/floor.bmp");
    ballsImage[1] = ImageLoad("images/14.bmp");
    ballsImage[4] = ImageLoad("images/12.bmp");
    ballsImage[6] = ImageLoad("images/10.bmp");
    ballsImage[9] = ImageLoad("images/9.bmp");
    ballsImage[11] = ImageLoad("images/15.bmp");
    ballsImage[13] = ImageLoad("images/13.bmp");
    ballsImage[15] = ImageLoad("images/11.bmp");


    ballsImage[2] = ImageLoad("images/7.bmp");
    ballsImage[3] = ImageLoad("images/5.bmp");
    ballsImage[5] = ImageLoad("images/8.bmp");
    ballsImage[7] = ImageLoad("images/6.bmp");
    ballsImage[8] = ImageLoad("images/4.bmp");
    ballsImage[10] = ImageLoad("images/3.bmp");
    ballsImage[12] = ImageLoad("images/2.bmp");
    ballsImage[14] = ImageLoad("images/1.bmp");
    for(int i = 1; i<=15;i++){
        golyok_elozo[i].x = 0.0;
        golyok_elozo[i].y = 0.0;
    }
}

void Layout::drawTable(int q){
  glEnable(GL_TEXTURE_2D);
if(q%3 == 0){
    Tabla_kicsi_0(f0);
    Tabla_kicsi_1(f1);
    Tabla_kicsi_2(f2);
}else if(q%3==1){
    Tabla_kozepes_0(f0);
    Tabla_kozepes_1(f1);
    Tabla_kozepes_2(f2);
}else if(q%3==2){
    Tabla_nagy_0(f0);
    Tabla_nagy_1(f1);
    Tabla_nagy_2(f2);
}
  glDisable(GL_TEXTURE_2D);
}
void Layout::drawLampa(){
    glPushMatrix();
      glPushAttrib(GL_LIGHTING_BIT);
        glDisable(GL_LIGHTING);
        glScalef(0.3,0.3,0.3);
        glTranslatef(0,230,0);
        glRotatef(90, 0, 1, 0);
        glColor3f(0,0.5,0);
        lampa1();
        lampa2();
        lampa3();
        glColor3f(0,0,0);
        lampa4();
        lampa5();
        lampa6();
      glPopAttrib();
    glPopMatrix();

}
void Layout::drawDako(GLfloat angle, bool loves){
	if(!game.getMovement()){
        if(elso){
	    elso = false; 
	    white.setX(whiteX);
	    white.setY(whiteY);
        }
	glPushMatrix();
		dakoRot+=angle;
                glTranslatef(game.golyok[0].x,36, game.golyok[0].y);
		glRotatef(-1*(180.0f+57.5*dakoRot), 0, 1, 0);
                glTranslatef(0,0,-7);
                if(loves){
                        dakoeltolas++;
	                glTranslatef(0,0,1*dakoeltolas);
                        whiteY = white.getY();
                        whiteX = white.getX();
		}else{
			dakoeltolas = 0;
		}
		glRotatef(5, 1, 0, 0);
		glScalef(0.15, 0.15, 0.15);
                glPushAttrib(GL_LIGHTING_BIT);
                  glDisable(GL_LIGHTING);
		  glColor3f(0.4,0.15,0.02);
		  dako1();//kozepso
		  glColor3f(1,1,1);
		  dako2();//eleje
		  glColor3f(0.0,0.0,0.0);
		  dako3();//vege
                glPopAttrib();
	glPopMatrix();
	}else{
		elso = true;
	}
}

void Layout::drawEnv(){
glPushMatrix();
    glColor3f(0.5,0.5,0.5);	
    glPushMatrix();
	drawFloor();
    glPopMatrix();
        glTranslatef(0.0,200.0,0.0);    
    glPushMatrix();
        drawWall();
    glPopMatrix();
    glPushMatrix();
    	glRotatef(180.0, 0.0, 1.0, 0.0);
	drawWall();    
    glPopMatrix();
    glPushMatrix();
    	glRotatef(90.0, 0.0, 1.0, 0.0);
	drawWall();    
    glPopMatrix();
    glPushMatrix();
    	glRotatef(-90.0, 0.0, 1.0, 0.0);
	drawWall();    
    glPopMatrix(); 
glPopMatrix();
}

void Layout::drawFloor() {
    glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, floor.sizeX, floor.sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, floor.data);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(0.0,1.0);
        glNormal3f(0.0, -1.0, 0.0);
    	glVertex3f(-250.0,-10.0,250.0);
        glTexCoord2f(1.0,1.0);
        glNormal3f(0.0, -1.0, 0.0);
    	glVertex3f(250.0,-10.0,250.0);
        glTexCoord2f(0.0,0.0);    	
        glNormal3f(0.0, -1.0, 0.0);
    	glVertex3f(-250.0,-10.0,-250.0);
        glTexCoord2f(1.0,0.0);
        glNormal3f(0.0, -1.0, 0.0);        
    	glVertex3f(250.0,-10.0,-250.0);    	
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void Layout::drawWall() {
    glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, wall.sizeX, wall.sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, wall.data);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(0.0,1.0);
        glNormal3f(0.0, -1.0, 0.0);
    	glVertex3f(-250.0,-10.0,250.0);
        glTexCoord2f(1.0,1.0);
        glNormal3f(0.0, -1.0, 0.0);
    	glVertex3f(250.0,-10.0,250.0);
        glTexCoord2f(0.0,0.0);    	
        glNormal3f(0.0, -1.0, 0.0);
    	glVertex3f(-250.0,-220.0,250.0);
        glTexCoord2f(1.0,0.0);
        glNormal3f(0.0, -1.0, 0.0);        
    	glVertex3f(250.0,-220.0,250.0);    	
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void Layout::initGolyok(){
  game.golyok[0].x = 0;
  game.golyok[0].y = 25;
  for(int i = 0; i <= 15; i++){
    game.disabled[i] = false;
  }
  int i;
  GLfloat e = 0.05f;
  GLfloat x = 0;
  GLfloat y = -20;
  game.golyok[1].x = x;
  game.golyok[1].y = y;
  x+=sugar+e;
  y-=1.8*sugar+e;
  int hanyadik = 1;
  for(i = 1; i<=2;i++){  
    hanyadik++;
    game.golyok[hanyadik].x = x;
    game.golyok[hanyadik].y = y;
    x-=2*sugar+e;
  }
  x+=sugar+e;
  y-=1.8*sugar+e;
  for(i = 1; i<=3;i++){  
    hanyadik++;
    game.golyok[hanyadik].x = x;
    game.golyok[hanyadik].y = y;
    x+=2*sugar+e;
  }
  x-=sugar+e;
  y-=1.8*sugar+e;
  for(i = 1; i<=4;i++){  
    hanyadik++;
    game.golyok[hanyadik].x = x;
    game.golyok[hanyadik].y = y;
    x-=2*sugar+e;
  }
  x+=sugar+e;
  y-=1.8*sugar+e;
  for(i = 1; i<=5;i++){  
    hanyadik++;
    game.golyok[hanyadik].x = x;
    game.golyok[hanyadik].y = y;
    x+=2*sugar+e;
  }
  for(i=1;i<=15;i++){
    game.golyok[i].xRot = 180;
  }
  for(int i = 1; i<=15;i++){
    golyok_elozo[i].x = game.golyok[i].x;
    golyok_elozo[i].y = game.golyok[i].y;
  }
}

void Layout::drawGolyok(){
  if(gInit == 0 || game.getEnd()) {
    initGolyok();
    game.newGameState();
    gInit = 1;
  }
  if(!game.disabled[0]){
  glPushMatrix();
    glColor3f(1,1,1);
    for(int i = 1; i<=10; i++)glDisable(GL_TEXTURE_2D);
    for(int i = 1; i<=15; i++){
       x_diff[i] = game.golyok[i].x - golyok_elozo[i].x;
       y_diff[i] = game.golyok[i].y - golyok_elozo[i].y;
       game.golyok[i].xRot+=y_diff[i]*15;
       game.golyok[i].zRot+=x_diff[i]*15;
    }
    glTranslatef(game.golyok[0].x, 35.5, game.golyok[0].y);

    if(!game.getMovement()){
        glBegin(GL_LINES); //A fehér golyó irányának vektora
            glVertex3f(0,0,0);
            glVertex3f(white.getX(), 0, white.getY());
        glEnd();
    }

    GLUquadric *qobj = gluNewQuadric();
    gluQuadricTexture(qobj,GL_TRUE);
    gluSphere(qobj,sugar,15,15);
    gluDeleteQuadric(qobj);
  glPopMatrix();
  }
  int i;
  for(i=15;i>=1;i--){
    if(game.disabled[i]){
        continue;
    }
    glColor3f(1,1,1);
    glPushMatrix();
      glTranslatef(game.golyok[i].x, 35.5, game.golyok[i].y);
      glRotatef(game.golyok[i].xRot, 1, 0, 0);
      glRotatef(game.golyok[i].yRot, 0, 1, 0);
      glRotatef(game.golyok[i].zRot, 0, 0, 1);
      GLUquadric *qobj = gluNewQuadric();
      gluQuadricTexture(qobj,GL_TRUE);
      glEnable(GL_TEXTURE_2D);
      glTexImage2D(GL_TEXTURE_2D, 0, 3, ballsImage[i].sizeX, ballsImage[i].sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, ballsImage[i].data);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
      gluSphere(qobj,sugar,15,15);
      gluDeleteQuadric(qobj);
      glDisable(GL_TEXTURE_2D);
    glPopMatrix();
  }
  for(int i = 1; i<=15;i++){
     golyok_elozo[i].x = game.golyok[i].x;
     golyok_elozo[i].y = game.golyok[i].y;
  }
}

void Layout::drawAxes(){
float ORG[3] = {0,0,0};

float XP[3] = {1,0,0},
YP[3] = {0,1,0},
ZP[3] = {0,0,1};

glPushMatrix ();

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

void Layout::BitmapText(GLfloat x, GLfloat y, char *string)
{
  int len, i;
  glRasterPos2f(x, y);
  len = (int) strlen (string);
  for (i = 0; i < len; i++){
    glutBitmapCharacter (GLUT_BITMAP_HELVETICA_18, string[i]);
  }
}

void Layout::drawAbout(int doAbout)
{
    if(doAbout){
      glPushAttrib(GL_LIGHTING_BIT);
        glDisable(GL_LIGHTING);
    	glColor3f(1,1,1);
    	BitmapText(0.0f, 21.0f+45, "Billiard");
    	BitmapText(0.0f, 18.0f+45, "Borde Sandor, Csernai Kornel, Ladanyi Gergely");
	BitmapText(0.0f, 15.0f+45, "Fejlett Grafikai Algoritmusok");
    	BitmapText(0.0f, 12.0f+45, "SZTE PTI MsC 2010/11 oszi felev");
      glPopAttrib();
    }
}

void Layout::drawHelp(int doHelp)
{
    if(doHelp){
      glPushAttrib(GL_LIGHTING_BIT);
        glDisable(GL_LIGHTING);
        glColor3f(1,1,1);
        BitmapText(-40.0f, 21.0f+45, "Hasznalhato billentyuk:");
        BitmapText(-40.0f, 18.0f+45, "a,s,d,w - kamera pozicionalasa");
        BitmapText(-40.0f, 15.0f+45, "fel,le - kamera iranyitasa");
        BitmapText(-40.0f, 12.0f+45, "2,4,6,8 - feher golyo celzasa");
        BitmapText(-40.0f, 9.0f+45,  "space - feher golyo kilovese");
      glPopAttrib();
    }
}

void Layout::drawScore(int doScore)
{
	if(doScore){
        int p1Score = game.getP1Score();
        int p2Score = game.getP2Score();
        glColor3f(1,1,1);
        char p1[50];
        char p2[50];
        char p1_pontszam[100] = "Pontszam: ";
        char p2_pontszam[100] = "Pontszam: ";
	sprintf(p1, "%d",p1Score);
	sprintf(p2, "%d",p2Score);
        strcat(p1_pontszam,p1);
        strcat(p2_pontszam,p2);       
      glPushAttrib(GL_LIGHTING_BIT);
        glDisable(GL_LIGHTING);
        BitmapText(-39.7f, 21.0f+50, "Player 1");
        BitmapText(  0.0f, 21.0f+50, "Player 2");
        BitmapText(-40.0f, 18.0f+50, p1_pontszam);
        BitmapText(  0.0f, 18.0f+50, p2_pontszam);
        glColor3f(1,1,0);
        if(game.getP1Turn()){
            glBegin(GL_LINES);
                glVertex3f(-40.0f, 73.0f, 0.0f);
       	        glVertex3f(-40.5f, 67.5f, 0.0f);
            glEnd();
            glBegin(GL_LINES);
                glVertex3f(-27.0f, 73.0f, 0.0f);
       	        glVertex3f(-27.4f, 67.5f, 0.0f);
            glEnd();
            glBegin(GL_LINES);
                glVertex3f(-27.0f, 73.0f, 0.0f);
       	        glVertex3f(-40.0f, 73.0f, 0.0f);
            glEnd();
            glBegin(GL_LINES);
                glVertex3f(-27.4f, 67.5f, 0.0f);
       	        glVertex3f(-40.5f, 67.5f, 0.0f);
            glEnd();
        }else{
            glBegin(GL_LINES);
                glVertex3f(-40.0f+39.5, 73.0f, 0.0f);
       	        glVertex3f(-40.0f+39.5, 67.5f, 0.0f);
            glEnd();
            glBegin(GL_LINES);
                glVertex3f(-27.0f+39.5, 73.0f, 0.0f);
       	        glVertex3f(-26.8f+39.5, 67.5f, 0.0f);
            glEnd();
            glBegin(GL_LINES);
                glVertex3f(-27.0f+39.5, 73.0f, 0.0f);
       	        glVertex3f(-40.0f+39.5, 73.0f, 0.0f);
            glEnd();
            glBegin(GL_LINES);
                glVertex3f(-26.8f+39.5, 67.5f, 0.0f);
       	        glVertex3f(-40.0f+39.5, 67.5f, 0.0f);
            glEnd();
        }
glPopAttrib();
	}
}
