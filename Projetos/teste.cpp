#if __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>

GLfloat angle, fAspect;
GLdouble rotTerra = 0, rotLua = 0; // Variáveis de rotação para Terra e Lua

// --- Funções OpenGL ---

void display(void){
    // Limpa o buffer de cor e o buffer de profundidade
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Entra no modo de modelagem e reseta a matriz
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Define a posição da câmera (para poder ver o sistema solar)
    // Câmera em (0,0,100), olhando para (0,0,0), com o topo em Y+
    gluLookAt(0, 0, 100,
              0, 0, 0,
              0, 1, 0);

    // --- Desenha o Sol ---
    glPushMatrix(); // Salva a matriz atual (para o sistema solar)
    {
        // Cor do Sol (Amarelo) - Corrigido para valores entre 0.0f e 1.0f
        glColor3f(1.0f, 221.0f / 255.0f, 0.0f);
        // Desenha o Sol na origem
        glutSolidSphere(10.0, 50, 50); // Raio 10, maior detalhe (50 fatias, 50 pilhas)

        // --- Desenha a Terra ---
        glPushMatrix(); // Salva a matriz para as transformações da Terra
        {
            // Rotação da Terra em torno do Sol (órbita)
            // A rotação deve vir ANTES da translação para o raio da órbita
            glRotatef(rotTerra, 0, 0, 1); // Rotação no eixo Z para órbita

            // Translação para a distância da órbita da Terra em relação ao Sol
            glTranslatef(20.0, 0.0, 0.0);

            // Rotação da Terra em torno do seu próprio eixo (se desejar)
            // glRotatef(rotTerraEixo, 0, 0, 1); // Variável nova para rotação própria

            // Cor da Terra (Azul/Roxo) - Corrigido
            glColor3f(93.0f / 255.0f, 0.0f, 1.0f);
            // Desenha a Terra
            glutSolidSphere(4.0, 50, 50); // Raio 4

            // --- Desenha a Lua ---
            glPushMatrix(); // Salva a matriz para as transformações da Lua
            {
                // Rotação da Lua em torno da Terra (órbita)
                glRotatef(rotLua, 0, 0, 1); // Rotação no eixo Z para órbita da Lua

                // Translação para a distância da órbita da Lua em relação à Terra
                glTranslatef(6.0, 0.0, 0.0);

                // Cor da Lua (Branco)
                glColor3f(1.0f, 1.0f, 1.0f);
                // Desenha a Lua
                glutSolidSphere(1.0, 50, 50); // Raio 1
            }
            glPopMatrix(); // Restaura a matriz da Lua
        }
        glPopMatrix(); // Restaura a matriz da Terra
    }
    glPopMatrix(); // Restaura a matriz do sistema solar

    glutSwapBuffers(); // Troca os buffers para exibir a cena
}

void init(){
    // Cor de fundo da janela (preto para o espaço)
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    // Habilita o teste de profundidade (para que objetos mais próximos escondam os mais distantes)
    glEnable(GL_DEPTH_TEST);

    // --- Habilita Iluminação (ESSENCIAL para ver as cores de glutSolidSphere) ---
    glEnable(GL_LIGHTING); // Habilita o sistema de iluminação
    glEnable(GL_LIGHT0);   // Habilita a luz 0

    // Define as propriedades da luz 0 (luz ambiente e difusa)
    // Uma luz ambiente clara ilumina todas as partes igualmente
    GLfloat ambientLight[] = {0.5f, 0.5f, 0.5f, 1.0f}; // Luz ambiente (cinza claro)
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);

    // Uma luz direcional vinda de uma direção específica (simulando o sol distante)
    GLfloat lightPos[] = {1.0f, 1.0f, 1.0f, 0.0f}; // Luz direcional (último componente 0.0f)
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    // Habilita o rastreamento de cor do material pelo glColor (para que glColor3f funcione com iluminação)
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    // Configurações iniciais da câmera e projeção
    angle = 45; // Ângulo de visão inicial (campo de visão)
}

void configProjection(void) {
    glMatrixMode(GL_PROJECTION); // Entra no modo de matriz de projeção
    glLoadIdentity();            // Reseta a matriz de projeção
    // Define uma projeção em perspectiva (como o olho humano vê)
    gluPerspective(angle, fAspect, 0.5, 500); // (FOV, Aspect Ratio, Near, Far)

    glMatrixMode(GL_MODELVIEW); // Volta para o modo de matriz de modelagem
    glLoadIdentity();            // Reseta a matriz de modelagem (não usado aqui pois redefinimos em display)
    // A gluLookAt é chamada em `display` para cada frame, o que é comum para câmera fixa.
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
        case 'q': // Acelera as rotações
            rotTerra += 1; // Ajuste a velocidade de rotação da Terra
            rotLua += 5; // Ajuste a velocidade de rotação da Lua (mais rápida)
            break;
        case 'e': // Desacelera as rotações (ou gira no sentido contrário)
            rotTerra -= 1;
            rotLua -= 5;
            break;
        case 32: // Barra de espaço - reseta rotações
            rotTerra = 0;
            rotLua = 0;
            break;
        default:
            break;
    }
    // Não precisa chamar configProjection aqui, pois a câmera não muda.
    glutPostRedisplay(); // Força a re-renderização da cena para ver a animação
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    // Adicionado GLUT_DEPTH para o buffer de profundidade
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Sistema Solar");

    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyboard);

    init(); // Inicializa as configurações OpenGL

    glutMainLoop(); // Inicia o loop principal do GLUT
    return 0;
}