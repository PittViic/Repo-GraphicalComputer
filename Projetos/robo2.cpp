#if __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

GLfloat angle, fAspect;
GLdouble rotX = 0, rotY = 0, rotZ = 0, rotLeftB = 0, rotRinghtB = 0, rotLeftP= 0, rotRinghtP = 0, traslY = 0;

void display(void){
    glClear(GL_COLOR_BUFFER_BIT);

    glLineWidth(2);
    glPushMatrix();
    {
        // Aplica rotações de visualização
        glRotatef(rotX, 1, 0, 0);
        glRotatef(rotY, 0, 1, 0);
        glRotatef(rotZ, 0, 0, 1);
        glTranslatef(0, traslY, 0);// Aplica a Translação do pulo do robô
        // Corpo do robô
        glPointSize(5);
        glColor3f(0.0f, 0.0f, 1.0f);
        glBegin(GL_POINTS);
        {
            glVertex3f (0, 0, 0);
        }glEnd();
        glutWireCube(30);
        // Cabeça
        glPushMatrix();
        {
            glColor3f(1.0f, 0.0f, 0.0f);
            glTranslatef(0, 20, 0);
            glBegin(GL_POINTS);
            {
                glVertex3f(0, 0, 0);
            }glEnd();
            glutWireCube(20); 
        }
        glPopMatrix();
        // Braço esquerdo
        glPushMatrix();
        {
            glTranslatef(-20, 10, 0);  // Posição inicial do braço
            glRotatef(rotLeftB, 0, 0, 1);  // Rotação do braço
            glColor3f(0.0f, 1.0f, 1.0f);
            glutWireCube(10);  // Parte superior do braço

            glPushMatrix();
            {
                glColor3f(0.0f, 1.0f, 0.0f);
                glTranslatef(0, -10, 0);  // Move para o antebraço
                glutWireCube(10);  // Parte inferior do braço
            }
            glPopMatrix();

        }
        glPopMatrix();
        // Braço Direito
        glPushMatrix();
        {
            glTranslatef(20, 10, 0);  // Posição inicial do braço
            glRotatef(rotRinghtB, 0, 0, 1);  // Rotação do braço
            glColor3f(0.0f, 1.0f, 1.0f);
            glutWireCube(10);  // Parte superior do braço

            glPushMatrix();
            {
                glColor3f(0.0f, 1.0f, 0.0f);
                glTranslatef(0, -10, 0);  // Move para o antebraço
                glutWireCube(10);  // Parte inferior do braço
            }
            glPopMatrix();

        }
        glPopMatrix();
        // Perna Esquerda
        glPushMatrix();
        {
            glTranslatef(-10, -20, 0);
            glRotatef(rotLeftP, 0, 0, 1);  // Rotação do braço
            glColor3f(0.0f, 0.0f, 0.0f);
            glutWireCube(10);

            glPushMatrix();
            {
                glColor3f(0.0f, 1.0f, 0.0f);
                glTranslatef(0, -10, 0);
                glutWireCube(10);
            }
            glPopMatrix();
        }
        glPopMatrix();
        // Perna Direita
        glPushMatrix();
        {
            glTranslatef(10, -20, 0);
            glRotatef(rotRinghtP, 0, 0, 1);  // Rotação do braço
            glColor3f(0.0f, 0.0f, 0.0f);
            glutWireCube(10);

            glPushMatrix();
            {
                glColor3f(0.0f, 1.0f, 0.0f);
                glTranslatef(0, -10, 0);
                glutWireCube(10);
            }
            glPopMatrix();
        }
        glPopMatrix();
    }

    glPopMatrix();
    glutSwapBuffers();
}

void init(){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    angle = 45;  // Ângulo de visão inicial
}

void configProjection(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angle, fAspect, 0.5, 500);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 100, 0, 0, 0, 0, 1, 0);  // Define a posição da câmera
}

void resize(GLsizei w, GLsizei h) {
    if (h == 0) h = 1;  // Evita divisão por zero

    fAspect = (GLfloat)w / (GLfloat)h;  // Calcula a razão de aspecto da tela
    configProjection();  // Recalcula a projeção
}

void mouse(int button, int state, int x, int y){
    if (button == GLUT_LEFT_BUTTON)
        if (state == GLUT_DOWN){
            if (angle >= 10) angle -= 5;
        }
    if (button == GLUT_RIGHT_BUTTON)
        if (state == GLUT_DOWN){
            if (angle <= 130) angle += 5;
        }
}

void keyboard(unsigned char key, int x, int y){
    switch (key){
    case 27: // Fecha o progrma
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
    case 'z':  // Move os braços (rotação)
        rotLeftB += 45;
        rotRinghtB -=45;
        rotLeftP += 15;
        rotRinghtP -= 15;
        traslY -= 3;
        break;
    case 'x':  // Move os braços no sentido contrário
        rotLeftB -= 45;
        rotRinghtB += 45;
        rotLeftP -= 15;
        rotRinghtP += 15;
        traslY += 3;
        break;
    case 32:  // Barra de espaço - reseta rotações principais
        rotX = 0;
        rotY = 0;
        rotZ = 0;
        rotLeftB = 0;
        rotRinghtB = 0;
        rotLeftP = 0;
        rotRinghtP = 0;
        traslY = 0;
        break;
    default:
        break;
    }
    // Limites para o ângulo do braço esquerdo
    if (rotLeftB > 0) rotLeftB = 0;
    if (rotLeftB < -180) rotLeftB = -180;
    // Limites para o ângulo do braço direito
    if (rotRinghtB < 0) rotRinghtB = 0;
    if (rotRinghtB > 180) rotRinghtB = 180;
    // Limites para o ângulo da perda esquerda
    if (rotLeftP > 0) rotLeftP = 0;
    if (rotLeftP < -60) rotLeftP = -60;
    // Limites para o ângulo do perna direito
    if (rotRinghtP < 0) rotRinghtP = 0;
    if (rotRinghtP > 60) rotRinghtP = 60;
    // Limites para altura do pulo do robo
    if (traslY < 0 ) traslY = 0;
    if (traslY > 12) traslY = 12;

    configProjection();      // Atualiza a projeção
    glutPostRedisplay();     // Re-renderiza a cena
}

int main(int argc,  char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800,600);
    glutCreateWindow("Visualização 3D");

    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);

    init();

    glutMainLoop();
    return 0;
}