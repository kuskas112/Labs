#define _USE_MATH_DEFINES  // Должно быть перед #include <cmath>
#include <glut.h>
#include <math.h>
#include <cmath>
#include "Source.h"
#include <iostream>
#include <vector>


const float a = 0.5f;

float tran = 0;
float con = 30;
float rot = 0;
int w = 350;
int commandCounter = 0;
int sceneCounter = 0;

float no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
float mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
float mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
float mat_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
//float mat_diffuse[] = { 0.7, 0.7, 0.7, 1.0 };
float mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
float no_shininess = 0.0;
float low_shininess = 5.0;
float high_shininess = 100.0;
float mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };

float xPos = 0, yPos = 0;


std::vector<void (*)()> scenes = {
    firstDisplay,
    secondDisplay,
    thirdDisplay,
    forthDisplay,
    fifthDisplay,
    sixthDisplay
};


void specialkeys(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) { con -= 2.0; };
    if (key == GLUT_KEY_RIGHT) { con += 2.0; };
    if (key == GLUT_KEY_UP) { tran -= 0.1; };
    if (key == GLUT_KEY_DOWN) { tran += 0.1; };
    if (key == GLUT_KEY_PAGE_UP) { sceneCounter += 1; };
    if (key == GLUT_KEY_PAGE_DOWN) { sceneCounter -= 1; };

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'a': // Клавиша 'A'
        xPos -= 0.03f;
        break;
    case 'd': // Клавиша 'D'
        xPos += 0.03f;
        break;
    case 'w': // Клавиша 'W'
        yPos += 0.03f;
        break;
    case 's': // Клавиша 'S'
        yPos -= 0.03f;
        break;
    case ' ': // Пробел
        commandCounter++;
        break;
    case '-':
        rot--;
        break;
    case '=':
        rot++;
        break;
    case 27:  // ASCII-код Esc
        exit(0); // Выход
        break;
    }
    glutPostRedisplay();
}


void materia(int c) {
    switch (c)
    {
    case 1: // diffuse and specular reflection; low shininess; no ambient
        glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
        glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
        break;
    case 2:  // diffuse and specular reflection; high shininess; no ambient
        glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
        break;
    case 3:
        // diffuse and specular reflection; high shininess; no ambient
        glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
        break;
    case 4:
        // diffuse reflection; emission; no ambient or specular reflection
        glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
        glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
        break;
    case 5:
        // ambient and diffuse reflection; no specular
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
        glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
        break;
    case 6:
        // ambient, diffuse and specular reflection; low shininess
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, 3);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
        break;
    case 7:
        // ambient, diffuse and specular reflection; high shininess
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
        break;
    case 8:
        // ambient and diffuse reflection; emission; no specular
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
        glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
        break;
    case 9:
        // colored ambient and diffuse reflection; no specular
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
        glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
        break;
    case 10:
        // colored ambient, diffuse and specular reflection; low shininess
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, low_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
        break;
    case 11:
        // colored ambient, diffuse and specular reflection; high shininess
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
        break;
    default:
        // colored ambient and diffuse reflection; emission; no specular
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
        glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
    }
}

void InitLight() {
    glShadeModel(GL_SMOOTH);
    glEnable(GL_AUTO_NORMAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

}

float sRad = 0.3;
float dist = 0.1;
int Count = 6;
int CountZ = 4;
float s = 0.8;
void (*displayFunc)() = nullptr;

void drawSceneRow() {
    glPushMatrix();
    glutSolidSphere(0.3, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1, 0, 0);
    glRotatef(30, 0.6, 0, 0);
    glutSolidSphere(0.3, 20, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1, 0, 0);
    glutSolidSphere(0.3, 20, 20);
    glPopMatrix();
}

void drawScene() {
    for (float i = -2; i <= 2; i += 1)
    {
        glPushMatrix();
            glTranslatef(0, i, 0);
            drawSceneRow();
        glPopMatrix();
    }
}

void firstDisplay() {
    glEnable(GL_LIGHT0);
    srand(time(0));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180);
    GLfloat light0_position[] = { 0.0, 0.0, 1.0, commandCounter % 2 };
    glPushMatrix();
    glTranslatef(0, 0, tran);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glPopMatrix();
    GLfloat light0_dir[] = { 0.0, 0.0, -1.0 ,0.0 };
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_dir);

    GLfloat light0_diffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);

    materia(2);

    drawScene();

    glutSwapBuffers();
}

void secondDisplay() {

    // переключение источника
    switch (commandCounter % 4)
    {
    case 0:
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        break;
    case 1:
        glEnable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        break;
    case 2:
        glEnable(GL_LIGHT1);
        glDisable(GL_LIGHT0);
        break;
    case 3:
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT0);
        break;
    default:
        break;
    }

    srand(time(0));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    GLfloat light0_position[] = { 0.5f, 0, 1, 0 };
    GLfloat light0_diffuse[] = { 1.0f, 0.2f, 0.2f, 1.0f }; // Красный

    GLfloat light1_position[] = { -0.5f, 0, 1, 0 };
    GLfloat light1_diffuse[] = { 0.2f, 1.0f, 0.2f, 1.0f }; // Зеленый
    GLfloat light1_specular[] = { 1, 1, 1, 1.0f }; // Зеленый

    glPushMatrix();
    glTranslatef(0, 0, tran);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glPopMatrix();
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);

    materia(2);

    drawScene();

    glutSwapBuffers();
}

void thirdDisplay() {
    glEnable(GL_LIGHT0);
    srand(time(0));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glPushMatrix();
    GLfloat light0_position[] = { 0, 0, 3.0, 1 };
    GLfloat light0_direction[] = { 0, 0, -1 };
    glTranslated(xPos, yPos, 0);
    glRotatef(rot, 0, 1, 0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_direction);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180);
    glPopMatrix();
    
    glPushMatrix();
    glTranslated(xPos, yPos, 3);
    glRotatef(rot, 0, 1, 0);
    glutSolidCube(0.5f);
    glPopMatrix();

    GLfloat light0_diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);

    materia(2);

    drawScene();

    glutSwapBuffers();
}

void forthDisplay() {

    // переключение источника
    switch (commandCounter % 4)
    {
    case 0:
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        break;
    case 1:
        glEnable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        break;
    case 2:
        glEnable(GL_LIGHT1);
        glDisable(GL_LIGHT0);
        break;
    case 3:
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT0);
        break;
    default:
        break;
    }

    srand(time(0));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 180);

    GLfloat light0_position[] = { 1, 0, 3, 1 };
    GLfloat light0_diffuse[] = { 1.0f, 0.2f, 0.2f, 1.0f }; // Красный

    GLfloat light1_position[] = { -1, 0, 3, 1 };
    GLfloat light1_diffuse[] = { 0.2f, 0.2f, 1.0f, 1.0f }; // Синий

    glPushMatrix();
    glTranslatef(0, 0, tran);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glPopMatrix();
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);

    materia(2);

    drawScene();

    glutSwapBuffers();
}

void fifthDisplay() {
    glEnable(GL_LIGHT0);
    srand(time(0));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180);

    GLfloat light0_diffuse[] = { 0, 0.6f, 0.4f, 1.0f };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);

    glPushMatrix();
    GLfloat light0_position[] = { 0.0, 0.0, 2.0, 1 };
    glRotatef(rot, 0, 1, 0);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glPopMatrix();

    glPushMatrix();
    glRotatef(rot, 0, 1, 0);
    glTranslatef(0, 0, 3);
    glutSolidCube(0.5f);
    glPopMatrix();

    materia(1);

    drawScene();

    glutSwapBuffers();
}

void sixthDisplay() {

    // переключение источника
    switch (commandCounter % 4)
    {
    case 0:
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        break;
    case 1:
        glEnable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        break;
    case 2:
        glEnable(GL_LIGHT1);
        glDisable(GL_LIGHT0);
        break;
    case 3:
        glDisable(GL_LIGHT1);
        glDisable(GL_LIGHT0);
        break;
    default:
        break;
    }

    srand(time(0));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, con);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, con);

    GLfloat light0_position[] = { 1, 0, 3, 1 };
    GLfloat light0_diffuse[] = { 1.0f, 0.2f, 0.2f, 1.0f };

    GLfloat light1_position[] = { -1, 0, 3, 1 };
    GLfloat light1_diffuse[] = { 0.2f, 0.2f, 1.0f, 1.0f };

    glPushMatrix();
    glTranslatef(0, 0, tran);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glPopMatrix();
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);

    materia(2);

    drawScene();

    glutSwapBuffers();
}


void Display() {
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
    int totalScenes = scenes.size();
    scenes[abs(sceneCounter) % totalScenes]();
}



void Initialize() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3.0, 3.0, -3.0, 3.0, -3.0, 3.0);               // Определяем границы рисования по горизонтали и вертикали
    //    glFrustum(-3.0, 3.0, -3.0, 3.0, 10.5, 15.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("Our first GLUT application!");
    glutDisplayFunc(Display);
    //	Определяем процедуру, отвечающую за обработку клавиш
    glutSpecialFunc(specialkeys);
    glutKeyboardFunc(keyboard);
    Initialize();
    InitLight();
    glutMainLoop();
    return 0;
}