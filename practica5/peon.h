#ifndef _PEON_
#define _PEON_

#include <GL/gl.h>
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

class Peon{
	private:
		ED peon;
		_vertex3f trasla;
		vector<float> v;
		Textura textura;
		int tipo;
	public:
		Peon();
		void ConstruirPeon(int tipo);
		void DibujarPeon(bool flat);
};

#endif
