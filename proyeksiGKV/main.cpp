// Kasur3D_Difan.cpp
#include <GL/glut.h>
#include <cmath>
#include <iostream>

int projectionMode = 0;
float rotateX = 20.0f, rotateY = -30.0f;
float scale = 1.0f;

void drawAxis() {
    glLineWidth(2.0);
    glBegin(GL_LINES);
    // X - Merah
    glColor3f(1, 0, 0);
    glVertex3f(-5, 0, 0);
    glVertex3f(5, 0, 0);
    // Y - Hijau
    glColor3f(0, 1, 0);
    glVertex3f(0, -5, 0);
    glVertex3f(0, 5, 0);
    // Z - Biru
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, -5);
    glVertex3f(0, 0, 5);
    glEnd();
}

void drawKasur() {
    // Difan
    glColor3f(0.3f, 0.15f, 0.05f);
    glPushMatrix();
    glTranslatef(0.0f, -0.15f, 0.0f);
    glScalef(2.0f, 0.3f, 1.0f);
    glutSolidCube(1.0);
    glPopMatrix();

    // Kasur
    glColor3f(0.9f, 0.9f, 0.7f);
    glPushMatrix();
    glTranslatef(0.0f, 0.1f, 0.0f);
    glScalef(1.9f, 0.2f, 0.9f);
    glutSolidCube(1.0);
    glPopMatrix();

    // Bantal
    glColor3f(0.0f, 0.0f, 0.5f);
    glPushMatrix();
    glTranslatef(-0.4f, 0.25f, 0.0f);
    glScalef(0.5f, 0.1f, 0.3f);
    glutSolidCube(1.0);
    glPopMatrix();

    // Guling
    glColor3f(0.0f, 0.0f, 0.5f);
    glPushMatrix();
    glTranslatef(0.2f, 0.25f, 0.0f);
    glRotatef(90, 0, 1, 0);
    GLUquadric* quad = gluNewQuadric();
    gluCylinder(quad, 0.08, 0.08, 0.7, 20, 5);
    gluDisk(quad, 0.0, 0.08, 20, 1);
    glTranslatef(0.0f, 0.0f, 0.7f);
    gluDisk(quad, 0.0, 0.08, 20, 1);
    gluDeleteQuadric(quad);
    glPopMatrix();
}

void setCamera() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float dist = 4.0;
    if (projectionMode == 0) {
        gluPerspective(60.0, 1.0, 0.1, 100.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(dist, dist, dist, 0, 0, 0, 0, 1, 0);
    } else if (projectionMode >= 7) {
        gluPerspective(60.0, 1.0, 0.1, 100.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        if (projectionMode == 7)
            gluLookAt(0, 0, 6, 0, 0, 0, 0, 1, 0);
        else if (projectionMode == 8)
            gluLookAt(5, 0, 5, 0, 0, 0, 0, 1, 0);
        else if (projectionMode == 9)
            gluLookAt(5, 4, 5, 0, 0, 0, 0, 1, 0);
    } else {
        glOrtho(-3, 3, -3, 3, -10, 10);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        switch (projectionMode) {
            case 1: gluLookAt(0, 6, 0, 0, 0, 0, 0, 0, -1); break; // top
            case 2: gluLookAt(0, 0, 6, 0, 0, 0, 0, 1, 0); break; // front
            case 3: gluLookAt(6, 0, 0, 0, 0, 0, 0, 1, 0); break; // side
            case 4: gluLookAt(dist, dist, dist, 0, 0, 0, 0, 1, 0); break; // isometric
            case 5: gluLookAt(dist, dist * 0.7, dist, 0, 0, 0, 0, 1, 0); break; // dimetric
            case 6: gluLookAt(dist * 0.7, dist * 0.5, dist, 0, 0, 0, 0, 1, 0); break; // trimetric
        }
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    setCamera();
    glPushMatrix();
    if (projectionMode == 0)
        glRotatef(rotateX, 1, 0, 0), glRotatef(rotateY, 0, 1, 0);
    glScalef(scale, scale, scale);
    drawAxis();
    drawKasur();
    glPopMatrix();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w / (float)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '0': projectionMode = 0; break;
        case '1': projectionMode = 1; break;
        case '2': projectionMode = 2; break;
        case '3': projectionMode = 3; break;
        case '4': projectionMode = 4; break;
        case '5': projectionMode = 5; break;
        case '6': projectionMode = 6; break;
        case '7': projectionMode = 7; break;
        case '8': projectionMode = 8; break;
        case '9': projectionMode = 9; break;
        case 'w': rotateX += 5; break;
        case 's': rotateX -= 5; break;
        case 'a': rotateY -= 5; break;
        case 'd': rotateY += 5; break;
        case '+': scale += 0.1f; break;
        case '-': scale = std::max(0.1f, scale - 0.1f); break;
        case 27: exit(0);
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Kasur di Atas Difan 3D");
    glEnable(GL_DEPTH_TEST);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glClearColor(0.95f, 0.95f, 1.0f, 1.0f);
    glutMainLoop();
    return 0;
}

