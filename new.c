//*****************************************************

//

// Exemplo3DComIluminacao.cpp

// Um programa OpenGL simples que abre uma janela GLUT,

// desenha um "torus" com iluminação, permite fazer

// zoom in e zoom out quando os botões do mouse são

// pressionados e mover a posição do observador virtual

// com as teclas de setas, HOME e END.

//

// Marcelo Cohen e Isabel H. Manssour

// "OpenGL - Uma Abordagem Prática e Objetiva"

//

//*****************************************************

#include <GL/glut.h>

#include <GL/freeglut.h>

#include <stdlib.h>

// Variáveis para controles de navegação
GLfloat azimuth = 0;

GLfloat turn = 0;

GLfloat wasd = 0;

GLfloat angle, fAspect;

GLfloat rotX, rotY, rotX_ini, rotY_ini;

GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;

int x_ini, y_ini, bot;

// Função responsável pela especificação dos parâmetros de iluminação

void DefineIluminacao(void)

{

	GLfloat luzAmbiente[4] = {1.5, 1.5, 1.5, 1.0};

	GLfloat luzDifusa[4] = {0.7, 0.7, 0.7, 1.0}; // "cor"

	GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0}; // "brilho"

	GLfloat posicaoLuz[4] = {90.0+0.5*azimuth,77.5,0, 1.0}; /* mesma do sol */

	// Capacidade de brilho do material

	GLfloat especularidade[4] = {0.1, 0.1, 0.1, 0.1};

	GLint especMaterial = 60;

	// Define a refletância do material

	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);

	// Define a concentração do brilho

	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

	// Ativa o uso da luz ambiente

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0

	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);

	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);

	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);
}


void DefineIluminacaoFosco(void)

{

	GLfloat luzAmbiente[4] = {1.5, 1.5, 1.5, 1.0};

	GLfloat luzDifusa[4] = {0.7, 0.7, 0.7, 1.0}; // "cor"

	GLfloat luzEspecular[4] = {1.0, 1.0, 1.0, 1.0}; // "brilho"

	/* GLfloat posicaoLuz[4] = {90.0+0.5*azimuth,77.5,0, 1.0}; */ /* mesma do sol */

	// Capacidade de brilho do material

	GLfloat especularidade[4] = {0, 0, 0, 0};

	GLint especMaterial = 60;

	// Define a refletância do material

	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);

	// Define a concentração do brilho

	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

	// Ativa o uso da luz ambiente

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0

	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);

	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);

	/* glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz); */
}

// Função callback de redesenho da janela de visualização

void drawFloor(){
	// Define a refletância do chao
	
	
	glPushMatrix(); //Inicia Carro, base
	
	glTranslatef(0, -32, 0);
    glScalef (4000,0.7,400);
	glutSolidCube(1.0);
	glPopMatrix();

}

void drawCloud(GLfloat xvalue, GLfloat zvalue){
	glPushMatrix();

	glTranslatef(xvalue,80, zvalue);
	glutSolidSphere(20, 10, 10);
	glTranslatef(20,5,0);
	glutSolidSphere(18, 10, 10);
	glTranslatef(20,0,0);
	glutSolidSphere(18, 10, 10);
	glPopMatrix();
}

void drawTree(){
	

	glPushMatrix();
	
	glTranslatef(120, -20.0, -80);
	glScalef (0.6,7,0.6);
	glutSolidCube(20.0);

	glPopMatrix();

	DefineIluminacao();
	glPushMatrix();
	
	glTranslatef(120, 40.0, -80);
	glColor3f(0,1,0);
	glutSolidSphere(40,40,40);

	glPopMatrix();

}

void drawChar(GLfloat wasd){


	   /* para o personagem andar de um lado para outro */
	glPushMatrix();
	glTranslatef(wasd*0.5, 0.0, -33.0);

	glPushMatrix(); //Inicia personagem, base
	glColor3f(0.2,0.2,0.2);
	glTranslatef(75.0, -18.0, -5.0);
	 
    glScalef (0.7,0.7,0.4);
	glutSolidCube(20.0);
	glPopMatrix();

	glPushMatrix(); //Inicia personagem, base
	glColor3f(0.2,0.2,0.2);
	glTranslatef(75.0, -8.0, -5.0);
	 
    glScalef (0.3,0.3,0.3);
	glutSolidCube(20.0);
	glPopMatrix();

	glPushMatrix(); //Inicia personagem, roda
	glColor3f(0,0,0);
	glTranslatef(75.0, -28.0, 0.0); 
	glRotatef(-wasd,0,0,1);
    glutSolidTorus(1,3,100,100);
	glBegin(GL_LINES);
  	glVertex3f(0.0f, 0.0f, 0.0f);
  	glVertex3f(5.0f, 0.0f, 0.0f);
	glEnd();
	
	glPopMatrix();

	glPushMatrix(); //Inicia personagem, roda
	glColor3f(0,0,0);

	glTranslatef(75.0, -28.0, -10.0); 
	glRotatef(-wasd,0,0,1);
    glutSolidTorus(1,3,100,100);
	glBegin(GL_LINES);
  	glVertex3f(0.0f, 0.0f, 0.0f);
  	glVertex3f(5.0f, 0.0f, 0.0f);
	glEnd();
	
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
}

void drawInsideWheel(){ /* fazendo linhas dentro da roda */

glPushMatrix();
glColor3f(0.16,0.16,0.16);

glPushMatrix();
glTranslatef(2,-0.25,-1);
	glScalef (3,0.5,0.5);
	glutSolidCube(2.0);
glPopMatrix();
	/* glBegin(GL_LINES);
  glVertex3f(0.0f, 0.0f, 0.0f);
  glVertex3f(5.0f, 0.0f, 0.0f);
glEnd(); */
glPushMatrix();
glRotatef(90,0,0,1);
glScalef (3,0.5,0.5);
glTranslatef(0,-4,-1);

	/* glScalef (3,0.5,0.5); */
	glutSolidCube(2.0);
glPopMatrix();

glPushMatrix();
glRotatef(45,0,0,1);
glScalef (3,0.3,0.5);
glTranslatef(0.5,-5.2,-1.2);

	/* glScalef (3,0.5,0.5); */
	glutSolidCube(2.0);
glPopMatrix();

glPushMatrix();
glRotatef(-45,0,0,1);
glScalef (3,0.3,0.5);
glTranslatef(0.5,4.4,-1.2);

	/* glScalef (3,0.5,0.5); */
	glutSolidCube(2.0);
glPopMatrix();

glPopMatrix();
}

void drawCar(GLfloat azimuth){

	/* glutSetKeyRepeat(1); */
	/* if(azimuth !=0){ */
	 /* glRotatef(turn*0.5, 0,1,0); */
	
	 glTranslatef(azimuth*0.5, 0.0, 0.0);
	 
	 
	 /* } */   /* para o carro andar de um lado para outro */
	 /* glRotatef(-azimuth,0,1,0); */   /* DK = drift king */
	glPushMatrix(); //Inicia Carro, base
	glTranslatef(15.0, -20.0, -5.0);
    glScalef (3.9,0.7,1.6);
	glutSolidCube(20.0);
	glPopMatrix();

	glPushMatrix(); //base frontal
	glTranslatef(-24, -20.2, -5.0);
    glRotatef(30,0,0,1);
    glScalef (0.4,0.6,1.6);
	glutSolidCube(20.0);
	glPopMatrix();

	glPushMatrix(); //base traseira
	glTranslatef(53, -20.2, -5.0);
    glRotatef(-36,0,0,1);
    glScalef (0.3,0.7,1.6);
	glutSolidCube(20.0);
	glPopMatrix();

    /* parte de cima */
	glPushMatrix(); 
	glTranslatef(20.0, -10, -5.0);
	glRotatef(2,0,0,1);
    glScalef (2,0.5,1.6);
	glutSolidCube(20.0);
	glPopMatrix();

	glPushMatrix(); /* janela traseira */
	glColor3f(0.7,0.7,0.7); 
	glTranslatef(42.0, -11.5, -5.0);
	glRotatef(35,0,0,1);
    glScalef (0.20,0.7,1.4);
	glutSolidCube(20.0);
	glPopMatrix();

	glPushMatrix(); /* janela frontal */
	glColor3f(0.7,0.7,0.7); 
	glTranslatef(-2, -11, -5.0);
	glRotatef(-40,0,0,1);
    glScalef (0.25,0.45,1.4);
	glutSolidCube(20.0);
	glPopMatrix();

	glPushMatrix(); /* janela lateral */
	glColor3f(0.7,0.7,0.7); 
	glTranslatef(10, -9, -5.0);
	glRotatef(2,0,0,1);
    glScalef (0.7,0.28,1.7);
	glutSolidCube(20.0);
	glPopMatrix();

	glPushMatrix(); /* janela lateral  2*/
	glColor3f(0.7,0.7,0.7); 
	glTranslatef(28, -8.5, -5.0);
	glRotatef(2,0,0,1);
    glScalef (0.7,0.28,1.7);
	glutSolidCube(20.0);
	glPopMatrix();


    
	glColor3f(0.0f, 0.0f, 0.0f);

	
	glPushMatrix();

	
    glScalef (2,2,2);
	
    /* raio interior, raio exterior */
	glColor3f(0,0,0);
	
    glTranslatef(20.0, -12.5, 6.5);
	
	
	glRotatef(-azimuth,0,0,1);
    glutSolidTorus(1,3,100,100);

	/* fazendo reta da roda */
	glTranslatef(-2.0, 0, 0.5);
	
	
	drawInsideWheel();
	
	glPopMatrix();

	glPushMatrix();

	
    glScalef (2,2,2);
	glColor3f(0,0,0);
    /* raio interior, raio exterior */
	
    glTranslatef(20.0, -12.5, -11.5);
	glRotatef(-azimuth,0,0,1);
    glutSolidTorus(1,3,100,100);

	glTranslatef(-1.5, 0, 1);
	
	drawInsideWheel();
	
	glPopMatrix();

	glPushMatrix();

	
    glScalef (2,2,2);
	glColor3f(0,0,0);
    /* raio interior, raio exterior */
    glTranslatef(-5.0, -12.5, 6.5);
	
	glRotatef(0, 0,1,0);
	glRotatef(-azimuth,0,0,1);
    glutSolidTorus(1,3,100,100);

	/* fazendo reta da roda */
	glTranslatef(-2, 0, 0.5);
	
	drawInsideWheel();
	
	glPopMatrix();

	glPushMatrix();

	
    glScalef (2,2,2);
	glColor3f(0,0,0);
    /* raio interior, raio exterior */
    glTranslatef(-5.0, -12.5, -11.5);
	
    glutSolidTorus(1,3,100,100);

	/* fazendo reta da roda */
	glTranslatef(-2, 0, 1);
	drawInsideWheel();
	
	glPopMatrix();

    glPopMatrix();//Fim carro

}


void display(void)

{

	// Limpa a janela de visualização com a cor

	// de fundo definida previamente

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /* inicia a matriz*/

    glPushMatrix();



	// Chama a função que especifica os parâmetros de iluminação

	

	// Altera a cor do desenho para azul

    glPushMatrix();//Inicio Carro/Sol

	

	// Função da GLUT para fazer o desenho de um "torus"

    glTranslatef( 0.0, 0.0, 0.0);

	DefineIluminacaoFosco();
	glColor3f(0.0f, 1.0f, 0.0f);

    drawFloor(); 
	DefineIluminacao();
	glColor3f(1.0f, 0.0f, 0.0f);
    drawCar(azimuth);

	DefineIluminacaoFosco();
	glColor3f(0.16f, 0.11f, 0.07f);
	drawTree();

	glColor3f(0.0f, 1.0f, 1.0f);
	drawChar(wasd); 

    
    glColor3f(1.0f, 1.0f, 0.0f);
    glPushMatrix();//Sol inicia

    glTranslatef(90.0+0.5*azimuth,77.5,0);
    glutSolidSphere(20.0,100,100);

    glPopMatrix(); //Fim Sol

    glPopMatrix(); //Fim carro/sol

	/* desenhando nuvem */
	glColor3f(1,1,1);
	drawCloud(0, -80);

	drawCloud(20, -80);


	glRotatef(90,0,1,0);
	drawCloud(20, -90);

	drawCloud(0, 80);

	

	drawCloud(-60, 50);

	drawCloud(50, 30);

	drawCloud(-100, -20);

    glPopMatrix();

	glutSwapBuffers();
}

// Função usada para especificar a posição do observador virtual

void PosicionaObservador(void)

{

	// Especifica sistema de coordenadas do modelo

	glMatrixMode(GL_MODELVIEW);

	// Inicializa sistema de coordenadas do modelo

	glLoadIdentity();

	DefineIluminacao();

	// Posiciona e orienta o observador

	glTranslatef(-obsX, -obsY, -obsZ);

	glRotatef(rotX, 1, 0, 0);

	glRotatef(rotY, 0, 1, 0);
}

// Função usada para especificar o volume de visualização

void EspecificaParametrosVisualizacao(void)

{

	// Especifica sistema de coordenadas de projeção

	glMatrixMode(GL_PROJECTION);

	// Inicializa sistema de coordenadas de projeção

	glLoadIdentity();

	// Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)

	gluPerspective(angle, fAspect, 0.5, 500);

	PosicionaObservador();
}

// Função callback chamada para gerenciar eventos de teclas normais (ESC)

void Teclado(unsigned char tecla, int x, int y)

{

	if (tecla == 27) // ESC ?

		exit(0);
}

// Função callback para tratar eventos de teclas especiais

void TeclasEspeciais(int tecla, int x, int y)

{

	switch (tecla)

	{

	case GLUT_KEY_PAGE_UP:  wasd +=10;   break;

	case GLUT_KEY_PAGE_DOWN:  wasd -=10;   break;

	case GLUT_KEY_LEFT:  azimuth -=10;   break;

        case GLUT_KEY_RIGHT: azimuth +=10;   break;

		case GLUT_KEY_UP :  turn -=10; azimuth -=0.5;    break;

        case GLUT_KEY_DOWN : turn +=10; azimuth -=0.5;  break;


	case GLUT_KEY_HOME:
		if (angle >= 10)
			angle -= 5;

		break;

	case GLUT_KEY_END:
		if (angle <= 150)
			angle += 5;

		break;
	}

	EspecificaParametrosVisualizacao();

	glutPostRedisplay();
}

// Função callback para eventos de botões do mouse

void GerenciaMouse(int button, int state, int x, int y)

{

	if (state == GLUT_DOWN)

	{

		// Salva os parâmetros atuais

		x_ini = x;

		y_ini = y;

		obsX_ini = obsX;

		obsY_ini = obsY;

		obsZ_ini = obsZ;

		rotX_ini = rotX;

		rotY_ini = rotY;

		bot = button;
	}

	else
		bot = -1;
}

// Função callback para eventos de movimento do mouse

#define SENS_ROT 5.0

#define SENS_OBS 10.0

#define SENS_TRANSL 10.0

void GerenciaMovim(int x, int y)

{

	// Botão esquerdo ?

	if (bot == GLUT_LEFT_BUTTON)

	{

		// Calcula diferenças

		int deltax = x_ini - x;

		int deltay = y_ini - y;

		// E modifica ângulos
		
		rotY = rotY_ini - deltax / SENS_ROT;
		/* adicionando trava para nao passar do chao */
		if(rotX_ini - deltay / SENS_ROT > -5){
		rotX = rotX_ini - deltay / SENS_ROT;}
	}

	// Botão direito ?

	else if (bot == GLUT_RIGHT_BUTTON)

	{

		// Calcula diferença

		int deltaz = y_ini - y;

		// E modifica distância do observador

		obsZ = obsZ_ini + deltaz / SENS_OBS;
	}

	// Botão do meio ?

	else if (bot == GLUT_MIDDLE_BUTTON)

	{

		// Calcula diferenças

		int deltax = x_ini - x;

		int deltay = y_ini - y;

		// E modifica posições

		obsX = obsX_ini + deltax / SENS_TRANSL;

		obsY = obsY_ini - deltay / SENS_TRANSL;
	}

	PosicionaObservador();

	glutPostRedisplay();
}

// Função callback chamada quando o tamanho da janela é alterado

void Reshape(GLsizei w, GLsizei h)

{

	// Para previnir uma divisão por zero

	if (h == 0)
		h = 1;

	// Especifica as dimensões da viewport

	glViewport(0, 0, w, h);

	// Calcula a correção de aspecto

	fAspect = (GLfloat)w / (GLfloat)h;

	EspecificaParametrosVisualizacao();
}

// Função responsável por inicializar parâmetros e variáveis

void init(void)

{

	// Define a cor de fundo da janela de visualização como branca

	glClearColor(0.0f, 1.0f, 1.0f, 0.0f);

	// Habilita a definição da cor do material a partir da cor corrente

	glEnable(GL_COLOR_MATERIAL);

	// Habilita o uso de iluminação

	glEnable(GL_LIGHTING);

	// Habilita a luz de número 0

	glEnable(GL_LIGHT0);

	// Habilita o depth-buffering

	glEnable(GL_DEPTH_TEST);

	// Habilita o modelo de colorização de Gouraud

	glShadeModel(GL_FLAT);

	// Inicializa a variável que especifica o ângulo da projeção

	// perspectiva

	angle = 45;

	// Inicializa as variáveis usadas para alterar a posição do

	// observador virtual

	rotX = 0;

	rotY = 0;

	obsX = obsY = 0;

	obsZ = 150;
}

// Programa Principal

int main(int argc, char **argv)

{

	glutInit(&argc, argv);

	// Define o modo de operação da GLUT

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// Especifica a posição inicial da janela GLUT

	glutInitWindowPosition(5, 5);

	// Especifica o tamanho inicial em pixels da janela GLUT

	glutInitWindowSize(450, 450);

	// Cria a janela passando como argumento o título da mesma

	glutCreateWindow("Desenho de carro 3D com iluminação");

	// Registra a função callback de redesenho da janela de visualização

	glutDisplayFunc(display);

	// Registra a função callback de redimensionamento da janela de visualização

	glutReshapeFunc(Reshape);

	// Registra a função callback para tratamento das teclas normais

	glutKeyboardFunc(Teclado);

	// Registra a função callback para tratamento das teclas especiais

	glutSpecialFunc(TeclasEspeciais);

	// Registra a função callback para eventos de botões do mouse

	glutMouseFunc(GerenciaMouse);

	// Registra a função callback para eventos de movimento do mouse

	glutMotionFunc(GerenciaMovim);

	// Chama a função responsável por fazer as inicializações

	init();

	// Inicia o processamento e aguarda interações do usuário

	glutMainLoop();

	return 0;
}