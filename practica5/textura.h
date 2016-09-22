#ifndef _TEXTURA_
#define _TEXTURA_

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <assert.h>
#include "vertex.h"
#include "jpg_imagen.hpp"

class Textura{
	private:
		char nombreTextura[30];
		GLuint id;
		jpg::Imagen *pimg;
		unsigned tamx, tamy;
		void *texels;
		GLfloat ma[4];
		GLfloat md[4];
		GLfloat ms[4];
		GLfloat me[4];
		GLfloat e;
	public:
		Textura();
		bool CrearTextura(char *nombre);
		void ActivarTextura(vector <float> &tablaCoordenadas);
		void DesactivarTextura();
		void ModificarMaterial(int tipo, float cantidad);
};

#endif
