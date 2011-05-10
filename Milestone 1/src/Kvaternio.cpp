#include "../include/Kvaternio.h"
#include <cmath>

Kvaternio::Kvaternio() {
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
	this->w = 1.0;
}

Kvaternio::Kvaternio(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

/*
 * Normalizálja a kvaterniót, feltéve ha szükséges (tehát 
 * ha a hossza nem 0.
 */
void Kvaternio::normalizal() {
	GLfloat hossznegyzet = w*w + x*x + y*y + z*z;
	
	if ( hossznegyzet != 0.0 ) {
		GLfloat hossz = sqrt(hossznegyzet);
		w /= hossz;
		z /= hossz;
		y /= hossz;
		x /= hossz;
	}
}

/*
 * Kvaternió komplex konjugáltja. Mivel először normalizáljuk
 * a kvaterniót, ezért egyszerű negálással fog megegyezni a 
 * konjugálás.
 */
Kvaternio Kvaternio::konjugalt() {
	return Kvaternio( -x, -y, -z, w);
}

/* 
 * Két kvaternió szorzása. Egymás utáni forgatásoknál
 * használható. Nem kommutatív művelet.
 */
Kvaternio Kvaternio::operator*( const Kvaternio& k ) const {
	return Kvaternio( w*k.x + x*k.w + y*k.z - z*k.y, w*k.y + y*k.w + z*k.x - x*k.z, w*k.z + z*k.w + x*k.y - y*k.x, w*k.w - x*k.x - y*k.y - z*k.z );
}

/* 
 * Egy vektor forgatása kvaternióval. 
 * Egy vektor forgatása úgy történik, hogy az elforgatni
 * kívánt vektort jobbról megszorozzuk a kvaternió konjugáltjával,
 * majd balról magával a kvaternióval.
 */
Vektor3 Kvaternio::operator*( const Vektor3& v ) {
	Vektor3 newvector(v);
	newvector.normalizal();
	
	Kvaternio vec, res;
	vec.x = newvector[0];
	vec.y = newvector[1];
	vec.z = newvector[2];
	vec.w = 0.0f;
	
	res = vec * konjugalt();
	res = *this * res;
	
	return ( Vektor3( res.x, res.y, res.z ) );
}

/* 
 * Kvaternió kiszámítása forgatási tengelyből és forgatási szögből.
 * Adott tengely körüli forgatás (amit a v vektor reprezentál) egy 
 * adott THETA szöggel úgy adódik, hogy a szög felének a szinuszával
 * szorozzuk a tengely vektort, majd hozzáadjuk a szög felének a 
 * koszinuszát. 
 */
void Kvaternio::kvaternioTengelybolEsSzogbol(const Vektor3& axis, GLfloat theta) {
	GLfloat valtasRadianba = M_PI/180.0;
	theta *= valtasRadianba;
	theta /= 0.5f;
	GLfloat sinTheta = sin(theta);
	GLfloat cosTheta = cos(theta);
	
	Vektor3 axisVektor(axis);
	axisVektor.normalizal();
	
	x = (axisVektor[0] * sinTheta);
	y = (axisVektor[1] * sinTheta);
	z = (axisVektor[2] * sinTheta);
	w = cosTheta;
}

/*
 * Kvaternió kiszámítása Euler szögekből ("előredöntés", "billegés", "fordulás")
 * Először mindegyik mozgáshoz számítunk egy kvaterniót, majd összeszorozzuk 
 * őket.
 */
void Kvaternio::kvaternioEulerSzogbol(GLfloat pitch, GLfloat yaw, GLfloat roll) {
	GLfloat valtasRadianba = M_PI/180.0;
	GLfloat p = pitch * valtasRadianba / 2.0;
	GLfloat y = yaw * valtasRadianba / 2.0;
	GLfloat r = roll * valtasRadianba / 2.0;		
	
	GLfloat sinP = sin(p);
	GLfloat sinY = sin(y);
	GLfloat sinR = sin(r);
	
	GLfloat cosP = cos(p);
	GLfloat cosY = cos(y);
	GLfloat cosR = cos(r);
	
	x = sinR * cosP * cosY - cosR * sinP * sinY;
	y = cosR * sinP * cosY + sinR * cosP * sinY;
	z = cosR * cosP * sinY - sinR * sinP * cosY;
	w = cosR * cosP * cosY + sinR * sinP * sinY;
	
	normalizal();
}

void Kvaternio::kvaterniobolMatrix(GLfloat *forgatoMatrix) const {
	forgatoMatrix[0] = GLfloat( 1.0f - 2.0f * (y*y + z*z) );
	forgatoMatrix[1] = GLfloat( 2.0f * (x*y + z*w) );
	forgatoMatrix[2] = GLfloat( 2.0f * (x*z - y*w) );
	forgatoMatrix[3] = 0.0f;
	
	forgatoMatrix[4] = GLfloat( 2.0f * (x*y - z*w) );
	forgatoMatrix[5] = GLfloat( 1.0f - 2.0f * (x*x + z*z) );
	forgatoMatrix[6] = GLfloat( 2.0f * (z*y + x*w) );
	forgatoMatrix[7] = 0.0f;
	
	forgatoMatrix[8] = GLfloat( 2.0f * (x*z + y*w) );
	forgatoMatrix[9] = GLfloat( 2.0f * (y*z - x*w) );
	forgatoMatrix[10] = GLfloat( 1.0f - 2.0f * (x*x + y*y) );
	forgatoMatrix[11] = 0.0f;	
	
	forgatoMatrix[12] = 0.0f;
	forgatoMatrix[13] = 0.0f;
	forgatoMatrix[14] = 0.0f;
	forgatoMatrix[15] = 1.0f;	
}

