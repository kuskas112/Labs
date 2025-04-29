#define _USE_MATH_DEFINES  // Должно быть перед #include <cmath>
#include <glut.h>
#include <math.h>
#include <cmath>
#include "Source.h"


int rot = 0;
int ro = 0;
int ex = 0;
float smRad = 0.38;
float smRadH = 0.125f;
float S = 0.35;
float headCoeff = 0.37f;

void (*sceneFunc)() = emptyScene;
float speed = 2.0f;
void specialkeys(int key, int x, int y) {
	if (key == GLUT_KEY_F1) { sceneFunc = sceneWithHat; }
	if (key == GLUT_KEY_F2) { sceneFunc = sceneSnowManParticles; }
	if (key == GLUT_KEY_F3) { sceneFunc = sceneThreeSnowMans; }
	if (key == GLUT_KEY_F4) { sceneFunc = sceneThreeSnowMansZ; }
	if (key == GLUT_KEY_F5) { sceneFunc = sceneThreeSnowMansY; }
	if (key == GLUT_KEY_F6) { sceneFunc = sceneThreeSnowMansDiag; }
	if (key == GLUT_KEY_F7) { sceneFunc = sceneThreeSnowMansX; }
	if (key == GLUT_KEY_F8) { sceneFunc = sceneThreeSnowMansXEvery; }
	if (key == GLUT_KEY_F9) { sceneFunc = sceneThreeSnowMansXLast; }
	if (key == GLUT_KEY_F10) { sceneFunc = sceneFlyingHead; }
	if (key == GLUT_KEY_F11) { sceneFunc = sceneThreeSnowMansEverywhere; }
	if (key == GLUT_KEY_LEFT) { rot = rot - speed; }
	else
		if (key == GLUT_KEY_RIGHT) { rot = rot + speed; }
		else
			if (key == GLUT_KEY_UP) { ro = ro - speed; }
			else
				if (key == GLUT_KEY_DOWN) { ro = ro + speed; }
				else {
					ex = key;
					rot = 0;
					ro = 0;
				}
	ro = ro % 360;
	rot = rot % 360;
	glutPostRedisplay();
}

void drawAxes() {
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);

	glEnd();
}

void emptySnowMan(){
	glPushMatrix();
	drawAxes();
	glPopMatrix();
}

void emptyScene(){}

void drawSnowMan() {
	glPushMatrix();
	drawAxes();
	glColor3f(1.0f, 1.0f, 1.0f);
	// тело снеговика
	glutSolidSphere(smRad, 20, 20);

	// голова снеговика
	glTranslatef(0, smRad, 0);
	glScalef(headCoeff, headCoeff, headCoeff);
	glTranslatef(0, smRad, 0);
	glutSolidSphere(smRad, 20, 20);

	glPushMatrix();

	// глаз левый
	glColor3f(0, 0, 0);
	glTranslatef(-0.2f, 0.1f, smRad);
	glutSolidSphere(smRad * 0.2, 20, 20);
	// глаз правый
	glTranslatef(0.4f, 0, 0);
	glutSolidSphere(smRad * 0.2, 20, 20);

	glPopMatrix();

	// нос
	glColor3f(235.0 / 256, 94.0 / 256, 52.0 / 256);
	glutSolidCone(0.2f, 0.8f, 20, 20);

	glPopMatrix();
}

void drawSnowManHeadRotated() {
	glPushMatrix();
	drawAxes();
	glColor3f(1.0f, 1.0f, 1.0f);
	// тело снеговика
	glutSolidSphere(smRad, 20, 20);

	// голова снеговика
	glRotatef(ro, 0, 0, 1);
	glTranslatef(0, smRad, 0);
	glScalef(headCoeff, headCoeff, headCoeff);
	glTranslatef(0, smRad, 0);
	glRotatef(-ro, 0, 0, 1);
	glutSolidSphere(smRad, 20, 20);

	glPushMatrix();

	// глаз левый
	glColor3f(0, 0, 0);
	glTranslatef(-0.2f, 0.1f, smRad);
	glutSolidSphere(smRad * 0.2, 20, 20);
	// глаз правый
	glTranslatef(0.4f, 0, 0);
	glutSolidSphere(smRad * 0.2, 20, 20);

	glPopMatrix();

	// нос
	glColor3f(235.0 / 256, 94.0 / 256, 52.0 / 256);
	glutSolidCone(0.2f, 0.8f, 20, 20);

	glPopMatrix();
}

void drawSnowManWithHat() {
	glPushMatrix();
	drawAxes();
	glColor3f(1.0f, 1.0f, 1.0f);
	// тело снеговика
	glutSolidSphere(smRad, 20, 20);

	// голова снеговика
	glTranslatef(0, smRad, 0);
	glScalef(headCoeff, headCoeff, headCoeff);
	glTranslatef(0, smRad, 0);
	glutSolidSphere(smRad, 20, 20);

	glPushMatrix();

	// глаз левый
	glColor3f(0, 0, 0);
	glTranslatef(-0.2f,0.1f, smRad);
	glutSolidSphere(smRad * 0.2, 20, 20);
	// глаз правый
	glTranslatef(0.4f, 0, 0);
	glutSolidSphere(smRad * 0.2, 20, 20);

	glPopMatrix();

	// нос
	glColor3f(235.0/256, 94.0/256, 52.0/256);
	glutSolidCone(0.2f, 0.8f, 20, 20);

	//шапочка
	//220, 52, 235
	glTranslatef(0, smRad, 0);
	glRotatef(-90, 1, 0, 0);

	double offset = abs(sin(ro * M_PI / 180));
	glTranslated(0, 0, 1.5f*offset);
	glRotatef(ro * 2, 0, 1, 0);

	glColor3f(220.0 / 256, 52.0 / 256, 235.0 / 256);
	glutSolidCone(0.15f, 0.7f, 20, 20);

	glPopMatrix();
}

void sceneWithHat() {
	drawSnowManWithHat();
	glRotatef(-ro, 0, 0, 10);

	glTranslatef(smRad + smRad*2*headCoeff,0, 0);
	glScalef(S, S, S);
	glTranslatef(smRad, 0, 0.0);
	drawSnowManWithHat();
}

void drawSnowManParticles() {
	float totalOffset = 0;
	glPushMatrix();
	drawAxes();
	glColor3f(1.0f, 1.0f, 1.0f);
	// тело снеговика
	glPushMatrix();
	glTranslatef(0, smRad, 0);
	glutSolidSphere(smRad, 20, 20);
	glPopMatrix();

	totalOffset = smRad;
	// голова снеговика
	glPushMatrix();
	glTranslatef(totalOffset + smRad*headCoeff, smRad * headCoeff, 0);
	glutSolidSphere(smRad*headCoeff, 20, 20);
	glPopMatrix();
	totalOffset += smRad * headCoeff * 2;

	// глаз левый
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(totalOffset + smRad * 0.13, smRad * 0.13, 0);
	glutSolidSphere(smRad * 0.13, 20, 20);
	glPopMatrix();
	totalOffset += smRad * 0.13 * 2;

	// глаз правый
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(totalOffset + smRad * 0.13, smRad * 0.13, 0);
	glutSolidSphere(smRad * 0.13, 20, 20);
	glPopMatrix();
	totalOffset += smRad * 0.13 * 2;

	// нос
	glColor3f(235.0 / 256, 94.0 / 256, 52.0 / 256);
	glRotatef(-90, 1, 0, 0);
	glTranslatef(totalOffset + 0.2f*0.3, 0, 0);
	glutSolidCone(0.2f * 0.3, 0.8f*0.3, 20, 20);

	glPopMatrix();
}

void sceneSnowManParticles() {
	drawSnowManParticles();
	glRotatef(ro, 0, 0, 10);
}

void sceneThreeSnowMans() {
	double scale = 0.7f;
	glRotatef(-ro, 0, 10, 0);
	drawSnowMan();
	glTranslatef(smRad, 0, 0);
	glScalef(scale*scale, scale * scale, scale * scale);
	glTranslatef(smRad, 0, 0);
	drawSnowMan();
	glTranslatef(smRad, 0, 0);
	glScalef(1/scale, 1 / scale, 1 / scale);
	glTranslatef(smRad, 0, 0);
	drawSnowMan();
}

void sceneThreeSnowMansEverywhere() {
	glScalef(0.7f, 0.7f, 0.7f);
	drawSnowMan();

	glRotatef(ro, 0, 1, 0);
	glTranslatef(smRad, 0, 0);
	glScalef(0.7f, 0.7f, 0.7f);
	glTranslatef(smRad*2, 0, 0);
	drawSnowMan();
	
	glPushMatrix();

	glRotatef(ro, 0, 0, 1);
	glTranslatef(0, smRad + smRad*headCoeff, 0);
	glScalef(0.7f, 0.7f, 0.7f);
	glTranslatef(0, smRad*2, 0);
	drawSnowMan();

	glPopMatrix();

	glRotatef(ro, 0, 1, 0);
	glTranslatef(smRad, smRad + smRad*headCoeff/2, 0);
	glScalef(0.49f, 0.49f, 0.49f);
	glTranslatef(smRad*2, 0, 0);
	drawSnowMan();
}

void sceneFlyingHead() {
	drawSnowManHeadRotated();
}

void sceneThreeSnowMansY() {
	glRotatef(-ro, 0, 10, 0);
	drawSnowMan();
	glTranslatef(0, smRad + smRad*headCoeff*2, 0);
	glScalef(0.5f, 0.5f, 0.5f);
	glTranslatef(0, smRad, 0);
	drawSnowMan();
	glTranslatef(0, smRad + smRad*headCoeff*2, 0);
	glScalef(0.5f, 0.5f, 0.5f);
	glTranslatef(0, smRad, 0);
	drawSnowMan();
}

void sceneThreeSnowMansZ() {
	drawSnowMan();
	glTranslatef(0, 0, smRad);
	glScalef(0.7f, 0.7f, 0.7f);
	glTranslatef(0, 0, smRad);

	glTranslatef(0, smRad, 0);
	glScalef(headCoeff, headCoeff, headCoeff);
	glTranslatef(0, smRad, 0);
	glRotatef(-ro, 0, 0, 10);
	glTranslatef(0, -smRad, 0);
	glScalef(1 / headCoeff, 1 / headCoeff, 1 / headCoeff);
	glTranslatef(0, -smRad, 0);

	drawSnowMan();

	glTranslatef(0, smRad, 0);
	glScalef(headCoeff, headCoeff, headCoeff);
	glTranslatef(0, smRad, 0);
	glRotatef(ro, 0, 0, 10);
	glTranslatef(0, -smRad, 0);
	glScalef(1 / headCoeff, 1 / headCoeff, 1 / headCoeff);
	glTranslatef(0, -smRad, 0);

	glTranslatef(0, 0, smRad);
	glScalef(0.7f, 0.7f, 0.7f);
	glTranslatef(0, 0, smRad);
	drawSnowMan();
}

void sceneThreeSnowMansDiag() {
	glRotatef(-ro, 0, 1, 0);
	//glRotatef(ro, 0, 1, 1);
	drawSnowMan();
	//glRotatef(-ro, 0, 1, 1);

	glRotatef(45, 0, 1, 1);
	
	glTranslatef(smRad, 0, 0);
	glScalef(0.7f, 0.7f, 0.7f);
	glTranslatef(smRad, 0, 0);
	
	glRotatef(-45, 0, 1, 1);
	//glRotatef(ro, 0, 1, 1);
	drawSnowMan();
	//glRotatef(-ro, 0, 1, 1);
	
	glRotatef(45, 0, 1, 1); 

	glTranslatef(smRad, 0, 0);
	glScalef(0.7f, 0.7f, 0.7f);
	glTranslatef(smRad, 0, 0);

	glRotatef(-45, 0, 1, 1);

	//glRotatef(ro, 0, 1, 1);
	drawSnowMan();
	//glRotatef(-ro, 0, 1, 1);
}


void sceneThreeSnowMansX() {
	// вращение вокруг среднего
	glTranslatef(smRad + smRad*0.7f, 0, 0);
	glRotatef(-ro, 0, 1, 0);
	glTranslatef(-smRad - smRad*0.7f, 0, 0);

	glPushMatrix();
	glTranslatef(0, smRad, 0);
	drawSnowMan();
	glPopMatrix();

	glTranslatef(smRad, 0, 0);
	glScalef(0.7f, 0.7f, 0.7f);
	glTranslatef(smRad, 0, 0);

	glPushMatrix();
	glTranslatef(0, smRad, 0);
	drawSnowMan();
	glPopMatrix();
	
	glTranslatef(smRad, 0, 0);
	glScalef(0.7f, 0.7f, 0.7f);
	glTranslatef(smRad, 0, 0);
	glTranslatef(0, smRad, 0);
	drawSnowMan();
}

void sceneThreeSnowMansXEvery() {
	glPushMatrix();
	glTranslatef(0, smRad, 0);
	glRotatef(-ro, 0, 1, 0);
	drawSnowMan();
	glPopMatrix();

	glTranslatef(smRad, 0, 0);
	glScalef(0.7f, 0.7f, 0.7f);
	glTranslatef(smRad, 0, 0);

	glPushMatrix();
	glTranslatef(0, smRad, 0);
	glRotatef(-ro, 0, 1, 0);
	drawSnowMan();
	glPopMatrix();

	glTranslatef(smRad, 0, 0);
	glScalef(0.7f, 0.7f, 0.7f);
	glTranslatef(smRad, 0, 0);
	glTranslatef(0, smRad, 0);
	glRotatef(-ro, 0, 1, 0);
	drawSnowMan();
}

void sceneThreeSnowMansXLast() {
	// вращение вокруг последнего
	glTranslatef(smRad + smRad * 0.7f * 2 + smRad*0.7f*0.7f , 0, 0);
	glRotatef(-ro, 0, 1, 0);
	glTranslatef(-smRad - smRad * 0.7f * 2 - smRad*0.7f*0.7f , 0, 0);

	glPushMatrix();
	glTranslatef(0, smRad, 0);
	drawSnowMan();
	glPopMatrix();

	glTranslatef(smRad, 0, 0);
	glScalef(0.7f, 0.7f, 0.7f);
	glTranslatef(smRad, 0, 0);

	glPushMatrix();
	glTranslatef(0, smRad, 0);
	drawSnowMan();
	glPopMatrix();

	glTranslatef(smRad, 0, 0);
	glScalef(0.7f, 0.7f, 0.7f);
	glTranslatef(smRad, 0, 0);
	glTranslatef(0, smRad, 0);
	drawSnowMan();
}


void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, 400, 400);
	glLoadIdentity();
	drawAxes();
	sceneFunc();

	glViewport(400, 0, 400, 400);
	glLoadIdentity();
	glRotatef(90, 1, 0, 0);
	drawAxes();
	sceneFunc();
	glutSwapBuffers();
}
void Initialize() {
	glClearColor(0.3, 0.3, 0.3, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.5, 1.5, -1.5, 1.5, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 400);
	glutInitWindowPosition(10, 20);
	glutCreateWindow("Our first GLUT application!");
	glutDisplayFunc(Display);
	glutSpecialFunc(specialkeys);
	Initialize();
	glutMainLoop();
	return 0;
}