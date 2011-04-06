#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glut.h>
#include "include/billiard.h"
#include "include/3dstexture.h"
#include "include/3dsloader.h"
#include "include/texture.h"




/**********************************************************
 *
 * VARIABLES DECLARATION
 *
 *********************************************************/

// The width and height of your window, change them as you like
int screen_width=1024;
int screen_height=768;

static GLuint textures[16];
static int gInit = 0;

//Now the object is generic, the cube has annoyed us a little bit, or not?
obj_type object1;
obj_type object2;

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

static GLfloat golyoSugar = 2.0f;
struct golyo {
   GLfloat x;
   GLfloat y;
   GLfloat xRot, yRot;
};
struct golyo golyok[16];

void BitmapText(GLfloat x, GLfloat y, char *string)
{
  int len, i;
  glRasterPos2f(x, y);
  len = (int) strlen (string);
  for (i = 0; i < len; i++){
    glutBitmapCharacter (GLUT_BITMAP_HELVETICA_18, string[i]);
  }
}

void golyokInit(){
  golyok[0].x = -25;
  golyok[0].y = -50;
  gInit = 1;
  int i;
  int par = 0;
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
  if(gInit==0) golyokInit();
  glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(golyok[0].x, golyok[0].y, 0);
    GLUquadric *qobj = gluNewQuadric();
    gluQuadricTexture(qobj,GL_TRUE);
    gluSphere(qobj,golyoSugar,10,10);
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
      gluSphere(qobj,golyoSugar,10,10);
      gluDeleteQuadric(qobj);
      glDisable(GL_TEXTURE_2D);
    glPopMatrix();
  }
}

void drawAbout()
{
    glColor3f(1,1,1);
    BitmapText(-20.0f, 21.0f, "Billiárd");
    BitmapText(-20.0f, 19.0f, "Bordé Sándor, Csernai Kornél, Ladányi Gergely");
    BitmapText(-20.0f, 17.0f, "Fejlett Grafikai Algoritmusok");
    BitmapText(-20.0f, 15.0f, "SZTE PTI MsC 2010/11 oszi felev");
}
void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0); // This clear the background color to black
    glShadeModel(GL_SMOOTH); // Type of shading for the polygons
   	
    // Viewport transformation
    glViewport(0,0,screen_width,screen_height);  

    // Projection transformation
    glMatrixMode(GL_PROJECTION); // Specifies which matrix stack is the target for matrix operations 
    glLoadIdentity(); // We initialize the projection matrix as identity
    gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,10.0f,10000.0f); // We define the "viewing volume"
   
    glEnable(GL_DEPTH_TEST); // We enable the depth test (also called z buffer)
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)
    
    glEnable(GL_TEXTURE_2D); // This Enable the Texture mapping

    Load3DS (&object1,"blender/obj1.3ds");
    Load3DS (&object2,"blender/obj2.3ds");

    object1.id_texture=LoadBitmap("images/asztal1.bmp"); // The Function LoadBitmap() return the current texture ID
    object2.id_texture=LoadBitmap("images/asztal2.bmp");

  textures[1] = TextureLoad("images/1.bmp", GL_FALSE, GL_LINEAR, GL_LINEAR, GL_REPEAT);
  textures[2] = TextureLoad("images/2.bmp", GL_FALSE, GL_LINEAR, GL_LINEAR, GL_REPEAT);
  textures[3] = TextureLoad("images/3.bmp", GL_FALSE, GL_LINEAR, GL_LINEAR, GL_REPEAT);
  textures[4] = TextureLoad("images/4.bmp", GL_FALSE, GL_LINEAR, GL_LINEAR, GL_REPEAT);
  textures[5] = TextureLoad("images/5.bmp", GL_FALSE, GL_LINEAR, GL_LINEAR, GL_REPEAT);
  textures[6] = TextureLoad("images/6.bmp", GL_FALSE, GL_LINEAR, GL_LINEAR, GL_REPEAT);
  textures[7] = TextureLoad("images/7.bmp", GL_FALSE, GL_LINEAR, GL_LINEAR, GL_REPEAT);
  textures[8] = TextureLoad("images/8.bmp", GL_FALSE, GL_LINEAR, GL_LINEAR, GL_REPEAT);
  textures[9] = TextureLoad("images/9.bmp", GL_FALSE, GL_LINEAR, GL_LINEAR, GL_REPEAT);
  textures[10] = TextureLoad("images/10.bmp", GL_FALSE, GL_LINEAR, GL_LINEAR, GL_REPEAT);
  textures[11] = TextureLoad("images/11.bmp", GL_FALSE, GL_LINEAR, GL_LINEAR, GL_REPEAT);
  textures[12] = TextureLoad("images/12.bmp", GL_FALSE, GL_LINEAR, GL_LINEAR, GL_REPEAT);
  textures[13] = TextureLoad("images/13.bmp", GL_FALSE, GL_LINEAR, GL_LINEAR, GL_REPEAT);
  textures[14] = TextureLoad("images/14.bmp", GL_FALSE, GL_LINEAR, GL_LINEAR, GL_REPEAT);
  textures[15] = TextureLoad("images/15.bmp", GL_FALSE, GL_LINEAR, GL_LINEAR, GL_REPEAT);

}



/**********************************************************
 *
 * SUBROUTINE resize(int,int)
 *
 * This routine must be called everytime we resize our window.
 * 
 *********************************************************/

void resize (int width, int height)
{
    screen_width=width; // We obtain the new screen width values and store it
    screen_height=height; // Height value

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // We clear both the color and the depth buffer so to draw the next frame
    glViewport(0,0,screen_width,screen_height); // Viewport transformation

    glMatrixMode(GL_PROJECTION); // Projection transformation
    glLoadIdentity(); // We initialize the projection matrix as identity
    gluPerspective(20.0f,(GLfloat)screen_width/(GLfloat)screen_height,10.0f,10000.0f);

    glutPostRedisplay (); // This command redraw the scene (it calls the same routine of glutDisplayFunc)
}


void Timer(int value)
{

  glutTimerFunc(100, Timer, value + 1);
}

/**********************************************************
 *
 * SUBROUTINE keyboard(unsigned char,int,int)
 *
 * Used to handle the keyboard input (ASCII Characters)
 * 
 *********************************************************/

void keyboard (unsigned char key, int x, int y)
{

}



/**********************************************************
 *
 * SUBROUTINE keyboard(int,int,int)
 *
 * Used to handle the keyboard input (not ASCII Characters)
 * 
 *********************************************************/

void keyboard_s (int key, int x, int y)
{
  if(key == GLUT_KEY_UP)
    xRot+= 5.0f;
  
  if(key == GLUT_KEY_DOWN)
    xRot -= 5.0f;
  
  if(key == GLUT_KEY_LEFT)
    yRot += 5.0f;
  
  if(key == GLUT_KEY_RIGHT)
    yRot -= 5.0f;
  
  if(xRot > 356.0f)
    xRot = 0.0f;
  
  if(xRot < 0.0f)
    xRot = 355.0f;
  
  if(yRot > 356.0f)
    yRot = 0.0f;
  
  if(yRot < -1.0f)
    yRot = 355.0f;
}



/**********************************************************
 *
 * SUBROUTINE display()
 *
 * This is our main rendering subroutine, called each frame
 * 
 *********************************************************/
void texturazas(obj_type object1){
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
    glFlush(); // This force the execution of OpenGL commands
}
void display(void)
{
    //glClearColor(0.0, 0.0, 0.0, 0.0); // This clear the background color to black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // This clear the background color to dark blue
    glMatrixMode(GL_MODELVIEW); // Modeling transformation
    glLoadIdentity(); // Initialize the model matrix as identity



    glTranslatef(0.0,0.0,-300); // We move the object forward (the model matrix is multiplied by the translation matrix
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);  
glPushMatrix();
    texturazas(object1);        
    texturazas(object2);
glPopMatrix();
glPushMatrix();
    glDisable(GL_TEXTURE_2D);
    glTranslatef(0.0,0.0,5);
    DrawGolyok();
glPopMatrix();
    glFlush(); // This force the execution of OpenGL commands
    glutSwapBuffers(); // In double buffered mode we invert the positions of the visible buffer and the writing buffer
}



/**********************************************************
 *
 * The main routine
 * 
 *********************************************************/

int main(int argc, char **argv)
{
    // We use the GLUT utility to initialize the window, to handle the input and to interact with the windows system
    glutInit(&argc, argv);    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(screen_width,screen_height);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Billiard");    
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc (resize);
    glutTimerFunc(100, Timer, 1);
    glutKeyboardFunc (keyboard);
    glutSpecialFunc (keyboard_s);
    init();
    glutMainLoop();

    return(0);    
}
