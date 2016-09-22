#include "CuerdaYCarga.h"

//Constructor donde se inicializan los tamaños de la carga, el raíl y la cuerda.
CuerdaYCarga::CuerdaYCarga(){
	largoCuerda=0.0;
	distrail=0.0;
	altRail= 0.2;
	ancRail= 0.4;
	laCuerda= 3;
	anCuerda= 0.05;
	anCarga= 1;
	alCarga= 1;
	invertirCuerda= invertiRail= false;
}

//Metodo para realizar los movimientos de escalada y traslancion tanto de la cuerda como del raíl.
void CuerdaYCarga::Dibujar(int accion, int tipoDibujo){
	if(accion==2 && largoCuerda < 4)
		largoCuerda+=0.5;
	if(accion==3 && distrail < 9)
		distrail+=0.5;
	if(accion==4 && distrail > -1.5)
		distrail-=0.5;
	if(accion==5 && largoCuerda > -0.5)
		largoCuerda-=0.5;
	if(accion==99){
		if(largoCuerda==4)
			invertirCuerda=true;
		if(largoCuerda==-0.5)
			invertirCuerda=false;
		if(distrail==9)
			invertiRail=true;
		if(distrail==-1.5)
			invertiRail=false;

		if(invertirCuerda)
			largoCuerda-=0.5;
		else
			largoCuerda+=0.5;

		if(invertiRail)
			distrail-=0.5;
		else
			distrail+=0.5;
	}

	glPushMatrix();
		glTranslatef(distrail,0,0);
		DibujarRail(tipoDibujo);

		glPushMatrix();
			glScalef(1,1+largoCuerda,0);
			DibujarCuerda(tipoDibujo);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(0,-(3*largoCuerda),0);
			DibujarCarga(tipoDibujo);
		glPopMatrix();
	glPopMatrix();
}

//Metodo para contruir esta última parte de la grúa
void CuerdaYCarga::Construir(){
	ConstruirRail();
	ConstruirCuerda();
	ConstruirCarga();
}

//Metodo para guardar en una ED el raíl 
void CuerdaYCarga::ConstruirRail(){
	vector<float> vaux;

	vaux.push_back(ancRail);
	vaux.push_back(0);
	vaux.push_back(0);
	vaux.push_back(ancRail);
	vaux.push_back(altRail);
	vaux.push_back(0);

	rail.calcularPuntos(vaux, 90, 5,0,false);
	rail.rotarSobreY(45);
	rail.trasladar(-14,-altRail,0);

	rail.calcularCaras(5, 90, 2, 0,false);
	rail.calcularNormales();
}

//Metodo para guardar en una ED la cuerda de la grúa
void CuerdaYCarga::ConstruirCuerda(){
	vector<float> vaux;

	vaux.push_back(anCuerda);
	vaux.push_back(0);
	vaux.push_back(0);
	vaux.push_back(anCuerda);
	vaux.push_back(laCuerda);
	vaux.push_back(0);

	cuerda.calcularPuntos(vaux, 90, 5,0,false);
	cuerda.trasladar(-14,-laCuerda,0);

	cuerda.calcularCaras(5, 90, 2, 0,false);
	cuerda.calcularNormales();
}

//Metodo para guardar en una ED la carga
void CuerdaYCarga::ConstruirCarga(){
	vector<float> vaux;

	vaux.push_back(anCarga);
	vaux.push_back(0);
	vaux.push_back(0);
	vaux.push_back(anCarga);
	vaux.push_back(alCarga);
	vaux.push_back(0);

	carga.calcularPuntos(vaux, 90, 5,0,false);
	carga.trasladar(-14,-(laCuerda+alCarga),0);

	carga.calcularCaras(5, 90, 2, 0, false);
	carga.calcularNormales();
}

//Metodo para dibujar con los distintos modos el raíl
void CuerdaYCarga::DibujarRail(int tipoDibujo){
	switch(tipoDibujo){
		case 0:
			rail.draw_puntos();
			break;
		case 1:
			rail.modo_alambre();
			break;
		case 2:
			rail.modo_solido(1);
			break;
		case 3:
			rail.modo_ajedrez();
			break;
	}
}

//Metodo para dibujar con los distintos modos la cuerda
void CuerdaYCarga::DibujarCuerda(int tipoDibujo){
		switch(tipoDibujo){
		case 0:
			cuerda.draw_puntos();
			break;
		case 1:
			cuerda.modo_alambre();
			break;
		case 2:
			cuerda.modo_solido(0);
			break;
		case 3:
			cuerda.modo_ajedrez();
			break;
	}
}

//Metodo para dibujar con los distintos modos la carga
void CuerdaYCarga::DibujarCarga(int tipoDibujo){
	switch(tipoDibujo){
		case 0:
			carga.draw_puntos();
			break;
		case 1:
			carga.modo_alambre();
			break;
		case 2:
			carga.modo_solido(1);
			break;
		case 3:
			carga.modo_ajedrez();
			break;
	}
}
