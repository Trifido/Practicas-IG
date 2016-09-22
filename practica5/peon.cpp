#include "peon.h"

Peon::Peon(){
	trasla.x=0;
	trasla.y=0;
	trasla.z=5;
}

//En la inicialización del peón indicamos la posición en la que vamos a visualizarlo,
//leemos el ply, y creamos su ED.
void Peon::ConstruirPeon(int tipo){
	if(tipo==3){
		char nombre[]= "text-madera.jpg";
		textura.CrearTextura(nombre);
		textura.ModificarMaterial(3,1.0);
		textura.ModificarMaterial(2,1.0);
		peon.AgregarTextura(textura);
	}

	this->tipo= tipo;
	char filename[30];
	vector<int> c;
	strcpy(filename, "peon.ply");
	_file_ply archivo;
	archivo.open(filename);
	archivo.read(v, c);
	archivo.close();

	if(tipo==1){
		trasla.z=5;
	}
	else if(tipo==2){
		trasla.x= 5;
		trasla.z= 0;
	}
	else if(tipo==3){
		trasla.z=-5;
	}
	peon.copiarPerfilTraslacion(v,73,5,trasla);
}

//Dependiendo del tipo de peón podemos visualizar con la textura de madera,
// con el material difuso o con el material especular.
void Peon::DibujarPeon(bool flat){
	if(tipo==3){
		peon.modo_textura_automatica();
	}
	else if(tipo==1){
		GLfloat colo[4] = {1.0, 1.0, 1.0, 1.0 };
		GLfloat colo2[4] = {0.0, 0.0, 0.0, 0.0};
		glMaterialfv( GL_FRONT, GL_DIFFUSE, colo);
		glMaterialfv(GL_FRONT, GL_SPECULAR, colo2);

		if(flat)
			peon.modo_sinTexturaCaras();
		else
			peon.modo_sinTextura();
	}
	else if(tipo==2){
		GLfloat colo[4] = {0.0, 0.0, 0.0, 0.1 };
		GLfloat colo2[4] = {1.0, 1.0, 1.0, 1.0};
		glMaterialfv( GL_FRONT, GL_DIFFUSE, colo);
		glMaterialfv(GL_FRONT, GL_SPECULAR, colo2);
		
		if(flat)
			peon.modo_sinTexturaCaras();
		else
			peon.modo_sinTextura();
	}
}