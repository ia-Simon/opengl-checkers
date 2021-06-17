#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
// #include <windows.h>
#include <GL/glut.h>
#endif

#include <irrKlang.h>

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <array>
#include <vector>

const GLfloat light_ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
const GLfloat light_diffuse[] = {0.7f, 0.7f, 0.7f, 1.0f};
const GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat light_position[] = {2.0f, 5.0f, 5.0f, 0.0f};

const GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
const GLfloat mat_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
const GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat high_shininess[] = {100.0f};

std::array<GLuint,1> textures;

#include "camera.h"
#include "piece.h"
#include "square.h"
#include "selector.h"
#include "checkers.h"

Checkers checkers = Checkers(2.0f, 16.0f, 12.0f);
bool mouseShiftMod = false;
float mouseSense = 0.25;
float mouseXOrg = -1;
float mouseYOrg = -1;


static void idle(void);
static void resize(int width, int height);
static void loadTexture(GLuint &texture, const char *filename, int width, int height);
static void display(void);
static void keyboardCallback(unsigned char key, int x, int y);
static void mouseCallback(int button, int state, int x, int y);
static void mouseMoveCallback(int x, int y);
static void drawBoard(void);


int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("3D Checkers");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardCallback);
    glutMouseFunc(mouseCallback);
    glutMotionFunc(mouseMoveCallback);
    glutIdleFunc(idle);

    glClearColor(1, 1, 1, 1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);

    glGenTextures(textures.size(), textures.data());
    loadTexture(textures[0], "wood.bmp", 800, 800);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glutMainLoop();

    return EXIT_SUCCESS;
}

static void idle(void) {
    glutPostRedisplay();
}

static void resize(int width, int height) {
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void loadTexture(GLuint &texture, const char *filename, int width, int height) {
    unsigned char * data;
    FILE *file = fopen(filename, "rb");

    if (file == NULL)
        return;
    
    data = (unsigned char *) malloc(width * height * 3);
    fread(data, width * height * 3, 1, file);
    fclose(file);
    for(int i = 0; i < width * height; i++) {
        int index = i * 3;
        unsigned char B,R;
        B = data[index];
        R = data[index+2];

        data[index] = R;
        data[index+2] = B;
    }

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    free(data);
}

static void keyboardCallback(unsigned char key, int x, int y) {
	switch (key) {
		case '=' :
            mouseSense += 0.01;
			break;
        case '-' :
            mouseSense -= 0.01;
            break;
        case '[' :
            checkers.prevPiece();
            break;
        case ']' :
            checkers.nextPiece();
            break;
        case 'q' :
            checkers.movePiece(UP_LEFT);
            break;
        case 'e' :
            checkers.movePiece(UP_RIGHT);
            break;
        case 'z' :
            checkers.movePiece(DOWN_LEFT);
            break;
        case 'c' :
            checkers.movePiece(DOWN_RIGHT);
            break;
        case 's' :
            checkers.nextTurn();
            break;
        case 27 : //ESC
            exit(0);
	}

    glutPostRedisplay();
}

static void mouseCallback(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON) {
        if(state == GLUT_DOWN) {
            mouseXOrg = x;
            mouseYOrg = y;
            if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
                glutSetCursor(GLUT_CURSOR_UP_DOWN);
                mouseShiftMod = true;
            } else {
                glutSetCursor(GLUT_CURSOR_CYCLE);
                mouseShiftMod = false;
            }
        } else {
            glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
        }
    }

    glutPostRedisplay();
}

static void mouseMoveCallback(int x, int y) {
    int deltaX = x - mouseXOrg;
    int deltaY = y - mouseYOrg;
    mouseXOrg = x;
    mouseYOrg = y;

    checkers.cam.translate(deltaX * mouseSense);
    if (mouseShiftMod)
        checkers.cam.changeHeight(deltaY * (mouseSense/2));
    else 
        checkers.cam.scaleRadius(-deltaY * (mouseSense/2));

    glutPostRedisplay();
}

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
	glLoadIdentity();

	// Set the camera
	gluLookAt(checkers.cam.get_posX(), checkers.cam.get_posY(), checkers.cam.get_posZ(),
			  0.0f, 0.0f,  0.0f,
		      0.0f, 1.0f,  0.0f);

    // Draw checkers game
    checkers.render();

    glutSwapBuffers();
}