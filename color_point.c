#include <iostream>
#include <GL/glut.h>

using namespace std;

GLsizei winWidth = 600, winHeight = 400;
void init(void)
{
	glClearColor(0.0, .5, 1.0, 1.0); // Cor da Janela em azul (R, G, B , alpha) de 0 à 1

	glMatrixMode(GL_PROJECTION); // Projeção 2D

	glOrtho(0.0, 200.0, 0.0, 150.0, -1.0, -1.0); // Definindo os limites da Projeção
}

void displayFcn()
{
	glClear(GL_COLOR_BUFFER_BIT); // Limpa ViewPort

	glColor3f(1.0, 0.0, 0.0); // Ponto em vermelho
	glPointSize(10.0); // Tamanho do ponto

	/* Não esperar! */
	glFlush();
}

void plotPoint(GLint x, GLint y)
{
	glBegin(GL_POINTS);
		glVertex2i(x, y);
	glEnd();
}

void mousePtPlot(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
	if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
	{
		int x1 = xMouse;
		int y1 = winHeight - yMouse; // ver comentário abaixo

		plotPoint(x1, y1); // ATENÇÃO Xo e Yo no canto superior esquerdo (0,0)

		cout<<"x1 da função"<<x1<<endl;
		cout<<"y1 da função"<<y1<<endl;
	}
	glFlush();
}

void winReshapeFcn (GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, GLdouble (newWidth), 0.0, GLdouble(newHeight), -1.0, 1.0);

	winWidth = newWidth;
	winHeight = newHeight;

	glFlush();
}

int main(int argc, char** argv)
{
	// Inicializa a GLUT
	glutInit(&argc, argv);

	// Janela com Buffer simples e em RGB
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Pontos usando o Mouse");

	init(); // Chama o procedimento de Inicialização

	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);
	glutMouseFunc(mousePtPlot);

	glutMainLoop();

	return 0;
}
