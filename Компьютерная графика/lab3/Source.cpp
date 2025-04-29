#define _USE_MATH_DEFINES  // Должно быть перед #include <cmath>
#include <glut.h>
#include <math.h>
#include <cmath>
#include "Source.h"


int rot = 0;
int ro = 0;
int ex = 0;
const float PI = 3.14159265358979;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = SCREEN_WIDTH / 4 * 3;

float speed = 2.0f;
void specialkeys(int key, int x, int y) {
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

void draw_model() {
	glBegin(GL_LINES);
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glEnd();
	glColor3f(1, 1, 1);

	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0.5);
	glVertex3f(0.5, 0, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0, -0.5, 0.5);
	glEnd();


	glBegin(GL_POLYGON);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(0, 0.5, 0.5);
	glVertex3f(0, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0.6, 0.7, 0.9);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 1, 0);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0, 0.5, -0.5);
	glVertex3f(0, 0.5, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0.5);
	glVertex3f(0, 0.5, 0.5);
	glVertex3f(0, 0.5, -0.5);
	glVertex3f(0, 0, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 1, 0);
	glVertex3f(0, 0, -0.5);
	glVertex3f(0, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0, -0.5);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex3f(0, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0, -0.5, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 0, 1);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(0, 1, 1);
	glVertex3f(0.5, 0, 0.5);
	glVertex3f(0, 0, 0.5);
	glVertex3f(0, 0, -0.5);
	glVertex3f(0.5, 0, -0.5);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0, 0.5);
	glVertex3f(0.5, 0, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glEnd();

	glColor3f(66.0 / 256, 200.0 / 256, 210.0 / 256);
	glTranslatef(0.2f, 0.2f, 0.2f);
	glutSolidSphere(0.2f, 20, 20);
}

void scene() {
	glPushMatrix();
	draw_model();
	glPopMatrix();
}

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int widthGap = SCREEN_WIDTH / 4;
	int heightGap = SCREEN_HEIGHT / 3;
	int i = 0, j = heightGap * 2;

	// 0. просто сцена
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.5, 1.5, -1.5, 1.5, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glViewport(i, j, widthGap, heightGap);
	glLoadIdentity();
	drawAxes();
	glRotatef(rot, 0, 1, 0);
	glRotatef(ro, 1, 0, 0);
	scene();
	i += widthGap;

	// 1. Фронтальная
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.5, 1.5, -1.5, 1.5, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glViewport(i, j, widthGap, heightGap);
	glLoadIdentity();
	drawAxes();
	scene();
	i += widthGap;
	
	// 2. План (сверху)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.5, 1.5, -1.5, 1.5, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(90, 1, 0, 0);
	glViewport(i, j, widthGap, heightGap);
	drawAxes();
	scene();
	i += widthGap;

	// 3. Сбоку
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.5, 1.5, -1.5, 1.5, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(-90, 0, 1, 0);
	glViewport(i, j, widthGap, heightGap);
	drawAxes();
	scene();
	i = 0;
	j = heightGap;

	// 4. Изометрия
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.5, 1.5, -1.5, 1.5, -2.0, 2.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(35.264f, 1, 0, 0); 
	glRotatef(-45, 0, 1, 0);
	glViewport(i, j, widthGap, heightGap);

	drawAxes();
	scene();
	i += widthGap;

	// 5. Диметрия
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.5, 1.5, -1.5, 1.5, -2.0, 2.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(20, 1, 0, 0);
	glRotatef(-45, 0, 1, 0);
	glScalef(1, 1, 0.7);
	//glRotatef(7.18f, 1, 0, 0);   // 7°10' по X
	//glRotatef(-41.42f, 0, 1, 0);  // 41°25' по Y
	//glScalef(0.94, 0.94, 0.47);   // Коэффициенты сокращения
	
	glViewport(i, j, widthGap, heightGap);
	drawAxes();
	scene();
	i += widthGap;

	// 6. Триметрическая
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.5, 1.5, -1.5, 1.5, -2.0, 2.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(20, 1, 0, 0);
	glRotatef(-30, 0, 1, 0);
	glRotatef(15, 0, 0, 1);

	glScalef(1.2, 0.9, 0.7);

	glViewport(i, j, widthGap, heightGap);
	drawAxes();
	scene();
	i += widthGap;

	// 7. Кабине
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.5, 1.5, -1.5, 1.5, -2.0, 2.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	GLfloat  a[16];
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, a);
	// angle из градусов в радианы
	float angle = 45 * PI / 180, scale = 0.5;
	a[8] = -scale * sin(angle);
	a[9] = -scale * cos(angle);
	glLoadMatrixf(a);

	glViewport(i, j, widthGap, heightGap);
	drawAxes();
	scene();
	i = 0;
	j = 0;

	// 8. Кавалье
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.5, 1.5, -1.5, 1.5, -2.0, 2.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGetFloatv(GL_MODELVIEW_MATRIX, a);
	a[8] = -cos(angle);
	a[9] = -sin(angle);
	glLoadMatrixf(a);

	glViewport(i, j, widthGap, heightGap);
	drawAxes();
	scene();
	i += widthGap;

	// 9. Одноточечная
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.5, 1.5, -1.5, 1.5, 1, 5);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Камера смотрит вдоль оси -Z (точка схода в центре)
	gluLookAt(0, 0, 1.8,  // Позиция камеры (X, Y, Z)
		0, 0, 0,  // Точка взгляда (центр экрана)
		0, 1, 0); // Вектор "вверх" (ось Y)

	glTranslatef(-0.5, -0.5, 0.2);

	glViewport(i, j, widthGap, heightGap);
	drawAxes();
	scene();
	i += widthGap;

	// 10. Двухточечная
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.5, 1.5, -1.5, 1.5, 1, 5);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Камера смотрит вдоль оси -Z (точка схода в центре)
	gluLookAt(0, 0, 1.8,  // Позиция камеры (X, Y, Z)
		0, 0, 0,  // Точка взгляда (центр экрана)
		0, 1, 0); // Вектор "вверх" (ось Y)
	
	glRotatef(30, 1, 0, 0);

	glViewport(i, j, widthGap, heightGap);
	drawAxes();
	scene();
	i += widthGap;

	// 11. Трехточечная
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.5, 1.5, -1.5, 1.5, 1, 5);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Камера смотрит вдоль оси -Z (точка схода в центре)
	gluLookAt(0.7, 1, 1.5,  // Позиция камеры (X, Y, Z)
		0, 0, 0,  // Точка взгляда (центр экрана)
		0, 1, 0); // Вектор "вверх" (ось Y)

	glScaled(1.4, 1.4, 1.4);
	glRotated(-20, 0, 1, 0);
	glViewport(i, j, widthGap, heightGap);
	drawAxes();
	scene();

	glutSwapBuffers();
}
void Initialize() {
	glClearColor(0.3, 0.3, 0.3, 1.0);
	
	glEnable(GL_DEPTH_TEST);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(10, 20);
	glutCreateWindow("Our first GLUT application!");
	glutDisplayFunc(Display);
	glutSpecialFunc(specialkeys);
	Initialize();
	glutMainLoop();
	return 0;
}