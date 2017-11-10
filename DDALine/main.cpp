#include<windows.h>
#include <GL/glut.h>
#include <cstdlib>
#include <math.h>
#include<iostream>
using namespace std;
void inicio(){
    glClearColor(1.0,1.0,1.0,0.0);//color rgb del color blanco
    glMatrixMode(GL_PROJECTION);//proyección sobre la ventana
    gluOrtho2D(-40,40,-40,40);//limites en pixeles de la proyección
}

void dibujarLinea(GLint x0,GLint y0,GLint xf,GLint yf){

for(float i=-39.5;i<40;i++){
    glLineWidth(1);//grosor de la linea
    glBegin(GL_LINES);
    glColor3f( 0, 1, 0);
    glVertex3f(i,40,-1);
    glVertex3f(i,-40,-1);
	
    glEnd();
}
for(float i=-39.5;i<40;i++){
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f( 0, 1, 0);
    glVertex3f(40,i,-1);
    glVertex3f(-40,i,-1);
    glEnd();
}
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f( 0, 0, 0);
    glVertex3f(0,40,-1);
    glVertex3f(0,-40,-1);
    glEnd();

    glBegin(GL_LINES);
    glColor3f( 0, 0, 0);
    glVertex3f(40,0,0);
    glVertex3f(-40,0,0);
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(1.0,0.5,0.2);
    glVertex2f(x0,y0);
    glVertex2f(xf,yf);
    glEnd();
    glFlush();

}
void setPixel(GLint x, GLint y){
    glColor3f(0.1,0.4,0.2);
    glPointSize(9);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush();
}
void DDA (GLint x1,GLint y1,GLint x2,GLint y2)
{
   float ax,ay,x,y,res;
   GLint i;
   if(abs(x2-x1)>=abs(y2-y1))
    //si la variacion en x es mayor o igual que la variacion en y
    res=abs(x2-x1);
        else
    //si la variacion en y es mayor que la variacion en x
    res=abs(y2-y1);

   ax=(x2-x1)/res;//el valor a aumentar en x
   ay=(y2-y1)/res;//el valor a aumentar en y

   //se realiza casteo a float porque los resultados de la división es un real

   x=(float)x1;
   y=(float)y1;

   i=0;
   while(i<=res)
   {
        setPixel(roundf(x),roundf(y));
        x=x+ax;
        y=y+ay;
        i++;
   }
}
void drawMyLine(void)
{
 glClear(GL_COLOR_BUFFER_BIT);

                             // MODIFICAR PUNTOS
                                     GLint x0 =  -2;
                                     GLint y0 =  -1;
                                     GLint xf =  1;
                                     GLint yf =  7;
									 
 
DDA(x0,y0,xf,yf);
 dibujarLinea(x0,y0,xf,yf);

}

int main(int argc, char *argv[])
{
 glutInit(&argc,argv);

 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

 glutInitWindowSize(800,600);

 glutInitWindowPosition(300,100);

 glutCreateWindow("Linea DDA");

 inicio();

 glutDisplayFunc(drawMyLine);

 glutMainLoop();
}
