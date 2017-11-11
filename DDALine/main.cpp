/*Libreria usada solo en Windows - debe ir antes que las demás librerias*/
#include<windows.h>
/*Otras librerias necesarias*/
#include<math.h>
#include<iostream>
/*Libreria del OpenGL*/
#include<GL/glut.h>

using namespace std;
/*Declaramos los valores de la proyección en la ventana*/
void iniciarProyecion()
{
    /*A nuestra proyección le colocamos color blanco de fondo (rgb blano= 1,1,1)*/
    glClearColor(1.0,1.0,1.0,0.0);
    /*Creamos la proyección*/
    glMatrixMode(GL_PROJECTION);
    /*Definimos los límites de nuestra proyección
    de izquierda a derecha que vaya de -40 hasta 40
    igual cantidad de arriba hacia abajo
    */
    gluOrtho2D(-40,40,-40,40);
}

/*Primero dibujar la linea sin DDA*/
void dibujarLinea(GLint x0,GLint y0, GLint xf, GLint yf)
{

    /*Dibujar malla
    para que el pixel se vea pintado dentro del cuadro
    aumentamos 0.5 unidades desde el inicio del recorrido
    tanto para x como para y

    asi sucesivamente probar hasta que coincida
    incluso usar la malla en 3d
    */
    glColor3f(0.0,1.0,0.0);/*Color verde*/
    glPointSize(1);

    /*usar de preferencia en f (porque el aumento se declaró iniciando en 0.5 mas)*/

    for(float i=-39.5; i<40; i++)
    {

        glBegin(GL_LINES);
        glVertex3f(i,40,1);
        glVertex3f(i,-40,1);
        glVertex3f(40,i,1);
        glVertex3f(-40,i,1);
        glEnd();

    }
    /*Dibujar eje de coordenadas*/
    glColor3f(0.0,0.0,1.0);/*Color azul*/

    /*Eje 'x' y 'y', recordar que va desde -40 hasta 40*/
    glBegin(GL_LINES);
    glVertex2i(40,0);
    glVertex2i(-40,0);
    glVertex2i(0,40);
    glVertex2i(0,-40);
    glEnd();

    /*Eje y, recordar que va desde -40 hasta 40*/
    glBegin(GL_LINES);

    glEnd();

    /*Para cualquier gráfico que se dibuje generalmente se hace mediante función
    así*/
    glBegin(GL_LINES);/*Inicio de la función, con el tipo de figura*/
    /*Declaramos colo de la linea*/
    glColor3f(0.0,0.0,0.0);/*Color negro en rgb= 0,0,0 y es 3f por ser "float" los parametros*/
    /*Posición inicial y final de la linea*/
    glVertex2i(x0,y0);
    glVertex2i(xf,yf);
    glEnd();/*Fin de la función*/
}

void setPixel(GLint x, GLint y)
{
    /*declaramos el color del pixel pintado*/
    glColor3f(1.0,0.0,0.0);/*Color rojo*/
    glPointSize(8);/*tamaño del pixel será de 5 (al ejecutar se entenderá mejor)*/
    /*funcion*/
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}

/*Algoritmo DDA*/

void dda(GLint x0,GLint y0, GLint xf, GLint yf)
{
    GLint i;
    float x,y,ax,ay,res;

    /*Primero verificamos si la variación de x es mayor que la de y*/
    if(abs(xf-x0)>=abs(yf-y0))
    {
        res=abs(xf-x0);
    }
    else
    {
        res=abs(yf-y0);
    }

    /*
    en el caso de que varia mas en x, entonces res queda con su valor absoluto
    si y varia mas, entonces res queda con el valor absoluto de y

    ahora los aumentos(ax y ay)
    */

    ax=(xf-x0)/res;
    ay=(yf-y0)/res;

    /*En caso de que res sea el valor absoluto de la variación de x, el ax queda en 1 y ay en la pendiente
    y viceversa si res es el valor absoluto de la variación de y*/

    i=0;

    x=(float)x0;
    y=(float)y0;

    /*se realiza el casteo para pasar a float los valores, ya que se necesita su resultado en decimales*/

    while(i<=res)
    {

        setPixel(roundf(x),roundf(y));
        cout<<roundf(x)<<" , "<<roundf(y)<<endl;
        x=x+ax;
        y=y+ay;
        i++;
    }
}

/*Función que realizará el pintado*/
void draw(void)
{
    /*LIMPIA BUFFER*/
    glClear(GL_COLOR_BUFFER_BIT);

    /*Declaramos variables*/
    GLint
                                     x0=-10,
                                     y0=-5,
                                     xf=5,
                                     yf=35;

    /*Colocamos antes del pintado sin dda por superposición*/
    dda(x0,y0,xf,yf);
    dibujarLinea(x0,y0,xf,yf);
    glFlush();/*Pinta lo dibujado*/

}

int main (int argc, char* argv[])
{
    /*Iniciamos Glut*/
    glutInit(&argc,argv);
    /*Modo gráfico COLORES: RGB*/
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    /*Definimos el tamaño de la ventana*/
    glutInitWindowSize(800,600);
    /*Definimos posición donde se ubicará en pantalla*/
    glutInitWindowPosition(300,100);

    /*Crear la ventana que contedrá el lienzo*/
    glutCreateWindow("DDA line");

    iniciarProyecion();
    /*Llamamos la función a dibujar*/
    glutDisplayFunc(draw);
    /*Constante redibujado*/
    glutMainLoop();

}
