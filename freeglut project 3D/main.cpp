#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>
//#include <GL/glut.h>

#include "Escena.h"

#include <iostream>
using namespace std;

// Freeglut parameters
// Flag telling us to keep processing events
// bool continue_in_main_loop= true; //(**)

Escena* escena;

void buildSceneObjects() {	 
	escena = new Escena(4000);

}

void initGL() {	 		 
	glClearColor(0.6f,0.7f,0.8f,1.0);
      
	glEnable(GL_COLOR_MATERIAL);
	glMaterialf(GL_FRONT, GL_SHININESS, 0.9f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	//Define el modelo de sombreado: GL_FLAT / GL_SMOOTH (suave)
	glShadeModel(GL_SMOOTH); // Shading by default

	buildSceneObjects();

	//Activa el modelo de iluminación /disable
	glEnable(GL_LIGHTING);  

	//Enciende una luz particular /disable
	glEnable(GL_LIGHT0);

	//Definir componentes difusa, especular y ambiente
    GLfloat d[]={0.7f,0.5f,0.5f,1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, d);//Luz que vuelve a irradiar la superficie en todas las direcciones.
    GLfloat a[]={0.3f,0.3f,0.3f,1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, a);//Luz que alcanza una superficie aunque no esté expuesta a la fuente de luz.
	GLfloat s[]={1.0f,1.0f,1.0f,1.0f};
    glLightfv(GL_LIGHT0, GL_SPECULAR, s);//Luz que refleja la superficie.
	GLfloat p[]={25.0f, 25.0f, 25.0f, 1.0f};	 
	glLightfv(GL_LIGHT0, GL_POSITION, p);//Define la posicion de una fuente de luz. ultimo parámetro: 1 local, 0 direccional
	

	//NO ESTÁ EN EL ESQUELETO
	//GLfloat amb[] = { 0.0, 0.0, 0.0, 1.0 };
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);

	//LUCES SECUNDARIAS
	/**
    GLfloat d[]={0.2f,0.7f,0.2f,1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
	GLfloat a[] = { 0.1f, 0.4f, 0.1f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, a);
	GLfloat s[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_SPECULAR, s);
	GLfloat p[]={25.0f, 25.0f, 25.0f, 1.0f};	
	glLightfv(GL_LIGHT0, GL_POSITION, p);

	GLfloat dir[] = { -1.0, -1.0, -1.0 };
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, dir);
	*/
 }

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

	glMatrixMode(GL_MODELVIEW);	 

	//Esto es por si la cámara se mueve, ajusta la posicion de la luz
	GLfloat p[] = { 25.0f, 25.0f, 25.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, p);

	glPushMatrix();
	
	escena->dibuja();
		
	glPopMatrix();
 
	glFlush();
	glutSwapBuffers();
}

void resize(int newWidth, int newHeight) {
	escena->resize(newWidth,newHeight);
}

void key(unsigned char key, int x, int y){
	bool need_redisplay = true;
	switch (key) {
		case 27:  /* Escape key */
			//continue_in_main_loop = false; // (**)
			//Freeglut's sentence for stopping glut's main loop (*)
			glutLeaveMainLoop (); 
			break;		 
		case 'f': escena->setAngX(escena->getAngX() + 5.0f); break;
		case 'z': escena->setAngX(escena->getAngX() - 5.0f); break;
		case 'v': escena->setAngY(escena->getAngY() + 5.0f); break;
		case 'x': escena->setAngY(escena->getAngY() - 5.0f); break;
		case 'd': escena->setAngZ(escena->getAngZ() + 5.0f); break;
		case 'c': escena->setAngZ(escena->getAngZ() - 5.0f); break;
		case 'q': escena->moverCoche(ArribaIz); break;
		case 'w': escena->moverCoche(ArribaDe); break;
		case 'a': escena->moverCoche(AbajoIz); break;
		case 's': escena->moverCoche(AbajoDe); break;
		case 't': escena->cambiarModo(); break;


		case '1': escena->giraX(5); break;//Rota la cámara alrededor del ejeX
		case '2':escena->roll(15); break; //Debería ser q //Rota la cámara con respecto al eje n de la cámara
		//case 'h': glEnable(GL_LIGHT0); break;
		//case 'n': glDisable(GL_LIGHT0); break;
		default:
			need_redisplay = false;
			break;
	}

	if (need_redisplay)
		glutPostRedisplay();
}

int main(int argc, char *argv[]){
	cout<< "Starting console..." << endl;

	int my_window; // my window's identifier

	// Initialization
	glutInitWindowSize(500, 500);
	glutInitWindowPosition (0, 0);
	//glutInitWindowPosition (140, 140);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);

	// Window construction
	my_window = glutCreateWindow("Thomas :)");
    
	// Callback registration
	glutReshapeFunc(resize);
	glutKeyboardFunc(key);
	glutDisplayFunc(display);

	// OpenGL basic setting
	initGL();

	// Freeglut's main loop can be stopped executing (**)
	// while (continue_in_main_loop) glutMainLoopEvent();

	// Classic glut's main loop can be stopped after X-closing the window,
	// using the following freeglut's setting (*)
	glutSetOption (GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION) ;
    
	// Classic glut's main loop can be stopped in freeglut using (*)
	glutMainLoop(); 
  
	// We would never reach this point using classic glut
	system("PAUSE"); 

	delete escena;
	escena = nullptr;

	return 0;
}
