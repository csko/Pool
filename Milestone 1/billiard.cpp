#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <GL/glut.h>
#include "include/billiard.h"
#include "include/game.h"
#include "include/layout.h"
#include "include/Camera.h"
#include "include/output.h"

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
static bool doHelp = 0;
static bool doAbout = 0;
static bool doScore = 1;

static int mouse_elozo_x = 0.0f;
static int q = 0;
static long ido = 0;
static bool mouse_init = false;
static bool loves = false;
static GLfloat angle=0.0f;
static GLfloat dakoAngle=0.0f;


// src/game.cpp
extern Vector white;
extern Vector movement[16];

extern bool isMovement;
extern Game game;
extern Layout layout;
extern Camera cam;

void init(void)
{
    glEnable(GL_LIGHTING); //Enable lighting
    glEnable(GL_LIGHT0); //Enable light #0
    glEnable(GL_LIGHT1); //Enable light #1

    //Ambient lighting
    GLfloat RADIUS = 10.0f;
    GLfloat ambientLight[] = {0.25f, 0.25f, 0.25f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    
    GLfloat lightColor[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat lightPos[] = {1.5f * RADIUS, 2 * RADIUS, 1.5 * RADIUS, 1.0f};
    //Diffuse (non-shiny) light component
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
    //Specular (shiny) light component
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    
    
    
    //Set up the material
    
    //The color of the object
    GLfloat materialColor[] = {0.9f, 0.9f, 1.0f, 1.0f};
    //The specular (shiny) component of the material
    GLfloat materialSpecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    //The color emitted by the material
    GLfloat materialEmission[] = {0, 0, 0, 1.0f};
    
    glDisable(GL_COLOR_MATERIAL); //Required for the glMaterial calls to work
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    //The shininess parameter.  A higher number indicates a more concentrated
    //shiny area, while a lower number indicates a larger shiny area.  The
    //shininess must be between 0 and 128.
    glMaterialf(GL_FRONT, GL_SHININESS, 15.0f);




   glEnable(GL_DEPTH_TEST);

    glShadeModel(GL_SMOOTH); // Type of shading for the polygons
   	
    // Viewport transformation
    glViewport(0,0,screen_width,screen_height);  

    // Projection transformation
    glMatrixMode(GL_PROJECTION); // Specifies which matrix stack is the target for matrix operations 
    glLoadIdentity(); // We initialize the projection matrix as identity
    gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,10.0f,10000.0f); // We define the "viewing volume"
   
    glEnable(GL_DEPTH_TEST); // We enable the depth test (also called z buffer)
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); // Polygon rasterization mode (polygon filled)

    glutWarpPointer( glutGet( GLUT_WINDOW_WIDTH )/2, glutGet( GLUT_WINDOW_HEIGHT )/2 );
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
    if (cam.isRotate()) cam.doRotate();
    if (cam.isMove()) cam.doMove();
    if(loves){
    	    ido++;
        if(ido==5){
	    ido = 0;
            loves = false;
            game.hit();
	    game.setMovement(true);
        }
    }
    
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
  	case 'k': 
  	case 'K':
  		 cam.negateKvaternio();
  		 break;
    case 'z':
    case 'Z':
       	cam.moveToPos(game.golyok[0].x, game.golyok[0].y-80, 40);
        break;  
    case 'e':
    case 'E':
    	if (!cam.isRotate())
			cam.rotateTo(90.0, 5.0, HORIZONTAL);
		else 
			cout << "Rotation in process..." << endl;
        break;        
    case 'r':
    case 'R':
    	if (!cam.isRotate())
			cam.rotateTo(90.0, 5.0, VERTICAL);
		else 
			cout << "Rotation in process..." << endl;			
        break;
    case 's':
    case 'S':
        cam.decVertical(1.0);
        break;
    case 'w':
    case 'W':
        cam.incVertical(1.0);        
        break;
    case 'a':
    case 'A':
        cam.incHorizontal(1.0);
        break;
    case 'd':
    case 'D':
        cam.decHorizontal(1.0);
        break;
    case 't':
    case 'T':
        cam.decZDir(1.0);
        break;
    case 'g':
    case 'G':
        cam.incZDir(1.0);
        break;
    case 'q':
    case 'Q':
        exit(0);
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
    case 'c':
        doAbout = !doAbout;
        break;
    case 'h':
        doHelp = !doHelp;
        break;
    case 'p':
        doScore = !doScore;
        break;
    case 'm':
    case 'M':
	q++;
        break;
    case 'n':
    case 'N':
	game.setEnd(true);
        break;
    default:
        cout << "Unknown key pressed: " << key << endl;
    }

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
  if(key == GLUT_KEY_UP) {
    cam.incXRot(5.0f);
  }
  
  if(key == GLUT_KEY_DOWN) {
    cam.decXRot(5.0f);
  }
  
  if(key == GLUT_KEY_LEFT) {
    cam.incZRot(5.0f);
  }    
  
  if(key == GLUT_KEY_RIGHT) {
    cam.decZRot(5.0f);
  }    
  
  if(key == GLUT_KEY_PAGE_UP) {  
    if (cam.getZoom() <= 0.1f) {
    	cam.incZoom(0.01f);
    } else {
	cam.incZoom(0.1f);
    }
  }        
  
  if(key == GLUT_KEY_PAGE_DOWN) {
    if (cam.getZoom() <= 0.1f) {
    	cam.decZoom(0.01f);
    } else {
	cam.decZoom(0.1f);
    }
  }                
}
void mouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON)
  {
    if (state == GLUT_DOWN)
    {

    }else{
      loves = true;
    }
  }
}

void motionPassive(int x, int y)
{ 
if(!mouse_init){
  mouse_init = true;
  mouse_elozo_x = x;
}
  glutSetCursor(GLUT_CURSOR_FULL_CROSSHAIR); 
  angle = (GLfloat)(mouse_elozo_x-x)*(-0.01f);
  if(loves)angle = 0;
  dakoAngle+=angle;	
  white.rotate(angle);
  mouse_elozo_x = x;
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

  glRotatef(30,1,0,0);    //egy kicsit döntött szögben nézünk az asztalra
  glTranslatef(0.0, -140.0,-180);   //minden a helyére kerül

  layout.drawHelp(doHelp);
  layout.drawAbout(doAbout);
  layout.drawScore(doScore);
  cam.view();
  layout.drawEnv(); //falak, padló, meg ami még jön
  layout.drawTable(q);
  layout.drawDako(dakoAngle, loves);dakoAngle = 0;
  layout.drawLampa();;
  game.updateBalls();
  layout.drawGolyok();
  layout.drawAxes();
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
    glutMouseFunc(mouse);
    glutPassiveMotionFunc(motionPassive);
    init();
    glutMainLoop();

    return(0);    
}
