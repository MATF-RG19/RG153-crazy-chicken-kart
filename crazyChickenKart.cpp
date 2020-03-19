#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <ctime>
#include <GL/glut.h>
#include <cmath>

using namespace std;

#define TIMER_INTERVAL 20
#define TIMER_ID 0
#define LEN 100


//Definicija strukture tacka radi lakseg i preglednijeg koda 
typedef struct Tacke{
  float x;
  float y;
  float z;
}TACKA;

//Callback funkcije

static void on_display(void);
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);
static void onTimer(int id);


static void lightInitialization(void);
static void drawKart(void);
static void drawSeat(void);
static void drawTires(void);

//Promenljive
static float animationParameter = 0;
static float animationOngoing = 0;
static int windowWidth;
static int windowHeight;
static int zoom = 0;


int main(int argc, char **argv){
   
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    //Postavljanje prozora
    glutInitWindowSize(1200, 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Crazy Chicken Kart");

    //Registrovanje callback funkcija
    glutDisplayFunc(on_display);
    glutReshapeFunc(on_reshape);
    glutKeyboardFunc(on_keyboard);

    //Ukljucivanje dodatnih opengl opcija
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);



    //Postavljanje pozadine na crnu boju
    glClearColor(0.6, 0.6, 0.6, 0);
    glutMainLoop();



    return 0;
}

void draw_axes(float len) {
    glDisable(GL_LIGHTING);

    glBegin(GL_LINES);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(len,0,0);

        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,len,0);

        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,len);
    glEnd();

    glEnable(GL_LIGHTING);
}

void on_keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'r':
          animationParameter = 0;
          glutPostRedisplay();
          break;
        case 's':
        case 'S':
          animationOngoing = 0;
          break;
        case 'g':
        case 'G':
          if(!animationOngoing){
            animationOngoing = 1;
            glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID);
          }
          break;        
        case 27:
          exit(0);
          break;  
            
    }
}

void onTimer(int id){
    if(id == TIMER_ID){
      animationParameter+=4;
    }
    glutPostRedisplay();
    if (animationOngoing)
      glutTimerFunc(TIMER_INTERVAL,onTimer,TIMER_ID);
}

void on_reshape(int width, int height) {
  windowWidth = width;
  windowHeight = height;

  // Viewport
  glViewport(0, 0, width, height);

  // Postavljanje projekcije
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, (float) width / height, 1, 100);
}




void on_display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    lightInitialization();

    //Postavljanje pogleda
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(4*sin(animationParameter/360), 3, 4*cos(animationParameter/360),
              0, 0, 0,
              0, 1, 0);
 
    //draw_axes(50);
    glScalef(3,3,2.5);
    drawKart();
    glutSwapBuffers();
}

void lightInitialization(){
  float lightPosition[] = { 8, 8, 0, 0};
  float lightAmbient[] = { 0.1, 0.1, 0.1, 0.1,1};
  float lightDiffuse[] = { 1, 1, 1, 1};
  float lightSpecular[] = { 0.9, 0.9, 0.9, 1};

  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,1);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
  glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
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



void drawTires() {

  glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(0.15,0.02,0.33);
    GLUquadric* quad1 = gluNewQuadric();
    gluCylinder(quad1,0.12,0.12,0.1,20,20);
    glColor3f(1,0,0);
    gluCylinder(quad1,0.05,0.05,0.1,20,20);
    glColor3f(1,0,0);
    glTranslatef(0,0,-0.03);
    glRotatef(-animationParameter,0,0,1);
    gluCylinder(quad1,0.05,0.05,0.05,20,20);

  glPopMatrix();
  
  glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(0.15,0.02,0.33);
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
    gluCylinder(quad1,0.12,0.12,0.1,20,20);
    glColor3f(1,0,0);
    gluCylinder(quad1,0.05,0.05,0.1,20,20);
    glColor3f(1,0,0);
    glTranslatef(0,0,-0.03);
    glRotatef(-animationParameter,0,0,1);
    gluCylinder(quad1,0.05,0.05,0.1,20,20);

  glPopMatrix();

  glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(-0.3,0.02,0.33);
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
    gluCylinder(quad1,0.12,0.12,0.1,20,20);
    glColor3f(1,0,0);
    gluCylinder(quad1,0.05,0.05,0.1,20,20);
    glColor3f(1,0,0);
    glTranslatef(0,0,0.03);
    glRotatef(-animationParameter,0,0,1);
    gluCylinder(quad1,0.05,0.05,0.1,20,20);

  glPopMatrix();

  glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(-0.3,0.02,-0.43);
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
    gluCylinder(quad1,0.12,0.12,0.1,20,20);
    glColor3f(1,0,0);
    gluCylinder(quad1,0.05,0.05,0.1,20,20);
    glColor3f(1,0,0);
    glTranslatef(0,0,0.03);
    glRotatef(-animationParameter,0,0,1);
    gluCylinder(quad1,0.05,0.05,0.1,20,20);

  glPopMatrix();

  glPushMatrix();
    glColor3f(0,0,0);
    glTranslatef(0.15,0.02,-0.43);
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