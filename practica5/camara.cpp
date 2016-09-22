#include "camara.h"

Camara::Camara(){
	up.x= 0.0001;
	up.y= 1;
	up.z= 0;

	at.x= 0;
	at.y= 0.0000001;
	at.z= 0;

	left= -.5;
	right= .5;
	bottom= -.5;
	top= .5;
	near= 1;
	far= 1000;
}

void Camara::Construir(int tipo){
	//tipo1= planta, tipo2= alzado, tipo3= perfil
	if(tipo==1){
		eye.x= 0;
		eye.y= 10;
		eye.z= 0;
	}
	else if(tipo==2){
		eye.x= 0;
		eye.y= 4;
		eye.z= 20;
		left= -4.5;
		right= 4.5;
		bottom= -4.5;
		top= 4.5;
		//Tiene proyección ortogonal
	}
	else if(tipo==3){
		eye.x= 10;
		eye.y= 4;
		eye.z= 0;
		//Tiene proyección perspectiva
	}
}

void Camara::Reiniciar(int tipo){
	Camara();
	Construir(tipo);
}

void Camara::CambiarOjo(int accion){
	if(accion==0){ //D
		eye.x+=1.0;
		at.x+=1.0;
	}
	else if(accion==1){ //A
		eye.x-=1.0;
		at.x-=1.0;
	}
	else if(accion==2){ //W
		eye.z-=1.0;
		at.z-=1.0;
	}
	else if(accion==3){ //S
		eye.z+=1.0;
		at.z+=1.0;
	}
}

//Activar la cámara con sus parámetros
void Camara::Visionar(int tipo){
	if(tipo==1){
		gluLookAt(eye.x,eye.y,eye.z, at.x,at.y,at.z, up.x,up.y, up.z);
		glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
		glFrustum(left,right,bottom,top,near,far);
	}
	else if(tipo==2){
		gluLookAt(eye.x,eye.y,eye.z, at.x,at.y,at.z, up.x,up.y, up.z);
		glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
		glOrtho(left,right,bottom,top,near,far);
	}
	else{
		gluLookAt(eye.x,eye.y,eye.z, at.x,at.y,at.z, up.x,up.y, up.z);
		glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
		glFrustum(left,right,bottom,top,near,far);
	}
}
