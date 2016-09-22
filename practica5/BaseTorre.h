#ifndef _BASETORRE_
#define _BASETORRE_

#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <assert.h>
#include "vertex.h"
#include "ed.h"

class BaseTorre{
	private:
		ED base;
		ED torre;
		int tamtorre, tambase;
		int anchoTorre, anchoBase;
	public:
		BaseTorre();
		void construirBaseTorre();
		void construirTorre(float alto, float ancho);
		void construirBase(float alto, float ancho);
		void dibujarBaseTorre(int tipoDibujo);
};

#endif