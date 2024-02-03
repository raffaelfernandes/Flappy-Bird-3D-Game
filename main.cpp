#ifdef __APPLE__
    #define GL_SILENCE_DEPRECATION
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <GL/glut.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include "Object.cpp"
#include "LinkedList.cpp"
#include "glut_text.h"

float xPlayer = -3.5;
float yPlayer = 0;
float zPlayer = 0;
 
float xEP = xPlayer;
float xDP = xPlayer + 0.4;

double gravity = 0.0015f;
double jumpStrength = 0.04f;
double newJumpStrength = jumpStrength;
double decremento = -0.02f;

int score = 0;
bool gameOver = false;

float gap = 1.2;
float reshape_ratio = 1.0; // Manter proporcional a projecao


void init(void);
void keyboard (unsigned char key, int x, int y);
void display(void);
void reshape (int w, int h);
void update(int value);
float randomNumber(float min, float max);

Player player = Player::Player(xPlayer, yPlayer, zPlayer, false);
LinkedList<Pipe> pipeList;

int main(int argc, char** argv) {
    // Inicializa a semente para a função rand() usando o tempo atual
    std::srand(static_cast<unsigned int>(std::time(NULL)));	
	
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glEnable(GL_DEPTH_TEST);
    glutInitWindowSize(1200, 675);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Flappy Bird 3D");
    
    pipeList.enqueue(Pipe(0, randomNumber(-2.0, 2.0), 0, gap));
    pipeList.enqueue(Pipe(4, randomNumber(-2.0, 2.0), 0, gap));
    pipeList.enqueue(Pipe(8, randomNumber(-2.0, 2.0), 0, gap));

	// Funções de Callback
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutTimerFunc(25, update, 0);

    init();
    glutMainLoop();
    return 0;
}

void init(void){
    glClearColor(0.19f, 0.75f, 0.87f, 1.0);
    
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    glEnable(GL_COLOR_MATERIAL);
    float globalAmb[] = {0.5f, 0.5f, 0.5f, 1.f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmb);
    
    float light0[4][4] = {
	{0.1f, 0.1f, 0.1f, 1.f}, // ambiente
	{0.8f, 0.8f, 0.8f, 1.f}, // diffuse
	{1.f, 1.f, 1.f, 1.f}, // specular
	{3.0f, 1.0f, 2.0f, 1.f} // position
	};
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, &light0[0][0]);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, &light0[1][0]);
    glLightfv(GL_LIGHT0, GL_SPECULAR, &light0[2][0]);
    glLightfv(GL_LIGHT0, GL_POSITION, &light0[3][0]);
    
}

void reshape (int w, int h){
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	
	// Define a matriz de projeção
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(45.0f, (float)w / (float)h, 1.0f, 100.0f);
    gluPerspective(30, (float)w/(float)h , 5.0, 50.0); //(angulo, aspecto, ponto_proximo, ponto distante)
    gluLookAt(0.0,1.0,9.0,  // posicao da camera (olho)
              0.0,0.0,0.0,  // direcao da camera (geralmente para centro da cena)
              0.0,1.0,0.0); // sentido ou orientacao da camera (de cabeca para cima)

    // Define a matriz de modelo e visualização
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	
}

void keyboard (unsigned char key, int x, int y){
	switch (key) {
        case 32: // Espaço
            player.setIsJumping(true);
            jumpStrength = newJumpStrength;
            break;
        case 27: // Esc
            exit(0);
            break;
    }
}

void drawBackground(){
	glPushMatrix();
		glTranslatef(0.0, -0.8f, -2.0);
		glColor3f(0.56f, 0.44f, 0.32f);
		glBegin(GL_POLYGON);
			glVertex3f(-7.f, -3.f, 0.f);
			glVertex3f(-5.f, -1.f, 0.f);
			glVertex3f(-4.5f, 0.f, 0.f);
			glVertex3f(-2.0f, 1.2f, 0.f);
			glVertex3f(0.7f, 1.3f, 0.f);
			glVertex3f(1.2f, -0.5f, 0.f);
			glVertex3f(1.7f, 0.5f, 0.f);
			glVertex3f(1.8f, 0.6f, 0.f);
			glVertex3f(6.0f, -3.f, 0.f);
		glEnd();
	glPopMatrix();
	
	//SOL
	// glPushMatrix();
	// 	glTranslatef(3.5, 1.2f, -2.2f);
	// 	glColor3f(1.f, 1.f, 0.0f);
	// 	glBegin(GL_POLYGON);
	// 		glVertex3f(0.f, 1.f, 0.f);
	// 		glVertex3f(0.8f, 0.7f, 0.0f);
	// 		glVertex3f(1.f, 0.f, 0.0f);
	// 		glVertex3f(0.8f, -0.8f, 0.0f);
	// 		glVertex3f(0.f, -1.f, 0.0f);
	// 		glVertex3f(-0.5f, -0.5f, 0.0f);
	// 		glVertex3f(-1.f, 0.f, 0.f);
	// 		glVertex3f(-0.5f, 0.5f, 0.0f);
			//glVertex3f(0.f, 0.f, 0.f);
			//glVertex3f(0.f, 0.f, 0.f);
			//glVertex3f(0.f, 0.f, 0.f);
			//glVertex3f(0.f, 0.f, 0.f);
	// 	glEnd();
	// glPopMatrix();
}


void display(void){
	// Apaga o video e o depth buffer, e reinicia a matriz
	if (gameOver){
		std::cout << "Game Over!" << std::endl;
	    exit(0);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Desenha o jogador e os obstáculos
	drawBackground();
    
    player.drawPlayer();
	pipeList.drawList(decremento);
	
	glPushMatrix();
		// Desenhando textos na janela GLUT
	    glDisable(GL_LIGHTING); // Desliga a Luz para desenhar o texto
	    glColor3f(0.0, 0.0, 0.0); // seleciona a cor preta para o texto
	    float x = -reshape_ratio-0.45;
	    glTranslatef(0.0, 0.0, 3.0);
	    draw_text_stroke(x-0.5, 1.25, "SCORE: " + to_string(score));
    glPopMatrix();
    glEnable(GL_LIGHTING);

    glutSwapBuffers();
}

void update(int value) {
    // Atualiza a posição do jogador
    if (player.getIsJumping()) {
        player.setYCoord(player.getYCoord() + jumpStrength);
        jumpStrength -= gravity;
        
        if (player.getYCoord() < -4.5f || player.getYCoord() > 4.5f){
			gameOver = true;
		}
        
        LinkedList<Pipe>::Iterator it = pipeList.begin();
	    LinkedList<Pipe>::Iterator end = pipeList.end();
	    for (; it != end; ++it) {
	        Pipe& pipe = *it; 
	        // Faça algo com o item, por exemplo, desenhe
	        pipe.setXCoord(pipe.getXCoord()+decremento);
	        if (pipe.getXCoord() < -5.5f){
				pipeList.dequeue(pipe);
				pipeList.enqueue(Pipe(6.5, randomNumber(-2.0, 2.0), 0, gap));
				score++;
				if(score > 0 && score%3  == 0){
					newJumpStrength += newJumpStrength*0.02;
					gravity += gravity*0.02;
					decremento += decremento*0.06;
					
				}
			}
			if (xEP <= (pipe.getXCoord()+1.0) && xDP >= pipe.getXCoord()){
				if (((player.getYCoord()) <= pipe.getYCoord()-(gap/2)) || (player.getYCoord()) >= pipe.getYCoord()+ (gap/2)){
					gameOver = true;
				}
			}
	    }
    }

    // Atualiza a tela
    glutPostRedisplay();
    glutTimerFunc(10, update, 0);
}

float randomNumber(float min, float max) {
    // Gera um número inteiro aleatório no intervalo [min, max]
    int range = static_cast<int>((max - min) * 1000.0f) + 1;
    int numeroInteiro = std::rand() % range + static_cast<int>(min * 1000.0f);

    // Converte o número inteiro para um número de ponto flutuante no intervalo [min, max]
    float numeroFloat = static_cast<float>(numeroInteiro) / 1000.0f;

    return numeroFloat;
}
