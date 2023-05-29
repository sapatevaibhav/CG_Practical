// Implement the following polygon filling methods Boundary fill using mouse click, keyboard interface and menu driven programming.

#include <iostream>
#include <GL/glut.h>

float R = 0, G = 0, B = 0;
int Algo;

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 640, 0, 480);
}

void boundaryFill(int x, int y, float *fillColor, float *bc)
{
    float color[3];
    glReadPixels(x, y, 1.0, 1.0, GL_RGB, GL_FLOAT, color);

    if ((color[0] != bc[0] || color[1] != bc[1] || color[2] != bc[2]) &&
        (fillColor[0] != color[0] || fillColor[1] != color[1] || fillColor[2] != color[2]))
    {
        glColor3fv(fillColor);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();

        boundaryFill(x + 1, y, fillColor, bc);
        boundaryFill(x - 1, y, fillColor, bc);
        boundaryFill(x, y + 1, fillColor, bc);
        boundaryFill(x, y - 1, fillColor, bc);
    }
}

void mouse(int btn, int state, int x, int y)
{
    y = 480 - y;

    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        float bcol[] = {1, 0, 0};
        float oldcol[] = {1, 1, 1};
        float newCol[] = {R, G, B};

        boundaryFill(x, y, newCol, bcol);
    }
}

void Boundry()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);

    glBegin(GL_LINE_LOOP);
    glVertex2i(200, 150);
    glVertex2i(300, 300);
    glVertex2i(400, 150);
    glEnd();

    glFlush();
}

void goMenu(int value)
{
    switch (value)
    {
    case 1:
        R = 0;
        G = 1;
        B = 0;
        break;
    case 2:
        R = 1;
        G = 1;
        B = 0;
        break;
    case 3:
        R = 1;
        G = 0;
        B = 1;
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Boundry Fill");
    init();

    glutCreateMenu(goMenu);
    glutAddMenuEntry("Color 1 Green", 1);
    glutAddMenuEntry("Color 2 Yellow", 2);
    glutAddMenuEntry("Color 3 Pink", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(Boundry);

    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}