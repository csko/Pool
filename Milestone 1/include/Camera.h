#ifndef _KAMERAMOZGAS_
#define _KAMERAMOZGAS_
#include <GL/glut.h> // GLfloat

class Camera {
public:
   //kamerapozíció
   GLfloat x;	//kamera x
   GLfloat y;	//kamera y
   GLfloat z;	//kamera z koordinátája
   
   GLfloat xRot;
   GLfloat zRot;
   GLfloat horizontal;
   GLfloat vertical;
   GLfloat zDir;
   GLfloat zoom;
   
   Camera();
   void view();
};

#endif
