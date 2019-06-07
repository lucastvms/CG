#include <iostream>
#include <GL/glut.h>

using namespace std;

GLsizei winWidth = 600, winHeight = 400;
GLfloat c1[3] = {1.0, 0.0 , 0.0}, c2[3] = {0.0, 1.0 , 0.0}, c3[3] = {0.0, 0.0 , 1.0}, c4[3] = {1.0, 0.0 , 1.0};
GLfloat colors[4][3] = {{1.0, 0.0 , 0.0}, {0.0, 1.0 , 0.0}, {0.0, 0.0 , 1.0}, {1.0, 1.0 , 0.0}};
int aux[4] = {0, 1, 2, 3};

void init(void)
{
	glClearColor(.5, .5, .5, 1.0); // Cor da Janela em azul (R, G, B , alpha) de 0 à 1

	glMatrixMode(GL_PROJECTION); // Projeção 2D

	glOrtho(0.0, 500.0, 100.0, 400.0, -1.0, 1.0); // Definindo os limites da Projeção
}

void displayFcn()
{
	glClear(GL_COLOR_BUFFER_BIT); // Limpa ViewPort

	glColor3f (1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex3f (249.0f, 250.0f, -1.0f);
		glVertex3f (251.0f, 250.0f, -1.0f);
		glVertex3f (249.0f, 100.0f, -1.0f);
		glVertex3f (251.0f, 100.0f, -1.0f);
	glEnd();

	// se não aplicasse essa glColor específica, a de cima iria ser aplicada em todos abaixo sem especificação
	glColor3f (colors[aux[0]][0], colors[aux[0]][1], colors[aux[0]][2]);
	glBegin(GL_TRIANGLES);
		glVertex2f (250.0f, 250.0f);
		glVertex2f (230.0f, 200.0f);
		glVertex2f (270.0f, 200.0f);
	glEnd();

	glColor3f (colors[aux[1]][0], colors[aux[1]][1], colors[aux[1]][2]);
	glBegin(GL_TRIANGLES);
		glVertex2f (250.0f, 250.0f);
		glVertex2f (200.0f, 270.0f);
		glVertex2f (200.0f, 230.0f);
	glEnd();

	glColor3f (colors[aux[2]][0], colors[aux[2]][1], colors[aux[2]][2]);
	glBegin(GL_TRIANGLES);
		glVertex2f (250.0f, 250.0f);
		glVertex2f (230.0f, 300.0f);
		glVertex2f (270.0f, 300.0f);
	glEnd();

	glColor3f (colors[aux[3]][0], colors[aux[3]][1], colors[aux[3]][2]);
	glBegin(GL_TRIANGLES);
		glVertex2f (250.0f, 250.0f);
		glVertex2f (300.0f, 270.0f);
		glVertex2f (300.0f, 230.0f);
	glEnd();

	glColor3f(1.0, 0.0, 0.0); // Ponto em vermelho
	glPointSize(10.0); // Tamanho do ponto

	/* Não esperar! */
	glFlush();
	glutSwapBuffers();
}

void swap(int button)
{
	int change, i;

	if(button == 1) {
		change = aux[0];
		for(i=0;i<3;i++) {
			aux[i] = aux[i+1];
		}
		aux[3] = change;
	}

	else if(button == 0) {
		change = aux[3];
		for(i=3;i>0;i--) {
			aux[i] = aux[i-1];
		}
		aux[0] = change;
	}

	glutPostRedisplay();
}

void mouseClChange(GLint button, GLint action, GLint xMouse, GLint yMouse)
{
	if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
	{
		int x1 = xMouse;
		int y1 = winHeight - yMouse;

		swap(1); // clique com botão esquerdo

		cout<<"x1 da função"<<x1<<endl;
		cout<<"y1 da função"<<y1<<endl;
	}
	else if(button == GLUT_RIGHT_BUTTON && action == GLUT_DOWN)
	{
		int x1 = xMouse;
		int y1 = winHeight - yMouse; // ver comentário abaixo

		swap(0); // clique com botão direito

		cout<<"x1 da função"<<x1<<endl;
		cout<<"y1 da função"<<y1<<endl;
	}
	glFlush();
}

void winReshapeFcn (GLint newWidth, GLint newHeight)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, GLdouble (newWidth), 100.0, GLdouble(newHeight), -1.0, 1.0);

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

	glutInitWindowPosition(200, 200);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Pontos usando o Mouse");

	init(); // Chama o procedimento de Inicialização

	glutDisplayFunc(displayFcn);
	glutReshapeFunc(winReshapeFcn);
	glutMouseFunc(mouseClChange);

	glutMainLoop();

	return 0;
}
