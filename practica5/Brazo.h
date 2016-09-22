#ifndef _BRAZO_
#define _BRAZO_

#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <assert.h>
#include "vertex.h"
#include "ed.h"
#include "CuerdaYCarga.h"

//Brazo está formado por un objeto CuerdaYCarga y por objetos ED.

class Brazo{
	private:
		ED brazo;
		ED pico;
		ED cable1, cable2;
		CuerdaYCarga cucarga;
		int tambrazo, anbrazo;
		int anpico, altpico1, altpico2;
		float ancuerda, lcuerda1, lcuerda2;
		int rot;
		bool invertiRotar;
	public:
		Brazo();
		void construirBrazoCarga();
		void construirBrazo();
		void construirPico();
		void construirCables();
		void dibujarBrazoCarga(int accion, int tipoDibujo);
		void MovimientoBrazo(int accion, int tipoDibujo);
};

#endif
