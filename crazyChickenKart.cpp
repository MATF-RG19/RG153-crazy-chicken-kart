#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <ctime>
#include <GL/glut.h>
#include <cmath>
#include "DrawFunctions.hpp"

using namespace std;

#define TIMER_INTERVAL 20
#define TIMER_ID 0
#define LEN 100

//Callback funkcije

static void on_display(void);
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);
static void onTimer(int id);


static void lightInitialization(void);

//Promenljive
float animationParameter = 0;
float roofParameter = 10.25;
float spoilerParameter = 3.3;
float tiresParameter = 0;
static float animationOngoing = 0;
static float cameraParameter = 0;
static int windowWidth;
static int windowHeight;
static int zoom = 0;
static bool roofOn = true;
static bool roofOff = false;
static bool takeOfRoof = false;
static bool putOnRoof = false; 
static bool activateSpoiler = false;


int main(int argc, char **argv){
   
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    //Postavljanje prozora
    glutInitWindowSize(1200, 1000);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Crazy Chicken Kart");
    //glutFullScreen();

    //Registrovanje callback funkcija
    glutDisplayFunc(on_display);
    glutReshapeFunc(on_reshape);
    glutKeyboardFunc(on_keyboard);

    //Ukljucivanje dodatnih opengl opcija
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);



    //Postavljanje pozadine na crnu boju
    glClearColor(0.031, 0.094, 0.227,0);
    glutMainLoop();



    return 0;
}

void on_keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'r':
          animationParameter = 0;
          cameraParameter = 0;
          roofParameter=10.25;
          takeOfRoof=false;
          putOnRoof=false;
          spoilerParameter=3.3;
          activateSpoiler=false;
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
        case 'j':
          if(!animationOngoing){
              animationOngoing = 1;
              glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID);
            } 
          takeOfRoof=true;
          putOnRoof=false;
          break;          
        case 'k':
          if(!animationOngoing){
              animationOngoing = 1;
              glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID);
            }
          putOnRoof=true;
          takeOfRoof=false;
          break;
        case 'l':
          activateSpoiler=true;
          break;          
        case 27:
          exit(0);
          break;  
            
    }
}

void onTimer(int id){
    if(id == TIMER_ID){
      if(cameraParameter<1120)
        cameraParameter+=5;
      else
      {
        animationParameter+=0.2;
        tiresParameter+=2;
      }

      if(animationParameter>100)
      {
        animationParameter = 0;
          cameraParameter = 0;
      }

      if(roofParameter >= 0 && takeOfRoof)
        roofParameter-=0.06;

      if(roofParameter <= 10.25 && putOnRoof)
        roofParameter+=0.06;

      if(activateSpoiler)
        spoilerParameter+=0.05;
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
    gluLookAt(5*cos(cameraParameter/360), 2.5, 4*sin(cameraParameter/360),
              1, 0, 0,
              0, 1, 0);

    /*gluLookAt(-4, 2, 0,
              0, 0, 0,
              0, 1, 0);*/
 	
 	 //draw_axes(50);
   drawFixedParts(); 

   glTranslatef(-animationParameter,0,0);
   drawCompleteScene();
    

    glutSwapBuffers();
}

void lightInitialization(){
  float lightPosition[] = { 5*cos(cameraParameter/360), 8, 4*sin(cameraParameter/360), 0};
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
