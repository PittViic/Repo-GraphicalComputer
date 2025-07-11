#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

GLfloat angle, fAspect;
GLdouble rotX = 0, rotY = 0, rotZ = 0, rotArm = 0, rotAnte = 0;

// Função responsável por desenhar a cena (o robô com seus componentes)
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);  // Limpa o buffer de cor

    glLineWidth(2);  // Define a espessura das linhas

    glPushMatrix();  // Salva a matriz de transformação atual

    // Aplica rotações de visualização
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);
    glRotatef(rotZ, 0, 0, 1);

    // Corpo do robô
    glPointSize(5);
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0, 0, 0);  // Centro
    glEnd();
    glutWireCube(30);  // Cubo representando o corpo

    // Cabeça
    glPushMatrix();
    {
        glColor3f(1.0f, 0.0f, 0.0f);
        glTranslatef(0, 25, 0);  // Move para cima do corpo
        glBegin(GL_POINTS);
        glVertex3f(0, 0, 0);
        glEnd();
        glutWireCube(20);  // Cubo da cabeça
    }
    glPopMatrix();

    // Braço esquerdo
    glPushMatrix();
    {
        glTranslatef(-20, 10, 0);  // Posição inicial do braço
        glRotatef(rotArm, 0, 0, 1);  // Rotação do braço
        glColor3f(0.0f, 1.0f, 1.0f);
        glutWireCube(10);  // Parte superior do braço

        glPushMatrix();
        {
            glColor3f(0.0f, 1.0f, 0.0f);
            glTranslatef(0, -5, 0);  // Move para o antebraço
            //glRotatef(rotAnte, 1, 0, 0);  // Rotação do antebraço
            glTranslatef(0, -5, 0);
            glutWireCube(10);  // Parte inferior do braço
        }
        glPopMatrix();
    }
    glPopMatrix();

    // Braço direito
    glPushMatrix();
    glTranslatef(20, 10, 0);
    glColor3f(0.0f, 1.0f, 1.0f);
    glutWireCube(10);
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0, -10, 0);
    glutWireCube(10);
    glPopMatrix();
    glPopMatrix();

    // Perna direita
    glPushMatrix();
    glTranslatef(10, -20, 0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glutWireCube(10);
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0, -10, 0);
    glutWireCube(10);
    glPopMatrix();
    glPopMatrix();

    // Perna esquerda
    glPushMatrix();
    glTranslatef(-10, -20, 0);
    glBegin(GL_POINTS);
    glVertex3f(0, 0, 0);
    glEnd();
    glColor3f(0.0f, 0.0f, 0.0f);
    glutWireCube(10);
    glPushMatrix();
    glTranslatef(0, -10, 0);
    glutWireCube(10);
    glPopMatrix();
    glPopMatrix();

    glPopMatrix();  // Restaura a matriz de transformação original

    glutSwapBuffers();  // Troca os buffers (para animação suave)
}

// Função de inicialização - define cor de fundo e o ângulo inicial da câmera
void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // Cor de fundo: branco
    angle = 45;  // Ângulo de visão inicial
}

// Função que configura a projeção (perspectiva e câmera)
void configProjection(void) {
    glMatrixMode(GL_PROJECTION);  // Muda para matriz de projeção
    glLoadIdentity();  // Reseta a matriz

    gluPerspective(angle, fAspect, 0.5, 500);  // Projeção em perspectiva

    glMatrixMode(GL_MODELVIEW);  // Volta para o modo de modelagem
    glLoadIdentity();  // Reseta a matriz

    gluLookAt(0, 0, 100, 0, 0, 0, 0, 1, 0);  // Define posição da câmera
}

// Função chamada quando a janela é redimensionada
void resize(GLsizei w, GLsizei h) {
    if (h == 0) h = 1;  // Evita divisão por zero

    fAspect = (GLfloat)w / (GLfloat)h;  // Calcula a razão de aspecto da tela

    configProjection();  // Recalcula a projeção
}

// Função para tratar eventos de mouse (zoom in/out com clique)
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON)
        if (state == GLUT_DOWN) {  // Zoom-in
            if (angle >= 10) angle -= 5;
        }

    if (button == GLUT_RIGHT_BUTTON)
        if (state == GLUT_DOWN) {  // Zoom-out
            if (angle <= 130) angle += 5;
        }

    configProjection();  // Atualiza a projeção
    glutPostRedisplay();  // Re-renderiza a cena
}

// Função para tratar entrada de teclado
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27:  // Tecla ESC - fecha o programa
            exit(0);
            break;

        case 'a':  // Rotaciona para a esquerda no eixo Y
            rotY += 10;
            break;
        case 'd':  // Rotaciona para a direita no eixo Y
            rotY -= 10;
            break;
        case 'w':  // Rotaciona para cima no eixo X
            rotX += 10;
            break;
        case 's':  // Rotaciona para baixo no eixo X
            rotX -= 10;
            break;
        case 'q':  // Rotaciona para um lado no eixo Z
            rotZ += 10;
            break;
        case 'e':  // Rotaciona para o outro lado no eixo Z
            rotZ -= 10;
            break;
        case 'z':  // Move o braço (rotação)
            rotArm += 45;
            break;
        case 'x':  // Move o braço no sentido contrário
            rotArm -= 45;
            break;
        case 'c':  // Move o antebraço
            rotAnte += 30;
            break;
        case 'v':  // Move o antebraço no sentido contrário
            rotAnte -= 30;
            break;
        case 32:  // Barra de espaço - reseta rotações principais
            rotX = 0;
            rotY = 0;
            rotZ = 0;
            break;
        default:
            break;
    }

    // Limites para o ângulo do braço
    if (rotArm > 0) rotArm = 0;
    if (rotArm < -180) rotArm = -180;

    configProjection();      // Atualiza a projeção
    glutPostRedisplay();     // Re-renderiza a cena
}

// Função principal - inicializa o GLUT e registra callbacks
int main(int argc, char *argv[]) {
    glutInit(&argc, argv);  // Inicializa o GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // Buffer duplo + modo RGB
    glutInitWindowSize(800, 600);  // Tamanho da janela
    glutCreateWindow("Visualizacao 3D");  // Cria a janela com título

    // Registra as funções de callback
    glutDisplayFunc(display);     // Renderização
    glutReshapeFunc(resize);      // Redimensionamento
    glutMouseFunc(mouse);         // Mouse
    glutKeyboardFunc(keyboard);   // Teclado

    init();  // Inicializações gerais

    glutMainLoop();  // Inicia o loop principal do GLUT
    return 0;
}
