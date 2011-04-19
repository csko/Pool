#include "../include/Camera.h"
#include <iostream>

#define _HACK

#ifdef _HACK
GLfloat abs(GLfloat a){
    return a < 0 ? -a : a;
}
#else
#endif

using namespace std;

Camera::Camera() {
    xRot = 0.0f;
    zRot = 0.0f;
    horizontal = 0.0f;
    vertical = 0.0f;
    zDir = 0.0f;
    zoom = 1.0f;
    
    roomDimension = 300.0f;
    
    horizontalBound1 = (-1)*(roomDimension*zoom/2);
    horizontalBound2 = (roomDimension*zoom/2);

    verticalBound1 = -65;
    verticalBound2 = 150;
    
    rotate = false;
}

void Camera::view() {
    glTranslatef(horizontal,zDir, vertical);   
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(zRot, 0.0f, 1.0f, 0.0f);     
    glScalef(zoom,zoom,zoom);    
}

GLfloat Camera::getXRot() {
	return xRot;
}

GLfloat Camera::getZRot() {
	return zRot;
}

GLfloat Camera::getHorizontal() {
	return horizontal;
}

GLfloat Camera::getVertical() {
	return vertical;
}

GLfloat Camera::getZDir() {
	return zDir;
}

GLfloat Camera::getZoom() {
	return zoom;
}

void Camera::incXRot(GLfloat par) {
	xRot += par;
	if (xRot > 360.0) 
		xRot -= 360.0;
	if (debug) cout << "xRot=" << xRot << endl;
}
void Camera::incZRot(GLfloat par) {
	zRot += par;
	if (zRot > 360.0) 
		zRot -= 360.0;
	if (debug) cout << "zRot=" << zRot << endl;		
}
void Camera::incHorizontal(GLfloat par) {
	horizontal += par;
	if (horizontal >= horizontalBound2) 
		horizontal = horizontalBound2-1;
	if (debug) cout << "horizontal=" << horizontal << endl;		
}
void Camera::incVertical(GLfloat par) {
	vertical += par;
	if (vertical >= verticalBound2) 
		vertical = verticalBound2-1;
	if (debug) cout << "vertical=" << vertical << endl;		
}
void Camera::incZDir(GLfloat par) {
	zDir += par;
	//if (zDir > 360.0) 
	//	zDir -= 360.0;
	if (debug) cout << "zDir=" << zDir << endl;		
}
void Camera::incZoom(GLfloat par) {
	zoom += par;
	if (zoom > 1.0) 
		zoom = 1.0;
	if (debug) cout << "xRot=" << xRot << endl;		
}

void Camera::decXRot(GLfloat par) {
	xRot -= par;
	if (xRot < 0.0) 
		xRot += 360.0;
	if (debug) cout << "xRot=" << xRot << endl;		
}
void Camera::decZRot(GLfloat par) {
	zRot -= par;
	if (zRot < 0.0) 
		zRot += 360.0;
	if (debug) cout << "zRot=" << zRot << endl;		
}
void Camera::decHorizontal(GLfloat par) {
	horizontal -= par;
	if (horizontal <= horizontalBound1) 
		horizontal = horizontalBound1+1;
	if (debug) cout << "horizontal=" << horizontal << endl;
}
void Camera::decVertical(GLfloat par) {
	vertical -= par;
	if (vertical <= verticalBound1) 
		vertical = verticalBound1+1;
	if (debug) cout << "vertical=" << vertical << endl;	
}
void Camera::decZDir(GLfloat par) {
	zDir -= par;
	//if (zDir > 360.0) 
	//	zDir -= 360.0;
	if (debug) cout << "zDir=" << zDir << endl;	
}
void Camera::decZoom(GLfloat par) {
	zoom -= par;
	if (zoom < 0.0) 
		zoom = 0.1;
	if (debug) cout << "zoom=" << zoom << endl;		
}

bool Camera::isRotate() {
	return rotate;
}

bool Camera::isMove() {
	return move;
}

void Camera::cubicEaseInRotate() {
  rotateTime++;
  GLfloat actualTime = rotateTime / (duration);
  actualSpeed = rotateSpeed*(actualTime*actualTime*actualTime) + rotateSpeed;
  cout << "actualSpeed=" << actualSpeed << endl;
}

void Camera::cubicEaseOutRotate() {
  rotateTime++;
  GLfloat actualTime = rotateTime / (duration) - 1;
  actualSpeed = rotateSpeed*(actualTime*actualTime*actualTime + 1) + rotateSpeed;
  cout << "actualSpeed=" << actualSpeed << endl;
}

void Camera::cubicEaseInOutRotate(){
  rotateTime++;
  GLfloat actualTime = rotateTime / (duration/2);
  if (actualTime < 1) {
  	actualSpeed = (rotateSpeed)*actualTime*actualTime*actualTime + rotateSpeed;
  } else {
  	actualTime -= 2;
  	actualSpeed = (rotateSpeed)*(actualTime*actualTime*(actualTime + 2)) + rotateSpeed;
  }
  cout << "actualSpeed=" << actualSpeed << endl;
}

void Camera::rotateHorizontal() {
  cubicEaseInOutRotate();  
  if ((rotated+actualSpeed)>withDeg) {
  	  xRot += (withDeg-rotated);
  	  rotated = withDeg;
  } else {
	  xRot += actualSpeed;
	  rotated += actualSpeed;	  
  }
  if(xRot < 0.0f)
    xRot = 355.0f;
  
  if(xRot > 360.0f)
    xRot = 5.0f;  
  if (abs(rotated) >= abs(withDeg)) {
  	rotate = false;
  	cout << "Rotated horizontally " << rotated << endl;
    cout << "xRot=" << xRot << endl;  	
  }
}
void Camera::rotateVertical() {
  cubicEaseInOutRotate();
  if ((rotated+actualSpeed)>withDeg) {
  	  zRot += (withDeg-rotated);
  	  rotated = withDeg;
  } else {
	  zRot += actualSpeed;
	  rotated += actualSpeed;
  }
  
  if(zRot > 356.0f)
    zRot = 0.0f;
  
  if(zRot < 0.0f)
    zRot = 355.0f;  
  if (abs(rotated) >= abs(withDeg)) {
       rotate = false;
       cout << "Rotated vertically " << rotated << endl;
       cout << "zRot=" << zRot << endl;
  }       
}

void Camera::cubicEaseInOutMove() {
  moveTime++;
  GLfloat actualTime = moveTime / (5.0);
  cout << actualTime << endl;
  if (actualTime < 1) {
  	moveSpeed = (2.0)*actualTime*actualTime*actualTime + 2.0;
  } else {
  	actualTime -= 2;
  	moveSpeed = (2.0)*(actualTime*actualTime*(actualTime + 2)) + 2.0;
  }
  cout << "moveSpeed=" << moveSpeed << endl;
}

void Camera::doMove() {
	cubicEaseInOutMove();	
	if ((xMoved+moveSpeed)>xMoveLength) {
		horizontal += xDirection*(xMoveLength-xMoved);
		xMoved = xMoveLength;
	} else {
		horizontal += xDirection*moveSpeed;
		xMoved += moveSpeed;
	}		
		
	if ((yMoved+moveSpeed)>yMoveLength) {
		vertical += yDirection*(yMoveLength-yMoved);
		yMoved = yMoveLength;
	} else {
		vertical += yDirection*moveSpeed;
		yMoved += moveSpeed;
	}
		
	if ((zMoved+moveSpeed)>zMoveLength) {
		zDir += zDirection*(zMoveLength-zMoved);
		zMoved = zMoveLength;
	} else {
		zDir += zDirection*moveSpeed;
		zMoved += moveSpeed; 	
	}
	
	if ((xMoved >= xMoveLength)&&(yMoved >= yMoveLength)&&(zMoved >= zMoveLength)) {
	  	move = false;
  		cout << "Moved to (" << horizontal << "," << vertical << "," << zDir << ")" << endl;
	}	
}

void Camera::moveToPos(GLfloat x, GLfloat y, GLfloat z) {
        x*=-1;
        y*=-1;
		
	move = true;
	moveTime = 0;
	
	xMoved = yMoved = zMoved = 0.0f;
	
	xMoveLength = abs(x - horizontal);
	yMoveLength = abs(y - vertical);
	zMoveLength = abs(z - zDir);
	
	if (x > horizontal) xDirection = 1;
	else if (x < horizontal) xDirection = -1;
	else xDirection = 0;
	
	if (y > vertical) yDirection = 1;
	else if (y < vertical) yDirection = -1;
	else yDirection = 0;
	
	if (z > zDir) zDirection = 1;
	else if (z < zDir) zDirection = -1;
	else zDirection = 0;
}

void Camera::doRotate(){
	if (rotateDirection == HORIZONTAL) {
		rotateHorizontal();
	} else {
		rotateVertical();
	}
}

//forgató függvény, paraméterben várja az elfordulás szögét és a másodpercenkénti szögelfordulást
void Camera::rotateTo(GLfloat deg, GLfloat speed, int direction) {
	rotateDirection = direction;
	withDeg = deg;
	rotate = true;
	rotateSpeed = speed;
	duration = withDeg / rotateSpeed;
	rotateTime = 0;
	rotated = 0;
}

