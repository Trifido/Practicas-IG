
#include "Brazo.h"

//Constructor donde se inicializan los tamaños del brazo de la torre, los cables y la parte superior.
Brazo::Brazo(){
	tambrazo= 22;
	anbrazo= 1;
	rot=0;
	anpico= 1;
	altpico1= 2;
	altpico2= 3;
	ancuerda= 0.05;
	lcuerda1= 11.5;
	lcuerda2= 5;
	invertiRotar=false;
}

//Metodo para construir las diferentes partes que forman el brazo junto con la cuerda y carga
void Brazo::construirBrazoCarga(){
	construirBrazo();
	construirPico();
	construirCables();
	cucarga.Construir();
}

//Metodo para guardar en una ED el brazo de la torre
void Brazo::construirBrazo(){
	vector<float> vaux;

	vaux.push_back(anbrazo);
	vaux.push_back(0);
	vaux.push_back(0);
	vaux.push_back(anbrazo);
	vaux.push_back(tambrazo);
	vaux.push_back(0);

	brazo.calcularPuntos(vaux, 90, 5,0,false);

	brazo.rotarSobreY(45);
	brazo.rotarSobreZ(90);
	float desp= sin((45*M_PI)/180);
	brazo.trasladar(6,desp,0);

	brazo.calcularCaras(5, 90, 2, 0, false);
	brazo.calcularNormales();
}

//Metodo para guardar en una ED el pico de la torre
void Brazo::construirPico(){
	float desp= sin((45*M_PI)/180);

	vector<float> vaux;
	vaux.push_back(anpico);
	vaux.push_back(0);
	vaux.push_back(0);
	vaux.push_back(anpico);
	vaux.push_back(altpico1);
	vaux.push_back(0);
	vaux.push_back(0);
	vaux.push_back(altpico2);
	vaux.push_back(0);

	pico.calcularPuntos(vaux, 90, 5,3,false);

	pico.rotarSobreY(45);
	pico.trasladar(0,desp*2,0);

	pico.calcularCaras(5, 90, 3, 3, false);
	pico.calcularNormales();
}

//Metodo para guardar en una ED los cables de la torre
void Brazo::construirCables(){
	float desp= sin((45*M_PI)/180);
	vector<float> vaux, vaux2;

	vaux.push_back(ancuerda);
	vaux.push_back(0);
	vaux.push_back(0);
	vaux.push_back(ancuerda);
	vaux.push_back(lcuerda1);
	vaux.push_back(0);

	cable1.calcularPuntos(vaux, 90, 5,0, false);

	cable1.rotarSobreZ(105);

	cable1.trasladar(0,(3+desp*2),0);
	cable1.calcularCaras(5, 90, 2, 0, false);
	cable1.calcularNormales();

	vaux2.push_back(ancuerda);
	vaux2.push_back(0);
	vaux2.push_back(0);
	vaux2.push_back(ancuerda);
	vaux2.push_back(lcuerda2);
	vaux2.push_back(0);

	cable2.calcularPuntos(vaux2, 90, 5,0,false);

	cable2.rotarSobreZ(-127);

	cable2.trasladar(0,(3+desp*2),0);
	cable2.calcularCaras(5, 90, 2, 0, false);
	cable2.calcularNormales();
}

//Metodo para dibujar las distintas partes del brazo
void Brazo::dibujarBrazoCarga(int accion, int tipoDibujo){
	switch(tipoDibujo){
		case 0:
			brazo.draw_puntos();
			pico.draw_puntos();
			cable1.draw_puntos();
			cable2.draw_puntos();
			break;
		case 1:
			brazo.modo_alambre();
			pico.modo_alambre();
			cable1.modo_alambre();
			cable2.modo_alambre();
			break;
		case 2:
			brazo.modo_solido(4);
			pico.modo_solido(5);
			cable1.modo_solido(0);
			cable2.modo_solido(0);
			break;
		case 3:
			brazo.modo_ajedrez();
			pico.modo_ajedrez();
			cable1.modo_ajedrez();
			cable2.modo_ajedrez();
			break;
	}
	cucarga.Dibujar(accion, tipoDibujo);
}

////Metodo para realizar los movimientos de rotación del brazo.
void Brazo::MovimientoBrazo(int accion, int tipoDibujo){
	glPushMatrix();
	if(accion==-1){
		dibujarBrazoCarga(0,tipoDibujo);
	}
	else{
		if(accion==0)
			rot++;
		else if(accion==1)
			rot--;
		else if(accion==99){
			if(rot==180)
				invertiRotar=true;
			if(rot==0)
				invertiRotar=false;

			if(invertiRotar)
				rot--;
			else
				rot++;
		}

		glPushMatrix();
			glRotatef(2*rot,0,1,0);
			dibujarBrazoCarga(accion,tipoDibujo);
		glPopMatrix();
	}
	glPopMatrix();
}
