#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <ctime>
#include <GL/glut.h>
#include "DrawFunctions.hpp"


extern float tiresParameter;


//Definicija strukture tacka radi lakseg i preglednijeg koda 

typedef struct Tacke{
  float x;
  float y;
  float z;
}TACKA;

void draw_axes(float len) {
    glDisable(GL_LIGHTING);

    glBegin(GL_LINES);
        /*glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(len,0,0);*/

        glColor3f(1,1,1);
        glVertex3f(0,0,1.8);
        glVertex3f(len,0,1.8);

        glColor3f(1,1,1);
        glVertex3f(0,0,-1.8);
        glVertex3f(len,0,-1.8);

        glColor3f(1,1,1);
        glVertex3f(0,0,5.4);
        glVertex3f(len,0,5.4);

        glColor3f(1,1,1);
        glVertex3f(0,0,-5.4);
        glVertex3f(len,0,-5.4);
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
    glVertex3f(1,0,5.4);

    glEnd();

    glEnable(GL_LIGHTING);
}

void setNormalAndVertexQuads(TACKA a,TACKA b,TACKA c,TACKA d){

  //Vektor normale cemo dobiti kao vektorski proizvod dva vektora

  TACKA v1={b.x-a.x,b.y-a.y,b.z-a.z};
  TACKA v2={c.x-a.x,c.y-a.y,c.z-a.z};

  glNormal3f(v1.y*v2.z-v1.z*v2.y,v1.z*v2.x-v1.x*v2.z,v1.x*v2.y-v1.y*v2.x);

  glVertex3f(a.x,a.y,a.z);
  glVertex3f(b.x,b.y,b.z);
  glVertex3f(c.x,c.y,c.z);
  glVertex3f(d.x,d.y,d.z);

}

void setNormalAndVertexTriangles(TACKA a,TACKA b,TACKA c){

  //Vektor normale cemo dobiti kao vektorski proizvod dva vektora

  TACKA v1={b.x-a.x,b.y-a.y,b.z-a.z};
  TACKA v2={c.x-a.x,c.y-a.y,c.z-a.z};

  glNormal3f(v1.y*v2.z-v1.z*v2.y,v1.z*v2.x-v1.x*v2.z,v1.x*v2.y-v1.y*v2.x);

  glVertex3f(a.x,a.y,a.z);
  glVertex3f(b.x,b.y,b.z);
  glVertex3f(c.x,c.y,c.z);

}

TACKA a,b,c,d;

void drawTires() {

  glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(0.15,0.02,0.33);
    glRotatef(-tiresParameter,0,0,1);
    GLUquadric* quad1 = gluNewQuadric();
    gluCylinder(quad1,0.12,0.12,0.1,20,20);
    glColor3f(1,0,0);
    gluCylinder(quad1,0.05,0.05,0.1,20,20);
    glColor3f(1,0,0);
    glTranslatef(0,0,-0.03);
    gluCylinder(quad1,0.05,0.05,0.05,20,20);

  glPopMatrix();
  
  glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(0.15,0.02,0.33);
    glRotatef(-tiresParameter,0,0,1);
    gluDisk(quad1,0.05,0.12,20,20);
    glTranslatef(0,0,0.1);
    gluDisk(quad1,0.05,0.12,20,20);
    glColor3f(1,0,0);
    gluDisk(quad1,0,0.05,20,20);
    glTranslatef(0,0,-0.1);
    gluDisk(quad1,0,0.05,20,20);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(-0.3,0.02,0.33);
    glRotatef(-tiresParameter,0,0,1);
    gluCylinder(quad1,0.12,0.12,0.1,20,20);
    glColor3f(1,0,0);
    gluCylinder(quad1,0.05,0.05,0.1,20,20);
    glColor3f(1,0,0);
    glTranslatef(0,0,-0.03);
    gluCylinder(quad1,0.05,0.05,0.1,20,20);

  glPopMatrix();

  glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(-0.3,0.02,0.33);
    glRotatef(-tiresParameter,0,0,1);
    gluDisk(quad1,0.05,0.12,20,20);
    glTranslatef(0,0,0.1);
    gluDisk(quad1,0.05,0.12,20,20);
    glColor3f(1,0,0);
    gluDisk(quad1,0,0.05,20,20);
    glTranslatef(0,0,-0.1);
    gluDisk(quad1,0,0.05,20,20);
  glPopMatrix();


  glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(-0.3,0.02,-0.43);
    glRotatef(-tiresParameter,0,0,1);
    gluCylinder(quad1,0.12,0.12,0.1,20,20);
    glColor3f(1,0,0);
    gluCylinder(quad1,0.05,0.05,0.1,20,20);
    glColor3f(1,0,0);
    glTranslatef(0,0,0.03);
    gluCylinder(quad1,0.05,0.05,0.1,20,20);

  glPopMatrix();

  glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(-0.3,0.02,-0.43);
    glRotatef(-tiresParameter,0,0,1);
    gluDisk(quad1,0.05,0.12,20,20);
    glTranslatef(0,0,0.1);
    gluDisk(quad1,0.05,0.12,20,20);
    glColor3f(1,0,0);
    gluDisk(quad1,0,0.05,20,20);
    glTranslatef(0,0,-0.1);
    gluDisk(quad1,0,0.05,20,20);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(0.15,0.02,-0.43);
    glRotatef(-tiresParameter,0,0,1);
    gluCylinder(quad1,0.12,0.12,0.1,20,20);
    glColor3f(1,0,0);
    gluCylinder(quad1,0.05,0.05,0.1,20,20);
    glColor3f(1,0,0);
    glTranslatef(0,0,0.03);
    gluCylinder(quad1,0.05,0.05,0.1,20,20);

  glPopMatrix();

  glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(0.15,0.02,-0.43);
    glRotatef(-tiresParameter,0,0,1);
    gluDisk(quad1,0.05,0.12,20,20);
    glTranslatef(0,0,0.1);
    gluDisk(quad1,0.05,0.12,20,20);
    glColor3f(1,0,0);
    gluDisk(quad1,0,0.05,20,20);
    glTranslatef(0,0,-0.1);
    gluDisk(quad1,0,0.05,20,20);
  glPopMatrix();
}

void drawSeat(){


  glPushMatrix();
    glColor3f(0.7,0.7,0.7);
    GLUquadric* quad2 = gluNewQuadric();
    glTranslatef(-0.3,0.2,0);
    glRotatef(90,0,1,0);
    gluCylinder(quad2,0.16,0.16,0.18,20,20);
    gluCylinder(quad2,0.1,0.1,0.18,20,20);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0.7,0.7,0.7);
    glTranslatef(-0.3,0.2,0);
    glRotatef(90,0,1,0);
    gluDisk(quad2,0.1,0.16,20,20);
    glTranslatef(0,0,0.18);
    gluDisk(quad2,0.1,0.16,20,20);
  glPopMatrix();

}

void drawKart(){


  glBegin(GL_QUADS);

    glColor3f(1,0,0);
    //Donji deo karta
    a={0.5,0,0.3};
    b={0.5,0,-0.3};
    c={-0.5,0,-0.3};
    d={-0.5,0,0.3};
    setNormalAndVertexQuads(a,b,c,d);


    glColor3f(0,0,1);
    //Prednji prvi spoiler(Ako bih ga tako nazvao)
    a={0.5,0,0.3};
    b={0.5,0,-0.3};
    c={0.47,0.03,-0.3};
    d={0.47,0.03,0.3};
    setNormalAndVertexQuads(a,b,c,d);

    glColor3f(1,0,0);

    //Prednji drugi spoiler
    a={0.47,0.03,-0.3};
    b={0.47,0.03,0.3};
    c={0.3,0.08,0.3};
    d={0.3,0.08,-0.3};
    setNormalAndVertexQuads(a,b,c,d);

    //Gornja povrsina karta
    a={0.3,0.08,0.3};
    b={0.3,0.08,-0.3};
    c={-0.5,0.08,-0.3};
    d={-0.5,0.08,0.3};
    setNormalAndVertexQuads(a,b,c,d);

    //Donji deo strane
    glColor3f(0,0,1);
    a={0.5,0,0.3};
    b={-0.5,0,0.3};
    c={-0.5,0.03,0.3}; 
    d={0.47,0.03,0.3};
    setNormalAndVertexQuads(a,b,c,d);

    //Gornji deo strane
    a={-0.5,0.03,0.3};
    b={-0.5,0.08,0.3};
    c={0.3,0.08,0.3};
    d={0.47,0.03,0.3};
    
    setNormalAndVertexQuads(a,b,c,d);

    //Donji deo strane
    a={0.5,0,-0.3};
    b={0.47,0.03,-0.3};
    c={-0.5,0.03,-0.3};
    d={-0.5,0,-0.3};
    setNormalAndVertexQuads(a,b,c,d);

    //Gornji deo strane
    a={-0.5,0.03,-0.3};
    b={0.47,0.03,-0.3};
    c={0.3,0.08,-0.3};
    d={-0.5,0.08,-0.3};
    setNormalAndVertexQuads(a,b,c,d);

    //Zadnji deo

    glColor3f(0,0,1);
    a={-0.5,0,-0.3};
    b={-0.5,0,0.3};
    c={-0.5,0.08,0.3};
    d={-0.5,0.08,-0.3};
    setNormalAndVertexQuads(a,b,c,d);

    //Soferka i panel
    glColor3f(0.55,0.55,0.55);
    a={0.3,0.08,0.3};
    b={0.15,0.25,0.2};
    c={0.15,0.25,-0.2};
    d={0.3,0.08,-0.3};
    setNormalAndVertexQuads(a,b,c,d);
    glColor3f(1,0,0);

    glColor3f(1,0,0);
    a={0,0.08,-0.3};
    b={0,0.08,0.3};
    c={0.15,0.25,0.2};
    d={0.15,0.25,-0.2};
    setNormalAndVertexQuads(a,b,c,d);

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

  glColor3f(1,0,0);
  a={0.3,0.08,0.3};
  b={0,0.08,0.3};
  c={0.15,0.25,0.2};
  setNormalAndVertexTriangles(a,b,c);

  //glColor3f(1,0,0);
  a={0.3,0.08,-0.3};
  b={0,0.08,-0.3};
  c={0.15,0.25,-0.2};
  setNormalAndVertexTriangles(a,b,c);

  glEnd();


  //Prednja svetla
  glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(0.44,0.03,0.22);
    glScalef(1,1,2);
    glutSolidCube(0.04);
  glPopMatrix();

  glPushMatrix();
    glColor3f(1,1,1);
    glTranslatef(0.44,0.03,-0.22);
    glScalef(1,1,2);
    glutSolidCube(0.04);
  glPopMatrix();


  //Zadnja svetla
  glPushMatrix();
    glColor3f(1,0,0);
    glTranslatef(-0.49,0.045,0.22);
    glScalef(1,1,2);
    glutSolidCube(0.04);
  glPopMatrix();

  glPushMatrix();
    glColor3f(1,0,0);
    glTranslatef(-0.49,0.045,-0.22);
    glScalef(1,1,2);
    glutSolidCube(0.04);
  glPopMatrix();

  //Volan

  glPushMatrix();

    glColor3f(0.3,0.3,0.3);
    GLUquadric* quad = gluNewQuadric();
    glTranslatef(0.04,0.2,0);
    glRotatef(90,1,1,0);
    gluCylinder(quad,0.01,0.01,0.15,20,20);

  glPopMatrix();

  glPushMatrix();
    glColor3f(0.3,0.3,0.3);
    glTranslatef(0.04,0.2,0);
    glRotatef(90,1,1,0);
    glutSolidTorus(0.01,0.05,20,20);

  glPopMatrix();

  glPushMatrix();
    glColor3f(0.3,0.3,0.3);
    glTranslatef(0.04,0.2,0);
    glRotatef(90,1,1,0);
    gluDisk(quad,0,0.01,20,20);
  glPopMatrix();


  //Brzinometar

  glPushMatrix();
    glColor3f(0.7,0.7,0.7);
    glTranslatef(0.13,0.2,0);
    glRotatef(45,0,0,1);
    glScalef(0.55,0.5,1.5);
    glutSolidCube(0.1);
  glPopMatrix();


  //Kocnica

  glPushMatrix();
    glColor3f(0.2,0.2,0.2);
    glTranslatef(0.04,0.1,0);
    glRotatef(45,0,0,1);
    glScalef(0.6,0.5,0.3);
    glutSolidCube(0.1);
  glPopMatrix();

  //Gas

  glPushMatrix();
    glColor3f(0.2,0.2,0.2);
    glTranslatef(0.04,0.1,0.05);
    glRotatef(45,0,0,1);
    glScalef(0.6,0.5,0.3);
    glutSolidCube(0.1);
  glPopMatrix();

  //Kvacilo

  glPushMatrix();
    glColor3f(0.2,0.2,0.2);
    glTranslatef(0.04,0.1,-0.05);
    glRotatef(45,0,0,1);
    glScalef(0.6,0.5,0.3);
    glutSolidCube(0.1);
  glPopMatrix();



  //Auspuh x6 adds on max speed +100000000

  glPushMatrix();
    glColor3f(0.7,0.7,0.7);
    glTranslatef(-0.4,0.2,-0.25);
    glRotatef(90,1,1,0);
    gluCylinder(quad,0.02,0.02,0.2,20,20);
    gluDisk(quad,0,0.02,20,20);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0.7,0.7,0.7);
    glTranslatef(-0.46,0.2,-0.25);
    glRotatef(90,1,1,0);
    gluCylinder(quad,0.02,0.02,0.2,20,20);
    gluDisk(quad,0,0.02,20,20);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0.7,0.7,0.7);
    glTranslatef(-0.52,0.2,-0.25);
    glRotatef(90,1,1,0);
    gluCylinder(quad,0.02,0.02,0.2,20,20);
    gluDisk(quad,0,0.02,20,20);
  glPopMatrix();


  glPushMatrix();
    glColor3f(0.7,0.7,0.7);
    glTranslatef(-0.4,0.2,0.25);
    glRotatef(90,1,1,0);
    gluCylinder(quad,0.02,0.02,0.2,20,20);
    gluDisk(quad,0,0.02,20,20);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0.7,0.7,0.7);
    glTranslatef(-0.46,0.2,0.25);
    glRotatef(90,1,1,0);
    gluCylinder(quad,0.02,0.02,0.2,20,20);
    gluDisk(quad,0,0.02,20,20);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0.7,0.7,0.7);
    glTranslatef(-0.52,0.2,0.25);
    glRotatef(90,1,1,0);
    gluCylinder(quad,0.02,0.02,0.2,20,20);
    gluDisk(quad,0,0.02,20,20);
  glPopMatrix();

  //Retrovizori

  glPushMatrix();
  glColor3f(0.3,0.3,0.3);
  glTranslatef(0.15,0.15,0.25);
  gluCylinder(quad,0.01,0.01,0.03,20,20);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.3,0.3,0.3);
  glTranslatef(0.15,0.15,0.3);
  glScalef(1,1,2);
  glutSolidCube(0.03);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.3,0.3,0.3);
  glTranslatef(0.15,0.15,-0.28);
  gluCylinder(quad,0.01,0.01,0.03,20,20);
  glPopMatrix();

  glPushMatrix();
  glColor3f(0.3,0.3,0.3);
  glTranslatef(0.15,0.15,-0.3);
  glScalef(1,1,2);
  glutSolidCube(0.03);
  glPopMatrix();


  // Tockovi
  glPushMatrix();
  drawTires();
  glPopMatrix();

  //Motor

  glPushMatrix();
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

  //Spojler

  glPushMatrix();
    glColor3f(0,0,1);
    glTranslatef(-0.55,0.22,0.12);
    glRotatef(90,1,0,0); 
    glRotatef(30,0,1,0);  
    gluCylinder(quad,0.01,0.01,0.2,20,20);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-0.55,0.22,-0.12);
    glRotatef(90,1,0,0); 
    glRotatef(30,0,1,0);  
    gluCylinder(quad,0.01,0.01,0.2,20,20);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(-0.55,0.22,0);
    glScalef(0.7,0.1,4);
    glutSolidCube(0.1);

  glPopMatrix();


  // Vozac

  // Noge

  glPushMatrix();
    glColor3f(0,0,1);
    glTranslatef(0.04,0.1,0.05);
    glRotatef(50,0,0,1);
    glScalef(0.4,2.5,0.25);
    glutSolidCube(0.1);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0,0,1);
    glTranslatef(0.04,0.1,-0.05);
    glRotatef(50,0,0,1);
    glScalef(0.4,2.5,0.25);
    glutSolidCube(0.1);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0,0,1);
    glTranslatef(-0.1,0.14,0.05);
    glRotatef(-60,0,0,1);
    glScalef(0.4,1.5,0.25);
    glutSolidCube(0.1);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0,0,1);
    glTranslatef(-0.1,0.14,-0.05);
    glRotatef(-60,0,0,1);
    glScalef(0.4,1.5,0.25);
    glutSolidCube(0.1);
  glPopMatrix();

  //Torso


  glPushMatrix();
    glColor3f(0.2,0.4,0);
    glTranslatef(-0.15,0.2,0);
    glScalef(0.5,2,1.5);
    glutSolidCube(0.1);
  glPopMatrix();

  //Ruke

  glPushMatrix();
    glColor3f(0.2,0.4,0);
    glTranslatef(-0.1,0.25,0.089);
    glRotatef(60,0,0,1);
    glScalef(0.3,1.2,0.25);
    glutSolidCube(0.1);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0.2,0.4,0);
    glTranslatef(-0.1,0.25,-0.089);
    glRotatef(60,0,0,1);
    glScalef(0.3,1.2,0.25);
    glutSolidCube(0.1);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0.2,0.4,0);
    glTranslatef(-0.023,0.205,-0.075);
    glRotatef(60,0,0,1);
    glRotatef(-20,1,0,0);
    glScalef(0.3,0.95,0.25);
    glutSolidCube(0.1);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0.2,0.4,0);
    glTranslatef(-0.023,0.205,0.075);
    glRotatef(60,0,0,1);
    glRotatef(20,1,0,0);
    glScalef(0.3,0.95,0.25);
    glutSolidCube(0.1);
  glPopMatrix();

  //Glava

  glPushMatrix();
    glColor3f(0.898, 0.760, 0.596);
    glTranslatef(-0.15,0.33,0);
    glutSolidSphere(0.032,20,20);
  glPopMatrix();



  //Sefovsko sediste
  glTranslatef(0.05,0,0);

  glPushMatrix();
    glColor3f(0.7,0.7,0.7);
    glTranslatef(-0.21,0.15,-0.128);
    glScalef(2,1.5,0.7);
    glutSolidCube(0.09);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0.7,0.7,0.7);
    glTranslatef(-0.21,0.15,0.128);
    glScalef(2,1.5,0.7);
    glutSolidCube(0.09);
  glPopMatrix();

  
  glPushMatrix();
    glColor3f(0.7,0.7,0.7);
    glTranslatef(-0.31,0.15,0);
    glScalef(0.2,0.7,1);
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
void drawFence(){
  glPushMatrix();
    glColor3f(0.37,0.18,0.00);
    glRotatef(-90,1,0,0);
    GLUquadric* quad3 = gluNewQuadric();
    gluCylinder(quad3,0.03,0.03,0.25,20,20);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0,0.25,0);
    glRotatef(-90,1,0,0);
    gluDisk(quad3,0,0.03,20,20);
  glPopMatrix();

  glPushMatrix();
    glColor3f(0.37,0.18,0.00);
    glTranslatef(0.5,0,0);
    glRotatef(-90,1,0,0);
    gluCylinder(quad3,0.03,0.03,0.25,20,20);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.5,0.25,0);
    glRotatef(-90,1,0,0);
    gluDisk(quad3,0,0.03,20,20);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.25,0.05,0);
    glScalef(1,0.05,0.1);
    glutSolidCube(0.5);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.25,0.13,0);
    glScalef(1,0.05,0.1);
    glutSolidCube(0.5);
  glPopMatrix();

  glPushMatrix();
    glTranslatef(0.25,0.21,0);
    glScalef(1,0.05,0.1);
    glutSolidCube(0.5);
  glPopMatrix();
}

void drawTrack(){
  glPushMatrix();
    glColor3f(0.2,0.2,0.2);
    glScalef(300,0.01,10.8);
    glutSolidCube(1);
  glPopMatrix();
}

void drawGrass(){
  glPushMatrix();
    glColor3f(0.043, 0.4, 0.137);
    glutSolidCube(1);
  glPopMatrix();
}

void drawDirt(){
  glPushMatrix();
    glColor3f(0.22,0.11,0.00);
    glutSolidCube(1);
  glPopMatrix();
}

void drawChristmasTree() {

  glPushMatrix();
    glColor3f(0.37,0.18,0.00);
    glRotatef(-90,1,0,0);
    GLUquadric* quad4 = gluNewQuadric();
    gluCylinder(quad4,0.08,0.04,0.15,20,20);
    glColor3f(0.129, 0.352, 0.027);
    glTranslatef(0,0,0.15);
    glutSolidCone(0.3,0.5,20,20);
    glTranslatef(0,0,0.2);
    glutSolidCone(0.22,0.3,20,20);
    glTranslatef(0,0,0.15);
    glutSolidCone(0.15,0.2,20,20);

  glPopMatrix();

}

void drawTree(){

  glPushMatrix();
    glColor3f(0.37,0.18,0.00);
    glRotatef(-90,1,0,0);
    GLUquadric* quad4 = gluNewQuadric();
    gluCylinder(quad4,0.08,0.04,0.5,20,20);
    glTranslatef(0,0,0.6);
    glColor3f(0.129, 0.352, 0.027);
    glScalef(1.5,1.5,1);
    glutSolidSphere(0.25,20,20);
  glPopMatrix(); 

  //Dodatna grana

  glPushMatrix();
    glColor3f(0.37,0.18,0.00);
    glTranslatef(0,0.3,0.05);
    gluCylinder(quad4,0.02,0.02,0.2,20,20);
    glTranslatef(0,0,0.2);
    gluDisk(quad4,0,0.02,20,20);
    glTranslatef(0,0,-0.2);
    glColor3f(0.7,0.7,0.7);
    glTranslatef(0,0,0.07);
    glRotatef(90,1,0,0);
    gluCylinder(quad4,0.005,0.005,0.1,20,20);
    glTranslatef(0,0.1,0);
    gluCylinder(quad4,0.005,0.005,0.1,20,20);
  glPopMatrix(); 

  //Guma

  glPushMatrix();
    glColor3f(0.1,0.1,0.1);
    glTranslatef(0,0.17,0.17);
    glRotatef(90,0,1,0);
    glutSolidTorus(0.02,0.05,20,20);


  glPopMatrix();

}

void drawMoon(){
  glColor3f(0.956, 0.945, 0.788);
  GLUquadric* quad5 = gluNewQuadric();
  glRotatef(90,0,1,0);
  gluDisk(quad5,0,2,100,100);
}

void drawHilltop(){
  glColor3f(0.439, 0.470, 0.501);
  glutSolidCube(1);


}

void drawRedWhiteTrack(){
  glPushMatrix();
    glColor3f(1,0,0);
    glutSolidCube(1);
    glTranslatef(1,0,0);
    glColor3f(1,1,1);
    glutSolidCube(1);
  glPopMatrix();
}

void drawWhiteTracks(){
  glPushMatrix();
    glColor3f(1,1,1);
    glutSolidCube(1);
  glPopMatrix();
}

void drawCompleteScene(){

    //draw_axes(150);
    
    glPushMatrix();
      drawTrack();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0,0.1,25.4);
      glScalef(300,0.01,40);
      drawGrass();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0,0.1,-25.4);
      glScalef(300,0.01,40);
      drawGrass();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0,0,25.4);
      glScalef(300,0.01,40);
      drawDirt();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0,0,-25.4);
      glScalef(300,0.01,40);
      drawDirt();
    glPopMatrix();


    glPushMatrix();
      glTranslatef(0,0.1,5.5);
      glScalef(4,4,4);
      drawFence();
      for(int i = 0 ; i < 100 ; i++)
      {
        glTranslatef(0.5,0,0);
        drawFence();
      }
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0,0.1,-5.5);
      glScalef(4,4,4);
      drawFence();
      for(int i = 0 ; i < 100 ; i++)
      {
        glTranslatef(0.5,0,0);
        drawFence();
      }
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-50,0,10.4);
      glScalef(6,6,6);
      drawChristmasTree();
      for(int i = 0 ; i < 20 ; i++)
      {
        glTranslatef(2,0,0);
        drawChristmasTree();
      }
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-50,0,-10.4);
      glScalef(6,6,6);
      drawChristmasTree();
      for(int i = 0 ; i < 20 ; i++)
      {
        glTranslatef(2,0,0);
        drawChristmasTree();
      }
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-20,0,12.4);
      glScalef(6,6,6);
      drawChristmasTree();
      for(int i = 0 ; i < 20 ; i++)
      {
        glTranslatef(2,0,0);
        drawChristmasTree();
      }
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-20,0,-12.4);
      glScalef(6,6,6);
      drawChristmasTree();
      for(int i = 0 ; i < 20 ; i++)
      {
        glTranslatef(2,0,0);
        drawChristmasTree();
      }
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-50,0,14.4);
      glScalef(6,6,6);
      drawChristmasTree();
      for(int i = 0 ; i < 20 ; i++)
      {
        glTranslatef(2,0,0);
        drawChristmasTree();
      }
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-50,0,-14.4);
      glScalef(6,6,6);
      drawChristmasTree();
      for(int i = 0 ; i < 20 ; i++)
      {
        glTranslatef(2,0,0);
        drawChristmasTree();
      }
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-20,0,16.4);
      glScalef(6,6,6);
      drawChristmasTree();
      for(int i = 0 ; i < 20 ; i++)
      {
        glTranslatef(2,0,0);
        drawChristmasTree();
      }
    glPopMatrix();

    glPushMatrix();
      glTranslatef(-20,0,-16.4);
      glScalef(6,6,6);
      drawChristmasTree();
      for(int i = 0 ; i < 20 ; i++)
      {
        glTranslatef(2,0,0);
        drawChristmasTree();
      }
    glPopMatrix();

    glPushMatrix();
      glTranslatef(2.5,0,8.4);
      glScalef(5.5,5.5,5.5);
      drawTree();
      for(int i = 0 ; i < 4 ; i++)
      {
        glTranslatef(8,0,0);
        drawTree();
      }
    glPopMatrix();

    glPushMatrix();
      glTranslatef(2.5,0,-8.4);
      glScalef(5.5,5.5,5.5);
      drawTree();
      for(int i = 0 ; i < 4 ; i++)
      {
        glTranslatef(8,0,0);
        drawTree();
      }
    glPopMatrix();

    glPushMatrix();
      glTranslatef(5,1,20);
      glRotatef(-30,1,0,0);
      glScalef(300,0.01,5);
      drawHilltop();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(5,1,-20);
      glRotatef(30,1,0,0);
      glScalef(300,0.01,5);
      drawHilltop();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0,1.9,-50);
      glScalef(300,0.01,40);
      drawGrass();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0,1.9,50);
      glScalef(300,0.01,40);
      drawGrass();
    glPopMatrix();

    glPushMatrix();
      glTranslatef(0,0,5.2);
      glScalef(1,0.1,0.4);
      drawRedWhiteTrack();
       for(int i = 0 ; i < 100 ; i++)
      {
        glTranslatef(2,0,0);
        drawRedWhiteTrack();
      }
    glPopMatrix();

     glPushMatrix();
      glTranslatef(0,0,-5.2);
      glScalef(1,0.1,0.4);
      drawRedWhiteTrack();
      for(int i = 0 ; i < 100 ; i++)
      {
        glTranslatef(2,0,0);
        drawRedWhiteTrack();
      }
    glPopMatrix();

    glPushMatrix();
      glScalef(2,0.02,0.2);
      glTranslatef(0,0,7.6);
      drawWhiteTracks();
      for(int i = 0 ; i < 100 ; i++)
      {
        glTranslatef(2,0,0);
        drawWhiteTracks();
      }
    glPopMatrix();

    glPushMatrix();
      glScalef(2,0.02,0.2);
      glTranslatef(0,0,-7.6);
      drawWhiteTracks();
      for(int i = 0 ; i < 100 ; i++)
      {
        glTranslatef(2,0,0);
        drawWhiteTracks();
      }
    glPopMatrix();

    glPushMatrix();
      glTranslatef(15,0,0);
      glScalef(1,2,1);
      drawXtrap();
    glPopMatrix();

}

void drawFixedParts(){
  glPushMatrix();
      glScalef(2.5,2.5,2);
      glTranslatef(0.5,0.1,0);
      drawKart();
    glPopMatrix();


   /* glPushMatrix();
      glColor3f(1,0,0);
      glScalef(2.5,1.25,1.8);
      glTranslatef(0.5,0.5,0);
      glutWireCube(1);
    glPopMatrix();
    */

    glPushMatrix();
      glTranslatef(100,0,0);
      glScalef(1,2,2.5);
      drawMoon();
    glPopMatrix();
}

void drawXtrap(){

  //Glavna zuta ploca
  glPushMatrix();
    glColor3f(1,1,0);
    glScalef(1,0.05,1);
    glTranslatef(0,-0.001,0);
    glutSolidCube(1.5);
  glPopMatrix();

  //Ivice
  glBegin(GL_QUADS);

    //Prednja strana

    a={0.95,-0.0375,-0.25};
    b={0.95,-0.0375,0.25};
    c={0.75,0.0375,0.25};
    d={0.75,0.0375,-0.25};
    setNormalAndVertexQuads(a, b, c, d);

    //Zadnja strana
    
    a={-0.95,-0.0375,-0.25};
    b={-0.95,-0.0375,0.25};
    c={-0.75,0.0375,0.25};
    d={-0.75,0.0375,-0.25};
    setNormalAndVertexQuads(a, b, c, d);

    //Desna strana

    a={-0.75,-0.0375,0.95};
    b={0.75,-0.0375,0.95};
    c={0.75,0.0375,0.75};
    d={-0.75,0.0375,0.75};
    setNormalAndVertexQuads(a, b, c, d);

    

    //Leva strana
    a={-0.75,-0.0375,-0.95};
    b={0.75,-0.0375,-0.95};
    c={0.75,0.0375,-0.75};
    d={-0.75,0.0375,-0.75};
    setNormalAndVertexQuads(a, b, c, d);

    glColor3f(1,0,0);

    //Zadnja strana
    a={-0.95,-0.0375,0.75};
    b={-0.75,0.0375,0.75};
    c={-0.75,0.0375,0.25};
    d={-0.95,-0.0375,0.25};
    setNormalAndVertexQuads(a,b,c,d);

    a={-0.95,-0.0375,-0.25};
    b={-0.75,0.0375,-0.25};
    c={-0.75,0.0375,-0.75};
    d={-0.95,-0.0375,-0.75};
    setNormalAndVertexQuads(a,b,c,d);

    //Prednja strana

    a={0.95,-0.0375,0.75};
    b={0.75,0.0375,0.75};
    c={0.75,0.0375,0.25};
    d={0.95,-0.0375,0.25};
    setNormalAndVertexQuads(a,b,c,d);

    a={0.95,-0.0375,-0.25};
    b={0.75,0.0375,-0.25};
    c={0.75,0.0375,-0.75};
    d={0.95,-0.0375,-0.75};
    setNormalAndVertexQuads(a,b,c,d);

    //Slovo X

    a={-0.75,0.0375,0.25};
    b={0.75,0.0375,-0.75};
    c={0.75,0.0375,-0.25};
    d={-0.75,0.0375,0.75};
    setNormalAndVertexQuads(a,b,c,d);

    a={-0.75,0.0375,-0.25};
    b={0.75,0.0375,0.75};
    c={0.75,0.0375,0.25};
    d={-0.75,0.0375,-0.75};
    setNormalAndVertexQuads(a,b,c,d);

    glColor3f(0,0,0);

    a={-0.75,0.0377,0.3};
    b={0.75,0.0377,-0.7};
    c={0.75,0.0377,-0.3};
    d={-0.75,0.0377,0.7};
    setNormalAndVertexQuads(a,b,c,d);

    a={-0.75,0.0377,-0.3};
    b={0.75,0.0377,0.7};
    c={0.75,0.0377,0.3};
    d={-0.75,0.0377,-0.7};
    setNormalAndVertexQuads(a,b,c,d);

    
  glEnd();

  glColor3f(1,0,0);


  glBegin(GL_TRIANGLES);
    a={0.95,-0.0375,0.95};
    b={0.75,-0.0375,0.95};
    c={0.75,0.0375,0.75};
    setNormalAndVertexTriangles(a,b,c);

    a={0.95,-0.0375,0.95};
    b={0.95,-0.0375,0.75};
    c={0.75,0.0375,0.75};
    setNormalAndVertexTriangles(a,b,c);

    a={-0.95,-0.0375,-0.95};
    b={-0.75,-0.0375,-0.95};
    c={-0.75,0.0375,-0.75};
    setNormalAndVertexTriangles(a,b,c);

    a={-0.95,-0.0375,-0.95};
    b={-0.95,-0.0375,-0.75};
    c={-0.75,0.0375,-0.75};
    setNormalAndVertexTriangles(a,b,c);

    a={-0.95,-0.0375,0.95};
    b={-0.75,-0.0375,0.95};
    c={-0.75,0.0375,0.75};
    setNormalAndVertexTriangles(a,b,c);

    a={-0.95,-0.0375,0.95};
    b={-0.95,-0.0375,0.75};
    c={-0.75,0.0375,0.75};
    setNormalAndVertexTriangles(a,b,c);

    a={0.95,-0.0375,-0.95};
    b={0.75,-0.0375,-0.95};
    c={0.75,0.0375,-0.75};
    setNormalAndVertexTriangles(a,b,c);

    a={0.95,-0.0375,-0.95};
    b={0.95,-0.0375,-0.75};
    c={0.75,0.0375,-0.75};
    setNormalAndVertexTriangles(a,b,c);
  glEnd();

}

