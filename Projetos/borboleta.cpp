#if __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h> // Para M_PI, cosf, sinf

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Variáveis globais (precisam ser declaradas fora das funções)
GLfloat angle, fAspect;
GLdouble rotX = 0, rotY = 0, rotZ = 0; // Para rotação da câmera (visualização)

// --- Função auxiliar para desenhar uma elipse sólida ---
void drawEllipse(float cx, float cy, float cz, float rx, float ry, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(cx, cy, cz); // Centro da elipse
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * M_PI * (float)i / (float)num_segments;
        float x = rx * cosf(theta); // Componente x com raio rx
        float y = ry * sinf(theta); // Componente y com raio ry
        glVertex3f(cx + x, cy + y, cz);
    }
    glEnd();
}

// --- Definição da Classe Borboleta ---
class borboleta
{
private:
    // Posição da borboleta no mundo
    GLfloat posX, posY, posZ;
    // Ângulo de rotação das asas (para futura animação)
    GLfloat flapAngle;

public:
    // Construtor
    borboleta(GLfloat x, GLfloat y, GLfloat z) :
        posX(x), posY(y), posZ(z), flapAngle(0.0f) {}

    // Destrutor
    ~borboleta() {}

    // Método para desenhar a borboleta
    void draw() {
        glPushMatrix(); // Salva a matriz atual (sistema de coordenadas do mundo)

        // Aplica a posição global da borboleta
        glTranslatef(posX, posY, posZ);

        // --- Corpo da Borboleta ---
        glColor3f(0.3f, 0.2f, 0.0f); // Cor marrom escura para o corpo

        // Segmento da cabeça
        glPushMatrix();
        glTranslatef(0.0f, 2.0f, 0.0f); // Move a cabeça para cima do corpo
        glutSolidSphere(1.0, 20, 20);   // Cabeça
        glPopMatrix();

        // Segmento do tórax (centro do corpo)
        glutSolidSphere(1.5, 20, 20); // Tórax

        // Segmento do abdômen
        glPushMatrix();
        glTranslatef(0.0f, -2.0f, 0.0f); // Move o abdômen para baixo do tórax
        glutSolidSphere(1.2, 20, 20);    // Abdômen
        glPopMatrix();

        // --- Asas ---
        glColor3f(0.8f, 0.1f, 0.6f); // Cor das asas (rosa/magenta)

        // Asa Superior Direita
        glPushMatrix();
        glTranslatef(1.5f, 1.0f, 0.0f); // Ponto de ancoragem da asa no corpo
        glRotatef(flapAngle, 0.0f, 1.0f, 0.0f); // Rotação para flapping (eixo Y)
        drawEllipse(0.0f, 0.0f, 0.0f, 5.0f, 3.0f, 50); // Desenha a elipse da asa
        glPopMatrix();

        // Asa Inferior Direita
        glPushMatrix();
        glTranslatef(1.5f, -1.0f, 0.0f); // Ponto de ancoragem da asa no corpo
        glRotatef(flapAngle, 0.0f, 1.0f, 0.0f); // Rotação para flapping (eixo Y)
        drawEllipse(0.0f, 0.0f, 0.0f, 4.0f, 2.5f, 50); // Desenha a elipse da asa
        glPopMatrix();

        // Asa Superior Esquerda (simétrica)
        glPushMatrix();
        glTranslatef(-1.5f, 1.0f, 0.0f); // Ponto de ancoragem da asa no corpo
        glRotatef(-flapAngle, 0.0f, 1.0f, 0.0f); // Rotação oposta para flapping
        drawEllipse(0.0f, 0.0f, 0.0f, 5.0f, 3.0f, 50); // Desenha a elipse da asa
        glPopMatrix();

        // Asa Inferior Esquerda (simétrica)
        glPushMatrix();
        glTranslatef(-1.5f, -1.0f, 0.0f); // Ponto de ancoragem da asa no corpo
        glRotatef(-flapAngle, 0.0f, 1.0f, 0.0f); // Rotação oposta para flapping
        drawEllipse(0.0f, 0.0f, 0.0f, 4.0f, 2.5f, 50); // Desenha a elipse da asa
        glPopMatrix();


        glPopMatrix(); // Restaura a matriz salva
    }

    // Método para animar as asas (simplesmente incrementa o ângulo)
    void flapWings() {
        // Altere este valor para controlar a velocidade e amplitude do "bater de asas"
        static float direction = 1.0f;
        flapAngle += 2.0f * direction; // Incrementa o ângulo

        if (flapAngle > 30.0f) { // Limite máximo
            flapAngle = 30.0f;
            direction = -1.0f; // Inverte a direção
        } else if (flapAngle < -30.0f) { // Limite mínimo
            flapAngle = -30.0f;
            direction = 1.0f; // Inverte a direção
        }
    }
};

// --- Instância global da borboleta ---
borboleta minhaBorboleta(0.0f, 0.0f, 0.0f); // Borboleta criada na origem do mundo

// --- Funções OpenGL ---

void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpa cor e profundidade

    glMatrixMode(GL_MODELVIEW); // Volta para o modo de modelagem
    glLoadIdentity();           // Reseta a matriz de modelagem

    // Define a posição da câmera (para poder ver a borboleta)
    gluLookAt(0, 0, 30,  // Câmera em (0,0,30)
              0, 0, 0,  // Olhando para a origem
              0, 1, 0); // Up vector (Y para cima)

    // Aplica rotações de visualização global (se quiser girar a cena inteira)
    glRotatef(rotX, 1, 0, 0);
    glRotatef(rotY, 0, 1, 0);
    glRotatef(rotZ, 0, 0, 1);

    // Desenha a borboleta
    minhaBorboleta.draw();

    glutSwapBuffers(); // Troca os buffers para exibir a cena
}

void init(){
    // Cor de fundo (azul)
    glClearColor(0.0f, 122.0f / 255.0f, 204.0f / 255.0f, 1.0f);
    glEnable(GL_DEPTH_TEST); // Habilita o teste de profundidade para objetos sólidos

    // Habilita a iluminação (opcional, mas recomendado para glutSolid* objetos)
    // Para ver as cores corretamente, é bom ter alguma luz, ou as faces solidas podem ficar pretas
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); // Habilita a luz 0

    // Configura uma luz ambiente (luz que ilumina igualmente todas as direções)
    GLfloat ambientLight[] = {0.5f, 0.5f, 0.5f, 1.0f};
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);

    // Habilita a coloração dos materiais
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    angle = 45; // Ângulo de visão inicial (campo de visão da câmera)
}

void configProjection(void) {
    glMatrixMode(GL_PROJECTION); // Entra no modo de projeção
    glLoadIdentity();            // Reseta a matriz de projeção
    // Configura uma projeção em perspectiva (como o olho humano vê)
    gluPerspective(angle, fAspect, 0.5, 500);

    glMatrixMode(GL_MODELVIEW); // Volta para o modo de modelagem (para desenhar objetos)
}

void resize(GLsizei w, GLsizei h) {
    if (h == 0) h = 1; // Evita divisão por zero
    glViewport(0, 0, w, h); // Define a área de desenho na janela
    fAspect = (GLfloat)w / (GLfloat)h; // Calcula a razão de aspecto da tela
    configProjection(); // Recalcula a projeção com a nova razão de aspecto
}

void keyboard(unsigned char key, int x, int y){
    switch (key){
    case 27: // Tecla ESC
        exit(0);
        break;
    case 'a': rotY += 5; break; // Rotaciona a cena (visualização)
    case 'd': rotY -= 5; break;
    case 'w': rotX += 5; break;
    case 's': rotX -= 5; break;
    case 'q': rotZ += 5; break;
    case 'e': rotZ -= 5; break;
    case 32: // Barra de espaço - reseta rotações de visualização
        rotX = rotY = rotZ = 0;
        break;
    case 'f': // Tecla 'f' para fazer as asas baterem
        minhaBorboleta.flapWings();
        break;
    default:
        break;
    }
    glutPostRedisplay(); // Força a re-renderização da cena
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Adicione GLUT_DEPTH
    glutInitWindowSize(1000, 800);
    glutCreateWindow("Borboleta 3D");

    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyboard); // Registra a função de teclado

    init(); // Inicializa OpenGL

    glutMainLoop(); // Inicia o loop principal do GLUT
    return 0;
}