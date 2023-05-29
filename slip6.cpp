// Implement the following polygon filling methods Flood fill / Seed fill using mouse click, keyboard interface and menu driven programming.

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

void floodFill(int x, int y, float *newCol, float *oldCol)
{
    float pixel[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, pixel);

    if (oldCol[0] == pixel[0] && oldCol[1] == pixel[1] && oldCol[2] == pixel[2])
    {
        glBegin(GL_POINTS);
        glColor3fv(newCol);
        glVertex2i(x, y);
        glEnd();
        glFlush();

        floodFill(x, y + 1, newCol, oldCol);
        floodFill(x + 1, y, newCol, oldCol);
        floodFill(x, y - 1, newCol, oldCol);
        floodFill(x - 1, y, newCol, oldCol);
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

        floodFill(x, y, newCol, oldcol);
    }
}

void Flood()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex2i(200, 150);
    glVertex2i(300, 300);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 1);
    glVertex2i(300, 300);
    glVertex2i(400, 150);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0, 0, 0);
    glVertex2i(400, 150);
    glVertex2i(200, 150);
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
    glutCreateWindow("Flood Filling");
    init();

    glutCreateMenu(goMenu);
    glutAddMenuEntry("Color 1 Green", 1);
    glutAddMenuEntry("Color 2 Yellow", 2);
    glutAddMenuEntry("Color 3 Pink", 3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutDisplayFunc(Flood);

    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}