#include "DrawFunctions.hpp"

#include <GL/glut.h>

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define OBSTACLE_NUMBER 20
#define STAR_NUMBER 10

struct OBSTACLE {
  float x;
  int track;
  int type;
};

struct STAR {
  float x;
  float y;
  int track;
  bool goUp;
};

/*
Funkcije za iscrtavanje karta 148-816
Funkcije za iscrtavanje buggy-ja 820-3590
Funkcije za iscrtavanje terena 3593-4278
Funkcije za iscrtavanje prepreka i zvezdica 4280-4797
*/

extern float tiresParameter;
extern float roofParameter;
extern float spoilerParameter;
extern float movementParameter;
// extern float turnParameter;
extern bool goLeft;
extern bool goRight;
extern bool activateHole;
extern bool activateXtrap;
extern bool activateBomb;
extern int firstBlock;
extern int firstObstacle;
extern vector<float> blockPosition;
extern vector<OBSTACLE> obstacle;
extern vector<STAR> stars;
extern float holeParameter, holeRotation;
extern float xTrapHorizontal, xTrapVertical, xTrapRotation;
extern float bombParameter;
extern int starRotationParameter;

// Definicija strukture tacka radi lakseg i preglednijeg koda

typedef struct Tacke {
  float x;
  float y;
  float z;
} TACKA;

void draw_axes(float len) {
  glDisable(GL_LIGHTING);

  glBegin(GL_LINES);
  /*glColor3f(1,0,0);
  glVertex3f(0,0,0);
  glVertex3f(len,0,0);*/

  glColor3f(1, 1, 1);
  glVertex3f(0, 0, 1.8);
  glVertex3f(len, 0, 1.8);

  glColor3f(1, 1, 1);
  glVertex3f(0, 0, -1.8);
  glVertex3f(len, 0, -1.8);

  glColor3f(1, 1, 1);
  glVertex3f(0, 0, 5.4);
  glVertex3f(len, 0, 5.4);

  glColor3f(1, 1, 1);
  glVertex3f(0, 0, -5.4);
  glVertex3f(len, 0, -5.4);
  /*
  glColor3f(1,1,0);
  glVertex3f(1,0,5.4);
  glVertex3f(1,len,5.4);

  glColor3f(0,0,1);
  glVertex3f(0,0,0);
  glVertex3f(0,0,len);*/
  glEnd();

  glPointSize(3);

  glBegin(GL_POINTS);
  glVertex3f(1, 0, 5.4);

  glEnd();

  glEnable(GL_LIGHTING);
}

void setNormalAndVertexQuads(TACKA a, TACKA b, TACKA c, TACKA d) {
  // Vektor normale cemo dobiti kao vektorski proizvod dva vektora

  TACKA v1 = {b.x - a.x, b.y - a.y, b.z - a.z};
  TACKA v2 = {c.x - a.x, c.y - a.y, c.z - a.z};

  glNormal3f(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
             v1.x * v2.y - v1.y * v2.x);

  glVertex3f(a.x, a.y, a.z);
  glVertex3f(b.x, b.y, b.z);
  glVertex3f(c.x, c.y, c.z);
  glVertex3f(d.x, d.y, d.z);
}

void setNormalAndVertexTriangles(TACKA a, TACKA b, TACKA c) {
  // Vektor normale cemo dobiti kao vektorski proizvod dva vektora

  TACKA v1 = {b.x - a.x, b.y - a.y, b.z - a.z};
  TACKA v2 = {c.x - a.x, c.y - a.y, c.z - a.z};

  glNormal3f(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z,
             v1.x * v2.y - v1.y * v2.x);

  glVertex3f(a.x, a.y, a.z);
  glVertex3f(b.x, b.y, b.z);
  glVertex3f(c.x, c.y, c.z);
}

TACKA a, b, c, d;

void drawTires() {
  glPushMatrix();
  glColor3f(0, 0, 0);
  glTranslatef(0.15, 0.02, 0.33);
  glRotatef(-tiresParameter, 0, 0, 1);
  GLUquadric* quad1 = gluNewQuadric();
  gluCylinder(quad1, 0.12, 0.12, 0.1, 20, 20);
  glColor3f(1, 0, 0);
  gluCylinder(quad1, 0.05, 0.05, 0.1, 20, 20);
  glColor3f(1, 0, 0);
  glTranslatef(0, 0, -0.03);
  gluCylinder(quad1, 0.05, 0.05, 0.05, 20, 20);

  glPopMatrix();

  glPushMatrix();
  glColor3f(0, 0, 0);
  glTranslatef(0.15, 0.02, 0.33);
  glRotatef(-tiresParameter, 0, 0, 1);
  gluDisk(quad1, 0.05, 0.12, 20, 20);
  glTranslatef(0, 0, 0.1);
  gluDisk(quad1, 0.05, 0.12, 20, 20);
  glColor3f(1, 0, 0);
  gluDisk(quad1, 0, 0.05, 20, 20);
  glTranslatef(0, 0, -0.1);
  gluDisk(quad1, 0, 0.05, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0, 0, 0);
  glTranslatef(-0.3, 0.02, 0.33);
  glRotatef(-tiresParameter, 0, 0, 1);
  gluCylinder(quad1, 0.12, 0.12, 0.1, 20, 20);
  glColor3f(1, 0, 0);
  gluCylinder(quad1, 0.05, 0.05, 0.1, 20, 20);
  glColor3f(1, 0, 0);
  glTranslatef(0, 0, -0.03);
  gluCylinder(quad1, 0.05, 0.05, 0.1, 20, 20);

  glPopMatrix();

  glPushMatrix();
  glColor3f(0, 0, 0);
  glTranslatef(-0.3, 0.02, 0.33);
  glRotatef(-tiresParameter, 0, 0, 1);
  gluDisk(quad1, 0.05, 0.12, 20, 20);
  glTranslatef(0, 0, 0.1);
  gluDisk(quad1, 0.05, 0.12, 20, 20);
  glColor3f(1, 0, 0);
  gluDisk(quad1, 0, 0.05, 20, 20);
  glTranslatef(0, 0, -0.1);
  gluDisk(quad1, 0, 0.05, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0, 0, 0);
  glTranslatef(-0.3, 0.02, -0.43);
  glRotatef(-tiresParameter, 0, 0, 1);
  gluCylinder(quad1, 0.12, 0.12, 0.1, 20, 20);
  glColor3f(1, 0, 0);
  gluCylinder(quad1, 0.05, 0.05, 0.1, 20, 20);
  glColor3f(1, 0, 0);
  glTranslatef(0, 0, 0.03);
  gluCylinder(quad1, 0.05, 0.05, 0.1, 20, 20);

  glPopMatrix();

  glPushMatrix();
  glColor3f(0, 0, 0);
  glTranslatef(-0.3, 0.02, -0.43);
  glRotatef(-tiresParameter, 0, 0, 1);
  gluDisk(quad1, 0.05, 0.12, 20, 20);
  glTranslatef(0, 0, 0.1);
  gluDisk(quad1, 0.05, 0.12, 20, 20);
  glColor3f(1, 0, 0);
  gluDisk(quad1, 0, 0.05, 20, 20);
  glTranslatef(0, 0, -0.1);
  gluDisk(quad1, 0, 0.05, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0, 0, 0);
  glTranslatef(0.15, 0.02, -0.43);
  glRotatef(-tiresParameter, 0, 0, 1);
  gluCylinder(quad1, 0.12, 0.12, 0.1, 20, 20);
  glColor3f(1, 0, 0);
  gluCylinder(quad1, 0.05, 0.05, 0.1, 20, 20);
  glColor3f(1, 0, 0);
  glTranslatef(0, 0, 0.03);
  gluCylinder(quad1, 0.05, 0.05, 0.1, 20, 20);

  glPopMatrix();

  glPushMatrix();
  glColor3f(0, 0, 0);
  glTranslatef(0.15, 0.02, -0.43);
  glRotatef(-tiresParameter, 0, 0, 1);
  gluDisk(quad1, 0.05, 0.12, 20, 20);
  glTranslatef(0, 0, 0.1);
  gluDisk(quad1, 0.05, 0.12, 20, 20);
  glColor3f(1, 0, 0);
  gluDisk(quad1, 0, 0.05, 20, 20);
  glTranslatef(0, 0, -0.1);
  gluDisk(quad1, 0, 0.05, 20, 20);
  glPopMatrix();
}

void drawSeat() {
  glPushMatrix();
  glColor3f(0.7, 0.7, 0.7);
  GLUquadric* quad2 = gluNewQuadric();
  glTranslatef(-0.3, 0.2, 0);
  glRotatef(90, 0, 1, 0);
  gluCylinder(quad2, 0.16, 0.16, 0.18, 20, 20);
  gluCylinder(quad2, 0.1, 0.1, 0.18, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.7, 0.7, 0.7);
  glTranslatef(-0.3, 0.2, 0);
  glRotatef(90, 0, 1, 0);
  gluDisk(quad2, 0.1, 0.16, 20, 20);
  glTranslatef(0, 0, 0.18);
  gluDisk(quad2, 0.1, 0.16, 20, 20);
  glPopMatrix();
}

void drawKart() {
  glBegin(GL_QUADS);

  glColor3f(1, 0, 0);
  // Donji deo karta
  a = {0.5, 0, 0.3};
  b = {0.5, 0, -0.3};
  c = {-0.5, 0, -0.3};
  d = {-0.5, 0, 0.3};
  setNormalAndVertexQuads(a, b, c, d);

  glColor3f(0, 0, 1);
  // Prednji prvi spoiler(Ako bih ga tako nazvao)
  a = {0.5, 0, 0.3};
  b = {0.5, 0, -0.3};
  c = {0.47, 0.03, -0.3};
  d = {0.47, 0.03, 0.3};
  setNormalAndVertexQuads(a, b, c, d);

  glColor3f(1, 0, 0);

  // Prednji drugi spoiler
  a = {0.47, 0.03, -0.3};
  b = {0.47, 0.03, 0.3};
  c = {0.3, 0.08, 0.3};
  d = {0.3, 0.08, -0.3};
  setNormalAndVertexQuads(a, b, c, d);

  // Gornja povrsina karta
  a = {0.3, 0.08, 0.3};
  b = {0.3, 0.08, -0.3};
  c = {-0.5, 0.08, -0.3};
  d = {-0.5, 0.08, 0.3};
  setNormalAndVertexQuads(a, b, c, d);

  // Donji deo strane
  glColor3f(0, 0, 1);
  a = {0.5, 0, 0.3};
  b = {-0.5, 0, 0.3};
  c = {-0.5, 0.03, 0.3};
  d = {0.47, 0.03, 0.3};
  setNormalAndVertexQuads(a, b, c, d);

  // Gornji deo strane
  a = {-0.5, 0.03, 0.3};
  b = {-0.5, 0.08, 0.3};
  c = {0.3, 0.08, 0.3};
  d = {0.47, 0.03, 0.3};

  setNormalAndVertexQuads(a, b, c, d);

  // Donji deo strane
  a = {0.5, 0, -0.3};
  b = {0.47, 0.03, -0.3};
  c = {-0.5, 0.03, -0.3};
  d = {-0.5, 0, -0.3};
  setNormalAndVertexQuads(a, b, c, d);

  // Gornji deo strane
  a = {-0.5, 0.03, -0.3};
  b = {0.47, 0.03, -0.3};
  c = {0.3, 0.08, -0.3};
  d = {-0.5, 0.08, -0.3};
  setNormalAndVertexQuads(a, b, c, d);

  // Zadnji deo

  glColor3f(0, 0, 1);
  a = {-0.5, 0, -0.3};
  b = {-0.5, 0, 0.3};
  c = {-0.5, 0.08, 0.3};
  d = {-0.5, 0.08, -0.3};
  setNormalAndVertexQuads(a, b, c, d);

  // Soferka i panel
  glColor3f(0.55, 0.55, 0.55);
  a = {0.3, 0.08, 0.3};
  b = {0.15, 0.25, 0.2};
  c = {0.15, 0.25, -0.2};
  d = {0.3, 0.08, -0.3};
  setNormalAndVertexQuads(a, b, c, d);
  glColor3f(1, 0, 0);

  glColor3f(1, 0, 0);
  a = {0, 0.08, -0.3};
  b = {0, 0.08, 0.3};
  c = {0.15, 0.25, 0.2};
  d = {0.15, 0.25, -0.2};
  setNormalAndVertexQuads(a, b, c, d);

  /*
   STARO SEDISTE(Previse mi je zao da obrisem deo koda :'(  )
   glColor3f(0.4,0.4,0.4);
   //Donji deo sedista
   a={-0.4,0.08,0.1};
   b={-0.4,0.08,-0.1};
   c={-0.1,0.08,-0.1};
   d={-0.1,0.08,0.1};
   setNormalAndVertexQuads(a,b,c,d);

   a={-0.4,0.08,0.15};
   b={-0.1,0.08,0.15};
   c={-0.1,0.12,0.15};
   d={-0.4,0.12,0.15};
   setNormalAndVertexQuads(a,b,c,d);

   a={-0.4,0.08,-0.15};
   b={-0.1,0.08,-0.15};
   c={-0.1,0.12,-0.15};
   d={-0.4,0.12,-0.15};
   setNormalAndVertexQuads(a,b,c,d);

   a={-0.1,0.12,0.15};
   b={-0.4,0.12,0.15};
   c={-0.4,0.12,-0.15};
   d={-0.1,0.12,-0.15};
   setNormalAndVertexQuads(a,b,c,d);

   a={-0.4,0.08,0.15};
   b={-0.4,0.12,0.15};
   c={-0.4,0.12,-0.15};
   d={-0.4,0.08,-0.15};
   setNormalAndVertexQuads(a,b,c,d);

   a={-0.1,0.08,0.15};
   b={-0.1,0.12,0.15};
   c={-0.1,0.12,-0.15};
   d={-0.1,0.08,-0.15};
   setNormalAndVertexQuads(a,b,c,d);

   //Gornji deo sedista

   a={-0.4,0.12,0.15};
   b={-0.4,0.12,-0.15};
   c={-0.4,0.4,-0.15};
   d={-0.4,0.4,0.15};
   setNormalAndVertexQuads(a,b,c,d);

   a={-0.4,0.4,-0.15};
   b={-0.4,0.4,0.15};
   c={-0.36,0.4,0.15};
   d={-0.36,0.4,-0.15};
   setNormalAndVertexQuads(a,b,c,d);

   a={-0.36,0.4,0.15};
   b={-0.36,0.4,-0.15};
   c={-0.36,0.12,-0.15};
   d={-0.36,0.12,0.15};
   setNormalAndVertexQuads(a,b,c,d);


   a={-0.36,0.4,-0.15};
   b={-0.4,0.4,-0.15};
   c={-0.4,0.12,-0.15};
   d={-0.36,0.12,-0.15};
   setNormalAndVertexQuads(a,b,c,d);

   a={-0.36,0.4,0.15};
   b={-0.4,0.4,0.15};
   c={-0.4,0.12,0.15};
   d={-0.36,0.12,0.15};
   setNormalAndVertexQuads(a,b,c,d);

   */

  glEnd();

  glBegin(GL_TRIANGLES);

  glColor3f(1, 0, 0);
  a = {0.3, 0.08, 0.3};
  b = {0, 0.08, 0.3};
  c = {0.15, 0.25, 0.2};
  setNormalAndVertexTriangles(a, b, c);

  // glColor3f(1,0,0);
  a = {0.3, 0.08, -0.3};
  b = {0, 0.08, -0.3};
  c = {0.15, 0.25, -0.2};
  setNormalAndVertexTriangles(a, b, c);

  glEnd();

  // Prednja svetla
  glPushMatrix();
  glColor3f(1, 1, 1);
  glTranslatef(0.44, 0.03, 0.22);
  glScalef(1, 1, 2);
  glutSolidCube(0.04);
  glPopMatrix();

  glPushMatrix();
  glColor3f(1, 1, 1);
  glTranslatef(0.44, 0.03, -0.22);
  glScalef(1, 1, 2);
  glutSolidCube(0.04);
  glPopMatrix();

  // Zadnja svetla
  glPushMatrix();
  glColor3f(1, 0, 0);
  glTranslatef(-0.49, 0.045, 0.22);
  glScalef(1, 1, 2);
  glutSolidCube(0.04);
  glPopMatrix();

  glPushMatrix();
  glColor3f(1, 0, 0);
  glTranslatef(-0.49, 0.045, -0.22);
  glScalef(1, 1, 2);
  glutSolidCube(0.04);
  glPopMatrix();

  // Volan

  glPushMatrix();

  glColor3f(0.3, 0.3, 0.3);
  GLUquadric* quad = gluNewQuadric();
  glTranslatef(0.04, 0.2, 0);
  glRotatef(90, 1, 1, 0);
  gluCylinder(quad, 0.01, 0.01, 0.15, 20, 20);

  glPopMatrix();

  glPushMatrix();
  glColor3f(0.3, 0.3, 0.3);
  glTranslatef(0.04, 0.2, 0);
  glRotatef(90, 1, 1, 0);
  glutSolidTorus(0.01, 0.05, 20, 20);

  glPopMatrix();

  glPushMatrix();
  glColor3f(0.3, 0.3, 0.3);
  glTranslatef(0.04, 0.2, 0);
  glRotatef(90, 1, 1, 0);
  gluDisk(quad, 0, 0.01, 20, 20);
  glPopMatrix();

  // Brzinometar

  glPushMatrix();
  glColor3f(0.7, 0.7, 0.7);
  glTranslatef(0.13, 0.2, 0);
  glRotatef(45, 0, 0, 1);
  glScalef(0.55, 0.5, 1.5);
  glutSolidCube(0.1);
  glPopMatrix();

  // Kocnica

  glPushMatrix();
  glColor3f(0.2, 0.2, 0.2);
  glTranslatef(0.04, 0.1, 0);
  glRotatef(45, 0, 0, 1);
  glScalef(0.6, 0.5, 0.3);
  glutSolidCube(0.1);
  glPopMatrix();

  // Gas

  glPushMatrix();
  glColor3f(0.2, 0.2, 0.2);
  glTranslatef(0.04, 0.1, 0.05);
  glRotatef(45, 0, 0, 1);
  glScalef(0.6, 0.5, 0.3);
  glutSolidCube(0.1);
  glPopMatrix();

  // Kvacilo

  glPushMatrix();
  glColor3f(0.2, 0.2, 0.2);
  glTranslatef(0.04, 0.1, -0.05);
  glRotatef(45, 0, 0, 1);
  glScalef(0.6, 0.5, 0.3);
  glutSolidCube(0.1);
  glPopMatrix();

  // Auspuh x6 adds on max speed +100000000

  glPushMatrix();
  glColor3f(0.7, 0.7, 0.7);
  glTranslatef(-0.4, 0.2, -0.25);
  glRotatef(90, 1, 1, 0);
  gluCylinder(quad, 0.02, 0.02, 0.2, 20, 20);
  gluDisk(quad, 0, 0.02, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.7, 0.7, 0.7);
  glTranslatef(-0.46, 0.2, -0.25);
  glRotatef(90, 1, 1, 0);
  gluCylinder(quad, 0.02, 0.02, 0.2, 20, 20);
  gluDisk(quad, 0, 0.02, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.7, 0.7, 0.7);
  glTranslatef(-0.52, 0.2, -0.25);
  glRotatef(90, 1, 1, 0);
  gluCylinder(quad, 0.02, 0.02, 0.2, 20, 20);
  gluDisk(quad, 0, 0.02, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.7, 0.7, 0.7);
  glTranslatef(-0.4, 0.2, 0.25);
  glRotatef(90, 1, 1, 0);
  gluCylinder(quad, 0.02, 0.02, 0.2, 20, 20);
  gluDisk(quad, 0, 0.02, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.7, 0.7, 0.7);
  glTranslatef(-0.46, 0.2, 0.25);
  glRotatef(90, 1, 1, 0);
  gluCylinder(quad, 0.02, 0.02, 0.2, 20, 20);
  gluDisk(quad, 0, 0.02, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.7, 0.7, 0.7);
  glTranslatef(-0.52, 0.2, 0.25);
  glRotatef(90, 1, 1, 0);
  gluCylinder(quad, 0.02, 0.02, 0.2, 20, 20);
  gluDisk(quad, 0, 0.02, 20, 20);
  glPopMatrix();

  // Retrovizori

  glPushMatrix();
  glColor3f(0.3, 0.3, 0.3);
  glTranslatef(0.15, 0.15, 0.25);
  gluCylinder(quad, 0.01, 0.01, 0.03, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.3, 0.3, 0.3);
  glTranslatef(0.15, 0.15, 0.3);
  glScalef(1, 1, 2);
  glutSolidCube(0.03);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.3, 0.3, 0.3);
  glTranslatef(0.15, 0.15, -0.28);
  gluCylinder(quad, 0.01, 0.01, 0.03, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.3, 0.3, 0.3);
  glTranslatef(0.15, 0.15, -0.3);
  glScalef(1, 1, 2);
  glutSolidCube(0.03);
  glPopMatrix();

  // Tockovi
  glPushMatrix();
  drawTires();
  glPopMatrix();

  // Motor

  glPushMatrix();
  glColor3f(0.4, 0.4, 0.4);
  glTranslatef(-0.4, 0.12, 0);
  glutSolidCube(0.1);
  glScalef(1, 0.1, 1.5);
  glutSolidCube(0.1);
  glTranslatef(0, 0.25, 0);
  glutSolidCube(0.1);
  glTranslatef(0, 0.25, 0);
  glutSolidCube(0.1);
  glTranslatef(0, -0.75, 0);
  glutSolidCube(0.1);
  glPopMatrix();

  // Spojler

  glPushMatrix();
  glColor3f(0, 0, 1);
  glTranslatef(-0.55, 0.22, 0.12);
  glRotatef(90, 1, 0, 0);
  glRotatef(30, 0, 1, 0);
  gluCylinder(quad, 0.01, 0.01, 0.2, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.55, 0.22, -0.12);
  glRotatef(90, 1, 0, 0);
  glRotatef(30, 0, 1, 0);
  gluCylinder(quad, 0.01, 0.01, 0.2, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-0.55, 0.22, 0);
  glScalef(0.7, 0.1, 4);
  glutSolidCube(0.1);

  glPopMatrix();

  // Vozac

  // Noge

  glPushMatrix();
  glColor3f(0, 0, 1);
  glTranslatef(0.04, 0.1, 0.05);
  glRotatef(50, 0, 0, 1);
  glScalef(0.4, 2.5, 0.25);
  glutSolidCube(0.1);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0, 0, 1);
  glTranslatef(0.04, 0.1, -0.05);
  glRotatef(50, 0, 0, 1);
  glScalef(0.4, 2.5, 0.25);
  glutSolidCube(0.1);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0, 0, 1);
  glTranslatef(-0.1, 0.14, 0.05);
  glRotatef(-60, 0, 0, 1);
  glScalef(0.4, 1.5, 0.25);
  glutSolidCube(0.1);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0, 0, 1);
  glTranslatef(-0.1, 0.14, -0.05);
  glRotatef(-60, 0, 0, 1);
  glScalef(0.4, 1.5, 0.25);
  glutSolidCube(0.1);
  glPopMatrix();

  // Torso

  glPushMatrix();
  glColor3f(0.2, 0.4, 0);
  glTranslatef(-0.15, 0.2, 0);
  glScalef(0.5, 2, 1.5);
  glutSolidCube(0.1);
  glPopMatrix();

  // Ruke

  glPushMatrix();
  glColor3f(0.2, 0.4, 0);
  glTranslatef(-0.1, 0.25, 0.089);
  glRotatef(60, 0, 0, 1);
  glScalef(0.3, 1.2, 0.25);
  glutSolidCube(0.1);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.2, 0.4, 0);
  glTranslatef(-0.1, 0.25, -0.089);
  glRotatef(60, 0, 0, 1);
  glScalef(0.3, 1.2, 0.25);
  glutSolidCube(0.1);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.2, 0.4, 0);
  glTranslatef(-0.023, 0.205, -0.075);
  glRotatef(60, 0, 0, 1);
  glRotatef(-20, 1, 0, 0);
  glScalef(0.3, 0.95, 0.25);
  glutSolidCube(0.1);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.2, 0.4, 0);
  glTranslatef(-0.023, 0.205, 0.075);
  glRotatef(60, 0, 0, 1);
  glRotatef(20, 1, 0, 0);
  glScalef(0.3, 0.95, 0.25);
  glutSolidCube(0.1);
  glPopMatrix();

  // Glava

  glPushMatrix();
  glColor3f(0.898, 0.760, 0.596);
  glTranslatef(-0.15, 0.33, 0);
  glutSolidSphere(0.032, 20, 20);
  glPopMatrix();

  // Sefovsko sediste

  glTranslatef(0.05, 0, 0);

  glPushMatrix();
  glColor3f(0.7, 0.7, 0.7);
  glTranslatef(-0.21, 0.15, -0.128);
  glScalef(2, 1.5, 0.7);
  glutSolidCube(0.09);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.7, 0.7, 0.7);
  glTranslatef(-0.21, 0.15, 0.128);
  glScalef(2, 1.5, 0.7);
  glutSolidCube(0.09);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.7, 0.7, 0.7);
  glTranslatef(-0.31, 0.15, 0);
  glScalef(0.2, 0.7, 1);
  glutSolidCube(0.32);
  glPopMatrix();

  glPushMatrix();
  double clip_plane[] = {0, -1, 0, 0.18};
  glClipPlane(GL_CLIP_PLANE0, clip_plane);
  glEnable(GL_CLIP_PLANE0);
  drawSeat();
  glDisable(GL_CLIP_PLANE0);
  glPopMatrix();
}

void drawTiresForBuggy() {
  // Zadnja desna

  glPushMatrix();
  glColor3f(0.1, 0.1, 0.1);
  glTranslatef(0.16, 0.03, 0.23);
  glRotatef(-tiresParameter, 0, 0, 1);
  GLUquadric* quad1 = gluNewQuadric();
  gluCylinder(quad1, 0.13, 0.13, 0.1, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.1, 0.1, 0.1);
  glTranslatef(0.16, 0.03, 0.23);
  glRotatef(-tiresParameter, 0, 0, 1);
  gluDisk(quad1, 0.05, 0.13, 20, 20);
  glTranslatef(0, 0, 0.1);
  gluDisk(quad1, 0.05, 0.13, 20, 20);
  glColor3f(1, 0, 0);
  gluDisk(quad1, 0, 0.05, 20, 20);
  glTranslatef(0, 0, -0.1);
  gluDisk(quad1, 0, 0.05, 20, 20);
  glPopMatrix();

  // Prednja desna

  glPushMatrix();
  glColor3f(0.1, 0.1, 0.1);
  glTranslatef(0.95, 0.02, 0.23);
  glRotatef(-tiresParameter, 0, 0, 1);
  gluCylinder(quad1, 0.12, 0.12, 0.1, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.1, 0.1, 0.1);
  glTranslatef(0.95, 0.02, 0.23);
  glRotatef(-tiresParameter, 0, 0, 1);
  gluDisk(quad1, 0.05, 0.12, 20, 20);
  glTranslatef(0, 0, 0.1);
  gluDisk(quad1, 0.05, 0.12, 20, 20);
  glColor3f(1, 0, 0);
  gluDisk(quad1, 0, 0.05, 20, 20);
  glTranslatef(0, 0, -0.1);
  gluDisk(quad1, 0, 0.05, 20, 20);
  glPopMatrix();

  // Zadnja leva

  glPushMatrix();
  glColor3f(0.1, 0.1, 0.1);
  glTranslatef(0.16, 0.03, -0.33);
  glRotatef(-tiresParameter, 0, 0, 1);
  gluCylinder(quad1, 0.13, 0.13, 0.1, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.1, 0.1, 0.1);
  glTranslatef(0.16, 0.03, -0.33);
  glRotatef(-tiresParameter, 0, 0, 1);
  gluDisk(quad1, 0.05, 0.13, 20, 20);
  glTranslatef(0, 0, 0.1);
  gluDisk(quad1, 0.05, 0.13, 20, 20);
  glColor3f(1, 0, 0);
  gluDisk(quad1, 0, 0.05, 20, 20);
  glTranslatef(0, 0, -0.1);
  gluDisk(quad1, 0, 0.05, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.1, 0.1, 0.1);
  glTranslatef(0.95, 0.02, -0.33);
  glRotatef(-tiresParameter, 0, 0, 1);
  gluCylinder(quad1, 0.12, 0.12, 0.1, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.1, 0.1, 0.1);
  glTranslatef(0.95, 0.02, -0.33);
  glRotatef(-tiresParameter, 0, 0, 1);
  gluDisk(quad1, 0.05, 0.12, 20, 20);
  glTranslatef(0, 0, 0.1);
  gluDisk(quad1, 0.05, 0.12, 20, 20);
  glColor3f(1, 0, 0);
  gluDisk(quad1, 0, 0.05, 20, 20);
  glTranslatef(0, 0, -0.1);
  gluDisk(quad1, 0, 0.05, 20, 20);
  glPopMatrix();
}

void drawRoof() {
  double clip_plane1[] = {-1, 0, 0, roofParameter};
  glClipPlane(GL_CLIP_PLANE1, clip_plane1);
  glEnable(GL_CLIP_PLANE1);

  glColor3f(0.1, 0.1, 0.1);

  glBegin(GL_QUADS);

  // Top plate

  a = {10.25, 5.75, -4};
  b = {10.25, 5.75, 4};
  c = {5, 5.75, 4};
  d = {5, 5.75, -4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {10.25, 6, -3};
  b = {10.25, 6, 3};
  c = {5, 6, 3};
  d = {5, 6, -3};

  setNormalAndVertexQuads(a, b, c, d);

  a = {10.25, 5.75, -4};
  b = {5, 5.75, -4};
  c = {5, 6, -3};
  d = {10.25, 6, -3};

  setNormalAndVertexQuads(a, b, c, d);

  a = {10.25, 5.75, 4};
  b = {5, 5.75, 4};
  c = {5, 6, 3};
  d = {10.25, 6, 3};

  setNormalAndVertexQuads(a, b, c, d);

  glEnd();

  glDisable(GL_CLIP_PLANE1);

  // Backplate

  glBegin(GL_TRIANGLES);

  a = {5, 5.75, 4};
  b = {0.5, 3.5, 4};
  c = {5, 3.5, 4};
  setNormalAndVertexTriangles(a, b, c);

  a = {5, 5.75, -4};
  b = {0.5, 3.5, -4};
  c = {5, 3.5, -4};
  setNormalAndVertexTriangles(a, b, c);

  a = {5, 5.75, 3.75};
  b = {5, 3.5, 3.75};
  c = {3, 3.5, 1.5};
  setNormalAndVertexTriangles(a, b, c);

  a = {5, 5.75, -3.75};
  b = {5, 3.5, -3.75};
  c = {3, 3.5, -1.5};
  setNormalAndVertexTriangles(a, b, c);
  glEnd();

  glBegin(GL_QUADS);

  a = {5, 5.75, 4};
  b = {5, 5.75, -4};
  c = {5, 6, -3};
  d = {5, 6, 3};

  setNormalAndVertexQuads(a, b, c, d);

  a = {5, 5.75, 4};
  b = {5, 5.75, -4};
  c = {3, 3.5, -1.5};
  d = {3, 3.5, 1.5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {5, 5.75, 4};
  b = {5, 5.75, 3.75};
  c = {5, 3.5, 3.75};
  d = {5, 3.5, 4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {5, 5.75, -4};
  b = {5, 5.75, -3.75};
  c = {5, 3.5, -3.75};
  d = {5, 3.5, -4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {5, 5.75, 4};
  b = {5, 5.75, -4};
  c = {0.5, 3.5, -4};
  d = {0.5, 3.5, 4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {5, 6, 3};
  b = {5, 6, -3};
  c = {0.25, 3.75, -3};
  d = {0.25, 3.75, 3};

  setNormalAndVertexQuads(a, b, c, d);

  a = {5, 5.75, 4};
  b = {5, 6, 3};
  c = {0.25, 3.75, 3};
  d = {0.5, 3.5, 4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {5, 5.75, -4};
  b = {5, 6, -3};
  c = {0.25, 3.75, -3};
  d = {0.5, 3.5, -4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {5, 5.75, 4};
  b = {5, 5.75, -4};
  c = {5, 6, 3};
  d = {5, 6, -3};

  setNormalAndVertexQuads(a, b, c, d);
  glEnd();

  // Spojler

  double clip_plane2[] = {0, -1, 0, spoilerParameter};
  glClipPlane(GL_CLIP_PLANE2, clip_plane2);
  glEnable(GL_CLIP_PLANE2);

  glColor3f(0, 1, 0);
  glPushMatrix();
  glTranslatef(2, 3.3, 3);
  glRotatef(-90, 1, 0, 0);
  glRotatef(-40, 0, 1, 0);
  GLUquadric* quad5 = gluNewQuadric();
  gluCylinder(quad5, 0.25, 0.25, 3, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(2, 3.3, -3);
  glRotatef(-90, 1, 0, 0);
  glRotatef(-40, 0, 1, 0);
  gluCylinder(quad5, 0.25, 0.25, 3, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 5.6, 0);
  glScalef(1, 0.3, 10);
  glutSolidCube(1);

  glPopMatrix();

  glDisable(GL_CLIP_PLANE2);
}

void drawBuggy() {
  glColor3f(0.1, 0.1, 0.1);

  if ( !activateXtrap ) {
    glPushMatrix();
    glScalef(17, 17, 17);
    drawTiresForBuggy();
    glPopMatrix();
  }

  glColor3f(0.1, 0.1, 0.1);

  glBegin(GL_QUADS);

  // Leva strana

  a = {6.5, 0, -5};
  b = {6.5, 2, -5};
  c = {12, 1.5, -5};
  d = {12, 0, -5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {5, 0, -5};
  b = {5, 3.5, -5};
  c = {6.5, 2, -5};
  d = {6.5, 0, -5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {5, 3.5, -5};
  b = {0, 3.5, -5};
  c = {0, 3, -5};
  d = {5, 3, -5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {12, 0, -5};
  b = {12, 1.5, -5};
  c = {14, 3, -5};
  d = {14, 0, -5};

  setNormalAndVertexQuads(a, b, c, d);

  // Zatvaramo prednji levi tocak

  glColor3f(1, 0, 0);

  a = {14, 2, -5};
  b = {14, 0, -5};
  c = {14, 0, -4};
  d = {14, 2, -4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {14, 2, -5};
  b = {14, 2, -4};
  c = {15.5, 2.5, -4};
  d = {15.5, 2.5, -5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {15.5, 2.5, -4};
  b = {15.5, 2.5, -5};
  c = {18, 2.5, -5};
  d = {18, 2.5, -4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {18, 2.5, -5};
  b = {18, 2.5, -4};
  c = {18.2, 2, -4};
  d = {18.2, 2, -5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {18.2, 2, -4};
  b = {18.2, 2, -5};
  c = {18.2, 1, -5};
  d = {18.2, 1, -4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {18.2, 1, -5};
  b = {18.2, 1, -4};
  c = {18.2, 0, -4};
  d = {18.2, 0, -4};

  setNormalAndVertexQuads(a, b, c, d);

  // Zatvaramo prednji desni tocak

  a = {14, 2, 5};
  b = {14, 0, 5};
  c = {14, 0, 4};
  d = {14, 2, 4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {14, 2, 5};
  b = {14, 2, 4};
  c = {15.5, 2.5, 4};
  d = {15.5, 2.5, 5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {15.5, 2.5, 4};
  b = {15.5, 2.5, 5};
  c = {18, 2.5, 5};
  d = {18, 2.5, 4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {18, 2.5, 5};
  b = {18, 2.5, 4};
  c = {18.2, 2, 4};
  d = {18.2, 2, 5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {18.2, 2, 4};
  b = {18.2, 2, 5};
  c = {18.2, 1, 5};
  d = {18.2, 1, 4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {18.2, 1, 5};
  b = {18.2, 1, 4};
  c = {18.2, 0, 4};
  d = {18.2, 0, 4};

  setNormalAndVertexQuads(a, b, c, d);

  glColor3f(0.1, 0.1, 0.1);

  a = {14, 3, -5};
  b = {19, 3, -5};
  c = {19, 2.5, -5};
  d = {14, 2.5, -5};

  setNormalAndVertexQuads(a, b, c, d);

  // Zatvaramo za zadnje tockove leve strane

  a = {5, 0, -5};
  b = {5, 0, -4};
  c = {5, 2, -4};
  d = {5, 2, -5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {5, 2, -5};
  b = {5, 2, -4};
  c = {3.5, 3, -4};
  d = {3.5, 3, -5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {3.5, 3, -5};
  b = {3.5, 3, -4};
  c = {1.5, 3, -4};
  d = {1.5, 3, -5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {1.5, 3, -5};
  b = {1.5, 3, -4};
  c = {0, 2, -4};
  d = {0, 2, -5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {0, 2, -4};
  b = {0, 2, -5};
  c = {0, 1, -5};
  d = {0, 1, -4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {0, 1, -5};
  b = {0, 1, -4};
  c = {-0.5, 1, -4};
  d = {-0.5, 1, -5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {-0.5, 1, -4};
  b = {-0.5, 1, -5};
  c = {-0.5, 3.5, -5};
  d = {-0.5, 3.5, -4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {-0.5, 3.5, -5};
  b = {-0.5, 3.5, -4};
  c = {0, 3.5, -4};
  d = {0, 3.5, -5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {5, 0, -5};
  b = {5, 0, -4};
  c = {5, 2, -4};
  d = {5, 2, -5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {0, 1, -5};
  b = {-0.5, 1, -5};
  c = {-0.5, 3.5, -5};
  d = {0, 3.5, -5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {5, 0, 5};
  b = {5, 0, 4};
  c = {5, 2, 4};
  d = {5, 2, 5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {5, 2, 5};
  b = {5, 2, 4};
  c = {3.5, 3, 4};
  d = {3.5, 3, 5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {3.5, 3, 5};
  b = {3.5, 3, 4};
  c = {1.5, 3, 4};
  d = {1.5, 3, 5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {1.5, 3, 5};
  b = {1.5, 3, 4};
  c = {0, 2, 4};
  d = {0, 2, 5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {0, 2, 4};
  b = {0, 2, 5};
  c = {0, 1, 5};
  d = {0, 1, 4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {0, 1, 5};
  b = {0, 1, 4};
  c = {-0.5, 1, 4};
  d = {-0.5, 1, 5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {-0.5, 1, 4};
  b = {-0.5, 1, 5};
  c = {-0.5, 3.5, 5};
  d = {-0.5, 3.5, 4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {-0.5, 3.5, 5};
  b = {-0.5, 3.5, 4};
  c = {0, 3.5, 4};
  d = {0, 3.5, 5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {5, 0, 5};
  b = {5, 0, 4};
  c = {5, 2, 4};
  d = {5, 2, 5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {0, 1, 5};
  b = {-0.5, 1, 5};
  c = {-0.5, 3.5, 5};
  d = {0, 3.5, 5};

  setNormalAndVertexQuads(a, b, c, d);

  // Zadnja strana auta

  a = {-0.5, 2, -4};
  b = {-0.5, 2, 4};
  c = {-0.5, 3.5, 4};
  d = {-0.5, 3.5, -4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {-0.5, 2, -4};
  b = {-0.5, 2, 4};
  c = {5, 0, 4};
  d = {5, 0, -4};

  setNormalAndVertexQuads(a, b, c, d);

  // Zeleni deo leve strane

  glColor3f(0, 1, 0);

  a = {6.5, 2, -5};
  b = {12, 1.5, -5};
  c = {12, 2.25, -4.5};
  d = {6.5, 2.75, -4.5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {6.5, 2, -4};
  b = {12, 1.5, -4};
  c = {12, 2.25, -4.5};
  d = {6.5, 2.75, -4.5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {6.5, 2, -5};
  b = {6.5, 2.75, -4.5};
  c = {5, 4.25, -4.5};
  d = {5, 3.5, -5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {6.5, 2, -4};
  b = {6.5, 2.75, -4.5};
  c = {5, 4.25, -4.5};
  d = {5, 3.5, -4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {5, 3.5, -5};
  b = {5, 4.25, -4.5};
  c = {0, 4.25, -4.5};
  d = {0, 3.5, -5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {5, 3.5, -4};
  b = {5, 4.25, -4.5};
  c = {0, 4.25, -4.5};
  d = {0, 3.5, -4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {12, 1.5, -5};
  b = {12, 2.25, -4.5};
  c = {13.75, 3.5, -4.5};
  d = {14, 3, -5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {12, 1.5, -4};
  b = {12, 2.25, -4.5};
  c = {13.75, 3.5, -4.5};
  d = {14, 3, -4};

  setNormalAndVertexQuads(a, b, c, d);

  // Zadnji deo zelene strane

  a = {-0.5, 3.5, -4};
  b = {-0.5, 3.5, 4};
  c = {0, 4.25, 4.5};
  d = {0, 4.25, -4.5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {0, 4.25, 4.5};
  b = {0, 4.25, -4.5};
  c = {0.5, 3.5, -4};
  d = {0.5, 3.5, 4};

  setNormalAndVertexQuads(a, b, c, d);

  // Desna strana

  glColor3f(0.1, 0.1, 0.1);

  a = {6.5, 0, +5};
  b = {6.5, 2, +5};
  c = {12, 1.5, +5};
  d = {12, 0, +5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {5, 0, +5};
  b = {5, 3.5, +5};
  c = {6.5, 2, +5};
  d = {6.5, 0, +5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {5, 3.5, +5};
  b = {0, 3.5, +5};
  c = {0, 3, +5};
  d = {5, 3, +5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {12, 0, +5};
  b = {12, 1.5, +5};
  c = {14, 3, +5};
  d = {14, 0, +5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {14, 3, +5};
  b = {19, 3, +5};
  c = {19, 2.5, +5};
  d = {14, 2.5, +5};

  setNormalAndVertexQuads(a, b, c, d);

  // Zeleni deo desne strane

  glColor3f(0, 1, 0);

  a = {6.5, 2, +5};
  b = {12, 1.5, +5};
  c = {12, 2.25, +4.5};
  d = {6.5, 2.75, +4.5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {6.5, 2, +4};
  b = {12, 1.5, +4};
  c = {12, 2.25, +4.5};
  d = {6.5, 2.75, +4.5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {6.5, 2, +5};
  b = {6.5, 2.75, +4.5};
  c = {5, 4.25, +4.5};
  d = {5, 3.5, +5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {6.5, 2, +4};
  b = {6.5, 2.75, +4.5};
  c = {5, 4.25, +4.5};
  d = {5, 3.5, +4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {5, 3.5, +5};
  b = {5, 4.25, +4.5};
  c = {0, 4.25, +4.5};
  d = {0, 3.5, +5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {5, 3.5, +4};
  b = {5, 4.25, +4.5};
  c = {0, 4.25, +4.5};
  d = {0, 3.5, +4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {12, 1.5, +5};
  b = {12, 2.25, +4.5};
  c = {13.75, 3.5, +4.5};
  d = {14, 3, +5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {12, 1.5, +4};
  b = {12, 2.25, +4.5};
  c = {13.75, 3.5, +4.5};
  d = {14, 3, +4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {15, 3.25, 4.75};
  b = {15, 3.25, 4.25};
  c = {14.5, 3.5, 4.25};
  d = {14.5, 3.5, 4.75};

  setNormalAndVertexQuads(a, b, c, d);

  a = {15, 3.25, 4.75};
  b = {14, 3, 5};
  c = {13.75, 3.5, +4.5};
  d = {14.5, 3.5, 4.75};

  setNormalAndVertexQuads(a, b, c, d);

  a = {15, 3.25, 4.25};
  b = {14, 3, 4};
  c = {13.75, 3.5, +4.5};
  d = {14.5, 3.5, 4.25};

  setNormalAndVertexQuads(a, b, c, d);

  a = {15, 3.25, -4.75};
  b = {15, 3.25, -4.25};
  c = {14.5, 3.5, -4.25};
  d = {14.5, 3.5, -4.75};

  setNormalAndVertexQuads(a, b, c, d);

  a = {15, 3.25, -4.75};
  b = {14, 3, -5};
  c = {13.75, 3.5, -4.5};
  d = {14.5, 3.5, -4.75};

  setNormalAndVertexQuads(a, b, c, d);

  a = {15, 3.25, -4.25};
  b = {14, 3, -4};
  c = {13.75, 3.5, -4.5};
  d = {14.5, 3.5, -4.25};

  setNormalAndVertexQuads(a, b, c, d);

  // Prednji deo desno

  a = {14, 3, 5};
  b = {14, 3.25, 4.75};
  c = {19, 3.25, 4.75};
  d = {19, 3, 5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {14, 3, 4};
  b = {14, 3.25, 4.25};
  c = {19, 3.25, 4.25};
  d = {19, 3, 4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {14, 3.25, 4.25};
  b = {19, 3.25, 4.25};
  c = {19, 3.25, 4.75};
  d = {14, 3.25, 4.75};

  setNormalAndVertexQuads(a, b, c, d);

  glColor3f(0, 1, 0);

  a = {19, 3.25, 3};
  b = {19, 3, 4};
  c = {19.5, 3.125, 3};
  d = {19, 3.25, 3};

  setNormalAndVertexQuads(a, b, c, d);

  a = {19.5, 3.125, 3};
  b = {19, 3.25, 3};
  c = {19, 3.25, -3};
  d = {19.5, 3.125, -3};

  setNormalAndVertexQuads(a, b, c, d);

  glColor3f(0.3, 0.3, 0.3);

  a = {19.5, 3.125, 3};
  b = {19.5, 3.125, -3};
  c = {20, 2.5, -2.75};
  d = {20, 2.5, 2.75};

  setNormalAndVertexQuads(a, b, c, d);

  glColor3f(0, 1, 0);

  a = {20, 2.5, 2.75};
  b = {20, 2.5, 2.25};
  c = {20.25, 2.25, 2.25};
  d = {20.125, 2.25, 3};

  setNormalAndVertexQuads(a, b, c, d);

  a = {20.25, 2.25, 2.25};
  b = {20.25, 1.75, 2.25};
  c = {20.125, 1.75, 3};
  d = {20.125, 2.25, 3};

  setNormalAndVertexQuads(a, b, c, d);

  a = {20.25, 2.25, 2.25};
  b = {20.25, 1.75, 2.25};
  c = {20.25, 1.75, -2.25};
  d = {20.25, 2.25, -2.25};

  setNormalAndVertexQuads(a, b, c, d);

  a = {20.125, 2.25, 3};
  b = {19.75, 2.25, 4};
  c = {19.75, 1.75, 4};
  d = {20.125, 1.75, 3};

  setNormalAndVertexQuads(a, b, c, d);

  a = {19.75, 2.25, 4};
  b = {19.75, 1.75, 4};
  c = {19, 2, 5};
  d = {19, 2.5, 5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {20, 2.5, 2.25};
  b = {20.25, 2.25, 2.25};
  c = {20.25, 2.25, -2.25};
  d = {20, 2.5, -2.25};

  setNormalAndVertexQuads(a, b, c, d);

  // Desna strana branika

  glColor3f(0.1, 0.1, 0.1);

  // 1

  a = {19.75, 1.75, 4};
  b = {20.125, 1.75, 3};
  c = {20.125, 0.75, 3};
  d = {19.75, 0.75, 4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {20.125, 0.75, 3};
  b = {19.75, 0.75, 4};
  c = {19, 0, 4};
  d = {19.375, 0, 3};

  setNormalAndVertexQuads(a, b, c, d);

  // 2

  a = {19.75, 1.75, 4};
  b = {19, 2, 5};
  c = {19, 1, 5};
  d = {19.75, 0.75, 4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {19.75, 0.75, 4};
  b = {19, 0, 4};
  c = {19, 0, 4};
  d = {19, 1, 5};

  setNormalAndVertexQuads(a, b, c, d);

  // 3

  a = {20.25, 1.75, 2.25};
  b = {20.125, 1.75, 3};
  c = {20.125, 0.75, 3};
  d = {20.25, 0.75, 2.25};

  setNormalAndVertexQuads(a, b, c, d);

  a = {20.125, 0.75, 3};
  b = {19.375, 0, 3};
  c = {19.375, 0, 2.25};
  d = {20.25, 0.75, 2.25};

  setNormalAndVertexQuads(a, b, c, d);

  a = {20.25, 1.75, 2.25};
  b = {20.25, 1.75, -2.25};
  c = {20.25, 0.75, -2.25};
  d = {20.25, 0.75, 2.25};

  setNormalAndVertexQuads(a, b, c, d);

  a = {19.375, 0, 2.25};
  b = {20.25, 0.75, 2.25};
  c = {20.25, 0.75, -2.25};
  d = {19.375, 0, -2.25};

  setNormalAndVertexQuads(a, b, c, d);

  // Sa strane do tocka

  a = {19, 2, 5};
  b = {19, 1, 5};
  c = {18.2, 1, 5};
  d = {18.2, 2, 5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {19, 1, 5};
  b = {18.2, 1, 5};
  c = {18.2, 0, 4};
  d = {19, 0, 4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {17.5, 2.5, 5};
  b = {19, 2.5, 5};
  c = {19, 2, 5};
  d = {18.2, 2, 5};

  setNormalAndVertexQuads(a, b, c, d);

  // Leva strana branika

  // 1

  a = {19.75, 1.75, -4};
  b = {20.125, 1.75, -3};
  c = {20.125, 0.75, -3};
  d = {19.75, 0.75, -4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {20.125, 0.75, -3};
  b = {19.75, 0.75, -4};
  c = {19, 0, -4};
  d = {19.375, 0, -3};

  setNormalAndVertexQuads(a, b, c, d);

  // 2

  a = {19.75, 1.75, -4};
  b = {19, 2, -5};
  c = {19, 1, -5};
  d = {19.75, 0.75, -4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {19.75, 0.75, -4};
  b = {19, 0, -4};
  c = {19, 0, -4};
  d = {19, 1, -5};

  setNormalAndVertexQuads(a, b, c, d);

  // 3

  a = {20.25, 1.75, -2.25};
  b = {20.125, 1.75, -3};
  c = {20.125, 0.75, -3};
  d = {20.25, 0.75, -2.25};

  setNormalAndVertexQuads(a, b, c, d);

  a = {20.125, 0.75, -3};
  b = {19.375, 0, -3};
  c = {19.375, 0, -2.25};
  d = {20.25, 0.75, -2.25};

  setNormalAndVertexQuads(a, b, c, d);

  // Sa strane do tocka

  a = {19, 2, -5};
  b = {19, 1, -5};
  c = {18.2, 1, -5};
  d = {18.2, 2, -5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {19, 1, -5};
  b = {18.2, 1, -5};
  c = {18.2, 0, -4};
  d = {19, 0, -4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {17.5, 2.5, -5};
  b = {19, 2.5, -5};
  c = {19, 2, -5};
  d = {18.2, 2, -5};

  setNormalAndVertexQuads(a, b, c, d);

  // Desno svetlo

  glColor3f(0.835, 0.360, 0.043);

  a = {19.75, 2.25, 4};
  b = {19.75, 2.5, 4};
  c = {19, 3, 5};
  d = {19, 2.5, 5};

  setNormalAndVertexQuads(a, b, c, d);

  glColor3f(0.95, 0.95, 0.95);

  a = {19.75, 2.5, 4};
  b = {19, 3, 5};
  c = {19, 3.25, 4.75};
  d = {19.75, 2.5, 4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {19.75, 2.5, 4};
  b = {19, 3.25, 4.75};
  c = {19, 3.25, 4.25};
  d = {19.75, 2.5, 4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {19.75, 2.5, 4};
  b = {19, 3.25, 4.25};
  c = {19, 3, 4};
  d = {19.75, 2.5, 4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {19.5, 3.125, 3};
  b = {20, 2.5, 2.75};
  c = {19.75, 2.5, 4};
  d = {19, 3.25, 4.25};

  setNormalAndVertexQuads(a, b, c, d);

  a = {19.75, 2.25, 4};
  b = {19.75, 2.5, 4};
  c = {20, 2.5, 2.75};
  d = {20.125, 2.25, 3};

  setNormalAndVertexQuads(a, b, c, d);

  // Levo svetlo

  glColor3f(0.835, 0.360, 0.043);

  a = {19.75, 2.25, -4};
  b = {19.75, 2.5, -4};
  c = {19, 3, -5};
  d = {19, 2.5, -5};

  setNormalAndVertexQuads(a, b, c, d);

  glColor3f(0.95, 0.95, 0.95);

  a = {19.75, 2.5, -4};
  b = {19, 3, -5};
  c = {19, 3.25, -4.75};
  d = {19.75, 2.5, -4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {19.75, 2.5, -4};
  b = {19, 3.25, -4.75};
  c = {19, 3.25, -4.25};
  d = {19.75, 2.5, -4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {19.75, 2.5, -4};
  b = {19, 3.25, -4.25};
  c = {19, 3, -4};
  d = {19.75, 2.5, -4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {19.5, 3.125, -3};
  b = {20, 2.5, -2.75};
  c = {19.75, 2.5, -4};
  d = {19, 3.25, -4.25};

  setNormalAndVertexQuads(a, b, c, d);

  a = {19.75, 2.25, -4};
  b = {19.75, 2.5, -4};
  c = {20, 2.5, -2.75};
  d = {20.125, 2.25, -3};

  setNormalAndVertexQuads(a, b, c, d);

  // Prednji deo levo

  glColor3f(0, 1, 0);

  a = {14, 3, -5};
  b = {14, 3.25, -4.75};
  c = {19, 3.25, -4.75};
  d = {19, 3, -5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {14, 3, -4};
  b = {14, 3.25, -4.25};
  c = {19, 3.25, -4.25};
  d = {19, 3, -4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {14, 3.25, -4.25};
  b = {19, 3.25, -4.25};
  c = {19, 3.25, -4.75};
  d = {14, 3.25, -4.75};

  setNormalAndVertexQuads(a, b, c, d);

  glColor3f(0, 1, 0);

  a = {19, 3.25, -3};
  b = {19, 3, -4};
  c = {19.5, 3.125, -3};
  d = {19, 3.25, -3};

  setNormalAndVertexQuads(a, b, c, d);

  a = {20, 2.5, -2.75};
  b = {20, 2.5, -2.25};
  c = {20.25, 2.25, -2.25};
  d = {20.125, 2.25, -3};

  setNormalAndVertexQuads(a, b, c, d);

  a = {20.25, 2.25, -2.25};
  b = {20.25, 1.75, -2.25};
  c = {20.125, 1.75, -3};
  d = {20.125, 2.25, -3};

  setNormalAndVertexQuads(a, b, c, d);

  a = {20.125, 2.25, -3};
  b = {19.75, 2.25, -4};
  c = {19.75, 1.75, -4};
  d = {20.125, 1.75, -3};

  setNormalAndVertexQuads(a, b, c, d);

  a = {19.75, 2.25, -4};
  b = {19.75, 1.75, -4};
  c = {19, 2, -5};
  d = {19, 2.5, -5};

  setNormalAndVertexQuads(a, b, c, d);

  // Unutrasnjost auta

  glColor3f(0.5, 0.5, 0.5);

  a = {6.5, 2, -4};
  b = {12, 1.5, -4};
  c = {12, 0, -4};
  d = {6.5, 0, -4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {6.5, 2, -4};
  b = {6.5, 0, -4};
  c = {5, 0, -4};
  d = {5, 3.5, -4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {12, 1.5, -4};
  b = {12, 0, -4};
  c = {14, 0, -4};
  d = {14, 3, -4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {6.5, 2, 4};
  b = {12, 1.5, 4};
  c = {12, 0, 4};
  d = {6.5, 0, 4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {6.5, 2, 4};
  b = {6.5, 0, 4};
  c = {5, 0, 4};
  d = {5, 3.5, 4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {12, 1.5, 4};
  b = {12, 0, 4};
  c = {14, 0, 4};
  d = {14, 3, 4};

  setNormalAndVertexQuads(a, b, c, d);

  // Pod

  a = {5, 0, -4};
  b = {14, 0, -4};
  c = {14, 0, 4};
  d = {5, 0, 4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {5, 3.5, 4};
  b = {-0.5, 3.5, 4};
  c = {-0.5, 3.5, -4};
  d = {5, 3.5, -4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {14, 3, 4};
  b = {14, 3, -4};
  c = {12, 1.5, -4};
  d = {12, 1.5, 4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {12, 1.5, -4};
  b = {12, 1.5, 4};
  c = {12, 0, 4};
  d = {12, 0, -4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {5, 3.5, 4};
  b = {5, 3.5, -4};
  c = {5, 0, -4};
  d = {5, 0, 4};

  setNormalAndVertexQuads(a, b, c, d);

  // Brzinometar

  glColor3f(0.2, 0.2, 0.2);
  a = {12.99, 2.25, -1.25};
  b = {12.99, 2.25, -3.25};
  c = {13.24, 2.4375, -3.25};
  d = {13.24, 2.4375, -1.25};

  setNormalAndVertexQuads(a, b, c, d);

  a = {13.24, 2.4375, -3.25};
  b = {13.24, 2.4375, -1.25};
  c = {13.74, 2.8125, -1.5};
  d = {13.74, 2.8125, -3};

  setNormalAndVertexQuads(a, b, c, d);

  // Donja povrsina table

  a = {13, 2.25, -1.25};
  b = {13, 2.25, -3.25};
  c = {12.5, 2.25, -3.25};
  d = {12.5, 2.25, -1.25};

  setNormalAndVertexQuads(a, b, c, d);

  // Strane

  // Leva

  a = {13, 2.25, -3.25};
  b = {13.25, 2.4375, -3.25};
  c = {12.5, 2.4375, -3.25};
  d = {12.5, 2.25, -3.25};

  setNormalAndVertexQuads(a, b, c, d);

  a = {13.24, 2.4375, -3.25};
  b = {12.49, 2.4375, -3.25};
  c = {12.75, 2.8125, -3};
  d = {13.74, 2.8125, -3};

  setNormalAndVertexQuads(a, b, c, d);

  // Desna

  a = {13, 2.25, -1.25};
  b = {13.25, 2.4375, -1.25};
  c = {12.5, 2.4375, -1.25};
  d = {12.5, 2.25, -1.25};

  setNormalAndVertexQuads(a, b, c, d);

  a = {13.24, 2.4375, -1.25};
  b = {12.49, 2.4375, -1.25};
  c = {12.75, 2.8125, -1.5};
  d = {13.74, 2.8125, -1.5};

  setNormalAndVertexQuads(a, b, c, d);

  // Gornja strana

  a = {12.75, 2.8125, -1.5};
  b = {13.74, 2.8125, -1.5};
  c = {13.74, 2.8125, -2};
  d = {13.25, 2.8125, -2};

  setNormalAndVertexQuads(a, b, c, d);

  a = {12.75, 2.8125, -3};
  b = {13.74, 2.8125, -3};
  c = {13.74, 2.8125, -2.5};
  d = {13.25, 2.8125, -2.5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {13.74, 2.8125, -2};
  b = {13.25, 2.8125, -2};
  c = {13.25, 2.8125, -2.5};
  d = {13.74, 2.8125, -2.5};

  setNormalAndVertexQuads(a, b, c, d);

  // Volan

  glColor3f(0.2, 0.2, 0.2);
  a = {12.49, 1.875, -1.25};
  b = {12.49, 1.875, -3.25};
  c = {11.99, 1.5, -3.25};
  d = {11.99, 1.5, -1.25};

  setNormalAndVertexQuads(a, b, c, d);

  a = {12.49, 1.875, -1.25};
  b = {12.49, 1.875, -3.25};
  c = {12.25, 2.25, -2.6};
  d = {12.25, 2.25, -1.85};

  setNormalAndVertexQuads(a, b, c, d);

  a = {12.25, 2.25, -2.6};
  b = {12.25, 2.25, -1.85};
  c = {11.5, 2.25, -2.1};
  d = {11.5, 2.25, -2.35};

  setNormalAndVertexQuads(a, b, c, d);

  a = {12.49, 1.875, -3.25};
  b = {11.99, 1.5, -3.25};
  c = {11.5, 2.25, -2.35};
  d = {12.25, 2.25, -2.6};

  setNormalAndVertexQuads(a, b, c, d);

  a = {12.49, 1.875, -1.25};
  b = {11.99, 1.5, -1.25};
  c = {11.5, 2.25, -2.1};
  d = {12.25, 2.25, -1.85};

  setNormalAndVertexQuads(a, b, c, d);

  a = {11.99, 1.5, -3.25};
  b = {11.99, 1.5, -1.25};
  c = {11.5, 2.25, -2.1};
  d = {11.5, 2.25, -2.35};

  setNormalAndVertexQuads(a, b, c, d);

  // Radio

  glColor3f(0.2, 0.2, 0.2);

  a = {13.74, 2.8125, -0.75};
  b = {13, 2.8125, -0.75};
  c = {13, 2.8125, 0.75};
  d = {13.74, 2.8125, 0.75};

  setNormalAndVertexQuads(a, b, c, d);

  a = {13, 2.8125, -0.75};
  b = {13, 2.8125, 0.75};
  c = {13, 1, 0.75};
  d = {13, 1, -0.75};

  setNormalAndVertexQuads(a, b, c, d);

  glColor3f(0.1, 0.1, 0.1);

  a = {13.01, 2.26, -0.75};
  b = {13.01, 2.26, 0.75};
  c = {11.99, 1.5, 0.75};
  d = {11.99, 1.5, -0.75};

  setNormalAndVertexQuads(a, b, c, d);

  glColor3f(0.509, 0.968, 0.964);

  a = {12.89, 2.175, -0.5};
  b = {12.89, 2.175, 0.5};
  c = {12.08, 1.575, 0.5};
  d = {12.08, 1.575, -0.5};

  setNormalAndVertexQuads(a, b, c, d);

  // Druga nijansa panela
  /*
              glColor3f(0.1,0.1,0.1);

              a={13.74,2.8125,0.75};
              b={13.74,2.8125,4};
              c={12.99,2.25,4};
              d={12.99,2.25,0.75};

              setNormalAndVertexQuads(a,b,c,d);

              a={13.74,2.8125,-0.75};
              b={13.74,2.8125,-1.5};
              c={12.99,2.25,-1.5};
              d={12.99,2.25,-0.75};

              setNormalAndVertexQuads(a,b,c,d);

              a={13.74,2.8125,-4};
              b={13.74,2.8125,-2.5};
              c={12.99,2.25,-3.25};
              d={12.99,2.25,-4};

              setNormalAndVertexQuads(a,b,c,d);

              a={13.74,2.8125,-4};
              b={13.74,2.8125,4};
              c={14,3,3};
              d={14,3,-3};

              //setNormalAndVertexQuads(a,b,c,d);*/

  // Povrsina koja razdvaja sedista i podloga za menjac

  glColor3f(0.3, 0.3, 0.3);
  a = {12, 0.5, -0.5};
  b = {5, 0.5, -0.5};
  c = {5, 0.5, 0.5};
  d = {12, 0.5, 0.5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {12, 0.5, -0.5};
  b = {12, 0, -0.75};
  c = {5, 0, -0.75};
  d = {5, 0.5, -0.5};
  setNormalAndVertexQuads(a, b, c, d);

  a = {12, 0.5, 0.5};
  b = {12, 0, 0.75};
  c = {5, 0, 0.75};
  d = {5, 0.5, 0.5};
  setNormalAndVertexQuads(a, b, c, d);

  // Menjac

  a = {10.75, 0.5, -0.5};
  b = {9.75, 0.5, -0.5};
  c = {10, 0.7, -0.15};
  d = {10.5, 0.7, -0.15};

  setNormalAndVertexQuads(a, b, c, d);

  a = {10.75, 0.5, 0.5};
  b = {9.75, 0.5, 0.5};
  c = {10, 0.7, 0.15};
  d = {10.5, 0.7, 0.15};

  setNormalAndVertexQuads(a, b, c, d);

  a = {9.75, 0.5, -0.5};
  b = {10, 0.7, -0.15};
  c = {10, 0.7, 0.15};
  d = {9.75, 0.5, 0.5};
  setNormalAndVertexQuads(a, b, c, d);

  a = {10.75, 0.5, -0.5};
  b = {10.5, 0.7, -0.15};
  c = {10.5, 0.7, 0.15};
  d = {10.75, 0.5, 0.5};
  setNormalAndVertexQuads(a, b, c, d);

  a = {10, 0.7, -0.15};
  b = {10, 0.7, 0.15};
  c = {10.5, 0.7, 0.15};
  d = {10.5, 0.7, -0.15};

  setNormalAndVertexQuads(a, b, c, d);

  // Levo sediste

  // Donji deo

  glColor3f(0.7, 0, 0);

  a = {10.5, 0.1, -3.75};
  b = {7, 0.1, -3.75};
  c = {7, 0.1, -1};
  d = {10.5, 0.1, -1};

  setNormalAndVertexQuads(a, b, c, d);

  a = {10.5, 0.1, -1};
  b = {10.5, 0.1, -3.75};
  c = {10.5, 0.5, -3.75};
  d = {10.5, 0.5, -1};

  setNormalAndVertexQuads(a, b, c, d);

  a = {10.5, 0.5, -3.75};
  b = {10.5, 0.5, -1};
  c = {10.25, 1, -1};
  d = {10.25, 1, -3.75};

  setNormalAndVertexQuads(a, b, c, d);

  a = {10.25, 1, -1};
  b = {10.25, 1, -3.75};
  c = {10, 1, -3.75};
  d = {10, 1, -1};

  setNormalAndVertexQuads(a, b, c, d);

  a = {10, 1, -3.75};
  b = {10, 1, -1};
  c = {9.75, 0.75, -1};
  d = {9.75, 0.75, -3.75};

  setNormalAndVertexQuads(a, b, c, d);

  a = {9.75, 0.75, -1};
  b = {9.75, 0.75, -3.75};
  c = {7.5, 0.75, -3.75};
  d = {7.5, 0.75, -1};

  setNormalAndVertexQuads(a, b, c, d);

  // Zatvaranje donje strane

  a = {7, 0.1, -1};
  b = {10.5, 0.1, -1};
  c = {10.5, 0.5, -1};
  d = {7.25, 0.5, -1};

  setNormalAndVertexQuads(a, b, c, d);
  a = {10.5, 0.5, -1};
  b = {7.25, 0.5, -1};
  c = {7.5, 0.75, -1};
  d = {9.75, 0.75, -1};

  setNormalAndVertexQuads(a, b, c, d);

  a = {10.5, 0.5, -1};
  b = {9.75, 0.75, -1};
  c = {10, 1, -1};
  d = {10.25, 1, -1};

  setNormalAndVertexQuads(a, b, c, d);

  a = {7, 0.1, -3.75};
  b = {10.5, 0.1, -3.75};
  c = {10.5, 0.5, -3.75};
  d = {7.25, 0.5, -3.75};

  setNormalAndVertexQuads(a, b, c, d);
  a = {10.5, 0.5, -3.75};
  b = {7.25, 0.5, -3.75};
  c = {7.5, 0.75, -3.75};
  d = {9.75, 0.75, -3.75};

  setNormalAndVertexQuads(a, b, c, d);

  a = {10.5, 0.5, -3.75};
  b = {9.75, 0.75, -3.75};
  c = {10, 1, -3.75};
  d = {10.25, 1, -3.75};

  setNormalAndVertexQuads(a, b, c, d);

  // Gornji deo

  a = {7, 0.1, -3.75};
  b = {7, 0.1, -1};
  c = {6, 4, -1};
  d = {6, 4, -3.75};

  setNormalAndVertexQuads(a, b, c, d);

  a = {7.5, 0.75, -3.75};
  b = {7.5, 0.75, -1};
  c = {6.4, 4, -1};
  d = {6.4, 4, -3.75};

  setNormalAndVertexQuads(a, b, c, d);

  a = {6.4, 4, -1};
  b = {6.4, 4, -3.75};
  c = {6.2, 4.1, -3.75};
  d = {6.2, 4.1, -1};

  setNormalAndVertexQuads(a, b, c, d);

  a = {6.2, 4.1, -3.75};
  b = {6.2, 4.1, -1};
  c = {6, 4, -1};
  d = {6, 4, -3.75};

  setNormalAndVertexQuads(a, b, c, d);

  a = {7, 0.1, -3.75};
  b = {7.5, 0.75, -3.75};
  c = {6.4, 4, -3.75};
  d = {6, 4, -3.75};

  setNormalAndVertexQuads(a, b, c, d);

  a = {7, 0.1, -1};
  b = {7.5, 0.75, -1};
  c = {6.4, 4, -1};
  d = {6, 4, -1};

  setNormalAndVertexQuads(a, b, c, d);

  // Desno sediste

  a = {10.5, 0.1, +3.75};
  b = {7, 0.1, +3.75};
  c = {7, 0.1, +1};
  d = {10.5, 0.1, +1};

  setNormalAndVertexQuads(a, b, c, d);

  a = {10.5, 0.1, +1};
  b = {10.5, 0.1, +3.75};
  c = {10.5, 0.5, +3.75};
  d = {10.5, 0.5, +1};

  setNormalAndVertexQuads(a, b, c, d);

  a = {10.5, 0.5, +3.75};
  b = {10.5, 0.5, +1};
  c = {10.25, 1, +1};
  d = {10.25, 1, +3.75};

  setNormalAndVertexQuads(a, b, c, d);

  a = {10.25, 1, +1};
  b = {10.25, 1, +3.75};
  c = {10, 1, +3.75};
  d = {10, 1, +1};

  setNormalAndVertexQuads(a, b, c, d);

  a = {10, 1, +3.75};
  b = {10, 1, +1};
  c = {9.75, 0.75, +1};
  d = {9.75, 0.75, +3.75};

  setNormalAndVertexQuads(a, b, c, d);

  a = {9.75, 0.75, +1};
  b = {9.75, 0.75, +3.75};
  c = {7.5, 0.75, +3.75};
  d = {7.5, 0.75, +1};

  setNormalAndVertexQuads(a, b, c, d);

  // Zatvaranje donje strane

  a = {7, 0.1, +1};
  b = {10.5, 0.1, +1};
  c = {10.5, 0.5, +1};
  d = {7.25, 0.5, +1};

  setNormalAndVertexQuads(a, b, c, d);
  a = {10.5, 0.5, +1};
  b = {7.25, 0.5, +1};
  c = {7.5, 0.75, +1};
  d = {9.75, 0.75, +1};

  setNormalAndVertexQuads(a, b, c, d);

  a = {10.5, 0.5, +1};
  b = {9.75, 0.75, +1};
  c = {10, 1, +1};
  d = {10.25, 1, +1};

  setNormalAndVertexQuads(a, b, c, d);

  a = {7, 0.1, +3.75};
  b = {10.5, 0.1, +3.75};
  c = {10.5, 0.5, +3.75};
  d = {7.25, 0.5, +3.75};

  setNormalAndVertexQuads(a, b, c, d);
  a = {10.5, 0.5, +3.75};
  b = {7.25, 0.5, +3.75};
  c = {7.5, 0.75, +3.75};
  d = {9.75, 0.75, +3.75};

  setNormalAndVertexQuads(a, b, c, d);

  a = {10.5, 0.5, +3.75};
  b = {9.75, 0.75, +3.75};
  c = {10, 1, +3.75};
  d = {10.25, 1, +3.75};

  setNormalAndVertexQuads(a, b, c, d);

  // Gornji deo

  a = {7, 0.1, +3.75};
  b = {7, 0.1, +1};
  c = {6, 4, +1};
  d = {6, 4, +3.75};

  setNormalAndVertexQuads(a, b, c, d);

  a = {7.5, 0.75, +3.75};
  b = {7.5, 0.75, +1};
  c = {6.4, 4, +1};
  d = {6.4, 4, +3.75};

  setNormalAndVertexQuads(a, b, c, d);

  a = {6.4, 4, +1};
  b = {6.4, 4, +3.75};
  c = {6.2, 4.1, +3.75};
  d = {6.2, 4.1, +1};

  setNormalAndVertexQuads(a, b, c, d);

  a = {6.2, 4.1, +3.75};
  b = {6.2, 4.1, +1};
  c = {6, 4, +1};
  d = {6, 4, +3.75};

  setNormalAndVertexQuads(a, b, c, d);

  a = {7, 0.1, +3.75};
  b = {7.5, 0.75, +3.75};
  c = {6.4, 4, +3.75};
  d = {6, 4, +3.75};

  setNormalAndVertexQuads(a, b, c, d);

  a = {7, 0.1, +1};
  b = {7.5, 0.75, +1};
  c = {6.4, 4, +1};
  d = {6, 4, +1};

  setNormalAndVertexQuads(a, b, c, d);

  // Hauba

  glColor3f(0, 1, 0);

  a = {14, 3, 4};
  b = {19, 3, 4};
  c = {19, 3.25, 3};
  d = {14, 3.25, 3};

  setNormalAndVertexQuads(a, b, c, d);

  a = {14, 3, -4};
  b = {19, 3, -4};
  c = {19, 3.25, -3};
  d = {14, 3.25, -3};

  setNormalAndVertexQuads(a, b, c, d);

  a = {19, 3.25, -3};
  b = {14, 3.25, -3};
  c = {14, 3.25, 3};
  d = {19, 3.25, 3};

  setNormalAndVertexQuads(a, b, c, d);

  a = {14, 3.25, -3};
  b = {14, 3.25, 3};
  c = {14, 3, 4};
  d = {14, 3, -4};

  setNormalAndVertexQuads(a, b, c, d);

  // Soferka

  /*
  glColor3f(0.776, 0.886, 0.890);
  a={14,3.25,-3};
  b={14,3.25,3};
  c={10.25,6,3};
  d={10.25,6,-3};

  setNormalAndVertexQuads(a,b,c,d);

  */

  /*
  a={14,3.25,-3};
  b={14,3.125,-3.5};
  c={10.25,5.875,-3.5};
  d={10.25,6,-3};


  setNormalAndVertexQuads(a,b,c,d);

  a={14,3.25,3};
  b={14,3.125,3.5};
  c={10.25,5.875,3.5};
  d={10.25,6,3};

  setNormalAndVertexQuads(a,b,c,d);
  */

  /*a={14,2.875,-3.5};							12.75,4.708,0
  b={10.25,5.625,-3.5};
  c={10.25,5.625,3.5};
  d={14,2.875,3.5};

  setNormalAndVertexQuads(a,b,c,d);*/

  // Leva ivica

  glColor3f(0.3, 0.3, 0.3);
  a = {14, 3, -4};
  b = {14, 3.125, -3.5};
  c = {10.25, 5.875, -3.5};
  d = {10.25, 5.75, -4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {10.25, 5.75, -4};
  b = {14, 3, -4};
  c = {14, 2.875, -3.5};
  d = {10.25, 5.625, -3.5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {14, 3.125, -3.5};
  b = {10.25, 5.875, -3.5};
  c = {10.25, 5.625, -3.5};
  d = {14, 2.875, -3.5};

  setNormalAndVertexQuads(a, b, c, d);

  // Desna ivica

  a = {14, 3, 4};
  b = {14, 3.125, 3.5};
  c = {10.25, 5.875, 3.5};
  d = {10.25, 5.75, 4};

  setNormalAndVertexQuads(a, b, c, d);

  a = {10.25, 5.75, 4};
  b = {14, 3, 4};
  c = {14, 2.875, 3.5};
  d = {10.25, 5.625, 3.5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {14, 3.125, 3.5};
  b = {10.25, 5.875, 3.5};
  c = {10.25, 5.625, 3.5};
  d = {14, 2.875, 3.5};

  setNormalAndVertexQuads(a, b, c, d);

  // Zatvaranje soferke odozgo

  glColor3f(0.15, 0.15, 0.15);

  a = {10.25, 5.625, -3.5};
  b = {10.25, 6, -3};
  c = {10.25, 6, 3};
  d = {10.25, 5.625, 3.5};

  setNormalAndVertexQuads(a, b, c, d);

  // Zatvaramo zvucnik

  glColor3f(0.3, 0, 0);

  a = {4.75, 3.5, 2.75};
  b = {4.75, 3.5, -2.75};
  c = {4.75, 5, -2.75};
  d = {4.75, 5, 2.75};

  setNormalAndVertexQuads(a, b, c, d);

  a = {4.75, 3.65, 2.5};
  b = {4.75, 3.65, -2.5};
  c = {4.99, 3.5, -2.75};
  d = {4.99, 3.5, 2.75};

  setNormalAndVertexQuads(a, b, c, d);

  a = {4.75, 4.85, 2.5};
  b = {4.75, 4.85, -2.5};
  c = {4.99, 5, -2.75};
  d = {4.99, 5, 2.75};

  setNormalAndVertexQuads(a, b, c, d);

  a = {4.99, 3.5, -2.75};
  b = {4.99, 5, -2.75};
  c = {4.75, 4.85, -2.5};
  d = {4.75, 3.65, -2.5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {4.99, 3.5, 2.75};
  b = {4.99, 5, 2.75};
  c = {4.75, 4.85, 2.5};
  d = {4.75, 3.65, 2.5};

  setNormalAndVertexQuads(a, b, c, d);

  // RetrovizoriPoligon

  glColor3f(0.2, 0.2, 0.2);

  // Levi retrovizor

  a = {14, 3.5, -4.5};
  b = {14.5, 3.5, -4.25};
  c = {14.5, 3.825, -4.25};
  d = {14, 3.825, -4.5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {14, 3.5, -4.5};
  b = {14, 3.825, -4.5};
  c = {14.25, 3.6, -5.3};
  d = {14.25, 3.5, -5.3};

  setNormalAndVertexQuads(a, b, c, d);

  a = {14.25, 3.6, -5.3};
  b = {14.25, 3.5, -5.3};
  c = {13.75, 3.35, -4.8};
  d = {13.75, 3.85, -4.8};

  setNormalAndVertexQuads(a, b, c, d);

  a = {14.5, 3.825, -4.25};
  b = {14, 3.825, -4.5};
  c = {14.25, 3.6, -5.3};
  d = {14.5, 3.6, -5.3};

  setNormalAndVertexQuads(a, b, c, d);

  a = {14.25, 3.6, -5.3};
  b = {14.5, 3.6, -5.3};
  c = {13.75, 3.85, -5.8};
  d = {13.75, 3.85, -4.8};

  setNormalAndVertexQuads(a, b, c, d);

  a = {14.25, 3.6, -5.3};
  b = {14.25, 3.6, -5.3};
  c = {13.75, 3.35, -5.8};
  d = {13.75, 3.35, -4.8};

  setNormalAndVertexQuads(a, b, c, d);

  a = {14.5, 3.825, -4.25};
  b = {14.5, 3.6, -5.3};
  c = {14.5, 3.5, -5.3};
  d = {14.5, 3.5, -4.25};

  setNormalAndVertexQuads(a, b, c, d);

  a = {14.5, 3.5, -5.3};
  b = {13.75, 3.35, -5.8};
  c = {13.75, 3.85, -5.8};
  d = {14.5, 3.6, -5.3};

  setNormalAndVertexQuads(a, b, c, d);

  // Desni retrovizor

  a = {14, 3.5, +4.5};
  b = {14.5, 3.5, +4.25};
  c = {14.5, 3.825, +4.25};
  d = {14, 3.825, +4.5};

  setNormalAndVertexQuads(a, b, c, d);

  a = {14, 3.5, +4.5};
  b = {14, 3.825, +4.5};
  c = {14.25, 3.6, +5.3};
  d = {14.25, 3.5, +5.3};

  setNormalAndVertexQuads(a, b, c, d);

  a = {14.25, 3.6, +5.3};
  b = {14.25, 3.5, +5.3};
  c = {13.75, 3.35, +4.8};
  d = {13.75, 3.85, +4.8};

  setNormalAndVertexQuads(a, b, c, d);

  a = {14.5, 3.825, +4.25};
  b = {14, 3.825, +4.5};
  c = {14.25, 3.6, +5.3};
  d = {14.5, 3.6, +5.3};

  setNormalAndVertexQuads(a, b, c, d);

  a = {14.25, 3.6, +5.3};
  b = {14.5, 3.6, +5.3};
  c = {13.75, 3.85, +5.8};
  d = {13.75, 3.85, +4.8};

  setNormalAndVertexQuads(a, b, c, d);

  a = {14.25, 3.6, 5.3};
  b = {14.25, 3.6, 5.3};
  c = {13.75, 3.35, 5.8};
  d = {13.75, 3.35, 4.8};

  setNormalAndVertexQuads(a, b, c, d);

  a = {14.5, 3.825, +4.25};
  b = {14.5, 3.6, +5.3};
  c = {14.5, 3.5, +5.3};
  d = {14.5, 3.5, +4.25};

  setNormalAndVertexQuads(a, b, c, d);

  a = {14.5, 3.5, +5.3};
  b = {13.75, 3.35, +5.8};
  c = {13.75, 3.85, +5.8};
  d = {14.5, 3.6, +5.3};

  setNormalAndVertexQuads(a, b, c, d);

  glEnd();

  glBegin(GL_TRIANGLES);

  glColor3f(0.1, 0.1, 0.1);

  // Leva strana

  a = {5, 2, -5};
  b = {3.5, 3, -5};
  c = {5, 3, -5};

  setNormalAndVertexTriangles(a, b, c);

  a = {1.5, 3, -5};
  b = {0, 2, -5};
  c = {0, 3, -5};

  setNormalAndVertexTriangles(a, b, c);

  a = {14, 2, -5};
  b = {15.5, 2.5, -5};
  c = {14, 2.5, -5};

  setNormalAndVertexTriangles(a, b, c);

  a = {1.5, 3, -5};
  b = {0, 2, -5};
  c = {0, 1, -5};

  setNormalAndVertexTriangles(a, b, c);

  // Zeleni krajevi leve strane

  glColor3f(0, 1, 0);

  a = {0, 3.5, -4};
  b = {-0.5, 3.5, -4};
  c = {0, 4.25, -4.5};

  setNormalAndVertexTriangles(a, b, c);

  a = {0, 3.5, -5};
  b = {-0.5, 3.5, -5};
  c = {0, 4.25, -4.5};

  setNormalAndVertexTriangles(a, b, c);

  a = {-0.5, 3.5, -5};
  b = {-0.5, 3.5, -4};
  c = {0, 4.25, -4.5};

  setNormalAndVertexTriangles(a, b, c);

  a = {13.75, 3.5, -4.5};
  b = {14.5, 3.5, -4.75};
  c = {14.5, 3.5, -4.25};

  setNormalAndVertexTriangles(a, b, c);

  // Desna strana

  glColor3f(0.1, 0.1, 0.1);

  a = {5, 2, 5};
  b = {3.5, 3, 5};
  c = {5, 3, 5};

  setNormalAndVertexTriangles(a, b, c);

  a = {1.5, 3, 5};
  b = {0, 2, 5};
  c = {0, 3, 5};

  setNormalAndVertexTriangles(a, b, c);

  a = {1.5, 3, 5};
  b = {0, 2, 5};
  c = {0, 1, 5};

  setNormalAndVertexTriangles(a, b, c);

  a = {14, 2, 5};
  b = {15.5, 2.5, 5};
  c = {14, 2.5, 5};

  setNormalAndVertexTriangles(a, b, c);

  // Zeleni krajevi desnee strane

  glColor3f(0, 1, 0);

  a = {0, 3.5, 4};
  b = {-0.5, 3.5, 4};
  c = {0, 4.25, 4.5};

  setNormalAndVertexTriangles(a, b, c);

  a = {0, 3.5, 5};
  b = {-0.5, 3.5, 5};
  c = {0, 4.25, 4.5};

  setNormalAndVertexTriangles(a, b, c);

  a = {-0.5, 3.5, 5};
  b = {-0.5, 3.5, 4};
  c = {0, 4.25, 4.5};

  setNormalAndVertexTriangles(a, b, c);

  a = {13.75, 3.5, 4.5};
  b = {14.5, 3.5, 4.75};
  c = {14.5, 3.5, 4.25};

  setNormalAndVertexTriangles(a, b, c);

  // Zatvaranje leve ivice soferke

  glColor3f(0.2, 0.2, 0.2);
  a = {10.25, 5.75, -4};
  b = {10.25, 5.875, -3.5};
  c = {10.25, 5.625, -3.5};

  setNormalAndVertexTriangles(a, b, c);

  a = {10.25, 5.875, -3.5};
  b = {10.25, 5.625, -3.5};
  c = {10.25, 6, -3};

  setNormalAndVertexTriangles(a, b, c);

  // Zatvaranje desne ivice soferke

  glColor3f(0.2, 0.2, 0.2);
  a = {10.25, 5.75, 4};
  b = {10.25, 5.875, 3.5};
  c = {10.25, 5.625, 3.5};

  setNormalAndVertexTriangles(a, b, c);

  a = {10.25, 5.875, 3.5};
  b = {10.25, 5.625, 3.5};
  c = {10.25, 6, 3};

  setNormalAndVertexTriangles(a, b, c);

  // Desni prozor

  glColor3f(0.1, 0.1, 0.1);

  // Zadnja strana auta

  a = {-0.5, 2, -4};
  b = {-0.5, 1, -4};
  c = {-0.5, 2, -2};

  setNormalAndVertexTriangles(a, b, c);

  a = {-0.5, 2, 4};
  b = {-0.5, 1, 4};
  c = {-0.5, 2, 2};

  setNormalAndVertexTriangles(a, b, c);

  // Zatvaranje gornjeg dela levog sedista

  glColor3f(1, 0, 0);

  setNormalAndVertexTriangles(a, b, c);

  a = {6.2, 4.1, -1};
  b = {6, 4, -1};
  c = {6.4, 4, -1};

  setNormalAndVertexTriangles(a, b, c);

  setNormalAndVertexTriangles(a, b, c);

  a = {6.2, 4.1, -3.75};
  b = {6, 4, -3.75};
  c = {6.4, 4, -3.75};

  setNormalAndVertexTriangles(a, b, c);

  // Zatvaranje gornjeg dela desnog sedista

  glColor3f(1, 0, 0);

  setNormalAndVertexTriangles(a, b, c);

  a = {6.2, 4.1, 1};
  b = {6, 4, 1};
  c = {6.4, 4, 1};

  setNormalAndVertexTriangles(a, b, c);

  setNormalAndVertexTriangles(a, b, c);

  a = {6.2, 4.1, 3.75};
  b = {6, 4, 3.75};
  c = {6.4, 4, 3.75};

  setNormalAndVertexTriangles(a, b, c);

  // Strane radija

  glColor3f(0.2, 0.2, 0.2);

  a = {13, 1, 0.75};
  b = {13, 2.8125, 0.75};
  c = {13.74, 2.8125, 0.75};

  setNormalAndVertexTriangles(a, b, c);

  a = {13, 1, -0.75};
  b = {13, 2.8125, -0.75};
  c = {13.74, 2.8125, -0.75};

  setNormalAndVertexTriangles(a, b, c);

  glEnd();

  // Stop svetla

  glPushMatrix();
  if ( !goRight )
    glColor3f(1, 0, 0);
  else
    glColor3f(1, 0.6, 0);

  glTranslatef(-0.7, 3, 4);
  glRotatef(90, 0, 1, 0);
  GLUquadric* quad4 = gluNewQuadric();
  gluCylinder(quad4, 0.4, 0.4, 0.2, 20, 20);
  gluCylinder(quad4, 0.2, 0.2, 0.2, 20, 20);
  gluDisk(quad4, 0.2, 0.4, 20, 20);

  glPopMatrix();

  glPushMatrix();
  if ( !goLeft )
    glColor3f(1, 0, 0);
  else
    glColor3f(1, 0.6, 0);

  glTranslatef(-0.7, 3, -4);
  glRotatef(90, 0, 1, 0);
  gluCylinder(quad4, 0.4, 0.4, 0.2, 20, 20);
  gluCylinder(quad4, 0.2, 0.2, 0.2, 20, 20);
  gluDisk(quad4, 0.2, 0.4, 20, 20);

  glPopMatrix();

  /*

  glPushMatrix();

          glTranslatef(23.5,2.5,0);
          glScalef(18,12,15);
      glColor3f(0.4,0.4,0.4);
      glTranslatef(-0.4,0.12,0);
      glutSolidCube(0.1);
      glScalef(1,0.1,1.5);
      glutSolidCube(0.1);
      glTranslatef(0,0.25,0);
      glutSolidCube(0.1);
      glTranslatef(0,0.25,0);
      glutSolidCube(0.1);
      glTranslatef(0,-0.75,0);
      glutSolidCube(0.1);
glPopMatrix();

*/

  drawRoof();

  // Menjac

  glPushMatrix();
  glTranslatef(9.7, 1.4, 0);
  glColor3f(1, 0, 0);
  glutSolidSphere(0.14, 20, 20);
  glRotatef(90, 1, 0, 0);
  glRotatef(40, 0, 1, 0);
  GLUquadric* quad6 = gluNewQuadric();
  glColor3f(0.2, 0.2, 0.2);
  gluCylinder(quad6, 0.1, 0.1, 1.5, 20, 20);
  glPopMatrix();

  // Brzinometar
  GLUquadric* quad7 = gluNewQuadric();
  /*
          glPushMatrix();
                  glColor3f(0,0,0.3);

                  glTranslatef(13.25,2.5,-2.7);
                  glRotatef(90,0,1,0);
                  glRotatef(45,1,0,0);
                  gluDisk(quad7,0,0.3,20,20);
          glPopMatrix();

          glPushMatrix();
                  glColor3f(0,0,0.3);
                  glTranslatef(13.25,2.5,-1.8);
                  glRotatef(90,0,1,0);
                  glRotatef(45,1,0,0);
                  gluDisk(quad7,0,0.3,20,20);
          glPopMatrix();
    */

  // RadioO

  glPushMatrix();
  glColor3f(0.6, 0, 0);
  glTranslatef(12.93, 2.4, -0.55);
  glRotatef(90, 0, 1, 0);
  gluCylinder(quad7, 0.12, 0.12, 0.1, 20, 20);
  gluDisk(quad7, 0, 0.12, 20, 20);

  glPopMatrix();

  glPushMatrix();
  glColor3f(0.6, 0, 0);
  glTranslatef(12.93, 2.4, 0.55);
  glRotatef(90, 0, 1, 0);
  gluCylinder(quad7, 0.12, 0.12, 0.1, 20, 20);
  gluDisk(quad7, 0, 0.12, 20, 20);

  glPopMatrix();

  glPushMatrix();
  glColor3f(0, 0, 0.7);
  glTranslatef(13.45, 2.65, 0);
  glScalef(1, 0.1, 1);
  glutSolidCube(1);

  glPopMatrix();

  // Dugmici za radio

  // Levi

  glPushMatrix();
  glColor3f(0.6, 0, 0);
  glTranslatef(12.15, 1.6, -0.6);
  glRotatef(-45, 0, 0, 1);
  glutSolidCube(0.125);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(12.35, 1.75, -0.6);
  glRotatef(-45, 0, 0, 1);
  glutSolidCube(0.125);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(12.55, 1.9, -0.6);
  glRotatef(-45, 0, 0, 1);
  glutSolidCube(0.125);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(12.75, 2.05, -0.6);
  glRotatef(-45, 0, 0, 1);
  glutSolidCube(0.125);
  glPopMatrix();

  // Desni

  glPushMatrix();
  glTranslatef(12.15, 1.6, 0.6);
  glRotatef(-45, 0, 0, 1);
  glutSolidCube(0.125);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(12.35, 1.75, 0.6);
  glRotatef(-45, 0, 0, 1);
  glutSolidCube(0.125);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(12.55, 1.9, 0.6);
  glRotatef(-45, 0, 0, 1);
  glutSolidCube(0.125);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(12.75, 2.05, 0.6);
  glRotatef(-45, 0, 0, 1);
  glutSolidCube(0.125);
  glPopMatrix();

  // Volan

  glPushMatrix();
  glBegin(GL_QUADS);
  glColor3f(1, 0, 0);

  a = {11.45, 2.35, -2.15};
  b = {11.45, 2.35, -2.3};
  c = {11.5, 2.8, -2.33};
  d = {11.5, 2.8, -2.12};

  setNormalAndVertexQuads(a, b, c, d);

  a = {11.45, 2.35, -2.15};
  b = {11.45, 2.35, -2.3};
  c = {11.45, 1.9, -2};
  d = {11.45, 1.975, -1.7};

  setNormalAndVertexQuads(a, b, c, d);

  a = {11.45, 2.35, -2.15};
  b = {11.45, 2.35, -2.3};
  c = {11.45, 1.975, -2.65};
  d = {11.45, 1.9, -2.4};

  setNormalAndVertexQuads(a, b, c, d);
  glEnd();
  glColor3f(0.2, 0.2, 0.2);
  glTranslatef(11.5, 2.3, -2.2);
  glRotatef(90, 0, 1, 0);
  glutSolidTorus(0.12, 0.55, 20, 20);
  glTranslatef(0, 0.05, -0.06);
  gluDisk(quad7, 0, 0.2, 20, 20);
  glPopMatrix();

  // Brisaci i migavci

  glPushMatrix();
  glColor3f(0.2, 0.2, 0.2);
  glTranslatef(11.9, 2.1, -2.2);
  glRotatef(-20, 1, 0, 0);
  gluCylinder(quad7, 0.02, 0.05, 1, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.2, 0.2, 0.2);
  glTranslatef(11.9, 2.45, -1.2);
  glScalef(1, 0.5, 1.2);
  glRotatef(-20, 1, 0, 0);
  glutSolidCube(0.2);

  glPopMatrix();

  glPushMatrix();
  glColor3f(0.2, 0.2, 0.2);
  glTranslatef(11.9, 2.1, -2.2);
  glRotatef(190, 0, 1, 0);
  glRotatef(-20, 1, 0, 0);
  gluCylinder(quad7, 0.02, 0.05, 1, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.2, 0.2, 0.2);
  glTranslatef(11.7, 2.45, -3.2);
  glScalef(1, 0.5, 1.2);
  glRotatef(20, 1, 0, 0);
  glutSolidCube(0.2);

  glPopMatrix();

  // Cupholders

  glPushMatrix();

  glTranslatef(0, 0, -0.5);

  glPushMatrix();
  glColor3f(0.2, 0.2, 0.2);
  glTranslatef(11.8, 1.3, 0.15);
  glRotatef(45, 0, 1, 0);
  glScalef(1, 0.5, 0.1);
  glutSolidCube(0.4);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.2, 0.2, 0.2);
  glTranslatef(11.8, 1.3, -0.15);
  glRotatef(-45, 0, 1, 0);
  glScalef(1, 0.5, 0.1);
  glutSolidCube(0.4);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.2, 0.2, 0.2);
  glTranslatef(11.5, 1.3, -0.15);
  glRotatef(45, 0, 1, 0);
  glScalef(1, 0.5, 0.1);
  glutSolidCube(0.4);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.2, 0.2, 0.2);
  glTranslatef(11.5, 1.3, 0.15);
  glRotatef(-45, 0, 1, 0);
  glScalef(1, 0.5, 0.1);
  glutSolidCube(0.4);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.2, 0.2, 0.2);
  glTranslatef(11.65, 1, 0);
  glRotatef(-90, 1, 0, 0);
  gluCylinder(quad7, 0.15, 0.25, 0.7, 20, 20);
  gluDisk(quad7, 0, 0.15, 20, 20);
  glTranslatef(0, 0, 0.6);
  glColor3f(0, 0.466, 0.745);
  gluDisk(quad7, 0, 0.2, 20, 20);

  glPopMatrix();

  glPopMatrix();

  glPushMatrix();

  glTranslatef(0, 0, 0.2);

  glPushMatrix();
  glColor3f(0.2, 0.2, 0.2);
  glTranslatef(11.8, 1.3, 0.15);
  glRotatef(45, 0, 1, 0);
  glScalef(1, 0.5, 0.1);
  glutSolidCube(0.4);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.2, 0.2, 0.2);
  glTranslatef(11.8, 1.3, -0.15);
  glRotatef(-45, 0, 1, 0);
  glScalef(1, 0.5, 0.1);
  glutSolidCube(0.4);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.2, 0.2, 0.2);
  glTranslatef(11.5, 1.3, -0.15);
  glRotatef(45, 0, 1, 0);
  glScalef(1, 0.5, 0.1);
  glutSolidCube(0.4);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.2, 0.2, 0.2);
  glTranslatef(11.5, 1.3, 0.15);
  glRotatef(-45, 0, 1, 0);
  glScalef(1, 0.5, 0.1);
  glutSolidCube(0.4);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.2, 0.2, 0.2);
  glTranslatef(11.65, 1, 0);
  glRotatef(-90, 1, 0, 0);
  gluCylinder(quad7, 0.15, 0.25, 0.7, 20, 20);
  gluDisk(quad7, 0, 0.15, 20, 20);
  glTranslatef(0, 0, 0.6);
  glColor3f(0, 0.466, 0.745);
  gluDisk(quad7, 0, 0.2, 20, 20);

  glPopMatrix();

  glPopMatrix();

  // Gas kocnica kvacilo

  glPushMatrix();
  glColor3f(0.1, 0.1, 0.1);
  glTranslatef(12, 0.15, -2.2);
  glScalef(1, 1.5, 1);
  glRotatef(45, 0, 0, 1);
  glutSolidCube(0.5);
  glTranslatef(0, 0, 0.7);
  glutSolidCube(0.5);
  glTranslatef(0, 0, -1.4);
  glutSolidCube(0.5);
  glPopMatrix();

  // Zvucnici

  glPushMatrix();
  double clip_plane3[] = {-1, 0, 0, 4.99};
  glClipPlane(GL_CLIP_PLANE3, clip_plane3);
  glEnable(GL_CLIP_PLANE3);
  glColor3f(0.3, 0, 0);
  glTranslatef(4.25, 4.26, 0);
  glScalef(3, 3, 11);
  glutSolidCube(0.5);

  glDisable(GL_CLIP_PLANE3);

  glPopMatrix();

  glPushMatrix();
  glColor3f(0.3, 0.3, 0.3);
  glTranslatef(5, 4.26, 1.5);
  glRotatef(-90, 0, 1, 0);
  gluCylinder(quad7, 0.7, 0.3, 1, 20, 20);
  glTranslatef(0, 0, 0.24);
  gluDisk(quad7, 0, 0.6, 20, 20);
  glColor3f(0, 0, 1);
  glTranslatef(0, 0, -0.01);
  gluDisk(quad7, 0, 0.3, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.3, 0.3, 0.3);
  glTranslatef(5, 4.26, -1.5);
  glRotatef(-90, 0, 1, 0);
  gluCylinder(quad7, 0.7, 0.3, 1, 20, 20);
  glTranslatef(0, 0, 0.24);
  gluDisk(quad7, 0, 0.6, 20, 20);
  glColor3f(0, 0, 1);
  glTranslatef(0, 0, -0.01);
  gluDisk(quad7, 0, 0.3, 20, 20);
  glPopMatrix();

  // Retrovizori

  // Levi

  glPushMatrix();
  glColor3f(0, 1, 0);
  glTranslatef(13.5, 3.6, -5.3);
  glScalef(0.5, 0.65, 1.2);
  glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.9, 0.9, 0.9);
  glTranslatef(13.4, 3.6, -5.3);
  glScalef(0.5, 0.65, 1.2);
  glutSolidCube(0.8);
  glPopMatrix();

  // Desni

  glPushMatrix();
  glColor3f(0, 1, 0);
  glTranslatef(13.5, 3.6, 5.3);
  glScalef(0.5, 0.65, 1.2);
  glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.9, 0.9, 0.9);
  glTranslatef(13.4, 3.6, 5.3);
  glScalef(0.5, 0.65, 1.2);
  glutSolidCube(0.8);
  glPopMatrix();
}

void drawFence() {
  glPushMatrix();
  glColor3f(0.37, 0.18, 0.00);
  glRotatef(-90, 1, 0, 0);
  GLUquadric* quad3 = gluNewQuadric();
  gluCylinder(quad3, 0.12, 0.12, 1, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 1, 0);
  glRotatef(-90, 1, 0, 0);
  gluDisk(quad3, 0, 0.12, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.37, 0.18, 0.00);
  glTranslatef(4, 0, 0);
  glRotatef(-90, 1, 0, 0);
  gluCylinder(quad3, 0.12, 0.12, 1, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(4, 1, 0);
  glRotatef(-90, 1, 0, 0);
  gluDisk(quad3, 0, 0.12, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(2, 0.2, 0);
  glScalef(2, 0.05, 0.1);
  glutSolidCube(2);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(2, 0.52, 0);
  glScalef(2, 0.05, 0.1);
  glutSolidCube(2);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(2, 0.84, 0);
  glScalef(2, 0.05, 0.1);
  glutSolidCube(2);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(6, 0.2, 0);
  glScalef(2, 0.05, 0.1);
  glutSolidCube(2);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(6, 0.52, 0);
  glScalef(2, 0.05, 0.1);
  glutSolidCube(2);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(6, 0.84, 0);
  glScalef(2, 0.05, 0.1);
  glutSolidCube(2);
  glPopMatrix();

  // 3

  glPushMatrix();
  glColor3f(0.37, 0.18, 0.00);
  glTranslatef(8, 0, 0);
  glRotatef(-90, 1, 0, 0);
  gluCylinder(quad3, 0.12, 0.12, 1, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(8, 1, 0);
  glRotatef(-90, 1, 0, 0);
  gluDisk(quad3, 0, 0.12, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(10, 0.2, 0);
  glScalef(2, 0.05, 0.1);
  glutSolidCube(2);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(10, 0.52, 0);
  glScalef(2, 0.05, 0.1);
  glutSolidCube(2);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(10, 0.84, 0);
  glScalef(2, 0.05, 0.1);
  glutSolidCube(2);
  glPopMatrix();
}

void drawTrack() {
  glPushMatrix();
  glColor3f(0.2, 0.2, 0.2);
  glutSolidCube(1);
  glPopMatrix();
}

void drawGrass() {
  glPushMatrix();
  glColor3f(0.043, 0.4, 0.137);
  glutSolidCube(1);
  glPopMatrix();
}

void drawDirt() {
  glPushMatrix();
  glColor3f(0.22, 0.11, 0.00);
  glutSolidCube(1);
  glPopMatrix();
}

void drawChristmasTree() {
  glPushMatrix();
  glColor3f(0.37, 0.18, 0.00);
  glRotatef(-90, 1, 0, 0);
  GLUquadric* quad4 = gluNewQuadric();
  gluCylinder(quad4, 0.48, 0.24, 0.9, 20, 20);
  glColor3f(0.129, 0.352, 0.027);
  glTranslatef(0, 0, 0.9);
  glutSolidCone(1.8, 3, 20, 20);
  glTranslatef(0, 0, 1.2);
  glutSolidCone(1.32, 1.8, 20, 20);
  glTranslatef(0, 0, 0.9);
  glutSolidCone(0.9, 1.2, 20, 20);

  glPopMatrix();
}

void drawTree() {
  glPushMatrix();
  glColor3f(0.37, 0.18, 0.00);
  glRotatef(-90, 1, 0, 0);
  GLUquadric* quad4 = gluNewQuadric();
  gluCylinder(quad4, 0.08, 0.04, 0.5, 20, 20);
  glTranslatef(0, 0, 0.6);
  glColor3f(0.129, 0.352, 0.027);
  glScalef(1.5, 1.5, 1);
  glutSolidSphere(0.25, 20, 20);
  glPopMatrix();

  // Dodatna grana

  glPushMatrix();
  glColor3f(0.37, 0.18, 0.00);
  glTranslatef(0, 0.3, 0.05);
  gluCylinder(quad4, 0.02, 0.02, 0.2, 20, 20);
  glTranslatef(0, 0, 0.2);
  gluDisk(quad4, 0, 0.02, 20, 20);
  glTranslatef(0, 0, -0.2);
  glColor3f(0.7, 0.7, 0.7);
  glTranslatef(0, 0, 0.07);
  glRotatef(90, 1, 0, 0);
  gluCylinder(quad4, 0.005, 0.005, 0.1, 20, 20);
  glTranslatef(0, 0.1, 0);
  gluCylinder(quad4, 0.005, 0.005, 0.1, 20, 20);
  glPopMatrix();

  // Guma

  glPushMatrix();
  glColor3f(0.1, 0.1, 0.1);
  glTranslatef(0, 0.17, 0.17);
  glRotatef(90, 0, 1, 0);
  glutSolidTorus(0.02, 0.05, 20, 20);

  glPopMatrix();
}

void drawMoon() {
  glColor3f(0.956, 0.945, 0.788);
  GLUquadric* quad5 = gluNewQuadric();
  glRotatef(90, 0, 1, 0);
  gluDisk(quad5, 0, 2, 100, 100);
}

void drawHilltop() {
  glColor3f(0.309, 0.313, 0.329);
  glutSolidCube(1);
}

void drawRedWhiteTrack() {
  glPushMatrix();
  glColor3f(1, 0, 0);
  glutSolidCube(1);
  glTranslatef(1, 0, 0);
  glColor3f(1, 1, 1);
  glutSolidCube(1);
  glTranslatef(1, 0, 0);

  glPopMatrix();
}

void drawWhiteTracks() {
  glPushMatrix();
  glColor3f(1, 1, 1);
  glutSolidCube(1);
  glPopMatrix();
}

void drawElectricPole() {
  glPushMatrix();
  glColor3f(0.4, 0.2, 0);
  // glTranslatef(0,0.105,-7);
  glRotatef(-90, 1, 0, 0);
  GLUquadric* quad8 = gluNewQuadric();
  gluCylinder(quad8, 0.2, 0.2, 6, 20, 20);
  glRotatef(90, 1, 0, 0);
  glTranslatef(0, 5, 0);
  glScalef(0.6, 0.3, 3);
  glutSolidCube(1);
  glTranslatef(0, 2, 0);
  glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.7, 0.7, 0.7);
  glTranslatef(0, 3.5, 0.5);
  glRotatef(-90, 1, 0, 0);
  gluCylinder(quad8, 0.3, 0.3, 0.8, 20, 20);
  gluDisk(quad8, 0, 0.3, 20, 20);
  glTranslatef(0, 0, 0.8);
  gluDisk(quad8, 0, 0.3, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.7, 0.7, 0.7);
  glTranslatef(0, 5.7, 1);
  glRotatef(-90, 1, 0, 0);
  gluCylinder(quad8, 0.2, 0.1, 0.3, 20, 20);
  glTranslatef(0, 2, 0);
  gluCylinder(quad8, 0.2, 0.1, 0.3, 20, 20);
  glPopMatrix();

  glDisable(GL_LIGHTING);

  glLineWidth(1.5);
  glColor3f(0, 0, 0);

  glBegin(GL_LINES);
  glVertex3f(0, 5.95, 1);
  glVertex3f(48, 5.95, 1);

  glVertex3f(0, 5.95, -1);
  glVertex3f(48, 5.95, -1);
  glEnd();

  glEnable(GL_LIGHTING);
}

void drawHouse() {
  /* Glavni deo kuce*/

  glPushMatrix();
  glScalef(1, 0.5, 0.6);
  glColor3f(0.803, 0.521, 0.247);
  glutSolidCube(9);
  glColor3f(0, 0, 0);
  glScalef(1.01, 1.01, 1.01);
  glutWireCube(9);
  glPopMatrix();

  /* Trem sa stepenicama */

  glPushMatrix();
  glColor3f(0.4, 0.4, 0.4);
  glTranslatef(-2.3, -1.7, 1.36);
  glScalef(1, 0.2, 1.8);
  glutSolidCube(4.5);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.5, -1.7, 2.7);
  glScalef(4, 1, 3);
  glutSolidCube(0.9);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.5, -1.85, 3.8);
  glScalef(4, 0.7, 1.5);
  glutSolidCube(0.9);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0.95, -1.95, 4.2);
  glScalef(3, 0.5, 1.5);
  glutSolidCube(0.9);
  glPopMatrix();

  /* Ograda trema */

  glPushMatrix();
  glColor3f(0.545, 0.270, 0.074);
  glTranslatef(-4.45, -0.6, 4);
  glScalef(0.05, 0.3, 0.65);
  glutSolidCube(4);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.545, 0.270, 0.074);
  glTranslatef(-2.35, -0.6, 5.3);
  glRotatef(90, 0, 1, 0);
  glScalef(0.05, 0.3, 1.1);
  glutSolidCube(4);
  glPopMatrix();

  /* Prozori */

  glPushMatrix();
  glColor3f(0.133, 0.874, 0.945);
  glTranslatef(-3.2, 0.9, 2.1);
  glutSolidCube(1.3);
  glColor3f(0, 0, 0);
  glScalef(1.01, 1.01, 1.01);
  glutWireCube(1.3);

  glTranslatef(1.3, 0, 0);
  glColor3f(0.133, 0.874, 0.945);
  glutSolidCube(1.3);
  glColor3f(0, 0, 0);
  glScalef(1.01, 1.01, 1.01);
  glutWireCube(1.3);

  glTranslatef(5.6, 0, 0);
  glColor3f(0.133, 0.874, 0.945);
  glutSolidCube(1.3);
  glColor3f(0, 0, 0);
  glScalef(1.01, 1.01, 1.01);
  glutWireCube(1.3);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.133, 0.874, 0.945);
  glTranslatef(-3.9, 0.9, 0);
  glScalef(1, 1, 2);
  glutSolidCube(1.3);
  glColor3f(0, 0, 0);
  glScalef(1.01, 1.01, 1.01);
  glutWireCube(1.3);
  glPopMatrix();

  /* Vrata */

  glPushMatrix();
  glColor3f(0.956, 0.643, 0.376);
  glTranslatef(0.9, 0.1, 1.8);
  glScalef(0.9, 1.3, 1);
  glutSolidCube(2);
  glColor3f(0, 0, 0);
  glScalef(1.01, 1.01, 1.01);
  glutWireCube(2);
  glPopMatrix();

  /* Krov */
  glPushMatrix();

  glColor3f(0.545, 0.270, 0.074);

  glBegin(GL_TRIANGLES);
  a = {-4.5, 2.25, -2.7};
  b = {-4.5, 2.25, 4};
  c = {-4.5, 5, -1};
  setNormalAndVertexTriangles(a, b, c);

  a = {4.5, 2.25, -2.7};
  b = {4.5, 2.25, 4};
  c = {4.5, 5, -1};
  setNormalAndVertexTriangles(a, b, c);

  glEnd();

  glColor3f(1, 0, 0);

  glBegin(GL_QUADS);
  a = {-5, 2.25, 4};
  b = {5, 2.25, 4};
  c = {5, 5, -1};
  d = {-5, 5, -1};
  setNormalAndVertexQuads(a, b, c, d);

  a = {5, 5, -1};
  b = {-5, 5, -1};
  c = {-5, 2.25, -2.7};
  d = {5, 2.25, -2.7};
  setNormalAndVertexQuads(a, b, c, d);
  glEnd();
  glPopMatrix();

  /* Odzak */

  glPushMatrix();
  glTranslatef(-3.8, 4.5, 0.3);
  glColor3f(0.4, 0.4, 0.4);
  glScalef(1, 2, 1);
  glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.4, 0.4, 0.4);
  glTranslatef(-3.8, 5.6, 0.3);
  glScalef(1.2, 0.2, 1.2);
  glutSolidCube(1);

  glPopMatrix();

  /* Kucica za kuce */

  glPushMatrix();
  glTranslatef(-7, -1.25, 0);
  glColor3f(1, 0, 0);
  glBegin(GL_QUADS);
  a = {1, 0.6, 1.7};
  b = {1, 0.6, -1.7};
  c = {0, 1.8, -1.7};
  d = {0, 1.8, 1.7};
  setNormalAndVertexQuads(a, b, c, d);

  a = {-1, 0.6, 1.7};
  b = {-1, 0.6, -1.7};
  c = {0, 1.8, -1.7};
  d = {0, 1.8, 1.7};
  setNormalAndVertexQuads(a, b, c, d);
  glEnd();
  glColor3f(0.545, 0.270, 0.074);

  glBegin(GL_TRIANGLES);
  a = {-0.8, 0.8, 1.5};
  b = {0.8, 0.8, 1.5};
  c = {0, 1.8, 1.5};
  setNormalAndVertexTriangles(a, b, c);

  a = {-0.8, 0.8, -1.5};
  b = {0.8, 0.8, -1.5};
  c = {0, 1.8, -1.5};
  setNormalAndVertexTriangles(a, b, c);
  glEnd();
  glScalef(0.8, 0.8, 1.5);
  glutSolidCube(2);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-7, -2, 1.51);
  glColor3f(0, 0, 0);
  GLUquadric* quad10 = gluNewQuadric();
  glScalef(0.5, 1.5, 1);
  gluDisk(quad10, 0, 1, 20, 20);
  glPopMatrix();
}

void drawFixedParts() {
  /*glPushMatrix();
    glTranslatef(1.25,0.3,-3.6);
    glScalef(2.5,2.5,2);
    drawKart();
  glPopMatrix();*/

  if ( activateBomb ) {
    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(1.5, 0, movementParameter);
    glutSolidSphere(bombParameter, 100, 100);
    glPopMatrix();
  }

  glPushMatrix();
  glTranslatef(0, 0.2, movementParameter);
  // glRotatef(-turnParameter,0,1,0);
  glScalef(0.15, 0.15, 0.15);
  if ( activateHole ) {
    glTranslatef(6 * holeParameter, 0.15 - 1.2 * holeRotation, 0);
    glRotatef(8 * holeRotation, 0, 0, -1);
  } else if ( activateXtrap ) {
    glTranslatef(xTrapHorizontal, xTrapVertical, 0);
    glRotatef(xTrapRotation, 0, -1, 0);
  }
  drawBuggy();
  glPopMatrix();

  /*
  glPushMatrix();
    glColor3f(1,0,0);
    glTranslatef(1.5,0.6,movementParameter);
    glScalef(3.1125,0.9,1.7);
    glutWireCube(1);
  glPopMatrix();*/

  /*glPushMatrix();
    glTranslatef(150,0,0);
    glScalef(1,2,2.5);
    drawMoon();
  glPopMatrix();*/

  glPushMatrix();
  glScalef(300, 0.01, 10.8);
  drawTrack();
  glPopMatrix();

  // Desna strana

  glPushMatrix();
  glTranslatef(0, 0.105, 5.9);
  glScalef(300, 0.01, 1);
  drawGrass();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 0, 5.9);
  glScalef(300, 0.01, 1);
  drawDirt();
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.094, 0.301, 0.447);
  glTranslatef(0, 0, 10);
  glScalef(300, 0.01, 7);
  glutSolidCube(1);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 0.1, 16);
  glScalef(300, 0.001, 5);
  drawGrass();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 0, 15);
  glScalef(300, 0.2, 5);
  drawDirt();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 1, 20);
  glRotatef(-30, 1, 0, 0);
  glScalef(300, 0.01, 20);
  drawHilltop();
  glPopMatrix();

  // Leva strana

  glPushMatrix();
  glTranslatef(0, 0.1, -45.4);
  glScalef(300, 0.01, 80);
  drawGrass();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 0, -25.4);
  glScalef(300, 0.01, 40);
  drawDirt();
  glPopMatrix();

  /*glPushMatrix();
    glTranslatef(0,1,-20);
    glRotatef(30,1,0,0);
    glScalef(300,0.01,20);
    drawHilltop();
  glPopMatrix();*/
}

void drawBlock(int blockNumber) {
  // Ograda

  glPushMatrix();
  glTranslatef(0, 0.105, -5.5);
  drawFence();
  glTranslatef(0, 0, 11);
  drawFence();
  glTranslatef(12, 0, 0);
  drawFence();
  glTranslatef(0, 0, -11);
  drawFence();
  glPopMatrix();

  // Jelke

  glPushMatrix();
  glTranslatef(1.8, 0.105, 16.4);
  drawChristmasTree();
  // glTranslatef(8, 0, 0);
  // drawChristmasTree();
  // glTranslatef(8,0,0);
  // drawChristmasTree();
  glPopMatrix();

  if ( blockNumber % 2 == 0 ) {
    glPushMatrix();
    glTranslatef(0, 0.105, -6);
    drawElectricPole();
    glPopMatrix();
  }

  if ( blockNumber == 0 || blockNumber == 4 || blockNumber == 7 ) {
    glPushMatrix();
    glTranslatef(0, 2, -20);
    glRotatef(-45, 0, 1, 0);
    drawHouse();
    glPopMatrix();
  }

  glPushMatrix();
  glTranslatef(1, 0, 5.2);
  glScalef(2, 0.1, 0.4);
  drawRedWhiteTrack();
  for ( int i = 0; i < 5; i++ ) {
    glTranslatef(2, 0, 0);
    drawRedWhiteTrack();
  }
  glPopMatrix();

  glPushMatrix();
  glTranslatef(1, 0, -5.2);
  glScalef(2, 0.1, 0.4);
  drawRedWhiteTrack();
  for ( int i = 0; i < 5; i++ ) {
    glTranslatef(2, 0, 0);
    drawRedWhiteTrack();
  }
  glPopMatrix();

  glPushMatrix();
  glTranslatef(2, 0, 1.8);
  glScalef(4, 0.02, 0.2);
  drawWhiteTracks();
  for ( int i = 0; i < 2; i++ ) {
    glTranslatef(2, 0, 0);
    drawWhiteTracks();
  }
  glPopMatrix();

  glPushMatrix();
  glTranslatef(2, 0, -1.8);
  glScalef(4, 0.02, 0.2);
  drawWhiteTracks();
  for ( int i = 0; i < 2; i++ ) {
    glTranslatef(2, 0, 0);
    drawWhiteTracks();
  }
  glPopMatrix();
}

void drawXtrap(void) {
  // Glavna zuta ploca

  glPushMatrix();
  glColor3f(1, 1, 0);
  glScalef(1, 0.05, 1);
  glTranslatef(0, -0.001, 0);
  glutSolidCube(1.5);
  glPopMatrix();

  // Ivice
  glBegin(GL_QUADS);

  // Prednja strana

  a = {0.95, -0.0375, -0.25};
  b = {0.95, -0.0375, 0.25};
  c = {0.75, 0.0375, 0.25};
  d = {0.75, 0.0375, -0.25};
  setNormalAndVertexQuads(a, b, c, d);

  // Zadnja strana

  a = {-0.95, -0.0375, -0.25};
  b = {-0.95, -0.0375, 0.25};
  c = {-0.75, 0.0375, 0.25};
  d = {-0.75, 0.0375, -0.25};
  setNormalAndVertexQuads(a, b, c, d);

  // Desna strana

  a = {-0.75, -0.0375, 0.95};
  b = {0.75, -0.0375, 0.95};
  c = {0.75, 0.0375, 0.75};
  d = {-0.75, 0.0375, 0.75};
  setNormalAndVertexQuads(a, b, c, d);

  // Leva strana
  a = {-0.75, -0.0375, -0.95};
  b = {0.75, -0.0375, -0.95};
  c = {0.75, 0.0375, -0.75};
  d = {-0.75, 0.0375, -0.75};
  setNormalAndVertexQuads(a, b, c, d);

  glColor3f(1, 0, 0);

  // Zadnja strana
  a = {-0.95, -0.0375, 0.75};
  b = {-0.75, 0.0375, 0.75};
  c = {-0.75, 0.0375, 0.25};
  d = {-0.95, -0.0375, 0.25};
  setNormalAndVertexQuads(a, b, c, d);

  a = {-0.95, -0.0375, -0.25};
  b = {-0.75, 0.0375, -0.25};
  c = {-0.75, 0.0375, -0.75};
  d = {-0.95, -0.0375, -0.75};
  setNormalAndVertexQuads(a, b, c, d);

  // Prednja strana

  a = {0.95, -0.0375, 0.75};
  b = {0.75, 0.0375, 0.75};
  c = {0.75, 0.0375, 0.25};
  d = {0.95, -0.0375, 0.25};
  setNormalAndVertexQuads(a, b, c, d);

  a = {0.95, -0.0375, -0.25};
  b = {0.75, 0.0375, -0.25};
  c = {0.75, 0.0375, -0.75};
  d = {0.95, -0.0375, -0.75};
  setNormalAndVertexQuads(a, b, c, d);

  // Slovo X

  a = {-0.75, 0.0375, 0.25};
  b = {0.75, 0.0375, -0.75};
  c = {0.75, 0.0375, -0.25};
  d = {-0.75, 0.0375, 0.75};
  setNormalAndVertexQuads(a, b, c, d);

  a = {-0.75, 0.0375, -0.25};
  b = {0.75, 0.0375, 0.75};
  c = {0.75, 0.0375, 0.25};
  d = {-0.75, 0.0375, -0.75};
  setNormalAndVertexQuads(a, b, c, d);

  glColor3f(0, 0, 0);

  a = {-0.75, 0.0377, 0.3};
  b = {0.75, 0.0377, -0.7};
  c = {0.75, 0.0377, -0.3};
  d = {-0.75, 0.0377, 0.7};
  setNormalAndVertexQuads(a, b, c, d);

  a = {-0.75, 0.0377, -0.3};
  b = {0.75, 0.0377, 0.7};
  c = {0.75, 0.0377, 0.3};
  d = {-0.75, 0.0377, -0.7};
  setNormalAndVertexQuads(a, b, c, d);

  glEnd();

  glColor3f(1, 0, 0);

  glBegin(GL_TRIANGLES);
  a = {0.95, -0.0375, 0.95};
  b = {0.75, -0.0375, 0.95};
  c = {0.75, 0.0375, 0.75};
  setNormalAndVertexTriangles(a, b, c);

  a = {0.95, -0.0375, 0.95};
  b = {0.95, -0.0375, 0.75};
  c = {0.75, 0.0375, 0.75};
  setNormalAndVertexTriangles(a, b, c);

  a = {-0.95, -0.0375, -0.95};
  b = {-0.75, -0.0375, -0.95};
  c = {-0.75, 0.0375, -0.75};
  setNormalAndVertexTriangles(a, b, c);

  a = {-0.95, -0.0375, -0.95};
  b = {-0.95, -0.0375, -0.75};
  c = {-0.75, 0.0375, -0.75};
  setNormalAndVertexTriangles(a, b, c);

  a = {-0.95, -0.0375, 0.95};
  b = {-0.75, -0.0375, 0.95};
  c = {-0.75, 0.0375, 0.75};
  setNormalAndVertexTriangles(a, b, c);

  a = {-0.95, -0.0375, 0.95};
  b = {-0.95, -0.0375, 0.75};
  c = {-0.75, 0.0375, 0.75};
  setNormalAndVertexTriangles(a, b, c);

  a = {0.95, -0.0375, -0.95};
  b = {0.75, -0.0375, -0.95};
  c = {0.75, 0.0375, -0.75};
  setNormalAndVertexTriangles(a, b, c);

  a = {0.95, -0.0375, -0.95};
  b = {0.95, -0.0375, -0.75};
  c = {0.75, 0.0375, -0.75};
  setNormalAndVertexTriangles(a, b, c);
  glEnd();
}

void drawXtrapOnTrack(int track) {
  switch ( track ) {
    case 0:
      glPushMatrix();
      glScalef(1, 3, 1);
      drawXtrap();
      glPopMatrix();
      break;
    case -1:
      glPushMatrix();
      glTranslatef(0, 0, -3.6);
      glScalef(1, 3, 1);
      drawXtrap();
      glPopMatrix();
      break;
    case 1:
      glPushMatrix();
      glTranslatef(0, 0, 3.6);
      glScalef(1, 3, 1);
      drawXtrap();
      glPopMatrix();
      break;
  }
}

void drawBomb() {
  glTranslatef(0, 0.9, 0);

  glColor3f(0.1, 0.1, 0.1);
  glutSolidSphere(1, 20, 20);

  glPushMatrix();
  glTranslatef(0, 0.85, 0.4);
  glRotatef(-60, 1, 0, 0);
  GLUquadric* quad3 = gluNewQuadric();
  gluCylinder(quad3, 0.25, 0.25, 0.3, 20, 20);
  glTranslatef(0, 0, 0.3);
  gluDisk(quad3, 0, 0.25, 20, 20);
  glPopMatrix();

  glPushMatrix();
  glColor3f(1, 0, 0);
  glTranslatef(0, 1.1, 0.55);
  glRotatef(-60, 1, 0, 0);
  gluCylinder(quad3, 0.1, 0.1, 0.15, 20, 20);
  glTranslatef(0, 0, 0.15);
  gluDisk(quad3, 0, 0.1, 20, 20);
  glPopMatrix();
}

void drawBombOnTrack(int track) {
  switch ( track ) {
    case 0:
      glPushMatrix();
      glScalef(0.5, 0.5, 0.5);
      drawBomb();
      glPopMatrix();
      break;
    case -1:
      glPushMatrix();
      glTranslatef(0, 0, -3.6);
      glScalef(0.5, 0.5, 0.5);
      drawBomb();
      glPopMatrix();
      break;
    case 1:
      glPushMatrix();
      glTranslatef(0, 0, 3.6);
      glScalef(0.5, 0.5, 0.5);
      drawBomb();
      glPopMatrix();
      break;
  }
}

void drawHole() {
  glPushMatrix();
  glColor3f(0, 0, 0);
  glTranslatef(0, 0.05, 0);
  GLUquadric* quad9 = gluNewQuadric();
  glRotatef(-90, 1, 0, 0);
  gluDisk(quad9, 0, 1.3, 50, 50);
  glPopMatrix();
}

void drawHoleOnTrack(int track) {
  switch ( track ) {
    case 0:
      glPushMatrix();
      drawHole();
      glPopMatrix();
      break;
    case -1:
      glPushMatrix();
      glTranslatef(0, 0, -3.6);
      drawHole();
      glPopMatrix();
      break;
    case 1:
      glPushMatrix();
      glTranslatef(0, 0, 3.6);
      drawHole();
      glPopMatrix();
      break;
  }
}

void drawObstacle(float x, int type, int track) {
  switch ( type ) {
    case 0:
      glPushMatrix();
      glTranslatef(x, 0, 0);
      drawXtrapOnTrack(track);
      glPopMatrix();
      break;

    case 1:
      glPushMatrix();
      glTranslatef(x, 0, 0);
      drawHoleOnTrack(track);
      glPopMatrix();
      break;

    case 2:
      glPushMatrix();
      glTranslatef(x, 0, 0);
      drawBombOnTrack(track);
      glPopMatrix();
      break;
  }
}

void drawObstacles() {
  for ( int i = 0; i < OBSTACLE_NUMBER; i++ ) {
    glPushMatrix();
    drawObstacle(obstacle[i].x, obstacle[i].type, obstacle[i].track);
    glPopMatrix();
  }
}

void drawStar() {
  glColor3f(0.988, 0.760, 0.003);

  glBegin(GL_POLYGON);
  a = {2.2, 3.1, 0};
  b = {3.6, -1.2, 0};
  c = {0, -3.8, 0};
  setNormalAndVertexTriangles(a, b, c);
  glVertex3f(-3.6, -1.2, 0);
  glVertex3f(-2.2, 3.1, 0);
  glEnd();

  glBegin(GL_TRIANGLES);

  glVertex3f(0, 10, 0);
  glVertex3f(2.2, 3.1, 0);
  glVertex3f(-2.2, 3.1, 0);

  glVertex3f(2.2, 3.1, 0);
  glVertex3f(9.5, 3.1, 0);
  glVertex3f(3.6, -1.2, 0);

  glVertex3f(3.6, -1.2, 0);
  glVertex3f(5.9, -8.1, 0);
  glVertex3f(0, -3.8, 0);

  glVertex3f(0, -3.8, 0);
  glVertex3f(-5.9, -8.1, 0);
  glVertex3f(-3.6, -1.2, 0);

  glVertex3f(-3.6, -1.2, 0);
  glVertex3f(-9.5, 3.1, 0);
  glVertex3f(-2.2, 3.1, 0);

  glEnd();

  glTranslatef(0, 0, 2);

  glBegin(GL_POLYGON);
  a = {2.2, 3.1, 0};
  b = {3.6, -1.2, 0};
  c = {0, -3.8, 0};
  setNormalAndVertexTriangles(a, b, c);
  glVertex3f(-3.6, -1.2, 0);
  glVertex3f(-2.2, 3.1, 0);
  glEnd();

  glBegin(GL_TRIANGLES);

  glVertex3f(0, 10, 0);
  glVertex3f(2.2, 3.1, 0);
  glVertex3f(-2.2, 3.1, 0);

  glVertex3f(2.2, 3.1, 0);
  glVertex3f(9.5, 3.1, 0);
  glVertex3f(3.6, -1.2, 0);

  glVertex3f(3.6, -1.2, 0);
  glVertex3f(5.9, -8.1, 0);
  glVertex3f(0, -3.8, 0);

  glVertex3f(0, -3.8, 0);
  glVertex3f(-5.9, -8.1, 0);
  glVertex3f(-3.6, -1.2, 0);

  glVertex3f(-3.6, -1.2, 0);
  glVertex3f(-9.5, 3.1, 0);
  glVertex3f(-2.2, 3.1, 0);

  glEnd();

  glTranslatef(0, 0, -2);

  /* Zatvaramo supljine */

  glBegin(GL_QUADS);
  a = {2.2, 3.1, 0};
  b = {9.5, 3.1, 0};
  c = {9.5, 3.1, 2};
  d = {2.2, 3.1, 2};
  setNormalAndVertexQuads(a, b, c, d);

  a = {-2.2, 3.1, 0};
  b = {-9.5, 3.1, 0};
  c = {-9.5, 3.1, 2};
  d = {-2.2, 3.1, 2};
  setNormalAndVertexQuads(a, b, c, d);

  a = {0, 10, 0};
  b = {2.2, 3.1, 0};
  c = {2.2, 3.1, 2};
  d = {0, 10, 2};
  setNormalAndVertexQuads(a, b, c, d);

  a = {0, 10, 0};
  b = {-2.2, 3.1, 0};
  c = {-2.2, 3.1, 2};
  d = {0, 10, 2};
  setNormalAndVertexQuads(a, b, c, d);

  a = {9.5, 3.1, 0};
  b = {3.6, -1.2, 0};
  c = {3.6, -1.2, 2};
  d = {9.5, 3.1, 2};
  setNormalAndVertexQuads(a, b, c, d);

  a = {-9.5, 3.1, 0};
  b = {-3.6, -1.2, 0};
  c = {-3.6, -1.2, 2};
  d = {-9.5, 3.1, 2};
  setNormalAndVertexQuads(a, b, c, d);

  a = {3.6, -1.2, 0};
  b = {5.9, -8.1, 0};
  c = {5.9, -8.1, 2};
  d = {3.6, -1.2, 2};
  setNormalAndVertexQuads(a, b, c, d);

  a = {-3.6, -1.2, 0};
  b = {-5.9, -8.1, 0};
  c = {-5.9, -8.1, 2};
  d = {-3.6, -1.2, 2};
  setNormalAndVertexQuads(a, b, c, d);

  a = {5.9, -8.1, 0};
  b = {0, -3.8, 0};
  c = {0, -3.8, 2};
  d = {5.9, -8.1, 2};
  setNormalAndVertexQuads(a, b, c, d);

  a = {-5.9, -8.1, 0};
  b = {0, -3.8, 0};
  c = {0, -3.8, 2};
  d = {-5.9, -8.1, 2};
  setNormalAndVertexQuads(a, b, c, d);
  glEnd();
}

void drawStarOnTrack(int track) {
  glTranslatef(0, 1, 0);

  switch ( track ) {
    case 0:
      glPushMatrix();
      glScalef(0.05, 0.05, 0.05);
      glRotatef(90 + starRotationParameter, 0, 1, 0);
      drawStar();
      glPopMatrix();
      break;
    case -1:
      glPushMatrix();
      glTranslatef(0, 0, -3.6);
      glScalef(0.05, 0.05, 0.05);
      glRotatef(90 + starRotationParameter, 0, 1, 0);
      drawStar();
      glPopMatrix();
      break;
    case 1:
      glPushMatrix();
      glTranslatef(0, 0, 3.6);
      glScalef(0.05, 0.05, 0.05);
      glRotatef(90 + starRotationParameter, 0, 1, 0);
      drawStar();
      glPopMatrix();
      break;
  }
}

void drawStars() {
  for ( int i = 0; i < STAR_NUMBER; i++ ) {
    glPushMatrix();
    glTranslatef(stars[i].x, stars[i].y, 0);
    drawStarOnTrack(stars[i].track);
    glPopMatrix();
  }
}

void drawCompleteScene() {
  // draw_axes(150);

  for ( int i = 0; i < 10; i++ ) {
    glPushMatrix();
    glTranslatef(blockPosition[i], 0, 0);
    drawBlock(i);
    glPopMatrix();
  }

  glPushMatrix();
  drawObstacles();
  drawStars();
  glPopMatrix();
}
