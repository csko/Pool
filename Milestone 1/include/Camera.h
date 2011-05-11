#ifndef _KAMERAMOZGAS_
#define _KAMERAMOZGAS_
#include <GL/glut.h> // GLfloat
#include "Vektor3.h"
#include "Kvaternio.h"

enum rotationOrientation {HORIZONTAL, VERTICAL};

class Camera {
private:

   //alapadatok
   GLfloat xRot;		//pitch
   GLfloat zRot;		//yaw
   
   GLfloat horizontal;	//kamera aktuális vízszintes pozíciója
   GLfloat vertical;   	//kamera aktuális mélységi pozíciója
   GLfloat zDir;		//kamera aktuális függőleges pozíciója
   GLfloat zoom;		//nagyítás mértéke
   GLfloat roomDimension;	//a szoba oldalának hossza kezdetben
   
   Vektor3 *iranyvektor;	//amerre éppen nézünk
   
   /********* Mozgatáskor szükséges adattagok.*******/
   int moveTime;				//mozgás időpillanata
   bool move;					//mozgás folyamatban van-e
   
   GLfloat xMoved;				//eddigi elmozdulás x irányban
   GLfloat yMoved;				//eddigi elmozdulás y irányban
   GLfloat zMoved;				//eddigi elmozdulás z irányban
   
   GLfloat horizontalBound1;	//mélységi egyik határ
   GLfloat horizontalBound2;   	//mélységi másik határ

   GLfloat verticalBound1;	//vízszintes egyik határ
   GLfloat verticalBound2; 	//vízszintes másik határ
   
   GLfloat xDirection;	//melyik irányba tartunk az x tengelyen
   GLfloat yDirection;	//melyik irányba tartunk az y tengelyen
   GLfloat zDirection;	//melyik irányba tartunk az z tengelyen
   
   GLfloat xMoveLength;	//mekkora távot teszünk majd meg az x tengelyen
   GLfloat yMoveLength; //mekkora távot teszünk majd meg az y tengelyen
   GLfloat zMoveLength; //mekkora távot teszünk majd meg az z tengelyen
   GLfloat moveSpeed;	//mozgás aktuális sebessége   
         
   /***************Forgatáskor szükséges adattagok.******************/
   GLfloat withDeg;		//hány fokkal forgatunk
   GLfloat actualSpeed;	//csillapított mozgás során az aktuális sebesség
   GLfloat rotateSpeed;	//csillapított forgás során az aktuális sebesség
   GLfloat duration;	//meddig tartana a forgás egyenletes sebességgel
   GLfloat rotated;		//hány fokkal forgattunk el eddig
   int rotateTime;		//hanyadik időpillanatban tart a forgatás
   bool rotate;   		//folyamatban van-e forgatás
   int rotateDirection;  //mely tengely mentén akarunk forgatni
   
   Kvaternio *start, *end;
   
   
   static const bool debug = true;	//szeretnénk-e az stdout-ra információt kiírni
   bool kvaternio;	//kvaterniókat használunk-e a mozgatáshoz?
   
   /********************Csillapítást számító függvények**************/
   void cubicEaseInOutRotate();
   void cubicEaseOutRotate();
   void cubicEaseInRotate();   
   void cubicEaseInOutMove();
   
   float fokRadianba(float);
   float radianFokba(float);
   
public:   

   Camera();
   void view();
      
   GLfloat getXRot();
   GLfloat getZRot();
   GLfloat getHorizontal();
   GLfloat getVertical();
   GLfloat getZDir();
   GLfloat getZoom();
   bool isRotate();
   bool isMove();
   
   void incXRot(GLfloat par);
   void incZRot(GLfloat par);
   void incHorizontal(GLfloat par);
   void incVertical(GLfloat par);
   void incZDir(GLfloat par);
   void incZoom(GLfloat par);
   
   void decXRot(GLfloat par);
   void decZRot(GLfloat par);
   void decHorizontal(GLfloat par);
   void decVertical(GLfloat par);
   void decZDir(GLfloat par);
   void decZoom(GLfloat par);
   
   void rotateHorizontal();
   void rotateVertical();
   void doRotate();
   void doMove();
   void rotateTo(GLfloat deg, GLfloat speed,int direction);
   void moveToPos(GLfloat x, GLfloat y, GLfloat z);
   
   void negateKvaternio();
   
};

#endif
