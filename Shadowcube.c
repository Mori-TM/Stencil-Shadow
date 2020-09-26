#include <GL/freeglut.h>
#include <GL/glext.h>


float angle = 0.0;
float angle1 = 0.0;
float a = 0.0;



void changeSize(int w, int h) 
{	
	float ratio =  w * 1.0 / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(45.0f, ratio, 0.1f, 1000000.0f);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND); //enable alpha blending

}



void render(void)
{
	glLoadIdentity();
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	gluLookAt(3.0, 4.0, 8.0,	//Cam Pos
			  0.0, 0.0, 0.0,	//Look At
			  0.0, 1.0, 0.0);
	

	float lightPosition[] = {angle, 8.0f, angle1, 0.0f};	// Holds our light position
	a += 0.01;
	angle = 12*cos(a);
	angle1 = 12*sin(a);
	
	#include "Stencil_Shadow.h"
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
	
	Shadow();
	
	glutSwapBuffers();
	glutPostRedisplay();
}

int main(int argc, char** argv)
{	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Glut M");
	
	glutReshapeFunc(changeSize);
	glutDisplayFunc(render);
	
	glutMainLoop();
	return 0;
}
