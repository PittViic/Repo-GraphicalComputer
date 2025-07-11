#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
// rgb(187, 255, 0);
void display(void) {
    glClearColor(0.0f, 122.0f / 255.0f, 204.0f / 255.0f, 1.0f);   // Define a cor de fundo da cena (branco)

    glClear(GL_COLOR_BUFFER_BIT);   // Limpa o buffer de cores

    glMatrixMode(GL_MODELVIEW);   // Informa que as operações seguintes serão executadas na matrix modelview
    glLoadIdentity();             // Carrega a matriz identidade

    // Grama
    glBegin(GL_QUADS);{
        glColor3f(29.0f / 255.0f, 129.0f / 255.0f, 0.0f);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(-1.0f, -0.0f);
        glVertex2f(1.0f, -0.0f);
        glVertex2f(1.0f, -1.0f); 
    }glEnd();
    // Calçada da casa
    glBegin(GL_QUADS);{
        glColor3f(75.0f / 255.0f, 127.0f / 255.0f, 175.0f / 255.0f);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(-0.8f, -0.8f);
        glVertex2f(-0.6f, -0.8f);
        glVertex2f(-0.7f, -1.0f); 
    }glEnd();
    // Fachada da casa
    glBegin(GL_QUADS);{
        glColor3f(178.0f / 255.0f, 50.0f / 255.0f, 75.0f / 255.0f); // Verde
        glVertex2f(-0.9f, -0.1f); // V3: Superior Esquerdo
        glVertex2f(-0.5f, -0.1f); // V4: Superior Direito
        glVertex2f(-0.5f, -0.8f); // V2: Inferior Direito
        glVertex2f(-0.9f, -0.8f); // V1: Inferior Esquerdo
    }glEnd();
    // Porta da casa
    glBegin(GL_QUADS); {
        glColor3f(177.0f / 255.0f, 127.0f / 255.0f, 228.0f / 255.0f);
        glVertex2f(-0.8f, -0.8f); // V1: Inferior Esquerdo
        glVertex2f(-0.8f, -0.3f); // V3: Superior Esquerdo
        glVertex2f(-0.6f, -0.3f); // V4: Superior Direito
        glVertex2f(-0.6f, -0.8f); // V2: Inferior Direito
    }glEnd();
    // Maçandeta da porta
    glPointSize(10.0f);
    glBegin(GL_POINTS);{
      glColor3f(0.0f, 0.0f, 0.0f); // Preto
      glVertex2f(-0.75f, -0.55f); // Ponto no centro da tela
    }glEnd();
    // Telhado da casa
    glBegin(GL_TRIANGLES);{
        glColor3f(0.5f, 0.25f, 0.0f); // Marrom
        glVertex2f(-0.9f, -0.1f); // V3: Inferio Esquerdo
        glVertex2f(-0.7f, 0.3f);  // V4: Superior Direito
        glVertex2f(-0.5f, -0.1f); // V2: Inferior Direito
    }glEnd();
    // Telhado parte lateral
    glBegin(GL_QUADS);{
        glColor3f(255.0f / 255.0f, 209.0f / 255.0f, 78.0f / 255.0f);
        glVertex2f(-0.5f, -0.1);
        glVertex2f(-0.7f, 0.3f);
        glVertex2f(0.1f, 0.3);
        glVertex2f(0.3f, -0.1f);
    }glEnd();
    // Muro lateral
    glBegin(GL_QUADS);{
        glColor3f(23.0f / 255.0f, 51.0f / 255.0f, 73.0f / 255.0f);
        glVertex2f(-0.5f, -0.8f);
        glVertex2f(-0.5f, -0.1);
        glVertex2f(0.3f, -0.1f);
        glVertex2f(0.3f, -0.8f);
    }glEnd();
    // Janela 1
    glBegin(GL_QUADS);{
        glColor3f(48.0f / 255.0f, 101.0 / 255.0f, 73.0f / 255.0f);
        glVertex2f(-0.4f, -0.5f);
        glVertex2f(-0.4f, -0.2);
        glVertex2f(-0.2f, -0.2f);
        glVertex2f(-0.2f, -0.5f);
    }glEnd();
    // Linha horizontal no meio
    glLineWidth(5.0f); // Define a espessura da linha (por exemplo, 10 pixels)
    glBegin(GL_LINES);{
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-0.4f, -0.35f);
        glVertex2f(-0.2f, -0.35f);
    }glEnd();
    // Linha Vestival no meio
    glBegin(GL_LINES);{
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-0.3f, -0.2);
        glVertex2f(-0.3f, -0.5f);
    }glEnd();
    // Janela 2
    glBegin(GL_QUADS);{
        glColor3f(48.0f / 255.0f, 101.0 / 255.0f, 73.0f / 255.0f);
        glVertex2f(0.0f, -0.5f);
        glVertex2f(0.0f, -0.2);
        glVertex2f( 0.2f, -0.2f);
        glVertex2f(0.2f, -0.5f);
    }glEnd();
    // Linha horizontal no meio
    glLineWidth(5.0f); // Define a espessura da linha (por exemplo, 10 pixels)
    glBegin(GL_LINES);{
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(0.0f, -0.35f);
        glVertex2f(0.2f, -0.35f);
    }glEnd();
    // Linha Vestival no meio
    glBegin(GL_LINES);{
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(0.1f, -0.2);
        glVertex2f(0.1f, -0.5f);
    }glEnd();
   
    glFlush(); // Informa que as operações devem ser processadas imediatamente e exibidas na tela
}
/*Recebe um o comprimento (width) e altura (height) da janela em pixels.*/
void resize(GLsizei w, GLsizei h) {
    if (h == 0) h = 1;

    printf("Tam. janela: (%i,%i)\n", w, h);

    // ESSENCIAL: Configurar a viewport
    glViewport(0, 0, w, h);

    // ESSENCIAL: Configurar a matriz de projeção para 2D
    glMatrixMode(GL_PROJECTION); // Seleciona a matriz de projeção
    glLoadIdentity();            // Carrega a matriz identidade na projeção
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // Mapeia as coordenadas -1 a 1 para a tela
    
    // Voltamos para a matriz MODELVIEW para operações de desenho no display
    glMatrixMode(GL_MODELVIEW);
}
/*Recebe um código para cada tecla (ASCII) e as coordenadas do mouse.*/
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // ESC
            exit(0);
            break;
        case 32: // Espaço
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Mudei para preto para ver a mudança de cor de fundo
            break;
        default:
            printf("Código tecla: %i. Mouse em (%i,%i)\n", key, x, y);
            break;
    }
    glutPostRedisplay(); // Informa que a janela atual deve ser redesenhada
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 500); // Tamanho da janela em pixels
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Projeto da Casa"); // Título da janela
    glutDisplayFunc(display);
    glutReshapeFunc(resize); // Garanta que esta linha NÃO esteja comentada!
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}