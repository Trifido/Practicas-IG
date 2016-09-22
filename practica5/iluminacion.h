#ifndef _LUZ_
#define _LUZ_

#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <assert.h>
#include "vertex.h"

class Foco{
	private:
		GLfloat colorLuz[4];
		bool esPosicional;
		GLfloat posicionLuz[4];
		float alfa, beta;
		bool encendido;
		int nfoco;
	public:
		Foco();
		void MontarFoco(GLfloat *color, GLfloat *posicion);
		void ActivarFoco();
		void VisionarLuz();
		void MoverAlfa(bool opcion);
		void MoverBeta(bool opcion);
};

#endif
