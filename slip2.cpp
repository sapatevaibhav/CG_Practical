// Implement DDA and Bresenham line drawing algorithm to draw Dotted line using mouse interface. Divide the screen in four quadrants with center as (0, 0). The line should work for all the slopes.

#include <iostream>
#include <GL/glut.h>
using namespace std;

int Algo;

int sign(float a)
{
    if (a == 0)
    {
        return 0;
    }
    if (a > 0)
    {
        return 1;
    }
    return -1;
}
void Init()
{
    glClearColor(0, 0, 0, 0);
    glColor3f(0, 1, 0);
    gluOrtho2D(0, 640, 0, 480);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Bresenham(int x_1, int y_1, int x_2, int y_2)
{
    int dx = abs(x_2 - x_1);
    int dy = abs(y_2 - y_1);
    int x = x_1;
    int y = y_1;
    int incx = (x_2 > x_1) ? 1 : -1;
    int incy = (y_2 > y_1) ? 1 : -1;

    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();

    if (dx > dy)
    {
        int p = 2 * dy - dx;
        for (int i = 0; i < dx; i++)
        {
            if (p >= 0)
            {
                y += incy;
                p -= 2 * dx;
            }
            x += incx;
            p += 2 * dy;

            if (i % 2 == 0)
            {
                glBegin(GL_POINTS);
                glVertex2i(x, y);
                glEnd();
            }
        }
    }
    else
    {
        int p = 2 * dx - dy;
        for (int i = 0; i < dy; i++)
        {
            if (p >= 0)
            {
                x += incx;
                p -= 2 * dy;
            }
            y += incy;
            p += 2 * dx;

            if (i % 2 == 0)
            {
                glBegin(GL_POINTS);
                glVertex2i(x, y);
                glEnd();
            }
        }
    }

    glFlush();
}

void DDA(int x_1, int y_1, int x_2, int y_2)
{
    float dx = x_2 - x_1;
    float dy = y_2 - y_1;
    float length = abs(dx) >= abs(dy) ? abs(dx) : abs(dy);
    float xinc = dx / length;
    float yinc = dy / length;
    float x = x_1 + 0.5 * sign(xinc);
    float y = y_1 + 0.5 * sign(yinc);

    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();

    for (int i = 0; i < length; i++)
    {
        x += xinc;
        y += yinc;

        if (i % 2 == 0)
        {
            glBegin(GL_POINTS);
            glVertex2i(x, y);
            glEnd();
        }
    }

    glFlush();
}

void display()
{
    DDA(0, 240, 640, 240);
    Bresenham(320, 0, 320, 640);
    glFlush();
}

void mymouse(int b, int s, int x, int y)
{
    static int x_s, y_s, x_e, y_e, pt = 0;

    if (b == GLUT_LEFT_BUTTON && s == GLUT_DOWN)
    {
        if (pt == 0)
        {
            x_s = x;
            y_s = 480 - y;
            pt++;
            glBegin(GL_POINTS);
            glVertex2i(x_s, y_s);
            glEnd();
        }
        else
        {
            x_e = x;
            y_e = 480 - y;

            glBegin(GL_POINTS);
            glVertex2i(x_e, y_e);
            glEnd();

            if (Algo == 1)
            {
                DDA(x_s, y_s, x_e, y_e);
            }
            if (Algo == 2)
            {
                Bresenham(x_s, y_s, x_e, y_e);
            }
        }
    }
    else if (b == GLUT_RIGHT_BUTTON && s == GLUT_DOWN)
    {
        pt = 0;
    }

    glFlush();
}

int main(int argc, char **argv)
{
    cout << "\n Select the Algorithm \n 1. DDA \n 2. Bresenham's \n";
    cin >> Algo;

    if (Algo != 1 && Algo != 2)
    {
        cout << "\n Option entered is wrong \n";
        return 0;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Dotted Line Drawing");
    Init();
    glutDisplayFunc(display);
    glutMouseFunc(mymouse);
    glutMainLoop();

    return 0;
}
