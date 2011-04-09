#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <GL/glut.h>
#include "include/billiard.h"
#include "include/3dstexture.h"
#include "include/3dsloader.h"
#include "include/texture.h"
#include "include/game.h"
#include "include/layout.h"

#include <iostream>
using namespace std;


/**********************************************************
 *
 * VARIABLES DECLARATION
 *
 *********************************************************/

// The width and height of your window, change them as you like
static int screen_width = 800;
static int screen_height = 600;
const static int timer = 10;

// src/layout.cpp
extern GLuint textures[16];
extern obj_type object1, object2, object3;

static GLfloat xRot = 110.0f;
static GLfloat zRot = 0.0f;
static GLfloat horizontal = 0.0f;
static GLfloat vertical = 0.0f;
static GLfloat zDir = -300.0f;
static GLfloat zoom = 0.5f;

// src/game.cpp
extern Vector white;
extern Vector movement[16];
extern struct golyo golyok[16];
extern bool isMovement;
extern Game game;

void BitmapText(GLfloat x, GLfloat y, char *string)
{
  int len, i;
  glRasterPos2f(x, y);
  len = (int) strlen (string);
  for (i = 0; i < len; i++){
    glutBitmapCharacter (GLUT_BITMAP_HELVETICA_18, string[i]);
  }
}


void drawAbout()
{
    glColor3f(1,1,1);
    BitmapText(-20.0f, 21.0f, "Billiárd");
    BitmapText(-20.0f, 18.0f, "Bordé Sándor, Csernai Kornél, Ladányi Gergely");
    BitmapText(-20.0f, 15.0f, "Fejlett Grafikai Algoritmusok");
    BitmapText(-20.0f, 12.0f, "SZTE PTI MsC 2010/11 oszi felev");
}
void init(void)
{
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
    Load3DS (&object3,"blender/obj3.3ds");

    object1.id_texture=LoadBitmap("images/asztal1.bmp"); // The Function LoadBitmap() return the current texture ID
    object2.id_texture=LoadBitmap("images/asztal2.bmp");
    object3.id_texture=LoadBitmap("images/asztal3.bmp");

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
    glutTimerFunc(timer, Timer, value + 1);
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

//  int state = glutGetModifiers();
  switch(key){
    case 's':
    case 'S':
        vertical += 1.0;
        break;
    case 'w':
    case 'W':
        vertical -= 1.0;
        break;
    case 'a':
    case 'A':
        horizontal += 1.0;
        break;
    case 'd':
    case 'D':
        horizontal -= 1.0;
        break;
    case 't':
    case 'T':
        zDir += 1.0;
        break;
    case 'g':
    case 'G':
        zDir -= 1.0;
        break;
    case 'q':
    case 'Q':
        exit(0);
        break;
    case ' ':
        game.hit();
        break;
    case '4':
        balraIrany();
        break;
    case '6':
        jobbraIrany();
        break;
    case '8':
        erosit();
        break;
    case '2':
        gyengit();
        break;
    default:
        cout << "Unknown key pressed: " << key << endl;
    }

  if ( vertical > 5.0 )
    vertical = 5.0;

  printf("vertical = %f\n", vertical);
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
    zRot += 5.0f;
  
  if(key == GLUT_KEY_RIGHT)
    zRot -= 5.0f;
  
  if(key == GLUT_KEY_PAGE_UP)
    zoom += 0.1f;
  
  if(key == GLUT_KEY_PAGE_DOWN)
    zoom -= 0.1f;  
 
// printf("xRot = %f\n", xRot);
  
  if(xRot > 270.0f)
    xRot = 270.0f;
  
  if(xRot < 90.0f)
    xRot = 90.0f;
  
  if(zRot > 356.0f)
    zRot = 0.0f;
  
  if(zRot < -1.0f)
    zRot = 355.0f;
    
  if(zoom > 1.0f)
    zoom = 1.0f;

  if(zoom < 0.1f)
    zoom = 0.1f;
    
}



/**********************************************************
 *
 * SUBROUTINE display()
 *
 * This is our main rendering subroutine, called each frame
 * 
 *********************************************************/
void display(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0); // This clear the background color to black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // This clear the background color to dark blue
    glMatrixMode(GL_MODELVIEW); // Modeling transformation
    glLoadIdentity(); // Initialize the model matrix as identity

    glEnable(GL_DEPTH_TEST);


    glTranslatef(horizontal,vertical,zDir); // We move the object forward (the model matrix is multiplied by the translation matrix

    glTranslatef(40,28.0,0.0);
        drawAbout();
    glTranslatef(-40,-28.0,0.0);

    //glTranslatef(0.0,0.0,-300); // We move the object forward (the model matrix is multiplied by the translation matrix

    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(zRot, 0.0f, 0.0f, 1.0f);
    glScalef(zoom,zoom,zoom);  
glPushMatrix();
    glColor3f(0.5,0.5,0.5);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLE_STRIP);
    	glVertex3f(-120.0,-10.0,200.0);
    	glVertex3f(70.0,-10.0,200.0);
    	glVertex3f(-120.0,-10.0,-100.0);
    	glVertex3f(70.0,-10.0,-100.0);    	
    glEnd();
glPopMatrix();
glPushMatrix();
    glRotatef(180.0, 1.0f, 0.0f, 0.0f);	//megforgattam a tárgyakat, mert így könnyebb a kameramozgást felügyelni
    texturazas(object3);
    texturazas(object1);        
    texturazas(object2);

glPopMatrix();

    game.updateBalls();
/*
glPushMatrix();
    glRotatef(180.0, 1.0f, 0.0f, 0.0f);
    texturazas(object3);
    texturazas(object1);       
    texturazas(object2);
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(-60.4,-84.29,0.0);
        glVertex3f(10.6,-84.29,0.0);
        glVertex3f(-60.4,28.14,0.0);       
        glVertex3f(10.6,28.14,0.0);
    glEnd();
glPopMatrix();
*/
glPushMatrix();
    glRotatef(180.0, 1.0f, 0.0f, 0.0f);	//megforgattam a tárgyakat, mert így könnyebb a kameramozgást felügyelni
    glDisable(GL_TEXTURE_2D);
    glTranslatef(0.0,0.0,5);
    DrawGolyok();
    axes();
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
    glutTimerFunc(timer, Timer, 1);
    glutKeyboardFunc (keyboard);
    glutSpecialFunc (keyboard_s);
    init();
    glutMainLoop();

    return(0);    
}
