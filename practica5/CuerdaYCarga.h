#ifndef _CuerdaYCarga_
#define _CuerdaYCarga_

#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <assert.h>
#include "vertex.h"
#include "ed.h"

class CuerdaYCarga{
	private:
		ED rail;
		ED cuerda;
		ED carga;
		float largoCuerda, distrail;
		float altRail, ancRail;
		float laCuerda, anCuerda;
		float anCarga, alCarga;
		bool invertirCuerda, invertiRail;
	public:
		CuerdaYCarga();
		void Dibujar(int accion, int tipoDibujo);
		void Construir();
		void ConstruirRail();
		void ConstruirCuerda();
		void ConstruirCarga();
		void DibujarRail(int tipoDibujo);
		void DibujarCuerda(int tipoDibujo);
		void DibujarCarga(int tipoDibujo);		
};

#endif
