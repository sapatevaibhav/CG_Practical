// Implement Bresenham circle drawing algorithm to draw any object. The object should be displayed in all the quadrants with respect to center and radius.

#include <GL/glut.h>
#include <iostream>
using namespace std;

int r;

void drawPoints(int x, int y)
{
    glBegin(GL_POINTS);
    glVertex2i(x + 320, y + 240);
    glVertex2i(y + 320, x + 240);
    glVertex2i(y + 320, -x + 240);
    glVertex2i(x + 320, -y + 240);
    glVertex2i(-x + 320, -y + 240);
    glVertex2i(-y + 320, -x + 240);
    glVertex2i(-y + 320, x + 240);
    glVertex2i(-x + 320, y + 240);
    glEnd();
    glFlush();
}

void drawCircle()
{
    float d = 3 - 2 * r;
    int x = 0;
    int y = r;

    while (x < y)
    {
        drawPoints(x, y);
        if (d < 0)
        {
            d += 4 * x + 6;
        }
        else
        {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void init()
{
    glClearColor(1, 1, 1, 0);
    glColor3f(1, 0, 1);
    gluOrtho2D(0, 640, 0, 480);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv)
{
    cout << "\n Enter Radius: ";
    cin >> r;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Circle");

    init();
    glutDisplayFunc(drawCircle);
    glutMainLoop();

    return 0;
}
