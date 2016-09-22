#ifndef _CAMARA_
#define _CAMARA_

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <assert.h>
#include "vertex.h"

struct Punto{
	GLdouble x, y, z;
};

class Camara{
	private:
		//Valor mínimo de X
		GLdouble left; 
		//Valor máximo de X
		GLdouble right;
		//Valor mínimo de Y
		GLdouble bottom;
		//Valor máximo de Y
		GLdouble top;
		//Distancia de la camara al plano más cercano
		GLdouble near; 
		//Distancia de la camara al plano más lejano
		GLdouble far;
		//Punto de posición EYE
		Punto eye;
		//Punto objetivo AT
		Punto at;
		//Punto UP
		Punto up;
	public:
		Camara();
		void Construir(int tipo);
		void Visionar(int tipo);
		void CambiarOjo(int accion);
		void Reiniciar(int tipo);
};

#endif