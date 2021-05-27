#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <array>
#include "camera.h"
#include "square.h"
#include "piece.h"
#include "cycle.h"
#include "checkers.h"

const GLfloat light_ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
const GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat light_position[] = {2.0f, 5.0f, 5.0f, 0.0f};

const GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
const GLfloat mat_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
const GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
const GLfloat high_shininess[] = {100.0f};

CircularCamera cam = CircularCamera(16.0f, 12.0f);
bool mouseShiftMod = false;
float mouseSense = 0.25;
float mouseXOrg = -1;
float mouseYOrg = -1;

Checkers checkers = Checkers(2.0f);

static void idle(void);
static void resize(int width, int height);
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

static void keyboardCallback(unsigned char key, int x, int y) {
	switch (key) {
		case '=' :
            mouseSense += 0.01;
			break;
        case '-' :
            mouseSense -= 0.01;
            break;
        case 'a' :
            
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
}

static void mouseMoveCallback(int x, int y) {
    int deltaX = x - mouseXOrg;
    int deltaY = y - mouseYOrg;
    mouseXOrg = x;
    mouseYOrg = y;

    cam.translate(deltaX * mouseSense);
    if (mouseShiftMod)
        cam.changeHeight(deltaY * (mouseSense/2));
    else 
        cam.scaleRadius(-deltaY * (mouseSense/2));

    glutPostRedisplay();
}

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
	glLoadIdentity();

	// Set the camera
	gluLookAt(cam.get_posX(), cam.get_posY(), cam.get_posZ(),
			  0.0f, 0.0f,  0.0f,
		      0.0f, 1.0f,  0.0f);

    // Draw checkers board
    checkers.render();

    glutSwapBuffers();
}