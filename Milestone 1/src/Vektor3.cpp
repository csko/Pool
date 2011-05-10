#include "../include/Vektor3.h"
#include <cmath>

/*
 * Default konstruktor, a nullvektor.
 */
Vektor3::Vektor3() {
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

/*
 * Copy konstruktor.
 */
Vektor3::Vektor3(const Vektor3& v) {
	x = v.x;
	y = v.y;
	z = v.z;
}

/*
 * Konstruktor koordináták megadásával.
 */
Vektor3::Vektor3(float x,float y,float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

/*
 * Vektor i. koordinátájának lekérése
 */
float Vektor3::operator[](int i) {
	switch (i) {
		case 0: return x;
		case 1: return y;
		case 2: return z;
		default: return 0.0;
	};
}

/*
 * Két vektor összege.
 */
Vektor3 Vektor3::operator+( const Vektor3& v) {
	Vektor3 returnVector( x+v.x, y+v.y, z+v.z );
	return returnVector;
}

/*
 * Két vektor keresztszorzata.
 */
Vektor3 Vektor3::operator*( const Vektor3& v) {
	Vektor3 returnVector( x*v.x, y*v.y, z*v.z);
	return returnVector;
}

/*
 * Vektor szorzása skalárral.
 */
Vektor3 Vektor3::operator*( const float konstans) {
	Vektor3 returnVektor( x*konstans, y*konstans, z*konstans );
	return returnVektor;
}

/*
 * Vektor normalizálása.
 */
void Vektor3::normalizal() {
	float hosszNegyzet = x*x + y*y + z*z;
	float hossz = sqrt(hosszNegyzet);
	*this = (*this)*(1.0/hossz);
}
