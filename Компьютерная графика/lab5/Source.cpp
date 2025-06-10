
#include <glut.h>
#include <iostream>
#include <vector>
#include <il.h>
#include "Source.h"
#pragma comment (lib,"DevIL.lib") 

const float a = 0.5f;
GLuint redBorderTexture;
GLuint cubeTextures[6];
GLuint MIPMAPtexture;
float tran = 0;
float con = 0;
int rot = 0, roty = 0;
int w = 350;
int sceneCounter, spaceCounter = 0;
std::vector<void (*)()> scenes = {
    //drawscene1Obj,
    //drawscene2Obj,
    //drawscene3Obj,
    //drawscene4Obj,
    //drawscene5Obj,
    drawscene1,
    drawscene2,
    drawscene3,
    drawscene4,
    drawscene5,
    drawscene6,
    drawscene7,
};

const char* myGluErrorString(GLenum err) {
    switch (err) {
    case GL_NO_ERROR: return "No error";
    case GL_INVALID_ENUM: return "Invalid enum";
    case GL_INVALID_VALUE: return "Invalid value";
    case GL_INVALID_OPERATION: return "Invalid operation";
    case GL_OUT_OF_MEMORY: return "Out of memory";
        // добавьте другие коды ошибок по мере необходимости
    default: return "Unknown error";
    }
}

void checkError() {
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << err << " - " << myGluErrorString(err) << std::endl;
    }
}

void processNormalKeys(unsigned char key, int x, int y) {
    if (key == ' ') {
        spaceCounter++;
    }
    if (key == 27)
        exit(0);
    glutPostRedisplay();
}

void specialkeys(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) { rot -= 1; };
    if (key == GLUT_KEY_RIGHT) { rot += 1; };
    if (key == GLUT_KEY_UP) { roty += 1; };
    if (key == GLUT_KEY_DOWN) { roty -= 1; };
    if (key == GLUT_KEY_PAGE_UP) { sceneCounter += 1; };
    if (key == GLUT_KEY_PAGE_DOWN) { sceneCounter -= 1; };
    glutPostRedisplay();
}

wchar_t FileName[] = L"128.bmp";

GLdouble ss[4] = { 0.25, 0, 0, 0.5 };
GLdouble tt[4] = { 0, 0.25, 0, 0.5 };

void disableObjectCoordinates() {
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
}

void configureTextureCoordinatesAsObject() {
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGendv(GL_S, GL_OBJECT_PLANE, ss);
    glTexGendv(GL_T, GL_OBJECT_PLANE, tt);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

GLuint loadTexture(const wchar_t fn[]) {
    ilInit();

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    if (!ilLoadImage(fn)) {
        printf("Ошибка загрузки текстуры: %ls\n", fn);
        return 0;
    }

    int width = ilGetInteger(IL_IMAGE_WIDTH);
    int height = ilGetInteger(IL_IMAGE_HEIGHT);
    int type = ilGetInteger(IL_IMAGE_TYPE);
    int fmt = ilGetInteger(IL_IMAGE_FORMAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        width,
        height,
        0,
        fmt,
        type,
        ilGetData()
    );

    return textureID;
}

GLuint MIPMAPloadTexture(std::vector<const wchar_t *> names) {
    ilInit();

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    for (int i = 0; i < names.size(); i++) {

        if (!ilLoadImage(names[i])) {
            printf("Ошибка загрузки текстуры: %ls\n", names[i]);
            return 0;
        }

        int width = ilGetInteger(IL_IMAGE_WIDTH);
        int height = ilGetInteger(IL_IMAGE_HEIGHT);
        int type = ilGetInteger(IL_IMAGE_TYPE);
        int fmt = ilGetInteger(IL_IMAGE_FORMAT);

        gluBuild2DMipmaps(
            GL_TEXTURE_2D,
            3,
            width,
            height,
            fmt,
            type,
            ilGetData()
        );
    }
    return textureID;
}


float dist = 0.1;
int Count = 6;
int CountZ = 4;
float s = 0.8;



void drawscene1() {
    glBindTexture(GL_TEXTURE_2D, redBorderTexture);
    glEnable(GL_TEXTURE_2D);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glTranslatef(0, 0, -12);
    
    glBegin(GL_POLYGON);
    glTexCoord2f(0,1);
    glVertex3f(-2, 2, 0);
    glTexCoord2f(0, 0);
    glVertex3f(-2, -2, 0);
    glTexCoord2f(1, 0);
    glVertex3f(2, -2, 0);
    glTexCoord2f(1, 1);
    glVertex3f(2, 2, 0);
    glEnd();

    glPopMatrix();
}

void drawscene1Obj() {
    glBindTexture(GL_TEXTURE_2D, redBorderTexture);

    GLdouble new_ss[4] = { 0.25, 0, 0, 0.5 };
    GLdouble new_tt[4] = { 0, 0.25, 0, 0.5 };
    memcpy(ss, new_ss, sizeof(ss));
    memcpy(tt, new_tt, sizeof(tt));

    configureTextureCoordinatesAsObject();
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0, 0, -12);

    glBegin(GL_POLYGON);
    glVertex3f(-2, 2, 0);
    glVertex3f(-2, -2, 0);
    glVertex3f(2, -2, 0);
    glVertex3f(2, 2, 0);
    glEnd();

    glPopMatrix();

    disableObjectCoordinates();
}

void drawscene2() {
    glBindTexture(GL_TEXTURE_2D, redBorderTexture);
    glEnable(GL_TEXTURE_2D);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0, 0, -12);

    glBegin(GL_POLYGON);
    glTexCoord2f(0, 2);
    glVertex3f(-2, 2, 0);
    glTexCoord2f(0, 0);
    glVertex3f(-2, -2, 0);
    glTexCoord2f(2, 0);
    glVertex3f(2, -2, 0);
    glTexCoord2f(2, 2);
    glVertex3f(2, 2, 0);
    glEnd();

    glPopMatrix();
}

void drawscene2Obj() {
    glBindTexture(GL_TEXTURE_2D, redBorderTexture);
    GLdouble new_ss[4] = { 0.5, 0, 0, 0 };
    GLdouble new_tt[4] = { 0, 0.5, 0, 0 };
    memcpy(ss, new_ss, sizeof(ss));
    memcpy(tt, new_tt, sizeof(tt));

    configureTextureCoordinatesAsObject();
    glEnable(GL_TEXTURE_2D);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0, 0, -12);

    glBegin(GL_POLYGON);
    glVertex3f(-2, 2, 0);
    glVertex3f(-2, -2, 0);
    glVertex3f(2, -2, 0);
    glVertex3f(2, 2, 0);
    glEnd();

    glPopMatrix();

    disableObjectCoordinates();
}

void drawscene3() {
    glBindTexture(GL_TEXTURE_2D, redBorderTexture);
    glEnable(GL_TEXTURE_2D);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0, 0, -12);

    glBegin(GL_POLYGON);
    glTexCoord2f(0, 4);
    glVertex3f(-2, 2, 0);
    glTexCoord2f(0, 0);
    glVertex3f(-2, -2, 0);
    glTexCoord2f(4, 0);
    glVertex3f(2, -2, 0);
    glTexCoord2f(4, 4);
    glVertex3f(2, 2, 0);
    glEnd();

    glPopMatrix();
}

void drawscene3Obj() {
    glBindTexture(GL_TEXTURE_2D, redBorderTexture);
    GLdouble new_ss[4] = { 1, 0, 0, 0 };
    GLdouble new_tt[4] = { 0, 1, 0, 0 };
    memcpy(ss, new_ss, sizeof(ss));
    memcpy(tt, new_tt, sizeof(tt));

    configureTextureCoordinatesAsObject();

    glEnable(GL_TEXTURE_2D);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0, 0, -12);

    glBegin(GL_POLYGON);
    glTexCoord2f(0, 4);
    glVertex3f(-2, 2, 0);
    glTexCoord2f(0, 0);
    glVertex3f(-2, -2, 0);
    glTexCoord2f(4, 0);
    glVertex3f(2, -2, 0);
    glTexCoord2f(4, 4);
    glVertex3f(2, 2, 0);
    glEnd();

    glPopMatrix();
    disableObjectCoordinates();
}

void drawscene4() {
    glBindTexture(GL_TEXTURE_2D, redBorderTexture);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0, 0, -12);
    glRotatef(rot, 0, 0, 1);

    glColor3f(0, 0, 0);
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_POLYGON);
    glVertex3f(-2, 2, 0);
    glVertex3f(-2, -2, 0);
    glVertex3f(2, -2, 0);
    glVertex3f(2, 2, 0);
    glEnd();
    glColor3f(1, 1, 1);

    glEnable(GL_TEXTURE_2D);
    glBegin(GL_POLYGON);
    glTexCoord2f(0, 1);
    glVertex3f(0, 2, 0);
    glTexCoord2f(0, 0);
    glVertex3f(-2, 0, 0);
    glTexCoord2f(1, 0);
    glVertex3f(0, -2, 0);
    glTexCoord2f(1, 1);
    glVertex3f(2, 0, 0);
    glEnd();


    glPopMatrix();
}
void drawscene4Obj() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0, 0, -12);
    glRotatef(rot, 0, 0, 1);

    glColor3f(0, 0, 0);
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_POLYGON);
    glVertex3f(-2, 2, 0);
    glVertex3f(-2, -2, 0);
    glVertex3f(2, -2, 0);
    glVertex3f(2, 2, 0);
    glEnd();
    glColor3f(1, 1, 1);

    glBindTexture(GL_TEXTURE_2D, redBorderTexture);
    GLdouble new_ss[4] = { 0.25, 0, 0, 0 };
    GLdouble new_tt[4] = { 0, 0.25, 0, 0 };
    memcpy(ss, new_ss, sizeof(ss));
    memcpy(tt, new_tt, sizeof(tt));

    configureTextureCoordinatesAsObject();

    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glTranslated(0.5, 0.5, 0);
    double scale = sqrt(2);
    glScaled(scale, scale, scale);
    glRotated(45, 0, 0, 1);

    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_TEXTURE_2D);
    glBegin(GL_POLYGON);
    glTexCoord2f(0, 1);
    glVertex3f(0, 2, 0);
    glTexCoord2f(0, 0);
    glVertex3f(-2, 0, 0);
    glTexCoord2f(1, 0);
    glVertex3f(0, -2, 0);
    glTexCoord2f(1, 1);
    glVertex3f(2, 0, 0);
    glEnd();

    glPopMatrix();

    disableObjectCoordinates();
    glMatrixMode(GL_TEXTURE);
    glPopMatrix();

}

void drawscene5() {
    glBindTexture(GL_TEXTURE_2D, redBorderTexture);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0, 0, -12);
    glRotatef(rot, 0, 0, 1);

    glColor3f(0, 0, 0);
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_POLYGON);
    glVertex3f(-2, 2, 0);
    glVertex3f(-2, -2, 0);
    glVertex3f(2, -2, 0);
    glVertex3f(2, 2, 0);
    glEnd();
    glColor3f(1, 1, 1);

    glEnable(GL_TEXTURE_2D);
    glBegin(GL_POLYGON);
    glTexCoord2f(0.5, 1);
    glVertex3f(0, 2, 0);
    glTexCoord2f(0, 0.5);
    glVertex3f(-2, 0, 0);
    glTexCoord2f(0.5, 0);
    glVertex3f(0, -2, 0);
    glTexCoord2f(1, 0.5);
    glVertex3f(2, 0, 0);
    glEnd();


    glPopMatrix();
}
void drawscene5Obj() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0, 0, -12);
    glRotatef(rot, 0, 0, 1);

    glColor3f(0, 0, 0);
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_POLYGON);
    glVertex3f(-2, 2, 0);
    glVertex3f(-2, -2, 0);
    glVertex3f(2, -2, 0);
    glVertex3f(2, 2, 0);
    glEnd();
    glColor3f(1, 1, 1);

    glBindTexture(GL_TEXTURE_2D, redBorderTexture);
    GLdouble new_ss[4] = { 0.25, 0, 0, 0.5 };
    GLdouble new_tt[4] = { 0, 0.25, 0, 0.5 };
    memcpy(ss, new_ss, sizeof(ss));
    memcpy(tt, new_tt, sizeof(tt));

    configureTextureCoordinatesAsObject();

    glEnable(GL_TEXTURE_2D);
    glBegin(GL_POLYGON);
    glTexCoord2f(0, 1);
    glVertex3f(0, 2, 0);
    glTexCoord2f(0, 0);
    glVertex3f(-2, 0, 0);
    glTexCoord2f(1, 0);
    glVertex3f(0, -2, 0);
    glTexCoord2f(1, 1);
    glVertex3f(2, 0, 0);
    glEnd();

    glPopMatrix();

    disableObjectCoordinates();
}

void drawCube() {
    glEnable(GL_DEPTH_TEST);

    configureTextureCoordinatesAsObject();

    glEnable(GL_TEXTURE_2D);

    GLdouble front_ss[4] = { 0.5, 0, 0, 0.5 };
    GLdouble front_tt[4] = { 0, 0.5, 0, 0.5 };
    glTexGendv(GL_S, GL_OBJECT_PLANE, front_ss);
    glTexGendv(GL_T, GL_OBJECT_PLANE, front_tt);

    glBindTexture(GL_TEXTURE_2D, cubeTextures[0]);
    // Передняя грань (Z = 1)
    glBegin(GL_QUADS);
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(-1, 1, 1);
    glEnd();

    // Задняя грань (Z = -1)
    glBindTexture(GL_TEXTURE_2D, cubeTextures[1]);
    glBegin(GL_QUADS);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, 1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(1, -1, -1);
    glEnd();

    GLdouble left_ss[4] = { 0, 0, 0.5, 0.5 };
    GLdouble left_tt[4] = { 0, 0.5, 0, 0.5 };
    glTexGendv(GL_S, GL_OBJECT_PLANE, left_ss);
    glTexGendv(GL_T, GL_OBJECT_PLANE, left_tt);

    // Левая грань (X = -1)
    glBindTexture(GL_TEXTURE_2D, cubeTextures[2]);
    glBegin(GL_QUADS);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, -1, 1);
    glVertex3f(-1, 1, 1);
    glVertex3f(-1, 1, -1);
    glEnd();

    // Правая грань (X = 1)
    glBindTexture(GL_TEXTURE_2D, cubeTextures[3]);
    glBegin(GL_QUADS);
    glVertex3f(1, -1, -1);
    glVertex3f(1, 1, -1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, -1, 1);
    glEnd();

    GLdouble top_ss[4] = { 0.5, 0, 0, 0.5 };
    GLdouble top_tt[4] = { 0, 0, 0.5, 0.5 };
    glTexGendv(GL_S, GL_OBJECT_PLANE, top_ss);
    glTexGendv(GL_T, GL_OBJECT_PLANE, top_tt);

    //// Верхняя грань (Y = 1)
    glBindTexture(GL_TEXTURE_2D, cubeTextures[4]);
    glBegin(GL_QUADS);
    glVertex3f(-1, 1, -1);
    glVertex3f(-1, 1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, -1);
    glEnd();

    //// Нижняя грань (Y = -1)
    glBindTexture(GL_TEXTURE_2D, cubeTextures[5]);
    glBegin(GL_QUADS);
    glVertex3f(-1, -1, -1);
    glVertex3f(1, -1, -1);
    glVertex3f(1, -1, 1);
    glVertex3f(-1, -1, 1);
    glEnd();

    disableObjectCoordinates();
    glDisable(GL_DEPTH_TEST);

}

void drawscene6() {
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0, 0, -13);
    glRotatef(rot * 3, 0, 1, 0);
    glRotatef(roty * 3, 1, 0, 0);

    drawCube();

    glPopMatrix();

}

void drawscene7() {

    /*GLdouble new_ss[4] = { 0.25, 0, 0, 0.5 };
    GLdouble new_tt[4] = { 0, 0.25, 0, 0.5 };
    memcpy(ss, new_ss, sizeof(ss));
    memcpy(tt, new_tt, sizeof(tt));
    configureTextureCoordinatesAsObject();*/
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, MIPMAPtexture);

    switch (spaceCounter % 5)
    {
    case 0:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        std::cout << "GL_LINEAR" << std::endl;
        break;
    case 1:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        std::cout << "GL_NEAREST_MIPMAP_NEAREST" << std::endl;
        break;
    case 2:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        std::cout << "GL_NEAREST_MIPMAP_LINEAR" << std::endl;
        break;
    case 3:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
        std::cout << "GL_LINEAR_MIPMAP_NEAREST" << std::endl;
        break;
    case 4:
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        std::cout << "GL_LINEAR_MIPMAP_LINEAR" << std::endl;
        break;
    default:
        break;
    }

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0, 0, rot*3-12);

    glBegin(GL_POLYGON);
    glTexCoord2f(0, 1);
    glVertex3f(-2, 2, 0);
    glTexCoord2f(0, 0);
    glVertex3f(-2, -2, 0);
    glTexCoord2f(1, 0);
    glVertex3f(2, -2, 0);
    glTexCoord2f(1, 1);
    glVertex3f(2, 2, 0);
    glEnd();

    glPopMatrix();

    disableObjectCoordinates();
}


void Display() {
    srand(time(0));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    int totalScenes = scenes.size();
    scenes[abs(sceneCounter) % totalScenes]();

    glutSwapBuffers();
}


void Initialize() {
    glClearColor(0.15, 0.15, 0.15, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    redBorderTexture = loadTexture(FileName);

    cubeTextures[0] = loadTexture(L"1.bmp");
    cubeTextures[1] = loadTexture(L"2.bmp");
    cubeTextures[2] = loadTexture(L"3.bmp");
    cubeTextures[3] = loadTexture(L"4.bmp");
    cubeTextures[4] = loadTexture(L"5.bmp");
    cubeTextures[5] = loadTexture(L"6.bmp");

    std::vector<const wchar_t*> names = {
        L"128.bmp",
    };

    MIPMAPtexture = MIPMAPloadTexture(names);

    //glOrtho(-10.0, 10.0, -10.0, 10.0, -20.0, 20.0);               // Определяем границы рисования по горизонтали и вертикали
    //glOrtho(-2, 2, -2, 2, -2, 2);
     glFrustum(-3.0, 3.0, -3.0, 3.0, 10.5, 400.0);
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
    glutKeyboardFunc(processNormalKeys);
    Initialize();
    glutMainLoop();
    return 0;
}