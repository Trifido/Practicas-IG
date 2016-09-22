#ifndef _FIGURA_
#define _FIGURA_

#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <assert.h>
#include "vertex.h"
#include "ed.h"
#include "BaseTorre.h"
#include "Brazo.h"

//La figura esta formada por un objeto BaseTorre
// y otro objeto brazo.
class Figura{
	private:
		BaseTorre batorre;
		Brazo brazo;
	public:
		Figura();
		void crearFigura();
		void Dibujar(int accion, int tipoDibujo);
};

#endif
