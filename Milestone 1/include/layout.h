#ifndef _LAYOUT_H_
#define _LAYOUT_H_
#include "billiard.h"
#include "texturefunctions.h"
#include "game.h"
#endif

using namespace std;

class Layout {
	public:
		Layout();
		void initGolyok();
		void drawGolyok();
		void drawTable(int q);
		void drawWall();
		void drawFloor();
		void drawAxes();
		void drawEnv();
		void drawDako(GLfloat dakoAngle, bool loves);
		void drawAbout(int doAbout);
		void drawHelp(int doHelp);
                void drawScore(int doScore);
		void BitmapText(GLfloat x, GLfloat y, char *string);




	private:
		Image ballsImage[16];
		Image f0;
		Image f1;
		Image f2;
		Image floor;
		Image wall;
		GLfloat sugar, dakoRot;
		int gInit;
                int dakoeltolas;
		bool elso;
		GLfloat whiteX, whiteY;
};
