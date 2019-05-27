#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>


using namespace std;

void init(void)
{
	/*selecionar cor de fundo(preto)*/
	glClearColor (0.0 ,0.0, 0.0, 0.0);

	glMatrixMode (GL_PROJECTION); //projeção 2D

	glOrtho(0.0, 500.0, 100.0, 400.0, -1.0, 1.0);
}

void display(void)
{
	/* Limpar todos os pixels */
	glClear (GL_COLOR_BUFFER_BIT);

	glColor3f (1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex3f (249.0f, 250.0f, -1.0f);
		glVertex3f (251.0f, 250.0f, -1.0f);
		glVertex3f (249.0f, 100.0f, -1.0f);
		glVertex3f (251.0f, 100.0f, -1.0f);
	glEnd();

	// se não aplicasse essa glColor específica, a de cima iria ser aplicada em todos abaixo sem especificação
	glColor3f (1.0, 1.0, .0);
	glBegin(GL_TRIANGLES);
		glVertex2f (250.0f, 250.0f);
		glVertex2f (230.0f, 200.0f);
		glVertex2f (270.0f, 200.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
		glVertex2f (250.0f, 250.0f);
		glVertex2f (200.0f, 270.0f);
		glVertex2f (200.0f, 230.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
		glVertex2f (250.0f, 250.0f);
		glVertex2f (300.0f, 270.0f);
		glVertex2f (300.0f, 230.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
		glVertex2f (250.0f, 250.0f);
		glVertex2f (230.0f, 300.0f);
		glVertex2f (270.0f, 300.0f);
	glEnd();

	glFlush();
}

int main(int argc, char** argv) {
	
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition (200, 200);
	glutCreateWindow("Flor de Abril");

	init ();

	glutDisplayFunc(display);

	glutMainLoop();

	/* C ANSI requer que main retorne um inteiro */
	return 0;

}
