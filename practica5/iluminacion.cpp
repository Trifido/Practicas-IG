#include "iluminacion.h"

Foco::Foco(){
	encendido=false;
	alfa=0.0;
	beta=0.0;
}

//Metodo para inicializar el foco
void Foco::MontarFoco(GLfloat *color, GLfloat *posicion){
	for(int i=0; i<4; i++){
		colorLuz[i]=color[i];
		posicionLuz[i]=posicion[i];
	}

	if(posicionLuz[3]==0.0){
		esPosicional=false;
	}
	else{
		esPosicional=true;
	}
}

//Metodo para activar o desactivar focos.
void Foco::ActivarFoco(){
	if(encendido){
		encendido=false;
	}
	else{
		encendido=true;	
	}
}

//Metodo para visionar los focos dinámico y posicional
void Foco::VisionarLuz(){
	if(encendido && !esPosicional){
		const float ejeZ[4] = { 0.0, 0.0, 1.0, 0.0 } ;
		//glMatrixMode( GL_MODELVIEW ) ;
		glPushMatrix() ;
		glLoadIdentity() ; 
		//glMultMatrixf( posicionLuz ) ; 
		// rotación a grados en torno a eje Y
		glRotatef( alfa, 0.0, 1.0, 0.0 ) ;
		// rotación b grados en torno al eje X
		glRotatef( beta, 1.0, 0.0, 0.0 ) ;
		// luz paralela eje Z+
		glLightfv( GL_LIGHT1, GL_DIFFUSE, colorLuz);
		glLightfv( GL_LIGHT1, GL_POSITION, ejeZ );
		glEnable(GL_LIGHT1);
		glPopMatrix() ;
	}
	else if(encendido && esPosicional){
		glLightfv( GL_LIGHT0, GL_AMBIENT, colorLuz);
		glLightfv( GL_LIGHT0, GL_POSITION, posicionLuz);
		glEnable(GL_LIGHT0);
	}
	else{
		if(esPosicional)
			glDisable(GL_LIGHT0);
		else
			glDisable(GL_LIGHT1);
	}
}

//Metodos para rotar el foco dinámico
void Foco::MoverAlfa(bool opcion){
	if(opcion)
		alfa+=10.0;
	else
		alfa-=10.0;
}

void Foco::MoverBeta(bool opcion){
	if(opcion)
		beta+=10.0;
	else
		beta-=10.0;
}