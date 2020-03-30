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
#define BLOCK_NUMBER 10


//Granice kretanja
#define MAX_LEFT -3.6
#define MAX_RIGHT 3.6
#define MAX_TURN_LENGTH 3.6


//Callback funkcije

static void on_display(void);
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);
static void onSpecialKeyPress(int key, int x, int y);
static void onTimer(int id);




static void lightInitialization(void);
static void adjustPositionParameters(void);
static void resetAllParameters(void);


//Promenljive
float animationParameter = 0;
float roofParameter = 10.25;
float spoilerParameter = 3.3;
float tiresParameter = 0;
float movementParameter = 0;
//float turnParameter = 0;
int track = 0; // -1 oznacava levu traku,0 srednju,a 1 desnu
//int cameraNumber = 2;
int prviBlok = 0;
int poslednjiBlok = 228;
vector<float> pozicije(BLOCK_NUMBER);



static float animationOngoing = 0;
static float cameraParameter = 0;
static int windowWidth;
static int windowHeight;
static bool roofOn = true;
static bool roofOff = false;
static bool takeOfRoof = false;
static bool putOnRoof = false; 
static bool activateSpoiler = false;
bool goLeft = false;
bool goRight = false;
static bool thirdPerson = true;



int main(int argc, char **argv){
   
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    //Postavljanje prozora
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(500, 300);
    glutCreateWindow("Crazy Chicken Kart");
    //glutFullScreen();


    for(int i = 0, j = 0 ; i < BLOCK_NUMBER ; i++ , j+=24)
    {
    	pozicije[i] = j;
    	//cout << pozicije[i] << endl;
    }



    

    //Registrovanje callback funkcija
    glutDisplayFunc(on_display);
    glutReshapeFunc(on_reshape);
    glutKeyboardFunc(on_keyboard);
    glutSpecialFunc(onSpecialKeyPress);

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
        	resetAllParameters();
        	glutPostRedisplay();
        	break;
        case 's':
        case 'S':
          	animationOngoing = 0;
          	break;
        case 'g':
        case 'G':
          	if(!animationOngoing)
          	{
            	animationOngoing = 1;
            	glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID);
          	}
          	break;
        case 'j':
          	if(!animationOngoing)
          	{
            	animationOngoing = 1;
            	glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID);
            } 
          	takeOfRoof=true;
          	putOnRoof=false;
          	break;          
        case 'k':
          	if(!animationOngoing)
          	{
            	animationOngoing = 1;
            	glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID);
            }
          	putOnRoof=true;
          	takeOfRoof=false;
          	break;
          	/*
        case 'l':
          	activateSpoiler=true;
          	break;*/
        case 'f':
          	if(thirdPerson)
            	thirdPerson = false;
          	else
            	thirdPerson = true;
            /*cameraNumber++;
            if(cameraNumber==3)
            	cameraNumber=0;*/
          	break;  
        case 'd':
        case 'D':
        	if(animationParameter > 0)
       		{
		        goRight=true;
		        goLeft=false;
	          	if(track != 1)
	            	track += 1;
		        glutPostRedisplay();
       		}
        	break;
        case 'a':
        case 'A':
        	if(animationParameter > 0)
       		{
		        goLeft=true;
		        goRight=false;
	          	if(track != -1)
	            	track -= 1;
		        glutPostRedisplay();
       		}
        	break;	                
        case 27:
          exit(0);
          break;  
            
    }
}

void onSpecialKeyPress(int key, int x, int y){

  switch(key){
    case GLUT_KEY_RIGHT:
      if(animationParameter > 0)
       {
	        goRight=true;
	        goLeft=false;
          if(track != 1)
            track += 1;
	        glutPostRedisplay();
        }
        break;
    case GLUT_KEY_LEFT:
      if(animationParameter > 0)
      	{
	        goLeft = true;
	        goRight = false;
          if(track != -1)
            track -= 1;
	        glutPostRedisplay();
    	}
        break;
      
    
  }
}

void onTimer(int id){
    if(id == TIMER_ID){

      if(cameraParameter<1120)
        cameraParameter+=5;
      else
      {
        animationParameter+=0.75;
        tiresParameter+=2;

        for(int i = 0 ; i < BLOCK_NUMBER ; i++)
        {
        	pozicije[i] -= 0.75;
        }

        if(pozicije[prviBlok] == -72)
        {
        	pozicije[prviBlok] = 168;
        	prviBlok++;

        	if(prviBlok == BLOCK_NUMBER)
        		prviBlok = 0;
        }
        
      }

      if(roofParameter >= 0 && takeOfRoof)
        roofParameter-=0.06;

      if(roofParameter <= 10.25 && putOnRoof)
        roofParameter+=0.06;

      /*if(activateSpoiler)
        spoilerParameter+=0.05;*/

    	adjustPositionParameters();



      //cout << animationParameter << endl;
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
	  gluPerspective(60, (float) width / height, 0.4, 150);
}

void on_display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  lightInitialization();

    //Postavljanje pogleda
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    if(thirdPerson)
      gluLookAt(5*cos(cameraParameter/360), 2.5, 4*sin(cameraParameter/360)+movementParameter,
                1, 0, 0+movementParameter,
                0, 1, 0);
    else
      gluLookAt(0.75, 0.85, -0.3+movementParameter,
              150, 0.5, -0.3+movementParameter,
              0, 1, 0);

 	
 	 //draw_axes(50);
   drawFixedParts(); 

   glPushMatrix();
    drawCompleteScene();
   glPopMatrix();

    

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

void adjustPositionParameters(){


	//Iz srednje u desnu
  	if(goRight && track==1)
  	{
        movementParameter+=0.2;
        if(movementParameter>=MAX_RIGHT)
        {
          	movementParameter=MAX_RIGHT;
          	goRight=false;
        }
    }

    if(goRight && track==0)
    {
    	movementParameter+=0.2;
        if(movementParameter>=0)
        {
          movementParameter=0;
          goRight=false;
        }
    }


    if(goLeft && track==-1)
    {
        movementParameter-=0.2;
        if(movementParameter<=MAX_LEFT)
        {
          movementParameter=MAX_LEFT;
          goLeft=false;
        }
    }


    if(goLeft && track==0)
    {
        movementParameter-=0.2;
        if(movementParameter<=0)
        {
          movementParameter=0;
          goLeft=false;
        }
    }

}

void resetAllParameters(){
  animationParameter = 0;
  cameraParameter = 0;
  roofParameter=10.25;
  takeOfRoof=false;
  putOnRoof=false;
  spoilerParameter=3.3;
  activateSpoiler=false;
  movementParameter = 0;
  movementParameter = 0;
  track = 0;
  prviBlok=0;

  for(int i = 0, j = 0 ; i < BLOCK_NUMBER ; i++ , j+=24)
    {
      pozicije[i] = j;
      //cout << pozicije[i] << endl;
    }
}
