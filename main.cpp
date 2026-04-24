#include <GL/glut.h>
#include <cmath>
#include <cstdlib>

float camHeight = 95.0f;
float camDist   = 120.0f;
float cloudMove = 0.0f;
float camAngleY = 0.0f;
const float PI = 3.14159265358979323846f;
int viewMode = 1;
float busPathPos1 = 0.0f;
float busPathPos2 = -220.0f;
float studentWalkPos = 0.0f;

void setColor(float r, float g, float b) {
    glColor3f(r, g, b);
}
void drawCube(float x, float y, float z,
float sx, float sy, float sz,
float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);
    setColor(r, g, b);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void drawSmallBush(float x, float z);

void drawStrokeText(float x, float y, float z,
float sx, float sy, float sz,
const char* text,
float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(sx, sy, sz);
    setColor(r, g, b);
    for (int i = 0; text[i] != '\0'; i++) {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
    }
    glPopMatrix();
}

void drawCylinderY(float x, float y, float z,
float radius, float height,
float r, float g, float b) {
    GLUquadric* q = gluNewQuadric();

    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(-90.0f, 1, 0, 0);
    setColor(r, g, b);
    gluCylinder(q, radius, radius, height, 32, 16);

    glPushMatrix();
    gluDisk(q, 0, radius, 32, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, height);
    gluDisk(q, 0, radius, 32, 1);
    glPopMatrix();

    glPopMatrix();
    gluDeleteQuadric(q);
}
void drawCylinderZ(float x, float y, float z,
float radius, float length,
float r, float g, float b) {
    GLUquadric* q = gluNewQuadric();
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(90.0f, 1, 0, 0);
    setColor(r, g, b);
    gluCylinder(q, radius, radius, length, 32, 16);
    glPushMatrix();
    gluDisk(q, 0, radius, 32, 1);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, 0, length);
    gluDisk(q, 0, radius, 32, 1);
    glPopMatrix();
    glPopMatrix();
    gluDeleteQuadric(q);
}
void drawInnovationLabBuilding() {

    float bx = 345.0f;
    float bz = 255.0f;
    glPushMatrix();
    glTranslatef(bx, 0.0f, bz);
    glRotatef(180.0f, 0, 1, 0);
    glTranslatef(-bx, 0.0f, -bz);

    for (float x = bx - 85; x <= bx + 85; x += 14) {
        for (float z = bz - 70; z <= bz + 30; z += 14) {
            if (((int)((x + z) / 14)) % 2 == 0)
            drawCube(x, 0.2f, z, 14, 0.4f, 14, 0.86f, 0.78f, 0.66f);
            else
            drawCube(x, 0.2f, z, 14, 0.4f, 14, 0.72f, 0.58f, 0.50f);
        }
    }

    drawCube(bx, 38, bz, 150, 76, 70, 0.92f, 0.93f, 0.92f);

    drawCube(bx, 12, bz, 148, 24, 68, 0.66f, 0.38f, 0.26f);

    drawCube(bx, 28, bz + 35.5f, 138, 52, 1.8f, 0.12f, 0.12f, 0.12f);
    drawCube(bx, 28, bz + 36.3f, 128, 48, 0.8f, 0.55f, 0.78f, 0.88f);

    drawCube(bx - 74.5f, 28, bz, 1.8f, 52, 64, 0.12f, 0.12f, 0.12f);
    drawCube(bx - 75.3f, 28, bz, 0.8f, 48, 58, 0.55f, 0.78f, 0.88f);

    for (float x = bx - 56; x <= bx + 56; x += 18) {
        drawCube(x, 28, bz + 36.0f, 1.5f, 50, 0.8f, 0.15f, 0.15f, 0.15f);
    }

    for (float z = bz - 22; z <= bz + 22; z += 16) {
        drawCube(bx - 75.0f, 28, z, 0.8f, 50, 1.5f, 0.15f, 0.15f, 0.15f);
    }

    float colors[6][3] = {
        {0.80f, 0.85f, 0.88f},
        {0.50f, 0.82f, 0.88f},
        {0.32f, 0.84f, 0.72f},
        {0.70f, 0.88f, 0.55f},
        {0.92f, 0.92f, 0.88f},
        {0.78f, 0.90f, 0.76f}
    };

    int ci = 0;
    for (float x = bx - 60; x <= bx + 60; x += 20) {
        drawCube(x, 72, bz + 35.8f, 18, 8, 2.0f,
        colors[ci][0], colors[ci][1], colors[ci][2]);
        ci = (ci + 1) % 6;
    }

    ci = 0;
    for (float z = bz - 20; z <= bz + 20; z += 16) {
        drawCube(bx - 75.0f, 72, z, 2.0f, 8, 14,
        colors[ci][0], colors[ci][1], colors[ci][2]);
        ci = (ci + 1) % 6;
    }

    for (float x = bx - 48; x <= bx + 48; x += 24) {
        drawCube(x, 36, bz + 36.8f, 12, 26, 0.7f, 0.90f, 0.90f, 0.90f);
    }

    for (float z = bz - 18; z <= bz + 18; z += 18) {
        drawCube(bx - 76.0f, 36, z, 0.7f, 26, 10, 0.90f, 0.90f, 0.90f);
    }

    drawCube(bx + 42, 12, bz + 36.9f, 20, 24, 0.8f, 0.16f, 0.16f, 0.16f);
    drawCube(bx + 42, 12, bz + 37.5f, 16, 22, 0.5f, 0.55f, 0.78f, 0.88f);

    drawCube(bx - 30, 15, bz + 34.8f, 4, 30, 4, 0.88f, 0.88f, 0.86f);
    drawCube(bx + 8,  15, bz + 34.8f, 4, 30, 4, 0.88f, 0.88f, 0.86f);
    drawCube(bx + 68, 15, bz + 34.8f, 4, 30, 4, 0.88f, 0.88f, 0.86f);

    drawCube(bx, 76, bz, 154, 3, 74, 0.18f, 0.18f, 0.18f);

    drawStrokeText(bx + 5, 60, bz + 38.5f,
    0.030f, 0.030f, 0.030f,
    "Innovation Lab", 0.90f, 0.18f, 1.0f);

    drawSmallBush(bx - 60, bz + 48);
    drawSmallBush(bx - 25, bz + 48);
    drawSmallBush(bx + 78, bz + 48);

    glPopMatrix();
}

void drawWestGate() {
    float gx = -360.0f;
    float gz = 40.0f;

    glPushMatrix();
    glTranslatef(gx, 0.0f, gz);
    glRotatef(90.0f, 0, 1, 0);

    drawCylinderY(0, 24, 0, 48.0f, 54.0f, 0.90f, 0.92f, 0.94f);

    drawCube(0, 22, 44.5f, 86, 34, 1.6f, 0.72f, 0.75f, 0.78f);
    drawCube(0, 22, 45.3f, 78, 30, 0.8f, 0.85f, 0.88f, 0.90f);

    drawCube(0, 10, 45.0f, 90, 4, 1.0f, 0.18f, 0.55f, 0.92f);
    drawCube(0, 22, 45.0f, 90, 4, 1.0f, 0.95f, 0.95f, 0.95f);
    drawCube(0, 34, 45.0f, 90, 4, 1.0f, 0.10f, 0.70f, 0.62f);

    drawCube(0, 52, 46.8f, 34, 12, 2.0f, 0.12f, 0.65f, 0.60f);

    drawStrokeText(-8, 50, 48.5f,
    0.090f, 0.090f, 0.090f,
    "DIU", 1.0f, 0.0f, 0.0f);

    drawCube(0, 69, 10, 54, 7, 20, 0.86f, 0.87f, 0.89f);
    drawStrokeText(-25, 66, 20,
    0.012f, 0.012f, 0.012f,
    "Daffodil International University",
    0.18f, 0.18f, 0.18f);

    drawCube(0, 7, 46.0f, 24, 14, 0.8f, 0.22f, 0.56f, 0.90f);

    drawCylinderY(-118, 18, 0, 24.0f, 48.0f, 0.90f, 0.92f, 0.94f);
    drawCube(-118, 18, 24.5f, 40, 26, 1.2f, 0.78f, 0.80f, 0.82f);
    drawCube(-118, 7, 25.0f, 42, 4, 1.0f, 0.18f, 0.55f, 0.92f);
    drawCube(-118, 19, 25.0f, 42, 4, 1.0f, 0.95f, 0.95f, 0.95f);
    drawCube(-118, 31, 25.0f, 42, 4, 1.0f, 0.10f, 0.70f, 0.62f);

    drawCylinderY(118, 18, 0, 24.0f, 48.0f, 0.90f, 0.92f, 0.94f);
    drawCube(118, 18, 24.5f, 40, 26, 1.2f, 0.78f, 0.80f, 0.82f);
    drawCube(118, 7, 25.0f, 42, 4, 1.0f, 0.18f, 0.55f, 0.92f);
    drawCube(118, 19, 25.0f, 42, 4, 1.0f, 0.95f, 0.95f, 0.95f);
    drawCube(118, 31, 25.0f, 42, 4, 1.0f, 0.10f, 0.70f, 0.62f);

    drawCube(-64, 61, 6, 102, 3.5f, 16, 0.10f, 0.70f, 0.62f);
    drawCube(-64, 57, 12, 98, 2.0f, 14, 0.18f, 0.55f, 0.92f);

    glPushMatrix();
    glTranslatef(-64, 63, -2);
    glRotatef(90, 0, 1, 0);
    drawCylinderZ(0, 0, 0, 7.0f, 102.0f, 0.10f, 0.70f, 0.62f);
    glPopMatrix();

    drawCube(-28, 44, 8, 3, 34, 3, 0.85f, 0.86f, 0.88f);

    drawCube(64, 61, 6, 102, 3.5f, 16, 0.10f, 0.70f, 0.62f);
    drawCube(64, 57, 12, 98, 2.0f, 14, 0.18f, 0.55f, 0.92f);
    glPushMatrix();
    glTranslatef(64, 63, -2);
    glRotatef(90, 0, 1, 0);
    drawCylinderZ(0, 0, 0, 7.0f, 102.0f, 0.10f, 0.70f, 0.62f);
    glPopMatrix();
    drawCube(28, 44, 8, 3, 34, 3, 0.85f, 0.86f, 0.88f);

    drawCube(0, 1.2f, 92, 176, 2.0f, 26, 0.96f, 0.96f, 0.96f);
    drawCube(0, 4.2f, 104, 158, 3.0f, 10, 0.92f, 0.20f, 0.18f);
    drawCube(0, 8.5f, 112, 146, 3.0f, 9, 0.96f, 0.96f, 0.96f);
    drawCube(0, 12.5f, 119, 134, 3.0f, 8, 0.92f, 0.20f, 0.18f);

    drawCube(0, 1, 134, 190, 2, 18, 0.40f, 0.68f, 0.28f);

    for (float x = -72; x <= 72; x += 24) {
        drawSmallBush(x, 82);
    }
    glPopMatrix();
}
void drawWheel(float x, float y, float z, float r) {
    glPushMatrix();
    glTranslatef(x, y, z);
    setColor(0.05f, 0.05f, 0.05f);
    glutSolidTorus(r * 0.35f, r, 18, 24);
    setColor(0.90f, 0.90f, 0.90f);
    glutSolidSphere(r * 0.35f, 14, 14);
    glPopMatrix();
}
void drawDIUBusModel() {

    drawCube(0, 12, 0, 64, 18, 20, 0.20f, 0.86f, 0.34f);

    drawCube(0, 23, 0, 60, 10, 19, 0.22f, 0.88f, 0.36f);

    drawCube(26, 17, 0, 12, 14, 19, 0.20f, 0.84f, 0.32f);

    drawCube(0, 22,  9.7f, 56, 9, 0.9f, 0.08f, 0.08f, 0.08f);
    for (float x = -20; x <= 16; x += 9) {
        drawCube(x, 22, 10.2f, 7, 7, 0.35f, 0.55f, 0.75f, 0.88f);
    }
    drawCube(18, 11, 10.3f, 8, 12, 0.35f, 0.85f, 0.92f, 0.95f);

    drawCube(0, 22, -9.7f, 56, 9, 0.9f, 0.08f, 0.08f, 0.08f);
    for (float x = -20; x <= 16; x += 9) {
        drawCube(x, 22, -10.2f, 7, 7, 0.35f, 0.55f, 0.75f, 0.88f);
    }
    drawCube(18, 11, -10.3f, 8, 12, 0.35f, 0.85f, 0.92f, 0.95f);

    setColor(0.12f, 0.72f, 0.28f);
    glPushMatrix(); glTranslatef(-18, 10,  10.5f); glutSolidSphere(2.8, 16, 16); glPopMatrix();
    glPushMatrix(); glTranslatef(-18, 10, -10.5f); glutSolidSphere(2.8, 16, 16); glPopMatrix();
    setColor(0.10f, 0.45f, 0.90f);
    glPushMatrix(); glTranslatef(-6,  9,  10.5f); glutSolidSphere(2.0, 16, 16); glPopMatrix();
    glPushMatrix(); glTranslatef(-6,  9, -10.5f); glutSolidSphere(2.0, 16, 16); glPopMatrix();
    setColor(0.85f, 0.20f, 0.18f);
    glPushMatrix(); glTranslatef(6,  11,  10.5f); glutSolidSphere(1.8, 16, 16); glPopMatrix();
    glPushMatrix(); glTranslatef(6,  11, -10.5f); glutSolidSphere(1.8, 16, 16); glPopMatrix();

    drawStrokeText(-8, 7.5f,  10.8f, 0.015f, 0.015f, 0.015f, "DIU", 1, 1, 1);
    drawStrokeText(-8, 7.5f, -10.8f, 0.015f, 0.015f, 0.015f, "DIU", 1, 1, 1);

    drawCube(0, 29, 0, 58, 1.4f, 18, 0.80f, 0.82f, 0.84f);

    drawCube(31, 8,  7.5f, 1.2f, 2.0f, 2.0f, 1.0f, 0.95f, 0.65f);
    drawCube(31, 8, -7.5f, 1.2f, 2.0f, 2.0f, 1.0f, 0.95f, 0.65f);

    drawCube(-31, 8,  7.5f, 1.2f, 2.0f, 2.0f, 0.95f, 0.10f, 0.10f);
    drawCube(-31, 8, -7.5f, 1.2f, 2.0f, 2.0f, 0.95f, 0.10f, 0.10f);

    drawWheel(-18, 3.5f,  9.5f, 4.2f);
    drawWheel( 18, 3.5f,  9.5f, 4.2f);
    drawWheel(-18, 3.5f, -9.5f, 4.2f);
    drawWheel( 18, 3.5f, -9.5f, 4.2f);
}
void drawAnimatedDIUBus(float t) {
    float x = 0.0f, z = 0.0f, angle = 0.0f;
    float total1 = 520.0f;
    float total2 = 270.0f;
    float total3 = 70.0f;
    float total  = total1 + total2 + total3;
    while (t < 0.0f)  t += total;
    while (t >= total) t -= total;

    if (t <= total1) {
        x = -260.0f + t;
        z = 190.0f;
        angle = 0.0f;
    }
    else if (t <= total1 + total2) {
        x = 260.0f;
        z = 190.0f - (t - total1);
        angle = -90.0f;
    }
    else {
        x = 260.0f + (t - total1 - total2);
        z = -80.0f;
        angle = 0.0f;
    }

    glPushMatrix();
    glTranslatef(x, 0.0f, z);
    glRotatef(angle, 0, 1, 0);
    drawDIUBusModel();
    glPopMatrix();
}

void drawWindowPanel(float x, float y, float z, float sx, float sy, float sz) {
    drawCube(x, y, z, sx + 1.2f, sy + 1.2f, sz + 0.18f, 0.08f, 0.08f, 0.08f);
    drawCube(x, y, z + 0.03f, sx + 0.25f, sy + 0.25f, sz + 0.06f, 0.92f, 0.93f, 0.95f);
    drawCube(x, y, z + 0.08f, sx * 0.82f, sy * 0.82f, sz, 0.10f, 0.45f, 0.92f);
}
void drawLineDDAXZ(float x1, float z1, float x2, float z2, float yLevel) {
    float dx = x2 - x1;
    float dz = z2 - z1;
    int steps = (fabs(dx) > fabs(dz)) ? (int)fabs(dx) : (int)fabs(dz);
    float xInc = dx / steps;
    float zInc = dz / steps;
    float x = x1;
    float z = z1;
    glDisable(GL_LIGHTING);
    glPointSize(2.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        glVertex3f(x, yLevel, z);
        x += xInc;
        z += zInc;
    }
    glEnd();

    glEnable(GL_LIGHTING);
}

void drawCircleMidpointXZ(float xc, float zc, float r, float yLevel) {
    int x = 0;
    int z = (int)r;
    int p = 1 - (int)r;

    glDisable(GL_LIGHTING);
    glPointSize(2.0f);

    glBegin(GL_POINTS);
    while (x <= z) {
        glVertex3f(xc + x, yLevel, zc + z);
        glVertex3f(xc - x, yLevel, zc + z);
        glVertex3f(xc + x, yLevel, zc - z);
        glVertex3f(xc - x, yLevel, zc - z);

        glVertex3f(xc + z, yLevel, zc + x);
        glVertex3f(xc - z, yLevel, zc + x);
        glVertex3f(xc + z, yLevel, zc - x);
        glVertex3f(xc - z, yLevel, zc - x);

        if (p < 0)
        p += 2 * x + 3;
        else {
            p += 2 * (x - z) + 5;
            z--;
        }
        x++;
    }
    glEnd();

    glEnable(GL_LIGHTING);
}

void init() {
    glClearColor(0.58f, 0.80f, 0.96f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    GLfloat lightPos[] = {180.0f, 260.0f, 220.0f, 1.0f};
    GLfloat ambient[]  = {0.35f, 0.35f, 0.35f, 1.0f};
    GLfloat diffuse[]  = {0.96f, 0.96f, 0.96f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
}

void drawGround() {
    drawCube(0, -1.0f, 0, 1400, 2, 1400, 0.22f, 0.64f, 0.18f);
}
void drawRoad(float x, float z, float sx, float sz) {
    drawCube(x, 0.05f, z, sx, 0.2f, sz, 0.82f, 0.74f, 0.66f);
}
void drawRoadMarksTopBottom(float z, float width) {
    for (float x = -width / 2 + 30; x <= width / 2 - 30; x += 34) {
        setColor(1,1,1);
        drawLineDDAXZ(x - 7, z, x + 7, z, 0.17f);
    }
}
void drawRoadMarksLeftRight(float x, float depth) {
    for (float z = -depth / 2 + 30; z <= depth / 2 - 30; z += 34) {
        drawLineDDAXZ(x, z - 7, x, z + 7, 0.17f);
    }
}
void drawFootballField() {
    float fx = 0.0f;
    float fz = 40.0f;
    float fw = 380.0f;
    float fd = 220.0f;
    drawCube(fx, 0.10f, fz, fw, 0.2f, fd, 0.30f, 0.68f, 0.25f);
    drawCube(fx, 0.20f, fz - fd / 2, fw, 0.02f, 1.2f, 1, 1, 1);
    drawCube(fx, 0.20f, fz + fd / 2, fw, 0.02f, 1.2f, 1, 1, 1);
    drawCube(fx - fw / 2, 0.20f, fz, 1.2f, 0.02f, fd, 1, 1, 1);
    drawCube(fx + fw / 2, 0.20f, fz, 1.2f, 0.02f, fd, 1, 1, 1);
    drawCube(fx, 0.20f, fz, 1.0f, 0.02f, fd, 1, 1, 1);
    glPushMatrix();
    glTranslatef(fx, 0.25f, fz);
    glRotatef(90, 1, 0, 0);
    setColor(1, 1, 1);
    glutWireTorus(0.08, 18.0, 20, 40);
    glPopMatrix();
    drawCube(fx - 155, 0.20f, fz, 1.0f, 0.02f, 70, 1, 1, 1);
    drawCube(fx - fw / 2, 0.20f, fz - 35, 70, 0.02f, 1.0f, 1, 1, 1);
    drawCube(fx - fw / 2, 0.20f, fz + 35, 70, 0.02f, 1.0f, 1, 1, 1);
    drawCube(fx + 155, 0.20f, fz, 1.0f, 0.02f, 70, 1, 1, 1);
    drawCube(fx + fw / 2, 0.20f, fz - 35, 70, 0.02f, 1.0f, 1, 1, 1);
    drawCube(fx + fw / 2, 0.20f, fz + 35, 70, 0.02f, 1.0f, 1, 1, 1);
    drawCube(fx - fw / 2 - 10, 7, fz, 1.0f, 14, 32, 1, 1, 1);
    drawCube(fx + fw / 2 + 10, 7, fz, 1.0f, 14, 32, 1, 1, 1);
    setColor(1,1,1);
    drawCircleMidpointXZ(0, 40, 18, 0.22f);
}
void drawRoadAroundField() {
    float width = 470.0f;
    float depth = 300.0f;
    float cz = 40.0f;
    drawRoad(0, cz - depth / 2, width, 18);
    drawRoad(0, cz + depth / 2, width, 18);
    drawRoad(-width / 2, cz, 18, depth);
    drawRoad(width / 2, cz, 18, depth);
    drawRoadMarksTopBottom(cz - depth / 2, width);
    drawRoadMarksTopBottom(cz + depth / 2, width);
    drawRoadMarksLeftRight(-width / 2, depth);
    drawRoadMarksLeftRight(width / 2, depth);
    drawRoad(295, -80, 90, 18);
}
void drawSmallBush(float x, float z) {
    glPushMatrix();
    glTranslatef(x, 3.2f, z);
    setColor(0.08f, 0.45f, 0.10f);
    glutSolidSphere(4.2, 16, 16);
    glTranslatef(-2.5f, -0.4f, 0.8f);
    glutSolidSphere(3.3, 16, 16);
    glTranslatef(5.0f, 0.0f, -0.8f);
    glutSolidSphere(3.4f, 16, 16);
    glPopMatrix();
}
void drawBushBorder() {
    for (float x = -160; x <= 160; x += 20) drawSmallBush(x, 155);
    for (float z = -40; z <= 120; z += 22) drawSmallBush(-205, z);
    for (float z = -40; z <= 120; z += 22) drawSmallBush(205, z);
    for (float x = -150; x <= 150; x += 22) drawSmallBush(x, -85);
}

void drawMainBuilding() {
    drawCube(-35, 96, -255, 130, 192, 44, 0.95f, 0.95f, 0.95f);
    for (float y = 18; y <= 170; y += 18) {
        drawCube(-35, y, -231.8f, 126, 1.2f, 1.0f, 0.82f, 0.82f, 0.82f);
    }
    for (float y = 28; y <= 160; y += 18) {
        for (float x = -78; x <= 8; x += 22) {
            drawWindowPanel(x, y, -230.5f, 14, 10, 0.55f);
        }
    }
    drawCube(-78, 182, -255, 18, 24, 44, 0.95f, 0.95f, 0.95f);
    drawCube(8,   182, -255, 18, 24, 44, 0.95f, 0.95f, 0.95f);
    drawCube(-35, 194, -255, 88, 4, 12, 0.95f, 0.95f, 0.95f);
    for (int i = 0; i < 7; i++) {
        float yy = 22 + i * 20;
        drawCylinderY(42, yy, -232.5f, 10.5f, 14.0f, 0.88f, 0.90f, 0.94f);
        drawCylinderY(42, yy + 0.3f, -231.8f, 8.2f, 13.4f, 0.10f, 0.45f, 0.92f);
    }

    drawCube(30, 90, -232.5f, 3.0f, 180, 1.0f, 0.86f, 0.88f, 0.92f);
    drawCube(54, 90, -232.5f, 3.0f, 180, 1.0f, 0.86f, 0.88f, 0.92f);

    glPushMatrix();
    glTranslatef(128, 92, -255);
    glRotatef(-8.0f, 0, 1, 0);

    drawCube(0, 0, 0, 165, 184, 44, 0.95f, 0.95f, 0.95f);

    for (float y = 18; y <= 166; y += 18) {
        drawCube(0, y - 92, 23.2f, 160, 1.2f, 1.0f, 0.82f, 0.82f, 0.82f);
    }

    for (float y = -64; y <= 66; y += 18) {
        for (float x = -56; x <= 56; x += 24) {
            drawWindowPanel(x, y, 24.0f, 16, 10, 0.55f);
        }
    }

    drawCube(82, 0, 7, 8, 184, 28, 0.82f, 0.82f, 0.84f);

    drawCube(20, 76, 26.5f, 150, 18, 4.0f, 0.10f, 0.30f, 0.75f);
    drawStrokeText(-52, 68.0f, 29.0f,
    0.075f, 0.075f, 0.075f,
    "Daffodil International University",
    1.0f, 1.0f, 1.0f);

    glPopMatrix();

    drawCube(92, 36, -188, 122, 72, 52, 0.95f, 0.95f, 0.95f);
    drawCylinderY(92, 72, -188, 70.0f, 5.0f, 0.58f, 0.30f, 0.12f);

    for (float x = 46; x <= 138; x += 23) {
        drawCube(x, 32, -161.5f, 4.0f, 64, 2.5f, 0.92f, 0.92f, 0.92f);
    }

    drawCube(92, 28, -160.0f, 94, 58, 1.6f, 0.12f, 0.12f, 0.12f);
    drawCube(92, 28, -158.8f, 84, 54, 1.0f, 0.10f, 0.45f, 0.90f);

    for (float x = 62; x <= 122; x += 15) {
        drawCube(x, 28, -158.0f, 1.5f, 56, 0.8f, 0.90f, 0.90f, 0.90f);
    }

    drawCube(92, 15, -145.5f, 70, 1.8f, 10, 0.55f, 0.28f, 0.12f);

    for (float x = 56; x <= 128; x += 18) {
        glPushMatrix();
        glTranslatef(x, 10.0f, -148.0f);
        glRotatef(-28.0f, 1, 0, 0);
        glScalef(1.0f, 10.0f, 1.0f);
        setColor(0.55f, 0.28f, 0.12f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }

    for (int i = 0; i < 6; i++) {
        drawCube(92, 0.7f + i * 0.55f, -136 + i * -2.6f,
        70 - i * 6, 0.40f, 2.3f,
        0.76f, 0.60f, 0.50f);
    }

    drawCube(145, 1, -130, 118, 2, 34, 0.45f, 0.68f, 0.28f);
    drawCube(25,  1, -130, 100, 2, 34, 0.45f, 0.68f, 0.28f);
}

void drawRoundTree(float x, float z) {
    drawCube(x, 15, z, 3, 30, 3, 0.28f, 0.15f, 0.07f);

    glPushMatrix();
    glTranslatef(x, 38, z);
    setColor(0.06f, 0.42f, 0.10f);
    glutSolidSphere(12, 20, 20);
    glTranslatef(-8, -1, 2);
    glutSolidSphere(9, 20, 20);
    glTranslatef(16, 0, -2);
    glutSolidSphere(9, 20, 20);
    glPopMatrix();
}
void drawBigTree(float x, float z) {

    drawCube(x, 20, z, 6, 40, 6, 0.36f, 0.20f, 0.08f);

    glPushMatrix();
    glTranslatef(x, 52, z);
    setColor(0.05f, 0.42f, 0.08f);
    glutSolidSphere(18, 24, 24);
    glTranslatef(-12, 2, 4);
    glutSolidSphere(14, 22, 22);
    glTranslatef(24, 0, -5);
    glutSolidSphere(15, 22, 22);
    glTranslatef(-6, 10, 0);
    glutSolidSphere(13, 22, 22);
    glPopMatrix();
}
void drawSwimmingPoolArea() {

    float px = -250.0f;
    float pz = -385.0f;

    drawCube(px, 0.35f, pz, 120, 0.7f, 68, 0.92f, 0.95f, 0.97f);

    drawCube(px, 0.55f, pz, 108, 0.4f, 56, 0.12f, 0.58f, 0.92f);

    for (float lx = px - 32; lx <= px + 32; lx += 16) {
        drawCube(lx, 0.78f, pz, 1.2f, 0.05f, 52, 0.95f, 0.95f, 0.95f);
    }

    drawCube(px, 0.20f, pz + 46, 132, 0.3f, 14, 0.80f, 0.78f, 0.74f);
    drawCube(px, 0.20f, pz - 46, 132, 0.3f, 14, 0.80f, 0.78f, 0.74f);
    drawCube(px - 66, 0.20f, pz, 14, 0.3f, 82, 0.80f, 0.78f, 0.74f);
    drawCube(px + 66, 0.20f, pz, 14, 0.3f, 82, 0.80f, 0.78f, 0.74f);

    drawCube(px + 44, 1.2f, pz - 20, 18, 1.2f, 8, 0.72f, 0.72f, 0.74f);

    drawSmallBush(px - 78, pz - 34);
    drawSmallBush(px - 78, pz + 34);
    drawSmallBush(px + 78, pz - 34);
    drawSmallBush(px + 78, pz + 34);
}
void drawMainBuildingLeftSideExtras() {

    drawCube(-210, 1, -210, 220, 2, 170, 0.42f, 0.68f, 0.30f);

    drawSwimmingPoolArea();

    drawBigTree(-315, -300);
    drawBigTree(-285, -245);
    drawBigTree(-300, -165);
    drawBigTree(-240, -320);
    drawBigTree(-145, -320);
    drawBigTree(-120, -140);
}
void drawSouthSideOppositeBuilding() {

    float bx = -255.0f;
    float bz = 250.0f;

    drawCube(bx, 1.0f, bz, 170, 2, 90, 0.82f, 0.74f, 0.62f);

    drawCube(bx, 22, bz, 120, 44, 34, 0.80f, 0.82f, 0.84f);

    for (float x = bx - 46; x <= bx + 46; x += 18) {
        drawCube(x, 38, bz - 16.8f, 14, 10, 2.0f, 0.18f, 0.72f, 0.20f);
    }

    glPushMatrix();
    glTranslatef(bx + 18, 48, bz - 8);
    glRotatef(-18.0f, 0, 0, 1);
    glScalef(110.0f, 10.0f, 26.0f);
    setColor(0.02f, 0.34f, 0.08f);
    glutSolidCube(1.0f);
    glPopMatrix();

    drawCube(bx - 18, 16, bz + 17.6f, 16, 24, 1.5f, 0.18f, 0.72f, 0.78f);
    drawCube(bx + 8,  16, bz + 17.6f, 16, 24, 1.5f, 0.18f, 0.72f, 0.78f);

    drawCube(bx - 58, 10, bz + 8, 16, 20, 12, 0.80f, 0.08f, 0.08f);

    drawCube(bx + 70, 12, bz + 4, 34, 24, 24, 0.72f, 0.94f, 0.72f);
    drawCube(bx + 70, 12, bz + 16.5f, 12, 16, 1.2f, 0.95f, 0.95f, 0.95f);

    drawCube(bx, 1.2f, bz + 34, 170, 2, 16, 0.90f, 0.82f, 0.70f);

    drawSmallBush(bx - 62, bz + 40);
    drawSmallBush(bx - 20, bz + 40);
    drawSmallBush(bx + 18, bz + 40);
    drawSmallBush(bx + 58, bz + 40);

    drawCube(bx + 30, 22, bz + 14, 5, 44, 5, 0.35f, 0.20f, 0.08f);
    glPushMatrix();
    glTranslatef(bx + 30, 52, bz + 14);
    setColor(0.02f, 0.30f, 0.05f);
    glutSolidCone(28, 34, 4, 4);
    glTranslatef(0, 10, 0);
    glutSolidCone(22, 28, 4, 4);
    glPopMatrix();
    drawCube(bx + 50, 18, bz + 2, 4, 36, 4, 0.35f, 0.20f, 0.08f);
    glPushMatrix();
    glTranslatef(bx + 50, 42, bz + 2);
    setColor(0.08f, 0.55f, 0.10f);
    glutSolidSphere(16, 20, 20);
    glPopMatrix();
}
void drawSouthFrontRoad() {

    float rx = -40.0f;
    float rz = 255.0f;
    drawRoad(rx, rz - 110.0f, 22, 240);
    drawRoadMarksLeftRight(rx, 220);

    drawRoad(0.0f, 190.0f, 120, 18);
}
void drawNorthSideTrees() {
    for (float z = -70; z <= 70; z += 26) {
        drawRoundTree(320, z);
        drawRoundTree(350, z + 8);
        drawRoundTree(380, z + 16);
    }
    for (float x = -30; x <= 260; x += 55) {
        drawRoundTree(x, -345);
    }
}

void drawSouthBuilding() {
    float bx = 165.0f;
    float bz = 255.0f;
    glPushMatrix();
    glTranslatef(bx, 0.0f, bz);

    drawCube(70, 62, 0, 44, 124, 26, 0.95f, 0.95f, 0.95f);
    drawCube(84, 62, -13.5f, 16, 124, 0.8f, 0.38f, 0.05f, 0.05f);
    for (float y = 18; y <= 106; y += 14) {
        drawWindowPanel(84, y, -14.2f, 7, 8, 0.3f);
    }

    drawCube(0, 46, 0, 118, 92, 26, 0.95f, 0.95f, 0.95f);

    for (float y = 16; y <= 74; y += 18) {
        drawCube(0, y, -13.4f, 116, 1.8f, 0.6f, 1.0f, 1.0f, 1.0f);
        drawCube(0, y + 7, -13.0f, 108, 12, 0.8f, 0.82f, 0.05f, 0.08f);
    }

    drawCube(34, 42, -13.8f, 7, 84, 0.8f, 0.12f, 0.62f, 0.70f);

    drawCube(-72, 34, -2, 56, 68, 24, 0.95f, 0.95f, 0.95f);
    drawCube(-118, 24, -6, 40, 48, 22, 0.95f, 0.95f, 0.95f);

    for (float y = 16; y <= 52; y += 18) {
        drawCube(-72, y, -14.0f, 52, 1.6f, 0.6f, 1.0f, 1.0f, 1.0f);
        drawCube(-72, y + 7, -13.5f, 48, 12, 0.8f, 0.82f, 0.05f, 0.08f);
    }

    for (float y = 16; y <= 34; y += 18) {
        drawCube(-118, y, -16.0f, 36, 1.6f, 0.6f, 1.0f, 1.0f, 1.0f);
        drawCube(-118, y + 7, -15.5f, 32, 12, 0.8f, 0.82f, 0.05f, 0.08f);
    }

    glPopMatrix();

    drawCube(bx, 1, bz - 36, 170, 2, 24, 0.40f, 0.68f, 0.28f);
}

void drawSouthMosque() {
    float mx = -95.0f;
    float mz = 248.0f;

    glPushMatrix();
    glTranslatef(mx, 0, mz);
    setColor(0.80f, 0.80f, 0.80f);
    glBegin(GL_QUADS);

    glVertex3f(-42, 0, -14);
    glVertex3f( 42, 0, -14);
    glVertex3f( 30, 44, -14);
    glVertex3f(-30, 44, -14);

    glVertex3f(-42, 0, 14);
    glVertex3f( 42, 0, 14);
    glVertex3f( 30, 44, 14);
    glVertex3f(-30, 44, 14);

    glVertex3f(-42, 0, -14);
    glVertex3f(-42, 0, 14);
    glVertex3f(-30, 44, 14);
    glVertex3f(-30, 44, -14);

    glVertex3f(42, 0, -14);
    glVertex3f(42, 0, 14);
    glVertex3f(30, 44, 14);
    glVertex3f(30, 44, -14);

    glVertex3f(-30, 44, -14);
    glVertex3f( 30, 44, -14);
    glVertex3f( 30, 44, 14);
    glVertex3f(-30, 44, 14);
    glEnd();
    glPopMatrix();

    drawCube(mx, 48, mz, 98, 5, 30, 0.88f, 0.88f, 0.88f);
    drawCube(mx, 36, mz - 14.5f, 34, 3, 1.0f, 0.06f, 0.06f, 0.06f);
    drawCube(mx, 18, mz - 14.8f, 28, 28, 1.2f, 0.62f, 0.16f, 0.12f);
    drawCube(mx, 12, mz - 15.6f, 12, 18, 0.6f, 0.95f, 0.95f, 0.90f);

    glPushMatrix();
    glTranslatef(mx, 11, mz - 16.2f);
    setColor(0.08f, 0.60f, 0.68f);
    glBegin(GL_POLYGON);
    glVertex3f(-4, -4, 0);
    glVertex3f(-4,  1, 0);
    glVertex3f( 0,  7, 0);
    glVertex3f( 4,  1, 0);
    glVertex3f( 4, -4, 0);
    glEnd();
    glPopMatrix();

    drawCube(mx, 1, mz - 36, 90, 2, 22, 0.40f, 0.68f, 0.28f);
}

void drawCloud(float x, float y, float z, float s) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glScalef(s, s, s);

    setColor(1, 1, 1);
    glutSolidSphere(7.0, 18, 18);
    glTranslatef(7, 1.5f, 0);
    glutSolidSphere(8.0, 18, 18);
    glTranslatef(7, -0.5f, 0);
    glutSolidSphere(7.0, 18, 18);
    glTranslatef(-18, -0.5f, 0);
    glutSolidSphere(6.0, 18, 18);

    glPopMatrix();
}

void drawClouds() {

    drawCloud(-360 + cloudMove * 0.5f, 320, -300, 1.2f);
    drawCloud(-80  + cloudMove * 0.8f, 305, -320, 1.0f);
    drawCloud(180  + cloudMove * 0.6f, 318, -305, 1.1f);
    drawCloud(380  + cloudMove * 0.7f, 298, -330, 0.95f);

    drawCloud(-260 + cloudMove * 0.35f, 290, 180, 0.95f);
    drawCloud(-20  + cloudMove * 0.45f, 310, 210, 1.05f);
    drawCloud(220  + cloudMove * 0.30f, 295, 185, 0.90f);
}

void drawWalkingStudent(float x, float z,
float shirtR, float shirtG, float shirtB,
float bagR, float bagG, float bagB,
bool stepForward) {
    glPushMatrix();
    glTranslatef(x, 0.0f, z);

    glPushMatrix();
    glTranslatef(0, 10.5f, 0);
    setColor(0.90f, 0.76f, 0.64f);
    glutSolidSphere(1.7, 16, 16);
    glPopMatrix();

    drawCube(0, 6.6f, 0, 3.2f, 5.8f, 2.0f, shirtR, shirtG, shirtB);

    drawCube(0, 8.7f, 0, 0.8f, 1.0f, 0.8f, 0.90f, 0.76f, 0.64f);

    drawCube(-1.8f, 6.4f, -1.6f, 2.2f, 3.8f, 1.2f, bagR, bagG, bagB);

    drawCube(-0.9f, 7.2f, -1.0f, 0.25f, 3.5f, 0.25f, 0.15f, 0.15f, 0.15f);
    drawCube( 0.9f, 7.2f, -1.0f, 0.25f, 3.5f, 0.25f, 0.15f, 0.15f, 0.15f);

    if (!stepForward) {
        drawCube(-2.2f, 6.3f, 0, 0.8f, 4.2f, 0.8f, 0.90f, 0.76f, 0.64f);
        drawCube( 2.2f, 6.0f, 0, 0.8f, 4.2f, 0.8f, 0.90f, 0.76f, 0.64f);

        drawCube(-0.9f, 2.8f, 0, 1.0f, 5.6f, 1.0f, 0.12f, 0.12f, 0.35f);
        drawCube( 0.9f, 2.4f, 0, 1.0f, 5.0f, 1.0f, 0.12f, 0.12f, 0.35f);
    } else {
        drawCube(-2.2f, 6.0f, 0, 0.8f, 4.2f, 0.8f, 0.90f, 0.76f, 0.64f);
        drawCube( 2.2f, 6.4f, 0, 0.8f, 4.2f, 0.8f, 0.90f, 0.76f, 0.64f);

        drawCube(-0.9f, 2.4f, 0, 1.0f, 5.0f, 1.0f, 0.12f, 0.12f, 0.35f);
        drawCube( 0.9f, 2.8f, 0, 1.0f, 5.6f, 1.0f, 0.12f, 0.12f, 0.35f);
    }

    glPopMatrix();
}

void drawStudentsGoingToMainBuilding() {
    float s = studentWalkPos;

    drawWalkingStudent(20 + s, -118 - s * 0.45f,
    0.85f, 0.20f, 0.20f,
    0.10f, 0.10f, 0.10f,
    ((int)(s / 8) % 2 == 0));

    drawWalkingStudent(35 + s * 0.9f, -126 - s * 0.40f,
    0.15f, 0.45f, 0.90f,
    0.20f, 0.20f, 0.20f,
    ((int)(s / 8 + 1) % 2 == 0));

    drawWalkingStudent(52 + s * 0.8f, -134 - s * 0.35f,
    0.20f, 0.70f, 0.30f,
    0.35f, 0.20f, 0.10f,
    ((int)(s / 8) % 2 == 0));

    drawWalkingStudent(68 + s * 0.7f, -142 - s * 0.30f,
    0.90f, 0.55f, 0.15f,
    0.12f, 0.12f, 0.35f,
    ((int)(s / 8 + 1) % 2 == 0));

    drawWalkingStudent(84 + s * 0.6f, -150 - s * 0.28f,
    0.55f, 0.20f, 0.75f,
    0.18f, 0.18f, 0.18f,
    ((int)(s / 8) % 2 == 0));

    drawWalkingStudent(5 + s * 0.75f, -132 - s * 0.38f,
    0.20f, 0.75f, 0.75f,
    0.40f, 0.10f, 0.10f,
    ((int)(s / 8 + 1) % 2 == 0));
}

void drawCricketStumps(float x, float y, float z) {
    for (float sx = -1.0f; sx <= 1.0f; sx += 1.0f) {
        drawCube(x + sx, y + 3.0f, z, 0.2f, 6.0f, 0.2f, 0.95f, 0.92f, 0.80f);
    }
    drawCube(x - 0.5f, y + 6.2f, z, 1.2f, 0.25f, 0.25f, 0.95f, 0.92f, 0.80f);
    drawCube(x + 0.5f, y + 6.2f, z, 1.2f, 0.25f, 0.25f, 0.95f, 0.92f, 0.80f);
}
void drawCricketGround() {
    float cx = 330.0f;
    float cz = -185.0f;

    drawCube(cx, 0.12f, cz, 210, 0.25f, 170, 0.28f, 0.68f, 0.22f);

    drawCube(cx, 0.35f, cz, 54, 0.3f, 5.5f, 0.88f, 0.82f, 0.66f);

    drawCricketStumps(cx - 22, 0.35f, cz);
    drawCricketStumps(cx + 22, 0.35f, cz);
}

void drawPracticeNet(float x, float z) {
    glPushMatrix();
    glTranslatef(x, 0.0f, z);

    drawCube(0, 0.3f, 0, 34, 0.4f, 10, 0.55f, 0.72f, 0.38f);

    drawCube(0, 0.5f, 0, 26, 0.2f, 3.2f, 0.88f, 0.82f, 0.66f);

    drawCube(-16, 7, -4.5f, 0.7f, 14, 0.7f, 0.95f, 0.95f, 0.95f);
    drawCube( 16, 7, -4.5f, 0.7f, 14, 0.7f, 0.95f, 0.95f, 0.95f);
    drawCube(-16, 7,  4.5f, 0.7f, 14, 0.7f, 0.95f, 0.95f, 0.95f);
    drawCube( 16, 7,  4.5f, 0.7f, 14, 0.7f, 0.95f, 0.95f, 0.95f);

    drawCube(0, 14, -4.5f, 34, 0.5f, 0.5f, 0.95f, 0.95f, 0.95f);
    drawCube(0, 14,  4.5f, 34, 0.5f, 0.5f, 0.95f, 0.95f, 0.95f);
    drawCube(-16, 14, 0, 0.5f, 0.5f, 10, 0.95f, 0.95f, 0.95f);
    drawCube( 16, 14, 0, 0.5f, 0.5f, 10, 0.95f, 0.95f, 0.95f);

    drawCube(16, 7, 0, 0.18f, 14, 9, 0.90f, 0.92f, 0.90f);
    drawCube(0,  7, -4.5f, 32, 14, 0.18f, 0.90f, 0.92f, 0.90f);
    drawCube(0,  7,  4.5f, 32, 14, 0.18f, 0.90f, 0.92f, 0.90f);

    drawCricketStumps(13,  0.5f, 0);
    drawCricketStumps(-13, 0.5f, 0);
    glPopMatrix();
}

void drawBikeParkingShed(float x, float z) {
    glPushMatrix();
    glTranslatef(x, 0.0f, z);

    drawCube(0, 0.4f, 0, 120, 0.6f, 40, 0.78f, 0.76f, 0.72f);

    for (float bx = -52; bx <= 52; bx += 26) {
        drawCube(bx, 10, -18, 2.0f, 20, 2.0f, 0.55f, 0.55f, 0.58f);
        drawCube(bx, 10,   0, 2.0f, 20, 2.0f, 0.55f, 0.55f, 0.58f);
        drawCube(bx, 10,  18, 2.0f, 20, 2.0f, 0.55f, 0.55f, 0.58f);
    }

    drawCube(0, 21, 0, 126, 2.0f, 46, 0.15f, 0.45f, 0.80f);

    glPushMatrix();
    glTranslatef(0, 20.2f, 25);
    glRotatef(12.0f, 1, 0, 0);
    drawCube(0, 0, 0, 126, 1.0f, 10, 0.15f, 0.45f, 0.80f);
    glPopMatrix();

    for (float bx = -48; bx <= 48; bx += 10) {

        drawCube(bx, 4, -8, 1.0f, 4, 6, 0.15f, 0.15f, 0.18f);
        glPushMatrix();
        glTranslatef(bx, 3, -11);
        setColor(0.08f, 0.08f, 0.08f);
        glutSolidTorus(0.6f, 2.2f, 10, 18);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(bx, 3, -5);
        setColor(0.08f, 0.08f, 0.08f);
        glutSolidTorus(0.6f, 2.2f, 10, 18);
        glPopMatrix();
        drawCube(bx + 1.5f, 7, -9.5f, 3.5f, 0.5f, 0.5f, 0.40f, 0.40f, 0.42f);

        drawCube(bx, 4, 8, 1.0f, 4, 6, 0.18f, 0.12f, 0.12f);
        glPushMatrix();
        glTranslatef(bx, 3, 5);
        setColor(0.08f, 0.08f, 0.08f);
        glutSolidTorus(0.6f, 2.2f, 10, 18);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(bx, 3, 11);
        setColor(0.08f, 0.08f, 0.08f);
        glutSolidTorus(0.6f, 2.2f, 10, 18);
        glPopMatrix();
        drawCube(bx + 1.5f, 7, 9.5f, 3.5f, 0.5f, 0.5f, 0.40f, 0.40f, 0.42f);
    }

    for (float bx = -45; bx <= 45; bx += 32) {

        drawCube(bx, 5, -30, 22, 6, 10, 0.20f, 0.35f, 0.75f);

        drawCube(bx, 10, -30, 16, 5, 8, 0.22f, 0.38f, 0.78f);

        drawCube(bx + 6, 10, -30, 0.5f, 4, 7, 0.65f, 0.82f, 0.92f);

        drawCube(bx - 6, 10, -30, 0.5f, 4, 7, 0.65f, 0.82f, 0.92f);

        glPushMatrix();
        glTranslatef(bx - 7, 3, -35);
        setColor(0.05f, 0.05f, 0.05f);
        glutSolidTorus(1.0f, 2.5f, 10, 18);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(bx + 7, 3, -35);
        setColor(0.05f, 0.05f, 0.05f);
        glutSolidTorus(1.0f, 2.5f, 10, 18);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(bx - 7, 3, -25);
        setColor(0.05f, 0.05f, 0.05f);
        glutSolidTorus(1.0f, 2.5f, 10, 18);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(bx + 7, 3, -25);
        setColor(0.05f, 0.05f, 0.05f);
        glutSolidTorus(1.0f, 2.5f, 10, 18);
        glPopMatrix();

        drawCube(bx + 10, 6, -30, 0.8f, 2, 2, 1.0f, 0.95f, 0.65f);

        drawCube(bx - 10, 6, -30, 0.8f, 2, 2, 0.95f, 0.10f, 0.10f);
    }
    glPopMatrix();
}

void drawAuditorium() {
    float ax = 600.0f;
    float az = -165.0f;

    drawCube(ax, 0.5f, az, 220, 1.2f, 90, 0.85f, 0.12f, 0.10f);

    for (float fx = ax - 100; fx <= ax + 100; fx += 40) {
        drawCylinderY(fx, 0, az + 38, 1.8f, 52.0f, 0.55f, 0.55f, 0.58f);
    }

    for (float fx = ax - 100; fx <= ax + 100; fx += 40) {
        drawCylinderY(fx, 0, az - 38, 1.8f, 52.0f, 0.55f, 0.55f, 0.58f);
    }

    for (float fx = ax - 100; fx <= ax + 100; fx += 40) {
        drawCylinderY(fx, 0, az, 1.8f, 52.0f, 0.55f, 0.55f, 0.58f);
    }

    drawCube(ax, 52, az, 216, 3.0f, 82, 0.12f, 0.42f, 0.88f);

    glPushMatrix();
    glTranslatef(ax, 51, az + 43);
    glRotatef(10.0f, 1, 0, 0);
    glScalef(216.0f, 2.5f, 14.0f);
    setColor(0.10f, 0.38f, 0.82f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(ax, 51, az - 43);
    glRotatef(-10.0f, 1, 0, 0);
    glScalef(216.0f, 2.5f, 14.0f);
    setColor(0.10f, 0.38f, 0.82f);
    glutSolidCube(1.0f);
    glPopMatrix();

    drawCube(ax, 55, az, 216, 2.0f, 5, 0.08f, 0.30f, 0.72f);

    for (float fx = ax - 100; fx <= ax + 100; fx += 40) {
        drawCube(fx, 48, az, 1.5f, 1.5f, 82, 0.55f, 0.55f, 0.58f);
    }
    drawCube(ax, 48, az - 38, 216, 1.5f, 1.5f, 0.55f, 0.55f, 0.58f);
    drawCube(ax, 48, az,      216, 1.5f, 1.5f, 0.55f, 0.55f, 0.58f);
    drawCube(ax, 48, az + 38, 216, 1.5f, 1.5f, 0.55f, 0.55f, 0.58f);

    drawCube(ax + 95, 3, az, 28, 5, 75, 0.75f, 0.72f, 0.70f);
    drawCube(ax + 108, 20, az, 4, 40, 78, 0.30f, 0.30f, 0.32f);

    drawStrokeText(ax - 28, 56, az + 43,
    0.022f, 0.022f, 0.022f,
    "Auditorium", 1.0f, 1.0f, 1.0f);

    for (float bx = ax - 95; bx <= ax + 85; bx += 18) {
        drawSmallBush(bx, az + 52);
    }
}

void drawCricketAreaExtras() {
    float cx = 330.0f;
    float cz = -185.0f;

    drawPracticeNet(cx + 95, cz - 10);
    drawPracticeNet(cx + 95, cz + 10);

    drawBigTree(cx - 60, cz - 170);
    drawBigTree(cx + 60, cz - 170);
    drawRoundTree(cx - 30, cz - 175);
    drawRoundTree(cx + 30, cz - 175);
    drawRoundTree(cx,      cz - 180);

    drawBikeParkingShed(cx + 125, cz - 165);

    for (float bx = 270; bx <= 420; bx += 16) {
        drawSmallBush(bx, -72);
    }

    drawAuditorium();
}
void drawRightSideExtraTrees() {

    for (float z = -60; z <= 140; z += 18) {
        drawRoundTree(270, z);
        drawRoundTree(280, z+6);
    }
}
void drawParkedBusesBehindMosque() {

    float baseZ = 700.0f;
    glPushMatrix();
    glTranslatef(-190.0f, 0.0f, baseZ);
    glRotatef(180.0f, 0, 1, 0);
    drawDIUBusModel();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-150.0f, 0.0f, baseZ + 20.0f);
    glRotatef(180.0f, 0, 1, 0);
    drawDIUBusModel();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-110.0f, 0.0f, baseZ - 15.0f);
    glRotatef(180.0f, 0, 1, 0);
    drawDIUBusModel();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-70.0f, 0.0f, baseZ + 10.0f);
    glRotatef(180.0f, 0, 1, 0);
    drawDIUBusModel();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-30.0f, 0.0f, baseZ - 5.0f);
    glRotatef(180.0f, 0, 1, 0);
    drawDIUBusModel();
    glPopMatrix();
}
void drawDIULogoSign(float x, float z) {

    drawCube(x, 1.0f, z,
    60, 2, 10,
    0.85f, 0.85f, 0.85f);

    drawCube(x, 2.2f, z,
    60, 2, 3,
    0.80f, 0.10f, 0.10f);

    drawCube(x + 15, 7, z, 3, 10, 1, 1, 1, 1);
    drawCube(x + 18, 11, z, 6, 3, 1, 1, 1, 1);
    drawCube(x + 18, 3, z, 6, 3, 1, 1, 1, 1);
    drawCube(x + 21, 7, z, 3, 10, 1, 1, 1, 1);

    drawCube(x, 7, z, 3, 10, 1, 1, 1, 1);

    drawCube(x - 22, 7, z, 3, 10, 1, 1, 1, 1);
    drawCube(x - 15, 7, z, 3, 10, 1, 1, 1, 1);
    drawCube(x - 18.5f, 3, z, 7, 3, 1, 1, 1, 1);
}

void drawScene() {
    drawGround();
    drawRoadAroundField();
    drawFootballField();
    glPushMatrix();
    glTranslatef(260, 0, -40);
    glRotatef(90, 0, 1, 0);
    drawDIULogoSign(0, 0);
    glPopMatrix();
    drawBushBorder();
    drawCricketGround();
    drawCricketAreaExtras();
    drawWestGate();
    drawRightSideExtraTrees();
    drawParkedBusesBehindMosque();
    drawMainBuilding();
    drawStudentsGoingToMainBuilding();
    drawMainBuildingLeftSideExtras();
    drawSouthBuilding();
    drawInnovationLabBuilding();
    drawSouthMosque();
    drawSouthSideOppositeBuilding();
    drawSouthFrontRoad();

    drawNorthSideTrees();
    drawClouds();

    drawAnimatedDIUBus(busPathPos1);
    drawAnimatedDIUBus(busPathPos2);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (viewMode == 1) {

        gluLookAt(
        0.0f, 95.0f, 420.0f,
        40.0f, 55.0f, -230.0f,
        0.0f, 1.0f, 0.0f
        );
    }
    else if (viewMode == 2) {

        gluLookAt(
        0.0f, 120.0f, -260.0f,
        0.0f, 35.0f, 255.0f,
        0.0f, 1.0f, 0.0f
        );
    }
    else if (viewMode == 3) {

        gluLookAt(
        420.0f, 110.0f, 40.0f,
        0.0f, 35.0f, 40.0f,
        0.0f, 1.0f, 0.0f
        );
    }
    else if (viewMode == 4) {

        gluLookAt(
        -420.0f, 110.0f, 40.0f,
        0.0f, 35.0f, 40.0f,
        0.0f, 1.0f, 0.0f
        );
    }
    else {

        float rad = camAngleY * PI / 180.0f;
        float eyeX = sin(rad) * camDist;
        float eyeZ = cos(rad) * camDist + 40.0f;

        gluLookAt(
        eyeX, camHeight, eyeZ,
        0.0f, 35.0f, 40.0f,
        0.0f, 1.0f, 0.0f
        );
    }

    drawScene();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    float ratio = (float)w / (float)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, ratio, 1.0, 2200.0);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_MODELVIEW);
}

void update(int value) {
    cloudMove += 0.35f;
    if (cloudMove > 1000.0f) cloudMove = -450.0f;

    busPathPos1 += 0.9f;
    busPathPos2 += 0.9f;
    float totalPath = 520.0f + 270.0f + 70.0f;
    if (busPathPos1 > totalPath) busPathPos1 -= totalPath;
    if (busPathPos2 > totalPath) busPathPos2 -= totalPath;

    studentWalkPos += 0.4f;
    if (studentWalkPos > 120.0f) studentWalkPos = 0.0f;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void keyboard(unsigned char key, int, int) {
    switch (key) {
    case '0':
            viewMode = 0;
            break;
        case '1':
                viewMode = 1;
                break;
            case '2':
                    viewMode = 2;
                    break;
                case '3':
                        viewMode = 3;
                        break;
                    case '4':
                            viewMode = 4;
                            break;

                        case 'a':
                            case 'A':
                                    if (viewMode == 0) camAngleY -= 3.0f;
                                    break;
                                case 'd':
                                    case 'D':
                                            if (viewMode == 0) camAngleY += 3.0f;
                                            break;
                                        case 'w':
                                            case 'W':
                                                    if (viewMode == 0) camHeight += 5.0f;
                                                    break;
                                                case 's':
                                                    case 'S':
                                                            if (viewMode == 0) {
                                                                camHeight -= 5.0f;
                                                                if (camHeight < 40.0f) camHeight = 40.0f;
                                                            }
                                                            break;
                                                        case 'q':
                                                            case 'Q':
                                                                    if (viewMode == 0) {
                                                                        camDist -= 10.0f;
                                                                        if (camDist < 120.0f) camDist = 120.0f;
                                                                    }
                                                                    break;
                                                                case 'e':
                                                                    case 'E':
                                                                            if (viewMode == 0) {
                                                                                camDist += 10.0f;
                                                                                if (camDist > 700.0f) camDist = 700.0f;
                                                                            }
                                                                            break;

                                                                        case 27:
                                                                                exit(0);
                                                                                break;
                                                                            }

                                                                            glutPostRedisplay();
                                                                        }

                                                                        int main(int argc, char** argv) {
                                                                            glutInit(&argc, argv);
                                                                            glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
                                                                            glutInitWindowSize(1366, 768);
                                                                            glutCreateWindow("DIU Campus");

                                                                            init();

                                                                            glutDisplayFunc(display);
                                                                            glutReshapeFunc(reshape);
                                                                            glutKeyboardFunc(keyboard);
                                                                            glutTimerFunc(16, update, 0);
                                                                            glutMainLoop();
                                                                            return 0;
                                                                        }
