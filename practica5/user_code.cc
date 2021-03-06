//**************************************************************************
// Codigo del usuario
//
// Domingo Martin Perandres 2013
//
// GPL
//**************************************************************************

#include "user_code.h"

//**************************************************************************
// Funcion para dibujar los vertices de un cubo unidad
//***************************************************************************

void draw_cube()
{
    GLfloat Vertices[8][3]= {{-0.5,-0.5,0.5},{0.5,-0.5,0.5},{0.5,0.5,0.5},{-0.5,0.5,0.5},{-0.5,-0.5,-0.5},{0.5,-0.5,-0.5},{0.5,0.5,-0.5},{-0.5,0.5,-0.5}};
	
    glColor3f(0,1,0);
    glPointSize(4);

    glBegin(GL_POINTS);
    for (unsigned i=0;i<8;i++){
        glVertex3fv((GLfloat *) &Vertices[i]);
    }
    glEnd(); 

}

//**************************************************************************
// Funcion para dibujar vertices
//***************************************************************************

void draw_vertices(vector<float> &Vertices)
{
if(Vertices.size()%3 == 0){
		glColor3f(0,1,0);
		glPointSize(4);
	
		glBegin(GL_POINTS);
			for (unsigned i= 0; i+3<=Vertices.size(); i= i+3){
				glVertex3f(Vertices.at(i), Vertices.at(i+1), Vertices.at(i+2));
			}
		glEnd();
	}
}

