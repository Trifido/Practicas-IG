#include "BaseTorre.h"

//Constructor donde se inicializan los tamaños de la base y la torre de la grúa
BaseTorre::BaseTorre(){
	tamtorre= 16;
	tambase= 3;
	anchoTorre= 1;
	anchoBase= 4;
}

//Metodo para contruir ambas partes de la grúa
void BaseTorre::construirBaseTorre(){
	construirBase(tambase, anchoBase);
	construirTorre(tamtorre, anchoTorre);
}

//Metodo para guardar en una ED la base de la grúa
void BaseTorre::construirBase(float alto, float ancho){
	vector<float> vaux;
	_vertex3f trasla;
	trasla.x= 0;
	trasla.y=-(tamtorre+tambase);
	trasla.z=0;
	vaux.push_back(ancho);
	vaux.push_back(0);
	vaux.push_back(0);
	vaux.push_back(ancho);
	vaux.push_back(alto);
	vaux.push_back(0);

	base.copiarPerfilTraslacion(vaux, 5, 90, trasla);
}

//Metodo para guardar en una ED la torre de la grúa
void BaseTorre::construirTorre(float alto, float ancho){
	vector<float> vaux;
	_vertex3f trasla;
	trasla.x= 0;
	trasla.y=-tamtorre;
	trasla.z=0;
	vaux.push_back(ancho);
	vaux.push_back(0);
	vaux.push_back(0);
	vaux.push_back(ancho);
	vaux.push_back(alto);
	vaux.push_back(0);
	vaux.push_back(ancho);
	vaux.push_back(alto);
	vaux.push_back(0);

	torre.copiarPerfilTraslacion(vaux, 5, 90, trasla);
}

//Metodo para dibujar la base y la torre.
void BaseTorre::dibujarBaseTorre(int tipoDibujo){
	switch(tipoDibujo){
		case 0:
			base.draw_puntos();
			torre.draw_puntos();
			break;
		case 1:
			base.modo_alambre();
			torre.modo_alambre();
			break;
		case 2:
			base.modo_solido(3);
			torre.modo_solido(5);
			break;
		case 3:
			base.modo_ajedrez();
			torre.modo_ajedrez();
			break;
	}
}