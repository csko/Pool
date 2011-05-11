#include "../include/Camera.h"
#include "../include/Kvaternio.h"
#include "../include/Vektor3.h"
#include <iostream>
#include <cmath>

#define _HACK

#ifdef _HACK
GLfloat abs(GLfloat a){
    return a < 0 ? -a : a;
}
#else
#endif

Camera cam;

Camera::Camera() {
    xRot = -1.0f;
    zRot = 0.0f;
    horizontal = 0.0f;
    vertical = 20.0f;
    zDir = 0.0f;
    zoom = 0.9f;
    
    roomDimension = 300.0f;
    
    horizontalBound1 = (-1)*(roomDimension*zoom/2);
    horizontalBound2 = (roomDimension*zoom/2);

    verticalBound1 = -65;
    verticalBound2 = 150;
    
    rotate = false;
    kvaternio = true;
}

void Camera::view() {
	if ( !kvaternio ) {
		std::cout << "Nem kvaternioval" << std::endl;
		glTranslatef(horizontal,zDir, vertical);   
		glRotatef(xRot, 1.0f, 0.0f, 0.0f);
		glRotatef(zRot, 0.0f, 1.0f, 0.0f);         
	} else {

		glTranslatef(horizontal,zDir, vertical);   
		std::cout << "Kvaternioval" << std::endl;
	
		GLfloat nezetMatrix[16];	//nézeti mátrixunk, ahol a forgatás után a szükséges paramétereket olvashatjuk ki
		Kvaternio q;				//ideiglenes kvaternio
		Kvaternio qPitch, qYaw;		//a pitch és yaw forgatásnak megfelelő kvaterniók
		
		//létrehozzuk az egyes irányok kvaternióit a forgatási tengelyből és a forgatás szögéből
		Vektor3 x(1.0f, 0.0f, 0.0f);
		Vektor3 z(0.0f, 1.0f, 0.0f);
		qPitch.kvaternioTengelybolEsSzogbol(x, xRot);		//döntés
		qYaw.kvaternioTengelybolEsSzogbol(z, zRot);			//forgás
		
		q = qPitch * qYaw;		//összeszorozzuk a két kvaterniót, hogy mindkét forgatást tárolja egy kvaternió
		q.kvaterniobolMatrix(nezetMatrix);	//lekérjük a két forgatás kombinációjának mátrixát
		
		glMultMatrixf(nezetMatrix);		//beállítjuk a kvaterniók szorzatából kapott mátrixot nézetmátrixnak
		
		qPitch.kvaterniobolMatrix(nezetMatrix);
		GLfloat iranyv[3];

		iranyv[1] = nezetMatrix[9];
		
		q = qYaw * qPitch;
		q.kvaterniobolMatrix(nezetMatrix);
		iranyv[0] = nezetMatrix[8];
		iranyv[2] = nezetMatrix[10];

		iranyvektor = new Vektor3(iranyv[0], iranyv[1], iranyv[2]);
		
	}	
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
	if (debug) std::cout << "xRot=" << xRot << std::endl;
}
void Camera::incZRot(GLfloat par) {
	zRot += par;
	if (zRot > 360.0) 
		zRot -= 360.0;
	if (debug) std::cout << "zRot=" << zRot << std::endl;		
}
void Camera::incHorizontal(GLfloat par) {
	horizontal += par;
	if (horizontal >= horizontalBound2) 
		horizontal = horizontalBound2-1;
	if (debug) std::cout << "horizontal=" << horizontal << std::endl;		
}
void Camera::incVertical(GLfloat par) {
	vertical += par;
	if (vertical >= verticalBound2) 
		vertical = verticalBound2-1;
	if (debug) std::cout << "vertical=" << vertical << std::endl;		
}
void Camera::incZDir(GLfloat par) {
	zDir += par;
	//if (zDir > 360.0) 
	//	zDir -= 360.0;
	if (debug) std::cout << "zDir=" << zDir << std::endl;		
}
void Camera::incZoom(GLfloat par) {
	zoom += par;
	if (zoom > 1.0) 
		zoom = 1.0;
	if (debug) std::cout << "xRot=" << xRot << std::endl;		
}

void Camera::decXRot(GLfloat par) {
	xRot -= par;
	if (xRot < 0.0) 
		xRot += 360.0;
	if (debug) std::cout << "xRot=" << xRot << std::endl;		
}
void Camera::decZRot(GLfloat par) {
	zRot -= par;
	if (zRot < 0.0) 
		zRot += 360.0;
	if (debug) std::cout << "zRot=" << zRot << std::endl;		
}
void Camera::decHorizontal(GLfloat par) {
	horizontal -= par;
	if (horizontal <= horizontalBound1) 
		horizontal = horizontalBound1+1;
	if (debug) std::cout << "horizontal=" << horizontal << std::endl;
}
void Camera::decVertical(GLfloat par) {
	vertical -= par;
	if (vertical <= verticalBound1) 
		vertical = verticalBound1+1;
	if (debug) std::cout << "vertical=" << vertical << std::endl;	
}
void Camera::decZDir(GLfloat par) {
	zDir -= par;
	std::cout << "iranyvektor[0]" << (*iranyvektor)[0] << std::endl;
	//if (zDir > 360.0) 
	//	zDir -= 360.0;
	if (debug) std::cout << "zDir=" << zDir << std::endl;	
}
void Camera::decZoom(GLfloat par) {
	zoom -= par;
	if (zoom < 0.0) 
		zoom = 0.1;
	if (debug) std::cout << "zoom=" << zoom << std::endl;		
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
  std::cout << "actualSpeed=" << actualSpeed << std::endl;
}

void Camera::cubicEaseOutRotate() {
  rotateTime++;
  GLfloat actualTime = rotateTime / (duration) - 1;
  actualSpeed = rotateSpeed*(actualTime*actualTime*actualTime + 1) + rotateSpeed;
  std::cout << "actualSpeed=" << actualSpeed << std::endl;
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
  std::cout << "actualSpeed=" << actualSpeed << std::endl;
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
  	std::cout << "Rotated horizontally " << rotated << std::endl;
    std::cout << "xRot=" << xRot << std::endl;  	
  }
}
void Camera::rotateVertical() {
	if ( !kvaternio ) {
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
		   std::cout << "Rotated vertically " << rotated << std::endl;
		   std::cout << "zRot=" << zRot << std::endl;
	  }       
  } else {
		rotateTime++;
			
		float gt = rotateTime / 50.0;
		float cosQTheta = start->kvaternioCosTheta(*end);	//két vektor által bezárt szög koszinusza
		std::cout << cosQTheta << std::endl;
		float qTheta = std::acos(cosQTheta);				//két vektor közötti szög
		if (qTheta<0.0) qTheta=-qTheta;
		std::cout << qTheta << std::endl;
		float sinQTheta = std::sqrt( 1.0 - cosQTheta * cosQTheta );	//azonosság: sqrt( 1 - cos^2(x) ) = sin(x)
		float sinTQTheta = std::sin(gt * qTheta) / sinQTheta;
		float sinMQTheta = std::sin((1.0 - gt) * qTheta) / sinQTheta;

		Kvaternio qm;
		qm.setX( start->getX()*sinMQTheta + end->getX()*sinTQTheta );
		qm.setY( start->getY()*sinMQTheta + end->getY()*sinTQTheta );
		qm.setZ( start->getZ()*sinMQTheta + end->getZ()*sinTQTheta );
		qm.setW( start->getW()*sinMQTheta + end->getW()*sinTQTheta );

		std::cout << radianFokba(qm.getW()) << std::endl;

		zRot = radianFokba( 2.0 * std::acos(qm.getW()) );
		
		std::cout << zRot << std::endl;		
		if(zRot > 356.0f)
			zRot = 0.0f;
		  
		if(zRot < 0.0f)
			zRot = 355.0f;  		
		
		if ( gt > 1.0f ){
			rotate = false;
			delete start;
			delete end;
		}


		
	}
}

void Camera::cubicEaseInOutMove() {
  moveTime++;
  GLfloat actualTime = moveTime / (5.0);
  std::cout << actualTime << std::endl;
  if (actualTime < 1) {
  	moveSpeed = (2.0)*actualTime*actualTime*actualTime + 2.0;
  } else {
  	actualTime -= 2;
  	moveSpeed = (2.0)*(actualTime*actualTime*(actualTime + 2)) + 2.0;
  }
  std::cout << "moveSpeed=" << moveSpeed << std::endl;
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
  		std::cout << "Moved to (" << horizontal << "," << vertical << "," << zDir << ")" << std::endl;
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
	if ( kvaternio ) {		
		Vektor3 z(0.0f, 1.0f, 0.0f);		
		start = new Kvaternio();
		start->kvaternioTengelybolEsSzogbol(z, (zRot));
		start->normalizal();
		end = new Kvaternio();
		end->kvaternioTengelybolEsSzogbol(z, (zRot+withDeg));	
		end->normalizal();	
	} 
}

void Camera::negateKvaternio() {
	kvaternio = !kvaternio;
}

float Camera::fokRadianba(float fok) {
	return fok * M_PI/180.0;
}
float Camera::radianFokba(float radian) {
	return radian * 180.0/M_PI;
}

