#include <math.h>
#include <gl/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

// Prototipos
void inicio(void);
void display(void);
void myreshape(int, int);
void puntoMedio(int, int, int, int);
void renderBitmapString(float x, float y, void* font, const char* string);
void dibujarGrafico();
void ingresoDatos(void);

// Variables para las coordenadas de la línea
int px0, py0, px1, py1;

int main(int argc, char** argv) {
	ingresoDatos();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Linea de cualquier pendiente");

    inicio();
    glutDisplayFunc(display);
    glutReshapeFunc(myreshape);

    glutMainLoop();
    return 0;
}

void inicio(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();

    dibujarGrafico();

    glPopMatrix();
    glFlush();
}

void myreshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float aspect = (GLfloat)w / (GLfloat)h;

    if (w <= h) {
        float adjustedHeight = 50.0 * aspect;
        glOrtho(-50.0, 50.0, -adjustedHeight, adjustedHeight, -10, 10);
    }
    else {
        float adjustedWidth = 50.0 * aspect;
        glOrtho(-adjustedWidth, adjustedWidth, -50.0, 50.0, -10, 10);

    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


// Algoritmo del punto medio para dibujar la línea
void puntoMedio(int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int incX = (x1 > x0) ? 1 : -1;
    int incY = (y1 > y0) ? 1 : -1;
    bool pendienteMayorA1 = dy > dx;

    if (pendienteMayorA1) {
        std::swap(dx, dy);
        std::swap(x0, y0);
        std::swap(x1, y1);
        std::swap(incX, incY);
    }

    int d = (2 * dy) - dx;
    int dE = 2 * dy;
    int dNE = 2 * (dy - dx);
    int x = x0;
    int y = y0;

    glBegin(GL_POINTS);
    if (pendienteMayorA1) {
        glVertex2f(y, x);
    }
    else {
        glVertex2f(x, y);
    }

    while (x != x1) {
        if (d <= 0) {
            d += dE;
        }
        else {
            d += dNE;
            y += incY;
        }
        x += incX;

        if (pendienteMayorA1) {
            glVertex2f(y, x);
        }
        else {
            glVertex2f(x, y);
        }
    }
    glEnd();
}

void dibujarGrafico() {

    glPushMatrix();

    //glTranslatef(20.0f, 0.0f, 0.0f);

    //ejes
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(-100, 0);
    glVertex2f(100, 0);
    glVertex2f(0, -50);
    glVertex2f(0, 50);
    glEnd();

    // Dibuja la línea con el algoritmo de punto medio
    glColor3f(0, 0, 1); // Azul
    glPointSize(5); // Fija el grosor de pixel
    puntoMedio(px0, py0, px1, py1);

    // Convertir las coordenadas a cadenas de texto
    char coordInicio[50], coordFin[50];
    sprintf_s(coordInicio, "(%d, %d)", px0, py0);
    sprintf_s(coordFin, "(%d, %d)", px1, py1);

    // Muestra las coordenadas en los extremos de la línea
    glColor3f(1, 0, 0); // Rojo para el texto
    renderBitmapString(px0 + 1, py0 + 1, GLUT_BITMAP_HELVETICA_12, coordInicio); // Coordenada inicial
    renderBitmapString(px1 + 1, py1 + 1, GLUT_BITMAP_HELVETICA_12, coordFin); // Coordenada final



    glPopMatrix();
}


// Función para dibujar texto en pantalla
void renderBitmapString(float x, float y, void* font, const char* string) {
    const char* c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void ingresoDatos(void)
{
    // lo que Ud desee
    cout << "\n leer px0="; cin >> px0;
    cout << "\n leer py0="; cin >> py0;
    cout << "\n leer px1="; cin >> px1;
    cout << "\n leer py1="; cin >> py1;
}