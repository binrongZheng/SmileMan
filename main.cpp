#include <iostream>
#define _USE_MATH_DEFINES
#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <math.h>

//FRANCISCOMUREA@ENTI.CAT

//ESCENARIO - SMILE+ALGO, MARTES, MAXIMES PRIMITIVES MILLIR 

using namespace std;
const GLint WIDTH = 800, HEIGHT = 800;

//LOS ORDEN NO SE PUEDE CAMBIA, SINO NO FUNCIONA
bool CCW = true;
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	//cuando se pulsa una tecla escape cerramos la aplicacion
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		if (CCW==true) {
			CCW = false;
		}
		if (CCW==false) {
			CCW = true;
		}
	}
}

//GEOMETRIA
//CCW O CW, UTILIZA key "W" para cambiar CCW O CW
void CCW_CW() {
	if (CCW == true) {
		glFrontFace(GL_CCW);
	}
	else
		glFrontFace(GL_CW);
	
}
//GL_POINT (AMB DADES: posX, posY, colorR,G,B, tamany de point)
void point(float posX, float posY, float colorR, float colorG, float colorB, const float siz) {
	glPointSize(siz);
	glColor3f(colorR, colorG, colorB);
	glBegin(GL_POINTS);
	glVertex2f(posX, posY);
	glEnd();
}
//GL_LINE (AMB DADES: quantitat de points, posX, posY, colorR,G,B, stroke de linea)
void line(const int numPoint, float posX[], float posY[], float colorR, float colorG, float colorB, float stroke) {
	glLineWidth(stroke); //stroke de linea
	glColor3f(colorR, colorG, colorB);
	glBegin(GL_LINES);

	for (int i = 0; i < numPoint; i++) {
		glVertex2f(posX[i], posY[i]);
	}
	glEnd();
}
//GL_LINE_LOOP (AMB DADES: quantitat de points, posX, posY, colorR,G,B, stroke de linea)
void lineLoop(const int numPoint, float posX[], float posY[], float colorR, float colorG, float colorB, float stroke) {
	glLineWidth(stroke);
	glColor3f(colorR, colorG, colorB);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < numPoint; i++) {
		glVertex2f(posX[i], posY[i]);
	}
	glEnd();
}
//GL_LINE_LOOP PER CERCLE DE LA CARA (AMB DADES: quantitat de Triangle, posX, posY, colorR,G,B, radi, angle, i  stroke de linea)
void circleLine(const int numTri,float posX,float posY, float colorR,float colorG, float colorB, float rad, float angle, float stroke) {
	const float PI = 3.1415926;
	GLfloat Angle = angle * PI;
	glColor3f(colorR,colorG, colorB);
	glLineWidth(stroke);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= numTri; i++) {
		glVertex2f(
		posX + (rad * cos(i* Angle / numTri)),
		posY + (rad * sin(i* Angle / numTri))
		);
	}
	glEnd();
}
//GL_TRIANGLE_FAN (AMB DADES: posX, posY, colorRGB )
void triangle(float posX[], float posY[], float colorRGB[]) {
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 3; i++) {
		glColor3f(colorRGB[i * 3 + 0], colorRGB[i * 3 + 1], colorRGB[i * 3 + 2]);
		glVertex2d(posX[i],posY[i]);
	}
	glEnd();
};
//GL_QUADS (AMB DADES: posX, posY, colorR,G,B i stroke de linea)
void quads(float posX[], float posY[], float colorR, float colorG, float colorB, float stroke) { 
	glLineWidth(stroke);
	glColor3f(colorR, colorG, colorB);
	glBegin(GL_QUADS);
	for (int i = 0; i < 4; i++) {
		glVertex2f(posX[i], posY[i]);
	}
	glEnd();
};
//GL_TRIANGLE_FAN (AMB DADES: posX, posY, colorR,G,B, radi, angle, i quantitat de Triangle)
void circle(float posX, float posY, float colorR, float colorG, float colorB, float rad, float angle, const int numTri) {
	const float PI = 3.1415926;
	GLfloat Angle = angle * PI;
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);
	CCW_CW();
	glColor3f(colorR, colorG, colorB);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(posX, posY);
	for (int i = 0; i <= numTri; i++) {
		glVertex2f(
			posX + (rad * cos(i* Angle / numTri)),
			posY + (rad * sin(i* Angle / numTri))
		);
	}
	glDisable(GL_CULL_FACE);
	glEnd();
}
//GL_POLYGON (AMB DADES: posX, posY, colorR,G,B, quantitat de triangle)
void polygon(float posX[], float posY[], float colorR, float colorG, float colorB, const int numTri) {	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//GL_CW SENTIDO HORARIO, GL_CCW ANTIHORARIO
	//glFrontFace(GL_CCW);
	CCW_CW();
	glBegin(GL_POLYGON);
	glColor3f(colorR, colorG, colorB);	
	for (int i = 0; i < numTri; i++) {
		glVertex2f(posX[i], posY[i]);
	}
	glEnd();
	glDisable(GL_CULL_FACE);
}

//DIBUIXOS
void smileFace() {
	//PINTAR CARA (GL_TRIANGLE_FAN I GL_LINE_LOOP) 
	circle(0.0f, 0.0f, 2.0f, 0.75f, 0.0f, 5.0f, 2.0f, 30);			//CIRCLE AMB DADES: posX, posY, radi, colorR,G,B i quantitat de Triangle
	circleLine(30, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 5.0f, 2.0f, 5.0f); //LINEA AMB DADES: quantitat de points, posX, posY, colorR,G,B, stroke de linea

	//PINTAR ULLERES (GL_POINTS, GL_QUADS I GL_LINES_LOOP)		
	point(-2.0, 1.2, 0.0f, 0.0f, 0.0f, 100.0f);						//POINTS AMB DADES: posX, posY, colorR,G,B i tamany de points
	point(2.0, 1.2, 0.0f, 0.0f, 0.0f, 100.0f);
					
	float X[] = {4.8f, -4.8f, -4.9f, 4.9f };						//QUADS AMB DADES:  posX, posY dels punts, colorR,G,B i stroke de linea
	float Y[] = { 1.4f, 1.4f, 1.0f, 1.0f };
	quads(X,Y,0.0f,0.0f,0.0f,5.0f);

	int numPoint = 20;												//LINE AMB DADES: quantitat dels punts, posX, posY, colorR,G,B i stroke de linea
	float x[20] = { -4.8f, -4.9f, -3.2f, -3.2f, -0.8f, -0.8f, 0.8f, 0.8f, 3.2f, 3.2f, 4.9f, 4.8f, 3.2f,  3.2f,  0.8f, 0.8f, -0.8f,  -0.8f, -3.2f, -3.2f };
	float y[20] = {  1.4f,  1.0f,  1.0f, -0.1f, -0.1f,  1.0f, 1.0f,-0.1f,-0.1f, 1.0f, 1.0f, 1.4f, 1.4f,  2.5f,  2.5f, 1.4f,  1.4f,   2.5f,  2.5f,  1.4f };
	lineLoop(numPoint,x,y,1.0,1.0,1.0,5.0);

	//PINTAR LA BOCA (GL_POLYGON I GL_LINES_LOOP) 
	float pX[] = { -3.0f, -2.9f, -2.4f, -1.0f,  0.0f,  1.0f,  2.4f,  2.9f,  3.0f };
	float pY[] = { -1.2f, -2.0f, -3.0f, -3.8f, -4.0f, -3.8f, -3.0f, -2.0f, -1.2f };
	polygon(pX, pY, 1.0, 0.0, 0.0, 9);								//POLYGON AMB DADES: posX, posY dels punts, colorR,G,B , numPunts
	lineLoop(9.0,pX, pY, 0.0, 0.0, 0.0,5.0);						//LINE AMB DADES: quantitat dels punts, posX, posY, colorR,G,B i stroke de linea
}
void estrella(float X[],float Y[],int numEstrella) {
	//PINTAR LES ESTRELLES (GL_TRIANGLE_FAN)
	for (int i = 0; i < numEstrella; i++) {
		circle(X[i], Y[i], 0.0,0.0, 1.0, 1.0, 4.0, 5.0);			//angle de triangle es 4*PI =720
	}
}
void sol(float posXInit, float posYInit, float rad, float radi1, float radi2, float colorR, float colorG, float colorB,int numTri) {
	//PINTAR SOL (GL_TRIANGLE_FAN I GL_LINE_LOOP)
	glColor3f(colorR, colorG, colorB);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);
	CCW_CW();
	glBegin(GL_TRIANGLE_FAN);

	const float PI = 3.1415926;
	GLfloat Angle = rad * PI;
	GLfloat AnglePetitInit = (rad*PI) / 2;

	float x1[100] ; float y1[100]; float x2[100]; float y2[100];
	float radiGran = radi1; float radiPetit = radi2;
	float listX[100]; float listY[100];

	for (int i = 0; i < numTri; i++) {
		x1[i]= posXInit+radi1*cos(i*Angle/numTri);
		y1[i]= posYInit+radi1*sin(i*Angle/numTri);	
		x2[i]= posXInit+radi2*cos((AnglePetitInit / numTri)+(i*Angle / numTri));
		y2[i]= posYInit+radi2*sin((AnglePetitInit / numTri)+(i*Angle / numTri));
	}
	for (int i = 0; i < numTri; i++) {
		listX[i * 2] = x1[i];
		listY[i * 2] = y1[i];
		listX[i * 2 + 1] = x2[i];
		listY[i * 2 + 1] = y2[i];
	}
	for (int i = 0; i < 2 * numTri; i++) {
		glVertex2f(listX[i], listY[i]);
	}
	glDisable(GL_CULL_FACE);
	glEnd();

	lineLoop(numTri*2, listX, listY, 0.0, 0.0, 0.0, 5.0);
	
}
void gorra() {
	//PINTAR LA GORRA (GL_TRIANGLE I GL_LINE)
	float x[] = { -5.5f,3.25f, -2.75f};
	float y[] = { 1.75f ,4.75f, 7.75f };
	float RGB[] = { 0.f, 0.f, 0.f,0.f, 0.f, 0.f,0.f, 0.f, 1.f };
	triangle(x,y,RGB);

	glLineWidth(5.0f);	
	float colorRGB[] = { 1.0, 1.0, 0.5 ,1.0, 1.0, 0.5 ,0.0, 0.0, 0.0 };
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 3; i++) {
		glColor3f(colorRGB[i * 3 + 0], colorRGB[i * 3 + 1], colorRGB[i * 3 + 2]);
		glVertex2d(x[i], y[i]);
	}
	glEnd();
}
void ploure() {
	//PINTAR AIGUA (GL_LINE)
	float posX[10]; float posY[10];
	for(int i=1;i<10;i++){
		posX[i] = -10 + rand() % 20;
		posY[i] = -10 + rand() % 20;
		glLineWidth(10.0f);							//stroke de linea
		glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 0.0f);				//color de lines
		glVertex2f(posX[i], posY[i]);				//posicio iniciar de la linies
		glVertex2f(posX[i], posY[i]+rand()%3);		//posicio final de la linies

	}
	glEnd();
}
void nuvol(float velX,float velY) {
	//PINTAR NUVUL (GL_TRIANGLE_FAN)
	circle(velX +0.5, velY, 0.20f, 0.0f, 1.0f,2.0f,2.0f,10.0f);
	circle(velX +1, velY -2, 0.20f, 0.0f, 1.0f, 1.55f, 2.0f, 10.0f);
	circle(velX -2, velY -1, 0.20f, 0.0f, 1.0f, 2.30f, 2.0f, 10.0f);
	circle(velX + 3, velY - 1, 0.20f, 0.0f, 1.0f, 1.50f, 2.0f, 10.0f);
}

int main() {
	GLFWwindow* window;
	//comprobar que GLFW esta activo
	if (!glfwInit())
		exit(EXIT_FAILURE);
	//crear la ventana
	window = glfwCreateWindow(WIDTH, HEIGHT, "Primera ventana", nullptr, nullptr);
	if (!window) {
		cout << "Error al crear" << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit()) {
		cout << "error" << endl;
		glfwTerminate();
		return NULL;
	}
	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	//que funcion se llama,a cuando se detecta una pulsacio de tecla en la ventana
	glfwSetKeyCallback(window, key_callback);
	//DATOS PARA MOVER EL NUVOL I ESTRELLA
	int i = 0;								// es per comptar el temps
	float X = 0;float Y = -8;				// posicio de nuvol
	float velX = 0.1, velY = 2;				// velocitat per moure
	while (!glfwWindowShouldClose(window)) {
		glViewport(0, 0, screenWidth, screenHeight);
		glClear(GL_COLOR_BUFFER_BIT);

		//COLOR FONDO
		glClearColor(0.0f, 2.0f, 3.0f, 0.0f);
		//ESTRELLA
		i++;
		float posX[20];
		float posY[20];
		if (i == 50) {
			for(int j=0;j<20;j++){
				posX[j] = -10 + rand() % 20;
				posY[j] = -10 + rand() % 20;
			}
			i = 0; 
		}
		estrella(posX,posY,20);
		//SOL
		sol(0.0f,0.0f,2.0f,5.8f,7.5f,5.0f,0.10f,0.0f,8.0f);

		//CARA
		smileFace();

		//gorra
		gorra();

		//nuvol	
		X += velX; 
		if (X > 10) { X = -10; Y = -10 + rand() % 5; }
		nuvol(X, Y);
		nuvol(-X, -Y);

		//ploure
		ploure();

		//definir la matriz de proyection
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-10.f, 10.f, -10.f, 10.f, -1.0f, 10.f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//intercambio el framebuffer
		glfwSwapBuffers(window);
		//comprobes que algun disparador se halla activado (tales)
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
