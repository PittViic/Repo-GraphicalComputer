#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Function to draw a circle
void drawCircle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN); // Use GL_TRIANGLE_FAN for a solid circle
    glVertex2f(cx, cy); // Center of the circle
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * M_PI * (float)i / (float)num_segments; // get the current angle
        float x = r * cosf(theta); // calculate the x component
        float y = r * sinf(theta); // calculate the y component
        glVertex2f(cx + x, cy + y); // output vertex
    }
    glEnd();
}

void display() {
    glClearColor(0.0f, 122.0f / 255.0f, 204.0f / 255.0f, 0.0f); // White background
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw the circle
    glColor3f(0.0f, 0.0f, 0.0f); // Blue color for the circle
    drawCircle(0.0f, 0.0f, 0.6f, 100); // Center (0,0), radius 0.3, 100 segments
    // Nariz do Gato
    glColor3f(1.0f, 0.6f, 0.6f);
    glBegin(GL_TRIANGLES);{
      glVertex2f(-0.05f, -0.05f);
      glVertex2f(0.05f, -0.05f);
      glVertex2f(0.0f, 0.05f);
    }glEnd();
    // Orelhas do Gato
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);{
      glVertex2f(-0.4f, 0.4);
      glVertex2f(0.0f, 0.4);
      glVertex2f(-0.3f, 0.9f);
    }glEnd();
    glBegin(GL_TRIANGLES);{
      glVertex2f(0.4f, 0.4);
      glVertex2f(0.0f, 0.4);
      glVertex2f(0.3f, 0.9f);
    }glEnd();
    // Olhos do Gato 
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(-0.2f, 0.2f, 0.1f, 100); 
    drawCircle(0.2f, 0.2f, 0.1f, 100); 
    // Pupilas dos olhos
    glColor3f(0.0f, 122.0f / 255.0f, 204.0f / 255.0f);
    drawCircle(-0.2f, 0.2f, 0.05f, 100); 
    drawCircle(0.2f, 0.2f, 0.05f, 100);
    // Bigode do Gato lado esquerdo
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);{
      glVertex2f(-0.1f, 0.0f);
      glVertex2f(-0.25f, -0.05f);
    }glEnd();
    glBegin(GL_LINES);{
      glVertex2f(-0.1f,- 0.05f);
      glVertex2f(-0.25f, -0.1f);
    }glEnd();
    glBegin(GL_LINES);{
      glVertex2f(-0.1f, -0.1f);
      glVertex2f(-0.25f,- 0.15f);
    }glEnd();
    // Bigode do Gato lado direito
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);{
      glVertex2f(0.1f, 0.0f);
      glVertex2f(0.25f, -0.05f);
    }glEnd();
    glBegin(GL_LINES);{
      glVertex2f(0.1f,- 0.05f);
      glVertex2f(0.25f, -0.1f);
    }glEnd();
    glBegin(GL_LINES);{
      glVertex2f(0.1f, -0.1f);
      glVertex2f(0.25f,- 0.15f);
    }glEnd();

    glFlush();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Circle and Triangle"); // Changed window title
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}