#include "ed.h"

//Funcion para calcular el baricentro de una cara
_vertex3f calcularBari(_vertex3f A, _vertex3f B, _vertex3f C){
	_vertex3f result;
	result.x= (A.x + B.x + C.x)/3;
	result.y= (A.y + B.y + C.y)/3;
	result.z= (A.z + B.z + C.z)/3;
	return result;
}

//Funcion para calcular la normal de una cara
_vertex3f calcularNormal(_vertex3f A, _vertex3f B, _vertex3f C){
	_vertex3f result, AB, BC;
	float modulo;
	AB= B-A;
	BC= C-B;
	result.x= (AB.y*BC.z) - (AB.z*BC.y);
	result.y= (AB.z*BC.x) - (AB.x*BC.z);
	result.z= (AB.x*BC.y) - (AB.y*BC.x);
	modulo= sqrt(result.x*result.x + result.y*result.y + result.z*result.z);
	modulo*=1.0;
	result.x/=modulo;
	result.y/=modulo;
	result.z/=modulo;

	return result;
}

//Funcion para calcular la normal de un vertice
_vertex3f calcularNormalVertices(verNormal vertice){
	_vertex3f result(0,0,0);
	
	float i;
	for(i=0; i<vertice.triang.size(); i++){
		result+= vertice.triang.at(i).normal.n2;
	}

	result.x/=i*1.0;
	result.y/=i*1.0;
	result.z/=i*1.0;

	return result;
}

ED::ED(){
}

void ED::trasladar(float x, float y, float z){
	for(int i=0; i<vertices.size(); i++){
		vertices.at(i).x+= x;
		vertices.at(i).y+= y;
		vertices.at(i).z+= z;
	}
}

void ED::trasladarFigura(_vertex3f trala){
	trasladar(trala.x, trala.y, trala.z);
	for(int i=0; i<triangulos.size(); i++){
		triangulos.at(i).v1+=trala;
		triangulos.at(i).v2+=trala;
		triangulos.at(i).v3+=trala;
	}
}

void ED::rotarSobreZ(int angulo){
	float rad= (angulo*M_PI)/180;
	float aux_x, aux_y;
	for(int i=0; i<vertices.size(); i++){
		aux_x= vertices.at(i).x;
		aux_y= vertices.at(i).y;
		vertices.at(i).x= cos(rad)*aux_x - sin(rad)*aux_y;
		vertices.at(i).y= sin(rad)*aux_x + cos(rad)*aux_y;
	}
}

void ED::rotarSobreX(int angulo){
	float rad= (angulo*M_PI)/180;
	float aux_y, aux_z;
	for(int i=0; i<vertices.size(); i++){
		aux_y= vertices.at(i).y;
		aux_z= vertices.at(i).z;
		vertices.at(i).y= cos(rad)*aux_y - sin(rad)*aux_z;
		vertices.at(i).z= sin(rad)*aux_y + cos(rad)*aux_z;
	}
}

void ED::rotarSobreY(int angulo){
	float rad= (angulo*M_PI)/180;
	float x, z;
	for(int j=0; j<vertices.size() ;j++){
		x= vertices.at(j).x;
		z= vertices.at(j).z;
		vertices.at(j).x= cos(rad)*x + sin(rad)*z;
		vertices.at(j).z= -sin(rad)*x + cos(rad)*z;
	}
}

//Metodo para calcular los puntos rotados sobre el eje Y
void ED::calcularPuntos(vector<float> &vaux, float angulo, int numrotaciones, int tipoperfil, bool p4){
	_vertex3f v, fin, fin2;
	float rad= (angulo*M_PI)/180;
	int tam= vaux.size();
	int nvertices= tam/3;
	int nv= nvertices;
	float x, y, z;

	if(vaux[1]>vaux[vaux.size()-2]){
		queue<float> aux;
		for(int i=0; i<vaux.size(); i++){
			aux.push(vaux[i]);
		}
		int j=0;
		while(!aux.empty()){
			vaux[j*3+2]= aux.front();
			aux.pop();
			vaux[j*3+1]= aux.front();
			aux.pop();
			vaux[j*3]= aux.front();
			aux.pop();
			j++;
		}
	}

	//Los dos vertices finales del vector corresponden a los dos extremos de la figura.
	//Según el perfil guardo los vertices más extremos que forman la tapadera. 
	if(tipoperfil==0){
		fin.x= 0;
		fin.y= vaux.at(1);
		fin.z=0;

		fin2.x= 0;
		fin2.y= vaux.at(tam-2);
		fin2.z= 0;

		tam+=3;
	}
		//Si los dos extremos se encuentran sobre el eje Y, guardaremos los vertices al final del vector.
	else if(tipoperfil==1){
		fin.x= vaux.at(0);
		fin.y= vaux.at(1);
		fin.z= vaux.at(2);

		fin2.x= vaux.at(tam-3);
		fin2.y= vaux.at(tam-2);
		fin2.z= vaux.at(tam-1);

		for(int i=0; i<3; i++){
			vaux.erase(vaux.begin());
			vaux.erase(vaux.end()-1);
		}
		tam-=3;
	}
		//En el caso de que solo el vertice inferior se encuentre sobre el eje Y.
	else if(tipoperfil==2){
		fin.x= vaux.at(0);
		fin.y= vaux.at(1);
		fin.z= vaux.at(2);

		fin2.x= 0;
		fin2.y= vaux.at(tam-2);
		fin2.z= 0;

		for(int i=0; i<3; i++)
			vaux.erase(vaux.begin());
	}
		//En el caso de que solo se encuentre el extremo superior sobre el eje Y.
	else{
		fin.x= 0;
		fin.y= vaux.at(1);
		fin.z= 0;

		fin2.x= vaux.at(tam-3);
		fin2.y= vaux.at(tam-2);
		fin2.z= vaux.at(tam-1);

		for(int i=0; i<3; i++)
			vaux.erase(vaux.end()-1);
	}

	//Reservamos el tamaño correspondiente
	tam-=3;
	vaux.resize((numrotaciones*tam)+tam);

	nvertices= tam/3;
	nv= nvertices;
	//Recorremos el vector de coordenadas de vertices y guardamos los puntos en el vector "vertices".
	if(numrotaciones==5)
		numrotaciones=4;
	//Voy obteniendo progresivamente los puntos calculando la rotación que supondría con el angulo que le doy.
	for(int i=1; i<=numrotaciones; i++){
		for(int j=0; j<nvertices ;j++, tam+=3, nv++){
			x= vaux.at((tam/nv)*j);
			y= vaux.at(((tam/nv)*j)+1);
			z= vaux.at(((tam/nv)*j)+2);

			v.x= cos(rad*i)*x + sin(rad*i)*z;
			v.y= y;
			v.z= -sin(rad*i)*x + cos(rad*i)*z;
			vertices.push_back(v);
		}
	}

	//Al final incluyo los dos vertices que son las tapaderas
	vertices.push_back(fin);
	vertices.push_back(fin2);

	//Reservo el tamaño para el vector de normales a los vertices
	if(!p4)
		verticesCaras.resize(vertices.size());
	else
		verticesCaras.resize(vertices.size()-2);
}

//Metodo para calcular las caras, voy obteniendo las caras de abajo a arriba, cuando llego al vertice superior en el que no
// se debe obtener ninguna cara vuelvo a empezar desde abajo.
void ED::calcularCaras(int rotaciones, int angulo, int nvert, int tipoperfil, bool p4){
	vector<int> caux;
	int aux;
	int numvertices= nvert;
	int mod= nvert*(rotaciones-1);
//Segun el tipo de perfil obtengo un modulo.
	if(tipoperfil==1){
		numvertices-=2;
		mod= (nvert-2)*(rotaciones-1);
	}
	else if(tipoperfil>1){
		numvertices-=1;
		mod= (nvert-1)*(rotaciones-1);
	}

	if((rotaciones-1)*angulo != 360){
		mod= 1000000000;
	}

	//Si es un objeto lata quitamos las tapaderas
	if(p4){
		vertices.pop_back();
		vertices.pop_back();
	}

	for(int r= 0; r< (rotaciones-1); r++){
		aux= (numvertices*(r+1))-1;
		for(int i=r*numvertices; i<(numvertices*(r+1)); i++){
			if(i!=aux){
				caux.push_back(i%mod);
				caux.push_back((i+numvertices)%mod);
				caux.push_back((i+1)%mod);
			
				caux.push_back((i+1)%mod);
				caux.push_back((numvertices+i)%mod);
				caux.push_back((numvertices+i+1)%mod);
			}
		}
	}

	indicesCaras.resize(caux.size());
	for(int i=0; i<caux.size(); i++){
		indicesCaras[i]= caux[i];
	}

	Triangulo taux;
	//Guardo los triangulos en el vector de caras "triangulos"
	//Cuerpo de la figura, guardo las normales a las caras y también las normales a los vertices
	for(int i=0,j=0; i+3<=caux.size(); i+=3, j++){
		taux.v1= vertices.at(caux.at(i));
		taux.v2= vertices.at(caux.at(i+1));
		taux.v3= vertices.at(caux.at(i+2));
		taux.normal.n1= calcularBari(taux.v1, taux.v2, taux.v3);
		taux.normal.n2= calcularNormal(taux.v1, taux.v2, taux.v3);

		verticesCaras.at(caux.at(i)).id= vertices.at(caux.at(i));
		verticesCaras.at(caux.at(i)).triang.push_back(taux);
		verticesCaras.at(caux.at(i+1)).id= vertices.at(caux.at(i+1));
		verticesCaras.at(caux.at(i+1)).triang.push_back(taux);
		verticesCaras.at(caux.at(i+2)).id= vertices.at(caux.at(i+2));
		verticesCaras.at(caux.at(i+2)).triang.push_back(taux);

		triangulos.push_back(taux);
	}
/*if(p4){
	printf("triangulos.size()=%i\n",triangulos.size());
	for(int i=0; i<20; i++)
		triangulos.pop_back();
}*/

if(!p4){
		int vertice1, vertice2, vertice3;
		//Guardo los triangulos que forman la tapadera inferior en el vector de caras "triangulos"
		//Tapadera inferior, guardo las normales a las caras y también las normales a los vertices
		for(int i=0; i<(rotaciones-1); i++){
			vertice1= (vertices.size()-2);
			vertice2= (numvertices*(i + 1))%mod;
			vertice3= (numvertices*i)%mod;

			indicesCaras.push_back(vertice1);
			indicesCaras.push_back(vertice2);
			indicesCaras.push_back(vertice3);

			taux.v1= vertices.at(vertice1);
			taux.v2= vertices.at(vertice2);
			taux.v3= vertices.at(vertice3);
			taux.normal.n1= calcularBari(taux.v1, taux.v2, taux.v3);
			taux.normal.n2= calcularNormal(taux.v1, taux.v2, taux.v3);

			verticesCaras.at(vertice1).id= vertices.at(vertice1);
			verticesCaras.at(vertice1).triang.push_back(taux);
			verticesCaras.at(vertice2).id= vertices.at(vertice2);
			verticesCaras.at(vertice2).triang.push_back(taux);
			verticesCaras.at(vertice3).id= vertices.at(vertice3);
			verticesCaras.at(vertice3).triang.push_back(taux);

			triangulos.push_back(taux);
		}	
		//Guardo los triangulos que forman la tapadera superior en el vector de caras "triangulos"
		//Tapadera superior, guardo las normales a las caras y también las normales a los vertices
		for(int i=0; i<(rotaciones-1); i++){
			vertice1= (vertices.size()-1);
			vertice2= ((numvertices-1)+(i*numvertices))%mod;
			vertice3= ((numvertices-1)+(i*numvertices)+numvertices)%mod;

			indicesCaras.push_back(vertice1);
			indicesCaras.push_back(vertice2);
			indicesCaras.push_back(vertice3);

			taux.v1= vertices.at(vertice1);
			taux.v2= vertices.at(vertice2);
			taux.v3= vertices.at(vertice3);
			taux.normal.n1= calcularBari(taux.v1, taux.v2, taux.v3);
			taux.normal.n2= calcularNormal(taux.v1, taux.v2, taux.v3);

			verticesCaras.at(vertice1).id= vertices.at(vertice1);
			verticesCaras.at(vertice1).triang.push_back(taux);
			verticesCaras.at(vertice2).id= vertices.at(vertice2);
			verticesCaras.at(vertice2).triang.push_back(taux);
			verticesCaras.at(vertice3).id= vertices.at(vertice3);
			verticesCaras.at(vertice3).triang.push_back(taux);

			triangulos.push_back(taux);		
		}
	}
}

//Metodo para calcular las normales a los vertices
void ED::calcularNormales(){
	for(int i=0; i<verticesCaras.size(); i++)
		verticesCaras.at(i).nv= calcularNormalVertices(verticesCaras.at(i));
}

//Metodo que nos indica el tipo de perfil: 0= ningun extremo del perfil sobre eje Y, 1= los dos extremos, 2= el extremo inferior, 3= extremo superior
int ED::detectarPerfil(float x_inf, float z_inf, float x_sup, float z_sup){
	if((x_inf!=0 || z_inf!=0) && (x_sup!=0 || z_sup!=0))
		return 0;
	else if((x_inf==0 && z_inf==0) && (x_sup==0 && z_sup==0))
		return 1;
	else if(x_inf==0 && z_inf==0)
		return 2;
	else if(x_sup==0 && z_sup==0)
		return 3;
}

//Constructor de la practica 2
void ED::copiarPerfil(vector<float> veraux, vector<int> triaux, int rotaciones, int grados){
	int nvert= veraux.size()/3;
	int tipoperfil= detectarPerfil(veraux.at(0), veraux.at(2), veraux.at(veraux.size()-3), veraux.at(veraux.size()-1));

	calcularPuntos(veraux, grados, rotaciones,tipoperfil, false);
	calcularCaras(rotaciones, grados, nvert, tipoperfil, false);
	calcularNormales();
}

void ED::copiarPerfilTraslacion(vector<float> veraux, int rotaciones, int grados, _vertex3f trasla){
	int nvert= veraux.size()/3;
	int tipoperfil= detectarPerfil(veraux.at(0), veraux.at(2), veraux.at(veraux.size()-3), veraux.at(veraux.size()-1));

	calcularPuntos(veraux, grados, rotaciones,tipoperfil, false);
	trasladar(trasla.x, trasla.y, trasla.z);

	coordVertices.resize(vertices.size()*3);
	for(int i=0, j=0; i<vertices.size(); i++, j++){
		coordVertices[j*3]=vertices.at(i).x;
		coordVertices[(j*3)+1]=vertices.at(i).y;
		coordVertices[(j*3)+2]=vertices.at(i).z;
	}

	calcularCaras(rotaciones, grados, nvert, tipoperfil, false);
	calcularNormales();

	verticesNormales.resize(vertices.size()*3);

	int pos;
	for(int i=0; i<vertices.size(); i++){
		pos= obtenerVerticeNormal(vertices[i]);
		verticesNormales[i*3]= verticesCaras.at(i).nv.x;
		verticesNormales[i*3 + 1]= verticesCaras.at(i).nv.y;
		verticesNormales[i*3 + 2]= verticesCaras.at(i).nv.z;
	}
}

//--------------------Practica 4 ------------------------------------------------------------------------------------------------------------------------

//Metodo para añadir coordenadas para las texturas.
void ED::agregarTablasCord(){
	float alfa=0.0;
	float mini, maxi, diff;

	int max= numVerticesTotales/nCopias;
	mini= vertices[0].y;
	maxi= vertices[0].y;

	for(int i=0; i<numVerticesTotales; i++){
		if(mini>vertices[i].y)
			mini= vertices[i].y;
		if(maxi<vertices[i].y)
			maxi= vertices[i].y;
	}

	diff= maxi - mini;

	for(int i=0; i<numVerticesTotales; i++){
		alfa= atan2(vertices[i].z, vertices[i].x);
		tablaCoordenadas.push_back(-1*(0.5+alfa)/(2.0*M_PI));
		tablaCoordenadas.push_back(-1*(vertices[i].y -mini)/(diff));
	}
}

//Constructor practica 4.
void ED::creaRevolucion(vector<float> veraux, float rotaciones, float grados, _vertex3f trasla,  int tipo){
	int nvert= veraux.size()/3;
	nCopias= rotaciones;
	numVerticesTotales= nvert*rotaciones;
	int tipoperfil= detectarPerfil(veraux.at(0), veraux.at(2), veraux.at(veraux.size()-3), veraux.at(veraux.size()-1));

	calcularPuntos(veraux, grados, rotaciones,tipoperfil, true);
	trasladar(trasla.x, trasla.y, trasla.z);
	coordVertices.resize(vertices.size()*3);
	for(int i=0, j=0; i<vertices.size(); i++, j++){
		coordVertices[j*3]=vertices.at(i).x;
		coordVertices[(j*3)+1]=vertices.at(i).y;
		coordVertices[(j*3)+2]=vertices.at(i).z;
	}

	calcularCaras(rotaciones, grados, nvert, tipoperfil, true);

	calcularNormales();

	if(tipo==1)
		agregarTablasCord();

	verticesNormales.resize(vertices.size()*3);

	int pos;
	for(int i=0; i<vertices.size(); i++){
		pos= obtenerVerticeNormal(vertices[i]);
		verticesNormales[i*3]= verticesCaras.at(i).nv.x;
		verticesNormales[i*3 + 1]= verticesCaras.at(i).nv.y;
		verticesNormales[i*3 + 2]= verticesCaras.at(i).nv.z;
	}	
}

//Funcion para obtener un vertice
int ED::obtenerVerticeNormal(_vertex3f vbuscar){
	bool encontrado=false;
	int result;
	for(int j=0; j<verticesCaras.size() && !encontrado; j++){
		if(vbuscar==verticesCaras.at(j).id){
			encontrado=true;
			result=j;
		}
	}
	return result;
}

void ED::AgregarTextura(Textura text){
	textura= text;
}

void ED::modo_sinTexturaCaras(){
	glPolygonMode(GL_FRONT,GL_FILL);
	glBegin(GL_TRIANGLES);				
		for(unsigned i=0; i<triangulos.size(); i++){
			glNormal3f(triangulos.at(i).normal.n2.x, triangulos.at(i).normal.n2.y, triangulos.at(i).normal.n2.z);
			glVertex3f(triangulos.at(i).v1.x, triangulos.at(i).v1.y, triangulos.at(i).v1.z);
			glNormal3f(triangulos.at(i).normal.n2.x, triangulos.at(i).normal.n2.y, triangulos.at(i).normal.n2.z);
			glVertex3f(triangulos.at(i).v2.x, triangulos.at(i).v2.y, triangulos.at(i).v2.z);
			glNormal3f(triangulos.at(i).normal.n2.x, triangulos.at(i).normal.n2.y, triangulos.at(i).normal.n2.z);
			glVertex3f(triangulos.at(i).v3.x, triangulos.at(i).v3.y, triangulos.at(i).v3.z);
		}		
	glEnd();
}

void ED::modo_sinTextura(){
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glNormalPointer(GL_FLOAT, 0, &verticesNormales[0]);
	glVertexPointer(3, GL_FLOAT, 0, &coordVertices[0]);
	glDrawElements(GL_TRIANGLES, indicesCaras.size(), GL_UNSIGNED_INT, &indicesCaras[0]);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void ED::modo_textura(){
	textura.ActivarTextura(tablaCoordenadas);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glNormalPointer(GL_FLOAT, 0, &verticesNormales[0]);
	glVertexPointer(3, GL_FLOAT, 0, &coordVertices[0]);
	glDrawElements(GL_TRIANGLES, indicesCaras.size(), GL_UNSIGNED_INT, &indicesCaras[0]);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	textura.DesactivarTextura();
}
void ED::modo_textura_automatica(){
	glEnable( GL_TEXTURE_GEN_S );
	glEnable( GL_TEXTURE_GEN_T );

	glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR ) ;
	glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR ) ;

	modo_textura();

	glDisable( GL_TEXTURE_GEN_S );
	glDisable( GL_TEXTURE_GEN_T );
}

//------------------------------------------------------------------------------------------------------------------------------------------------------

//Constructor por copia para los modelos de la practica 1, incluyendo las normales.
void ED::copiar(vector<float> veraux, vector<int> triaux)
{
	_vertex3f vaux;
	Triangulo taux;
	int tam= veraux.size()/3;

	vertices.resize(tam);
	triangulos.resize(triaux.size()/3);
	verticesCaras.resize(tam);

	//Añadimos los vertices al array de vertices
	int j=0;
	for(unsigned i= 0; i+3<=veraux.size(); i= i+3, j++){
		vaux(veraux.at(i), veraux.at(i+1), veraux.at(i+2));
		vertices[j]= vaux;
	}

	j=0;
	for(unsigned i= 0; i+3<=triaux.size(); i= i+3, j++){
		//Añadimos triangulos
		taux.v1= vertices.at(triaux.at(i));
		taux.v2= vertices.at(triaux.at(i+1));
		taux.v3= vertices.at(triaux.at(i+2));
		taux.normal.n1= calcularBari(taux.v1, taux.v2, taux.v3);
		taux.normal.n2= calcularNormal(taux.v1, taux.v2, taux.v3);
		triangulos[j]= taux;
		//Añadimos las caras/triangulos que están relacionadas con cada vertice

		verticesCaras.at(triaux.at(i)).id=taux.v1;
		verticesCaras.at(triaux.at(i+1)).id= taux.v2;
		verticesCaras.at(triaux.at(i+2)).id= taux.v3;

		for(int aux=0; aux<3; aux++)
			verticesCaras.at(triaux.at(i+aux)).triang.push_back(taux);
		for(int aux=0; aux<3; aux++)
			verticesCaras.at(triaux.at(i+aux)).nv= calcularNormalVertices(verticesCaras.at(triaux.at(i+aux)));

	}
}

//Dibujamos los puntos de la figura.
void ED::draw_puntos()
{
	glColor3f(0,0,0);
	glPointSize(4);

	glBegin(GL_POINTS);
		for (unsigned i= 0; i<vertices.size(); i++){
			glVertex3f(vertices.at(i).x, vertices.at(i).y, vertices.at(i).z);
		}
	glEnd();
}

void ED::modo_alambre(){
	glColor3f(0,0,0);
	glPointSize(4);

	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glBegin(GL_TRIANGLES);				
		for(unsigned i=0; i<triangulos.size(); i++){
			glVertex3f(triangulos.at(i).v1.x, triangulos.at(i).v1.y, triangulos.at(i).v1.z);
			glVertex3f(triangulos.at(i).v2.x, triangulos.at(i).v2.y, triangulos.at(i).v2.z);
			glVertex3f(triangulos.at(i).v3.x, triangulos.at(i).v3.y, triangulos.at(i).v3.z);
		}		
	glEnd();
}

void ED::modo_solido(int color){
	switch(color){
		case 0:
			glColor3f(0,0,0); //NEGRO
			break;
		case 1:
			glColor3f(1,0,0); //ROJO
			break;
		case 2:
			glColor3f(0,1,0); //VERDE
			break;
		case 3:
			glColor3f(0,0,1); //AZUL
			break;
		case 4:
			glColor3f(1,1,0); //AMARILLO
			break;
		case 5:
			glColor3f(1,0.5,0); //NARANJA
			break;
		case 6:
			glColor3f(1,1,1); //BLANCO
			break;
	}

	glPointSize(4);
	//Indicamos solo GL_FRONT porque solo vamos a observar el exterior.
	glPolygonMode(GL_FRONT,GL_FILL);

	glBegin(GL_TRIANGLES);				
		for(unsigned i=0; i<triangulos.size(); i++){
			glVertex3f(triangulos.at(i).v1.x, triangulos.at(i).v1.y, triangulos.at(i).v1.z);
			glVertex3f(triangulos.at(i).v2.x, triangulos.at(i).v2.y, triangulos.at(i).v2.z);
			glVertex3f(triangulos.at(i).v3.x, triangulos.at(i).v3.y, triangulos.at(i).v3.z);
		}		
	glEnd();
}

void ED::modo_ajedrez(){
	glPointSize(4);
	glPolygonMode(GL_FRONT,GL_FILL);
	glBegin(GL_TRIANGLES);				
		for(unsigned i=0; i<triangulos.size(); i++){
			if(i%2==0)
				glColor3f(0,0,0);
			else 
				glColor3f(1,0,0);

			glVertex3f(triangulos.at(i).v1.x, triangulos.at(i).v1.y, triangulos.at(i).v1.z);
			glVertex3f(triangulos.at(i).v2.x, triangulos.at(i).v2.y, triangulos.at(i).v2.z);
			glVertex3f(triangulos.at(i).v3.x, triangulos.at(i).v3.y, triangulos.at(i).v3.z);
		}		
	glEnd();
}
//Metodo para pintar las normales a los vertices
void ED::normales_vertices(){
	_vertex3f sumatoria;
	glColor3f(1,0,1);
	glPointSize(4);
	glBegin(GL_LINES);
		for(int i=0; i<verticesCaras.size(); i++){
			glVertex3f(verticesCaras.at(i).id.x, verticesCaras.at(i).id.y, verticesCaras.at(i).id.z);
			glVertex3f(verticesCaras.at(i).nv.x + verticesCaras.at(i).id.x, verticesCaras.at(i).nv.y + verticesCaras.at(i).id.y, 
					verticesCaras.at(i).nv.z + verticesCaras.at(i).id.z);
		}
	glEnd();
}
//Metodo para pintar las normales a las caras
void ED::modo_normales(){
	glColor3f(0,1,1);
	glPointSize(4);

	glBegin(GL_LINES);
		for (unsigned i= 0; i<triangulos.size(); i++){
				glVertex3f(triangulos.at(i).normal.n1.x, triangulos.at(i).normal.n1.y, triangulos.at(i).normal.n1.z);
				glVertex3f(triangulos.at(i).normal.n2.x + triangulos.at(i).normal.n1.x, triangulos.at(i).normal.n2.y + triangulos.at(i).normal.n1.y, 
					triangulos.at(i).normal.n2.z + triangulos.at(i).normal.n1.z);
		}
	glEnd();

	normales_vertices();
}

void ED::limpiar(){
	triangulos.clear();
	vertices.clear();
	verticesCaras.clear();
}