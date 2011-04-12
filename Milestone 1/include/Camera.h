#ifndef _KAMERAMOZGAS_
#define _KAMERAMOZGAS_
#include <GL/glut.h> // GLfloat

enum rotationOrientation {HORIZONTAL, VERTICAL};

class Camera {
private:
   //kamerapozíció
   GLfloat xDirection;
   GLfloat yDirection;
   GLfloat zDirection;
   GLfloat xMoveLength;
   GLfloat yMoveLength;
   GLfloat zMoveLength;
   GLfloat moveSpeed;
   
   int moveTime;
   bool move;
   
   GLfloat xMoved;
   GLfloat yMoved;
   GLfloat zMoved;
   
   GLfloat horizontalBound1;
   GLfloat horizontalBound2;   

   GLfloat verticalBound1;
   GLfloat verticalBound2; 
   
   GLfloat roomDimension;
   
   int rotateDirection;  
   
   GLfloat xRot;
   GLfloat zRot;
   GLfloat horizontal;
   GLfloat vertical;
   GLfloat zDir;
   GLfloat zoom;
   
   GLfloat withDeg;
   GLfloat actualSpeed;
   GLfloat rotateSpeed;
   GLfloat duration;	//meddig tartana a forgás egyenletes sebességgel
   GLfloat rotated;
   int rotateTime;
   bool rotate;   
   
   static const bool debug = true;
   
   void cubicEaseInOutRotate();
   void cubicEaseOutRotate();
   void cubicEaseInRotate();
   
   void cubicEaseInOutMove();
   
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
   
};

#endif
