#include "lata.h"

Lata::Lata(){

}

//Metodo para construir la lata.
void Lata::crearFigura(){
	char nombre[]= "text-lata-1.jpg";
	textura.CrearTextura(nombre);
	central.AgregarTextura(textura);

	char filename[30];
	vector<int> c;
	_file_ply archivo;
	_vertex3f trasla;
	trasla.x=0;
	trasla.y=0;
	trasla.z=0;

	strcpy(filename, "lata-psup.ply");
	archivo.open(filename);
	archivo.read(vsup, c);
	archivo.close();
	superior.creaRevolucion(vsup,21,18,trasla,2);

	strcpy(filename, "lata-pcue.ply");
	archivo.open(filename);
	archivo.read(vcen, c);
	archivo.close();
	//central.creaRevolucion(vcen,21,18,trasla,1);
	central.creaRevolucion(vcen,361,1,trasla,1);

	strcpy(filename, "lata-pinf.ply");
	archivo.open(filename);
	archivo.read(vinf, c);
	archivo.close();
	inferior.copiarPerfilTraslacion(vinf,21,18,trasla);
}

//Metodo para dibujar la figura.
void Lata::Dibujar(){
	central.modo_textura();

	GLfloat color[4] = {1.0, 1.0, 1.0, 1.0 };
	GLfloat color2[4] = {1.0, 1.0, 1.0, 1.0};
	glMaterialfv( GL_FRONT, GL_DIFFUSE, color);
	glMaterialfv(GL_FRONT, GL_SPECULAR, color2);
	
	superior.modo_sinTextura();
	inferior.modo_sinTextura();
}
