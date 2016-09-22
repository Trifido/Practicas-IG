#include "figura.h"

Figura::Figura(){
}

//Metodo para construir la figura.
void Figura::crearFigura(){
	batorre.construirBaseTorre();
	brazo.construirBrazoCarga();
}

//Metodo para dibujar la figura.
void Figura::Dibujar(int accion, int tipoDibujo){
	glTranslatef (0, 19, 0);
	batorre.dibujarBaseTorre(tipoDibujo);
	brazo.MovimientoBrazo(accion, tipoDibujo);
}

