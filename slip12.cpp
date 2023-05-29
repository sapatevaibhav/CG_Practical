// Implement animation principles for any object

#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>

float triangleX = 0.0;

void display()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(triangleX, 0.0, 0.0);

    glBegin(GL_TRIANGLES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glVertex3f(0.5, 1.0, 0.0);
    glEnd();

    glutSwapBuffers();
}

void update(int value)
{
    triangleX += 0.01;
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)width / (float)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Moving Triangle");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);

    glutMainLoop();

    return 0;
}
