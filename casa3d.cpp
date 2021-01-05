#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

/*
 * Adaptado de:
 *   https://github.com/mdrkb/3D-House-using-OpenGL-and-C-/blob/master/main.cpp
*/

// actual vector representing the camera's direction
float lx=0.0f,lz=-1.0f;

// XZ position of the camera
float x=0.0f,z=7.0f;

// initial door angle, used for it's rotation
float door_angle = 0.0f;

// angle for rotating
float angle = 0.0f;

void init(void) {
    // sky color
    glClearColor(0.0, 0.7, 1.0, 1.0);
}

void drawHouse(){

    // Front side
    glPushMatrix();
    glTranslatef(0.0f, 1.3f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.65f);

        glBegin(GL_QUADS);  // Wall
            glVertex3f(0.3,0,1);
            glVertex3f(2,0,1);
            glVertex3f(2,-1.5,1);
            glVertex3f(0.3,-1.5,1);
        glEnd();

        glBegin(GL_QUADS);  // Wall
            glVertex3f(-2,0,1);
            glVertex3f(-0.3,0,1);
            glVertex3f(-0.3,-1.5,1);
            glVertex3f(-2,-1.5,1);
        glEnd();

        glBegin(GL_QUADS);  // Wall
		glVertex3f(0.3, 0, 1);
		glVertex3f(-0.3, 0, 1);
		glVertex3f(-0.3, -0.25, 1);
		glVertex3f(0.3,-0.25, 1);
	glEnd();

        glColor3f(0.4f, 0.0f, 0.0f);
        glBegin(GL_QUADS);  // Roof
            glVertex3f(-2.2,0.5,0);
            glVertex3f(2.2,0.5,0);
            glVertex3f(2.2,-0.1,1.25);
            glVertex3f(-2.2,-0.1,1.25);
        glEnd();

        glColor3f(0.7f, 0.7f, 0.0f);
        glBegin(GL_QUADS);  // Window Left
            glVertex3f(-1.5,-0.3,1.0001);
            glVertex3f(-0.75,-0.3,1.0001);
            glVertex3f(-0.75,-0.8,1.0001);
            glVertex3f(-1.5,-0.8,1.0001);
        glEnd();

        glBegin(GL_QUADS);  // Window Right
            glVertex3f(1.5,-0.3,1.0001);
            glVertex3f(0.75,-0.3,1.0001);
            glVertex3f(0.75,-0.8,1.0001);
            glVertex3f(1.5,-0.8,1.0001);
        glEnd();
    glPopMatrix();

    // Back side
    glPushMatrix();
    glTranslatef(0.0f, 1.3f, 0.0f);
        glColor3f(0.0f, 0.0f, 0.65f);
        glBegin(GL_QUADS);  // Wall
            glVertex3f(-2,0,-1);
            glVertex3f(2,0,-1);
            glVertex3f(2,-1.5,-1);
            glVertex3f(-2,-1.5,-1);
        glEnd();

        glColor3f(0.4f, 0.0f, 0.0f);
        glBegin(GL_QUADS);  // Roof
            glVertex3f(-2.2,0.5,0);
            glVertex3f(2.2,0.5,0);
            glVertex3f(2.2,-0.1,-1.25);
            glVertex3f(-2.2,-0.1,-1.25);
        glEnd();

        glBegin(GL_QUADS);  // Window Left
             glVertex3f(-1.5,-0.3,-1.0001);
             glVertex3f(-0.75,-0.3,-1.0001);
             glVertex3f(-0.75,-0.8,-1.0001);
             glVertex3f(-1.5,-0.8,-1.0001);
        glEnd();

        glBegin(GL_QUADS);  // Window Right
             glVertex3f(1.5,-0.3,-1.0001);
             glVertex3f(0.75,-0.3,-1.0001);
             glVertex3f(0.75,-0.8,-1.0001);
             glVertex3f(1.5,-0.8,-1.0001);
        glEnd();
    glPopMatrix();

    // Right side
    glPushMatrix();
    glTranslatef(0.0f, 1.3f, 0.0f);
        glColor3f(0.0f, 0.0f, 0.65f);
        glBegin(GL_QUADS);  // Wall
             glVertex3f(2,0,1);
             glVertex3f(2,0,-1);
            glVertex3f(2,-1.5,-1);
             glVertex3f(2,-1.5,1);
        glEnd();

        glBegin(GL_TRIANGLES);  // Wall Upper
             glVertex3f(2,0.5,0);
             glVertex3f(2,0,1);
             glVertex3f(2,0,-1);
        glEnd();
    glPopMatrix();

    // Left side
    glPushMatrix();
    glTranslatef(0.0f, 1.3f, 0.0f);
        glColor3f(0.0f, 0.0f, 0.65f);
        glBegin(GL_QUADS);  // Wall
                glVertex3f(-2,0,1);
                glVertex3f(-2,0,-1);
                glVertex3f(-2,-1.5,-1);
                glVertex3f(-2,-1.5,1);
        glEnd();

        glBegin(GL_TRIANGLES);  // Wall Upper
               glVertex3f(-2,0.5,0);
               glVertex3f(-2,0,1);
               glVertex3f(-2,0,-1);
        glEnd();
    glPopMatrix();
}

void drawDoor() {

    glPushMatrix();
		glTranslatef(-0.3f, 0.5f, 1); //translada para a origem
        glRotatef (door_angle, 0,1,0); // rotaciona
    	glTranslatef(0.3f, 0, 0); //manda para origem
        glColor3f(0.7f, 0.7f, 0.7f); //colore a porta
        glScalef(0.6, 1.1, 0.1f); // estica o cubo inicial para se tornar a porta
        glutSolidCube(1.0); // indica que o cubo é sólido
    glPopMatrix();

}

void changeSize(int w, int h){

    // Prevent a divide by zero, when window is too short
    // (you cant make a window of zero width).
    if (h == 0) h = 1;
    float ratio = w * 1.0 / h;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(45.0f, ratio, 0.1f, 100.0f);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}

void renderScene(void){

    // Para ver os objetos em modo polígono (somente os traços)	
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();

    // Set the camera
    gluLookAt(x, 1.0f, z, x+lx, 1.0f, z+lz, 0.0f, 1.0f, 0.0f);

    // Draw ground
    glColor3f(0.0, 0.65, 0.0);
        glBegin(GL_QUADS);
        glVertex3f(-100.0f, 0.0f, -100.0f);
        glVertex3f(-100.0f, 0.0f, 100.0f);
        glVertex3f( 100.0f, 0.0f, 100.0f);
        glVertex3f( 100.0f, 0.0f, -100.0f);
    glEnd();

    drawHouse();
    drawDoor();

    glFlush();
    glutSwapBuffers();
}


void processNormalKeys(unsigned char key, int x, int y) {
    switch(key){
        case 'o':
            if(door_angle <= 118.0f) door_angle += 2.0f;
            glutPostRedisplay();
        break;

        case 'c':
            if(door_angle >= 2.0f) door_angle -= 2.0f;
            glutPostRedisplay();
        break;

        case 27:
            exit(0);
        break;
    }
}


void processSpecialKeys(int key, int xx, int yy){

float fraction = 0.5f;

    switch (key) {
        // funções que indicam a mudança de ângulo de visão e não dá um passo ao lado
        case GLUT_KEY_LEFT :
        printf("%f", lx);
            angle -= 0.05f;
            lx = sin(angle);
            lz = -cos(angle);
            printf("%f", lx);
        break;
        case GLUT_KEY_RIGHT :
            angle += 0.05f;
            lx = sin(angle);
            lz = -cos(angle);
        break;
        // passos para frente e para traz
        case GLUT_KEY_UP :
            x += lx * fraction;
            z += lz * fraction;
        break;
        case GLUT_KEY_DOWN :
            x -= lx * fraction;
            z -= lz * fraction;
        break;
    }
}

int main(int argc, char **argv){

    // init GLUT and create window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(800,600);
    glutCreateWindow("House 3D");

    init();

    // register callbacks
    glutDisplayFunc(renderScene); //normalmente displayfunc
    glutReshapeFunc(changeSize); //normalmente reshape
    glutIdleFunc(renderScene); // essa função chamada em loop infinito, sempre modificando variáveis de posicionamento
    glutKeyboardFunc(processNormalKeys); //normalmente keyboardfunc
    glutSpecialFunc(processSpecialKeys); 
    // por que temos duas funções de keyboard. Pois algumas entradas de keyboard são processadas separadamente, assim como mouse, que se encaixam na specialkeys

    // OpenGL init
    glEnable(GL_DEPTH_TEST); //reforçar que queremos o teste de profundidade

    // enter GLUT event processing cycle
    glutMainLoop();

    return 1;
}   
