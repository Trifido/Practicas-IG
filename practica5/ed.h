#ifndef _ED_
#define _ED_

#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <queue>
#include <assert.h>
#include "vertex.h"
#include "textura.h"

#include "jpg_imagen.hpp"
#include "jpg_jinclude.h"

using namespace std;

//Struct para guardar las normales, guardo el origen y la dirección de la normal
struct Normal{
	_vertex3f n1, n2;
};

//He añadido una variable normal para poder acceder directamente a la normal de dicho triangulo
struct Triangulo{
	_vertex3f v1;
	_vertex3f v2;
	_vertex3f v3;
	Normal normal;
};

//Struct para guardar las normales a los vertices,
//en el campo triang guardo los triangulos relacionados con el vertice
//id donde guardo el propio vertice
//nv que es la normal a dicho vertice
struct verNormal{
	vector<Triangulo> triang;
	_vertex3f id;
	_vertex3f nv;
};

_vertex3f calcularBari(_vertex3f A, _vertex3f B, _vertex3f C);

_vertex3f calcularNormal(_vertex3f A, _vertex3f B, _vertex3f C);

_vertex3f calcularNormalVertices(verNormal vertice);

void reducirLongitudNormal(Triangulo &triangulo, float num);

class ED{
	private:
		int numVerticesTotales;
		int nCopias;
		vector<_vertex3f> vertices;
		vector<Triangulo> triangulos;
		//En este vector guardo las normales a los vertices.
		vector<verNormal> verticesCaras;
		//Practica 4
		//He realizado cambios y para visualizar en modo suave he usado otro tipo de estructuras de datos
		//tambien guardo las coordenadas que le corresponde a cada textura.
		vector<float> tablaCoordenadas;
		vector<GLfloat> coordVertices;
		vector<int> indicesCaras;
		vector<GLfloat> verticesNormales;
		vector<GLfloat> carasNormales;
		Textura textura;
	public:
		ED();
		void calcularNormales();
		int detectarPerfil(float x_inf, float z_inf, float x_sup, float z_sup);
		void calcularPuntos(vector<float> &vaux, float angulo, int numrotaciones, int tipoperfil, bool p4);
		int obtenerVerticeNormal(_vertex3f vbuscar);
		void calcularCaras(int rotaciones, int angulo, int nvert, int tipoperfil, bool p4);
		void trasladar(float x, float y, float z);
		void trasladarFigura(_vertex3f trala);
		void rotarSobreZ(int angulo);
		void rotarSobreX(int angulo);
		void rotarSobreY(int angulo);
		void copiar(vector<float> veraux, vector<int> triaux);
		void copiarPerfilTraslacion(vector<float> veraux, int rotaciones, int grados, _vertex3f trasla);
		void copiarPerfilRotacion(vector<float> veraux, int rotaciones, int grados, _vertex3f trasla);
		void copiarPerfil(vector<float> veraux, vector<int> triaux, int rotaciones, int grados);
		void creaRevolucion(vector<float> veraux, float rotaciones, float grados, _vertex3f trasla, int tipo);
		void agregarTablasCord();
		void draw_puntos();
		void modo_alambre();
		void modo_solido(int color);
		void modo_ajedrez();
		void AgregarTextura(Textura text);
		void modo_textura();
		void modo_textura_automatica();
		void modo_sinTextura();
		void modo_sinTexturaCaras();
		void limpiar();
		void modo_normales();
		void normales_vertices();
};

#endif
