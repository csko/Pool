#ifndef _VEKTOR3_
#define _VEKTOR3_
#include <GL/glut.h> // GLfloat

class Vektor3 {
private:
		float x;
		float y;
		float z;
public:
		Vektor3();
		Vektor3(const Vektor3&);
		Vektor3(float,float,float);
		float operator[](int);
		Vektor3 operator+( const Vektor3&);
		Vektor3 operator*( const Vektor3&);
		Vektor3 operator*( const float);		
		void normalizal();
		
};

#endif
