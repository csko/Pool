#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <GL/glut.h>
#include "include/billiard.h"
#include "include/3dstexture.h"
#include "include/3dsloader.h"
#include "include/texture.h"
#include "include/jateklogika.h"
#include "include/vector.h"

#include <iostream>
using namespace std;



/**********************************************************
 *
 * VARIABLES DECLARATION
 *
 *********************************************************/

// The width and height of your window, change them as you like
int screen_width=800;
int screen_height=600;

static GLuint textures[16];
static int gInit = 0;

obj_type object1, object2, object3;

static GLfloat xRot = 110.0f;
static GLfloat zRot = 0.0f;
static GLfloat horizontal = 0.0f;
static GLfloat vertical = 0.0f;
static GLfloat zDir = -300.0f;
static GLfloat zoom = 0.5f;

static GLfloat golyoSugar = 2.0f;
struct golyo {
   GLfloat x;
   GLfloat y;
   GLfloat xRot, yRot;
};

struct golyo golyok[16];
Vector feher(0, 20);
Vector mozgas[16];


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
  if(gInit==0) golyokInit();
  glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(golyok[0].x, golyok[0].y, 0);

    glBegin(GL_LINES); // A fehér golyó irányának vektora
        glVertex3f(0,0,0);
        glVertex3f(feher.getX(),feher.getY(),0);
    glEnd();

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

void axes(){
float ORG[3] = {0,0,0};

float XP[3] = {1,0,0},
YP[3] = {0,1,0},
ZP[3] = {0,0,1};

glPushMatrix ();

//glTranslatef (-2.4, -1.5, -5);
//glRotatef (tip , 1,0,0);
//glRotatef (turn, 0,1,0);
glScalef (100, 100, 100);

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

void hit(){ // A fehér golyót el kell indítani
    cout << "hit()" << endl;
}

void balraIrany(){
    feher.rotate(balra_a);
    cout << feher.length() << endl;
}
void jobbraIrany(){
    feher.rotate(-jobbra_a);
    cout << feher.length() << endl;
}
void erosit(){
    feher *= erosit_a;
    /* TODO: max érték
    if(feher.len() >= MAX){
        feher.normalize();
        feher *= MAX;
    }
    */
}
void gyengit(){
    feher /= erosit_a;
    /* TODO: min érték
    if(feher.len() <= MIN){
        feher.normalize();
        feher *= MIN;
    }
    */
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
    // Move the balls

    //    for(int i = 1; i <= 15; i++){
    //        golyok[0].x += 10;
    //    }

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

  int state = glutGetModifiers();
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
        hit();
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
 
 printf("xRot = %f\n", xRot);
  
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
    glutTimerFunc(100, Timer, 1);
    glutKeyboardFunc (keyboard);
    glutSpecialFunc (keyboard_s);
    init();
    glutMainLoop();

    return(0);    
}
