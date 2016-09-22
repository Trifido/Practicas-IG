#include "textura.h"

Textura::Textura(){
	ma[0]= ma[1]= ma[2]= 0.2;
	md[0]= md[1]= md[2]= 0.8;
	ms[0]= ms[1]= ms[2]= 0.0;
	me[0]= me[1]= me[2]= 0.0;
	ma[3]= md[3]= ms[3]= me[3]= 1.0;
	e=20.0;
}

//Inicializamos la textura agregandole la imagen.
bool Textura::CrearTextura(char *nombre){
	strcpy(nombreTextura, &nombre[0]);
	pimg= new jpg::Imagen(nombre);

	GLuint idTex;
	
	glGenTextures(1, &idTex);
	glBindTexture(GL_TEXTURE_2D,idTex);

	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SEPARATE_SPECULAR_COLOR);
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

	gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGB, pimg->tamX(), pimg->tamY(), GL_RGB, GL_UNSIGNED_BYTE, &(pimg->leerPixels()[0]) );
	//glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, pimg->tamX(), pimg->tamY(), 0, GL_RGB, GL_UNSIGNED_BYTE, &(pimg->leerPixels()[0]) );

	this->id= idTex;

	return true;
}

//Metodo para visualizar la textura.
void Textura::ActivarTextura(vector <float> &tablaCoordenadas){
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ma);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, ms);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, e);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, md);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, id);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, &tablaCoordenadas[0]);
}

//Metodo para desactivar la textura
void Textura::DesactivarTextura(){
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

//Metodo para modificar las especificaciones del material.
void Textura::ModificarMaterial(int tipo, float cantidad){
	if(tipo==1){
		ma[0]= ma[1]= ma[2]= cantidad;
	}
	else if(tipo==2){
		md[0]= md[1]= md[2]= cantidad;
	}
	else if(tipo==3){
		ms[0]= ms[1]= ms[2]= cantidad;
	}
	else if(tipo==4){
		me[0]= me[1]= me[2]= cantidad;
	}
	else if(tipo==5){
		e=cantidad;
	}
}