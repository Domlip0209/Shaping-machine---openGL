#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265


const float R=1;
float Omega = 1;
void init();
void Reshape(int, int);
void display();
void draw(int);
void timer(int);
const int N = 360;
int step;
float Bx[N];
    float By[N];
    float Cx[N];
    float Cy[N];
    float Beta;
    float Vx[N], Vy[N];
    float Ax = 0, Ay =0;
 float Ox = 0;
 float Oy= 3;


int main(int argc, char *argv[])
{
    int i;
    int OB = R;
    float AC = 5 * R;

    //starting points B X=0; y=3+R

    float r, delta = 2*M_PI/360, lengh;
    for(i=0, r=0; i<360; i++, r+=delta)
    {

        Bx[i] = Ox + sin(r);
        By[i] = Oy + cos(r);
        lengh = sqrt(pow(Bx[i]-Ax,2)+pow(By[i]-Ay,2));
         Vx[i] = (Bx[i] - Ax) / lengh;
         Vy[i] = (By[i] - Ay) / lengh;
         Cx[i] = 5*Vx[i];
         Cy[i] = 5*Vy[i];
    }

    printf("Shaping machine scheme OABC \nSides: OB = %d and AC = %f\n", OB, AC);

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB);
    glutInitWindowPosition(250,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("Mechanism simulation");
    init();

    glutDisplayFunc(&display);
    glutReshapeFunc(&Reshape);
    glutTimerFunc(0, &timer, 0);
    glutMainLoop();
    return 0;
}
void Reshape(int w, int h)
{
    //definition of the starting points
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    //projection mode
    glMatrixMode(GL_PROJECTION);
    //reset
    glLoadIdentity();
    //resolution definition
    gluOrtho2D(-3.0,3.0,-1.0,6.0);
    glMatrixMode(GL_MODELVIEW);
}
void display()
{
    //buffor clear
    glClear(GL_COLOR_BUFFER_BIT);
    //reset
    glLoadIdentity();
    draw(step);
    //drawing
    glutSwapBuffers();
}

void timer(int n)
{
    glutTimerFunc(1000/60, &timer, 0);
    glutPostRedisplay();
    step++;
    if(step== N) step=0;
}

void init()
{
    //background colour
    glClearColor(0,0,0,1);
}

void draw(int i)
{
    glPointSize(10);
    glBegin(GL_POINTS);
        //pkt O
        glColor3f(1.0, 1.0, 0.0);
        glVertex2f(Ox, Oy);
        //pkt A
       glColor3f(1.0, 0.0, 0.0);
        glVertex2f(Ax, Ay);
        //pkt B
         glColor3f(0.0, 0.0, 1.0);
        glVertex2f(Bx[i], By[i]);
        //pkt C
        glColor3f(1.0, 1.0, 0.0);
        glVertex2f(Cx[i], Cy[i]);
    glEnd();

   //draw lines
    glLineWidth(4);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    //line OB
        glVertex2f(0, 3);
        glVertex2f(Bx[i], By[i]);
    //line AB
        glVertex2f(0, 0);
        glVertex2f(Bx[i], By[i]);
    //line BC
       glVertex2f(Bx[i], By[i]);
        glVertex2f(Cx[i], Cy[i]);
    glEnd();

}
