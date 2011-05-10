#ifndef _KVATERNIO_
#define _KVATERNIO_
#include <GL/glut.h> // GLfloat
#include "Vektor3.h"

class Kvaternio {
private: 
		GLfloat x;
		GLfloat y;
		GLfloat z;
		GLfloat w;
		
public:		
		void normalizal();
		Kvaternio konjugalt();
		Kvaternio operator*(const Kvaternio&) const;
		Vektor3 operator*(const Vektor3&);
		void kvaternioTengelybolEsSzogbol(const Vektor3&, GLfloat szog);
		void kvaternioEulerSzogbol(GLfloat pitch, GLfloat yaw, GLfloat roll);
		void kvaterniobolMatrix(GLfloat *forgatoMatrix) const;
		void kvaterniobolTengely(Vektor3 *tengely, GLfloat *szog);
		
		Kvaternio();
		Kvaternio(GLfloat,GLfloat,GLfloat,GLfloat);

};

#endif
