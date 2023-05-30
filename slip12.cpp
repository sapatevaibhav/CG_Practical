// Implement animation principles for any object

#include <GL/glut.h>

int x = 0;
int direction = 1;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2i(x, 220);
    glVertex2i(x + 40, 220);
    glVertex2i(x + 40, 260);
    glVertex2i(x, 260);
    glEnd();
    glutSwapBuffers();
}

void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
    x += direction * 3;
    if (x == 600 || x == 0)
    {
        direction *= -1;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Animation");
    glOrtho(0, 640, 0, 480, -1, 1);
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}