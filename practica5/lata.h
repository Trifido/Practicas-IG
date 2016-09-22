#ifndef _LATA_
#define _LATA_

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <assert.h>
#include "vertex.h"
#include "ed.h"
#include "file_ply_stl.h"
#include "textura.h"

//La figura esta formada por un objeto BaseTorre
// y otro objeto brazo.
class Lata{
	private:
		ED inferior;
		ED central;
		ED superior;
		vector<float> vsup, vinf, vcen;
		Textura textura;
	public:
		Lata();
		void crearFigura();
		void Dibujar();
};

#endif
