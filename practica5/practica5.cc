//**************************************************************************
// Práctica 1
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include "stdlib.h"
#include "stdio.h"
#include <GL/glut.h>
#include <ctype.h>
#include "user_code.h"
#include "file_ply_stl.h"
#include "ed.h"
#include "figura.h"
#include "lata.h"
#include "peon.h"
#include "iluminacion.h"
#include "camara.h"
#include <iostream>

//Estructura de datos
Figura figura;
Lata lata;
Foco focoPos, focoDir;
ED estructura;
Camara cam1;
Camara cam2;
Camara cam3;
int opcionCamara=0;

//ED peon1, peon2, peon3;
Peon peon1, peon2, peon3;
// Vectores que guardan coordenadas de puntos e índices de caras
vector<float> v1, v2, v3, v4, v5, v6, v7, v8;
vector<int> c1, c2, c3, c4, c5;
//Opcion elegida por el teclado y variable para identificar al objeto elegido
int opcionMovimientos, opcionDibujar, opcion_estruc;
//Booleano que indica el archivo.ply de la figura ha sido leído
bool leido[5]={0,0,0,0,0};
//Archivo que vamos a leer
char filename[30];
//Variable booleana para activar o desactivar visualizado de normales
bool normales=false;

bool figuraCreada=false, figuraActiva= false;

bool shift=false;

bool teclarot=false, teclatras=false, teclaesc=false;

int tipoDibujo= 0;

bool automatico=false;

bool encenderFoco1=false, encenderFoco2=false;

bool practica4=false, modo_flat=false;

int xorigen=1;
int yorigen=1;

void inicioPractica4(){
	practica4=false;
	leido[4]=true;
	GLfloat colores[4]= {0.0, 0.0, 0.0, 1.0};
	GLfloat posf[4]=  {3.0, 0.0, 0.0, 1.0};
	GLfloat colores2[4]= {1.0, 1.0, 1.0, 1.0};
	GLfloat posf2[4]=  {-5.0, 0.0, 0.0, 0.0};

	focoPos.MontarFoco(colores, posf);
	focoDir.MontarFoco(colores2, posf2);
	focoPos.ActivarFoco();
	focoDir.ActivarFoco();

	peon1.ConstruirPeon(3);
	peon2.ConstruirPeon(1);
	peon3.ConstruirPeon(2);
	lata.crearFigura();

	opcion_estruc=5;

	opcionDibujar=4;
	figuraActiva=false;
	encenderFoco1=true;
	encenderFoco2=true;
}

void leerArchivo(char *filename, vector<float> &vaux, vector<int> &caux){
	_file_ply archivo;
	
	archivo.open(filename);
	archivo.read(vaux, caux);
	archivo.close();
}

void copiarVectores(vector<float> vaux1, vector<float> &vaux2, vector<int> caux1, vector<int> &caux2){
	vaux2= vaux1;
	caux2= caux1;
}

// tamaño de los ejes
const int AXIS_SIZE=5000; 

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Window_width,Window_height,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
//int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=1000,UI_window_height=1000;
int UI_window_pos_x=50,UI_window_pos_y=50,UI_window_width=500,UI_window_height=500;

//**************************************************************************
//
//***************************************************************************


void clear_window()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glFrustum(-Window_width,Window_width,-Window_height,Window_height,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{
	// posicion del observador
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0,0,-Observer_distance);
	glRotatef(Observer_angle_x,1,0,0);
	glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//***************************************************************************

void draw_objects()
{
	if(opcionCamara==1){
		cam1.Visionar(1);
	}else if(opcionCamara==2){
		cam2.Visionar(2);
	}else if(opcionCamara==3){
		cam3.Visionar(3);
	}


	if(opcion_estruc<4){
		switch (opcionDibujar){
			case 0:
				estructura.draw_puntos();
				break;
			case 1:
				estructura.modo_alambre();
				break;
			case 2:
				estructura.modo_solido(3);
				break;
			case 3:
				estructura.modo_ajedrez();
				break;
		}
	}
	else if(opcion_estruc==4){
		switch(opcionMovimientos){
			case 4:
				figura.Dibujar(-9,opcionDibujar);
				break;
			case 5:
				if(teclarot){
					figura.Dibujar(0,opcionDibujar);
					teclarot=false;
				}
				else
					figura.Dibujar(-9,opcionDibujar);
				break;
			case 6:
				if(teclaesc){
					figura.Dibujar(2,opcionDibujar);
					teclaesc=false;
				}
				else
					figura.Dibujar(-9,opcionDibujar);
				break;
			case 7:
				if(teclatras){
					figura.Dibujar(3,opcionDibujar);
					teclatras=false;
				}
				else
					figura.Dibujar(-9,opcionDibujar);
				break;
			case 8:
				if(teclatras){
					figura.Dibujar(4,opcionDibujar);
					teclatras=false;
				}
				else
					figura.Dibujar(-9,opcionDibujar);
				break;
			case 9:
				if(teclaesc){
					figura.Dibujar(5,opcionDibujar);
					teclaesc=false;
				}
				else
					figura.Dibujar(-9,opcionDibujar);
				break;
			case 10:
				if(teclarot){
					figura.Dibujar(1,opcionDibujar);
					teclarot=false;
				}
				else
					figura.Dibujar(-9,opcionDibujar);
				break;
		}
	}
	else{
		peon1.DibujarPeon(modo_flat);
		peon2.DibujarPeon(modo_flat);
		peon3.DibujarPeon(modo_flat);
		lata.Dibujar();
	}

	if(normales){
		estructura.modo_normales();
		estructura.normales_vertices();
	}
}



void reiniciar_observer(){
    Observer_distance=3*Front_plane;
    Observer_angle_x=0;
    Observer_angle_y=0;
}

//**************************************************************************
//
//***************************************************************************

void draw_scene(void)
{
	clear_window();
	change_observer();
	draw_axis();

	if(encenderFoco1){
		glEnable(GL_LIGHTING);
		focoPos.VisionarLuz();
	}
	else{
		glDisable(GL_LIGHTING);
	}
	if(encenderFoco2){
		glEnable(GL_LIGHTING);
		focoDir.VisionarLuz();
	}
	else{
		glDisable(GL_LIGHTING);
	}

	draw_objects();
	glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
	change_projection();
	glViewport(0,0,Ancho1,Alto1);
	glutPostRedisplay();
}


//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_keys(unsigned char Tecla1,int x,int y)
{
	int mod = glutGetModifiers();

	if(mod==1){
		shift=true;
	}

	if(opcionCamara!=0){
		switch (toupper(Tecla1)){
			case 'A':
				cam1.CambiarOjo(1);
				cam2.CambiarOjo(1);
				cam3.CambiarOjo(1);
				break;
			case 'S':
				cam1.CambiarOjo(3);
				cam2.CambiarOjo(3);
				cam3.CambiarOjo(3);
				break;
			case 'D':
				cam1.CambiarOjo(0);
				cam2.CambiarOjo(0);
				cam3.CambiarOjo(0);
				break;
			case 'W':
				cam1.CambiarOjo(2);
				cam2.CambiarOjo(2);
				cam3.CambiarOjo(2);
				break;
			case 'R':
				cam1.Reiniciar(1);
				cam2.Reiniciar(2);
				cam3.Reiniciar(3);
				draw_objects();
				break;
		}
	}

	if(opcion_estruc!=5){
		switch (toupper(Tecla1)){
			case 'Q':
				exit(0);
				break;
			case 'P':
				opcionDibujar=0;
				break;
			case 'L':
				opcionDibujar=1;
				break;
			case 'S':
				opcionDibujar=2;
				break;
			case 'A':
				opcionDibujar=3;
				break;
			case 'N':
				if(!normales)
					normales=true;
				else
					normales=false;
				break;
			case 'Z':
				if(shift){
					opcionMovimientos=5;
					shift=false;
				}
				else
					opcionMovimientos=10;

				teclarot=true;
				break;
			case 'X':
				if(shift){
					opcionMovimientos=6;	
					shift=false;
				}
				else
					opcionMovimientos=9;

				teclaesc=true;
				break;
			case 'C':
				if(shift){
					opcionMovimientos=7;
					shift=false;
				}
				else
					opcionMovimientos=8;

				teclatras=true;
				break;
			case 'M':
				if(automatico)
					automatico=false;
				else
					automatico=true;
				break;
		}
	}
	else{
		switch (toupper(Tecla1)){
			case 'Q':
				exit(0);
				break;
			case 'N':	//Habilitar foco posicional
				focoPos.ActivarFoco();
				break;
			case 'M':	//Habilitar foco direccional

				focoDir.ActivarFoco();
				break;
			case 'A':
				focoDir.MoverBeta(true);
				break;
			case 'Z':
				focoDir.MoverBeta(false);
				break;
			case 'X':
				focoDir.MoverAlfa(true);
				break;
			case 'C':
				focoDir.MoverAlfa(false);
				break;
			case 'V':
				if(modo_flat)
					modo_flat=false;
				else
					modo_flat=true;
				break;
		}
	}
	//El archivo.ply solo se lee una vez y se guardan los datos en los correspondientes vectores 
	if(opcionCamara==0){
		switch (toupper(Tecla1)){
			case 'W':
				if(opcion_estruc!=0){
					if(!leido[0]){
						leido[0]=true;
						strcpy(filename, "ant.ply");
						leerArchivo(filename, v1, c1);
					}
					opcion_estruc=0;
					estructura.limpiar();
					estructura.copiar(v1,c1);
					figuraActiva=false;
				}
				opcionDibujar=1;
				automatico=false;
				encenderFoco1=false;
				encenderFoco2=false;
				break;
			case 'E':
				if(opcion_estruc!=1){
					if(!leido[1]){
						leido[1]=true;
						strcpy(filename, "beethoven.ply");
						leerArchivo(filename, v2, c2);
					}
					opcion_estruc=1;
					estructura.limpiar();
					estructura.copiar(v2,c2);
					figuraActiva=false;
				}
				opcionDibujar=1;
				automatico=false;
				encenderFoco1=false;
				encenderFoco2=false;
				break;
			case 'R':
				if(opcion_estruc!=2){
					if(!leido[2]){
						leido[2]=true;
						strcpy(filename, "big_dodge.ply");
						leerArchivo(filename, v3, c3);
					}
					opcion_estruc=2;
					estructura.limpiar();
					estructura.copiar(v3,c3);
					figuraActiva=false;
				}
				opcionDibujar=1;
				automatico=false;
				encenderFoco1=false;
				encenderFoco2=false;
				break;
			case '2':
				if(opcion_estruc!=3){
					if(!leido[3]){
						leido[3]=true;
						strcpy(filename, "perfil.ply");
						leerArchivo(filename, v4, c4);
					}
					opcion_estruc=3;
					estructura.limpiar();
					estructura.copiarPerfil(v4,c4,21,18);
					figuraActiva=false;
				}
				automatico=false;
				opcionDibujar=1;
				encenderFoco1=false;
				encenderFoco2=false;
				break;
			case '3':
				if(opcion_estruc!=4){
					estructura.limpiar();
					opcion_estruc=4;
					opcionMovimientos=4;
					if(!figuraCreada){
						figura.crearFigura();
						figuraCreada=true;
					}
					else
						figura.Dibujar(-1,opcionDibujar);
					figuraActiva=true;
					opcionDibujar=1;
					encenderFoco1=false;
					encenderFoco2=false;
				}
				break;
			case '4':									//Escena con 3 peones y una lata
				if(opcion_estruc!=5){
					if(!leido[4])
						inicioPractica4();
					else{
						opcion_estruc=5;
						opcionDibujar=4;
						figuraActiva=false;
						encenderFoco1=true;
						encenderFoco2=true;
					}
				}
				automatico=false;
				break;
		}
	}
	//Hay que actualizar el buffer trás seleccionar una tecla
	draw_scene();
}

//***************************************************************************
// Funcion llamada cuando se produce aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_keys(int Tecla1,int x,int y)
{

switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	case GLUT_KEY_F1:opcionCamara=1;reiniciar_observer();change_projection();break;
	case GLUT_KEY_F2:opcionCamara=2;reiniciar_observer();change_projection();break;
	case GLUT_KEY_F3:opcionCamara=3;reiniciar_observer();change_projection();break;
	case GLUT_KEY_F4:opcionCamara=0;reiniciar_observer();change_projection();break;
	}
glutPostRedisplay();
}



//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
	//Inicializamos las distintas cámaras
	cam1.Construir(1);
	cam2.Construir(2);
	cam3.Construir(3);

	if(practica4){
		inicioPractica4();
	}
	// se inicalizan la ventana y los planos de corte
	Window_width=.5;
	Window_height=.5;
	Front_plane=1;
	Back_plane=1000;

	// se inicia la posicion del observador, en el eje z
	Observer_distance=3*Front_plane;
	Observer_angle_x=0;
	Observer_angle_y=0;

	// se indica cual sera el color para limpiar la ventana	(r,v,a,al)
	// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
	glClearColor(0.5,0.5,0.5,1);

	// se habilita el z-bufer
	glEnable(GL_DEPTH_TEST);
	change_projection();
	glViewport(0,0,UI_window_width,UI_window_height);


}

//Metodo para recalcular coordenadas con el movimiento del ratón
void ratonMovido( int x, int y ) {
	if(xorigen>=0){
		if(x>xorigen){
			Observer_angle_y++;
		}
		else if(x<xorigen){
			Observer_angle_y--;
		}
		if(y>xorigen){
			Observer_angle_x++;
		}
		else if(y<xorigen){
			Observer_angle_x--;
		}
	}
	xorigen=x;
	yorigen=y;
	glutPostRedisplay();
}

//Función para realizar acción cuando se clickée el boton derecho
void clickRaton( int boton, int estado, int x, int y ){
	if ( boton == GLUT_RIGHT_BUTTON ) {
		ratonMovido(x,y);
	}

}

//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************

void idle(){
	if(automatico){
		figura.Dibujar(99, opcionDibujar);
	}
 	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	float ngrados;
	int nrotaciones;//, nvert;
	bool p3=false;
	if (argc == 3 || argc > 4){
		printf("Error: practica1 <nombre_archivo.ply> (<numero_grados>) (<numero_rotaciones>)\n");
		return 1;
	}
	else if(argc == 4){
		nrotaciones= atoi(argv[3]);
		nrotaciones+=1;
		if(nrotaciones<0){
			printf("Error: El número de rotaciones debe ser positivo.\n");
			return 1;
		}
		ngrados= atoi(argv[2]);
		if((nrotaciones-1)*ngrados>360){
			printf("Error: rotaciones x grados es mayor de 360.\n");
			return 1;
		}
		leerArchivo(argv[1], v1, c1);
		c1.clear();
		estructura.copiarPerfil(v1,c1,nrotaciones, ngrados);
	}
	else if(argc == 1){
		practica4=true;
	}
	else if(argc == 2){
		if(!strcmp(argv[1], "p3")){
			figura.crearFigura();
			p3=true;
		}
		else{
			leerArchivo(argv[1], v1, c1);
			nrotaciones=0;
			estructura.copiar(v1,c1);
		}
	}
	
	//Indicamos la figura que está por pantalla.
	//Uso los dos vectores correspondientes a la hormiga para el archivo que se pasa por argumento.
	if(!p3 && !practica4){
		if(strcmp(argv[1], "ant.ply")==0){
			opcion_estruc=0;
			leido[0]=true;
		}
		else if(strcmp(argv[1], "beethoven.ply")==0){
			opcion_estruc=1;
			leido[1]=true;
			copiarVectores(v1, v2, c1, c2);
			v1.clear();
			c1.clear();
		}
		else if(strcmp(argv[1], "big_dodge.ply")==0){
			opcion_estruc=2;
			leido[2]=true;
			copiarVectores(v1, v3, c1, c3);
			v1.clear();
			c1.clear();
		}
		else{
			opcion_estruc=3;
			leido[3]=true;
			copiarVectores(v1, v4, c1, c4);
			v1.clear();
			c1.clear();
		}
	}
	else if(p3){
		opcion_estruc=4;
		opcionMovimientos=4;
		figuraCreada=true;
		figuraActiva=true;
	}

    // se llama a la inicialización de glut
    glutInit(&argc, argv);

    // se indica las caracteristicas que se desean para la visualización con OpenGL
    // Las posibilidades son:
    // GLUT_SIMPLE -> memoria de imagen simple
    // GLUT_DOUBLE -> memoria de imagen doble
    // GLUT_INDEX -> memoria de imagen con color indizado
    // GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
    // GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
    // GLUT_DEPTH -> memoria de profundidad o z-bufer
    // GLUT_STENCIL -> memoria de estarcido
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    // posicion de la esquina inferior izquierdad de la ventana
    glutInitWindowPosition(UI_window_pos_x,UI_window_pos_y);

    // tamaño de la ventana (ancho y alto)
    glutInitWindowSize(UI_window_width,UI_window_height);

    // llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
    // al bucle de eventos)
    glutCreateWindow("Práctica 4");

    // asignación de la funcion llamada "dibujar" al evento de dibujo
    glutDisplayFunc(draw_scene);
    // asignación de la funcion llamada "cambiar_tamanio_ventana" al evento correspondiente
    glutReshapeFunc(change_window_size);
    // asignación de la funcion llamada "tecla_normal" al evento correspondiente
    glutKeyboardFunc(normal_keys);
    // asignación de la funcion llamada "tecla_Especial" al evento correspondiente
    glutSpecialFunc(special_keys);

    glutMouseFunc( clickRaton );
	glutMotionFunc( ratonMovido );

	glutIdleFunc(idle);
    // funcion de inicialización
    initialize();
    // inicio del bucle de eventos
    glutMainLoop();
    return 0;
}
