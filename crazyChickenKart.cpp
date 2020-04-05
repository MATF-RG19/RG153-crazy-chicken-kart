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
#define TIMER_ID1 0 // Koristimo za animaciju voznje
#define TIMER_ID2 1 // Koristimo za animaciju kamere
#define TIMER_ID3 2 // Koristimo za animaciju prepreka
#define LEN 100
#define BLOCK_NUMBER 10
#define OBSTACLE_NUMBER 20
#define SPACEBAR 32


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
static void detectColision(void);

//Struktura prepreke

struct OBSTACLE {
	float x;
	int track;
	int type;
};


//Promenljive
float roofParameter = 10.25;
float spoilerParameter = 3.3;
float tiresParameter = 0;
float movementParameter = 0;
//float turnParameter = 0;
int track = 0; // -1 oznacava levu traku,0 srednju,a 1 desnu
//int cameraNumber = 2;
int firstBlock = 0;
int firstObstacle = 0;
int tajmercic = 0;
float holeParameter = 0;
float holeRotation = 0;
vector<float> blockPosition(BLOCK_NUMBER);
vector<OBSTACLE> obstacle(OBSTACLE_NUMBER);



static float animationOngoing = 0;
static float cameraParameter = 0;
static int windowWidth;
static int windowHeight;
static bool roofOn = true;
static bool roofOff = false;
static bool takeOfRoof = false;
static bool putOnRoof = false; 
static bool activateSpoiler = false;
static bool thirdPerson = true;
static bool pressedStart = false;
static bool goPressed = false;
bool goLeft = false;
bool goRight = false;
bool activateHole = false;


//Promenljive za odredjivanje animacija

static float driveAnimation = 0;
int cameraAnimation = 1;
int trapAnimation = 0;




int main(int argc, char **argv){
   
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE | GLUT_MULTISAMPLE);

    //Postavljanje prozora
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(500, 300);
    glutCreateWindow("Crazy Chicken Kart");
    //glutFullScreen();

    //Inicijalizacija pocetnih pozicija blokova okoline i prepreka

    for(int i = 0, j = 0 ; i < BLOCK_NUMBER ; i++ , j+=24)
    	blockPosition[i] = j;

    srand(time(NULL));
    for(int i = 0 , j = 40; i < OBSTACLE_NUMBER ; i++ , j+=40)
    {
    	obstacle[i].x = j;
    	obstacle[i].type = rand()%3;
    	obstacle[i].track = rand()%3-1;
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
        	if(!pressedStart)
        	{
        		pressedStart = true;
	          	if(!driveAnimation && cameraAnimation == 0)
	          	{
	            	driveAnimation = 1;
	            	glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID1);
	          	}else if(cameraAnimation)
	          		glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID2);
          	}
          	break;
        case 'j': 
        	if(cameraAnimation || driveAnimation)
        	{
	          	takeOfRoof=true;
	          	putOnRoof=false;
          	}
          	break;          
        case 'k':
          	if(cameraAnimation || driveAnimation)
          	{
	          	putOnRoof=true;
	          	takeOfRoof=false;
          	}
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
        	if(driveAnimation)
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
        	if(driveAnimation)
       		{
		        goLeft=true;
		        goRight=false;
	          	if(track != -1)
	            	track -= 1;
		        glutPostRedisplay();
       		}
        	break;
        case SPACEBAR:
        	if(!goPressed)
        		goPressed=true;
        	break;		                
        case 27:
          exit(0);
          break;  
            
    }
}

void onSpecialKeyPress(int key, int x, int y){

  switch(key){
    case GLUT_KEY_RIGHT:
      if(driveAnimation)
       {
	        goRight=true;
	        goLeft=false;
          if(track != 1)
            track += 1;
	        glutPostRedisplay();
        }
        break;
    case GLUT_KEY_LEFT:
      if(driveAnimation)
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
    if(id == TIMER_ID1){

    	if(goPressed)
    	{
        tiresParameter+=2;

        for(int i = 0 ; i < BLOCK_NUMBER ; i++)
        	blockPosition[i] -= 1;

        if(blockPosition[firstBlock] == -72)
        {
        	blockPosition[firstBlock] = 168;
        	firstBlock++;

        	if(firstBlock == BLOCK_NUMBER)
        		firstBlock = 0;
        }

        for(int i = 0 ; i < OBSTACLE_NUMBER ; i++)
      		obstacle[i].x -= 1;


      if(obstacle[firstObstacle].x == -20)
      {
      	obstacle[firstObstacle].x  = 780;
      	firstObstacle++;

      	if(firstObstacle == OBSTACLE_NUMBER)
      		firstObstacle = 0;
      }

      detectColision();


      if(roofParameter >= 0 && takeOfRoof)
        roofParameter-=0.06;

      if(roofParameter <= 10.25 && putOnRoof)
        roofParameter+=0.06;

      /*if(activateSpoiler)
        spoilerParameter+=0.05;*/

    	adjustPositionParameters();
    }

    }else if(id == TIMER_ID2)
    {

    	cameraParameter+=2.5;
    	if(cameraParameter > 1130)
    	{
    		cameraAnimation = 0;
    		driveAnimation = 1;
    	}
    }else
    {
      thirdPerson = true;
      holeParameter += 0.1;

      if(holeParameter > 1.2)
      {
        holeRotation += 0.2;
        holeParameter += 0.05;
      }
    }
    glutPostRedisplay();
    if (driveAnimation)
    	glutTimerFunc(TIMER_INTERVAL,onTimer,TIMER_ID1);
  	else if(cameraAnimation)
  		glutTimerFunc(TIMER_INTERVAL,onTimer,TIMER_ID2);
  	else
  		glutTimerFunc(TIMER_INTERVAL,onTimer,TIMER_ID3);
}

void on_reshape(int width, int height) {
	  windowWidth = width;
	  windowHeight = height;

	  // Viewport
	  glViewport(0, 0, width, height);

	  // Postavljanje projekcije
	  glMatrixMode(GL_PROJECTION);
	  glLoadIdentity();
	  gluPerspective(60, (float) width / height, 0.3, 150);
}

void on_display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  lightInitialization();

    //Postavljanje pogleda
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if(driveAnimation || trapAnimation)
    {
	    if(thirdPerson)
	      gluLookAt(5*cos(cameraParameter/360), 3, sin(cameraParameter/360)+movementParameter,
	                120, 0,movementParameter,
	                0, 1, 0);
	    else
	      gluLookAt(1, 0.85, -0.3+movementParameter,
	              120, 0, movementParameter,
	              0, 1, 0);
	}
	else
		gluLookAt(5*cos(cameraParameter/360), 3,-2.5*sin(cameraParameter/360),
		                1.5, cameraParameter/400, 0,
		                0, 1, 0);

  	glEnable(GL_MULTISAMPLE);
    glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_FASTEST);

 	
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
  cameraParameter = 0;
  roofParameter=10.25;
  takeOfRoof=false;
  putOnRoof=false;
  spoilerParameter=3.3;
  activateSpoiler=false;
  movementParameter = 0;
  track = 0;
  firstBlock=0;
  firstObstacle=0;
  activateHole = false;
  driveAnimation = 0;
  cameraAnimation = 1;
  trapAnimation = 0;
  goPressed = false;
  goLeft = false;
  goRight = false;
  tajmercic = 0;
  holeRotation = 0;
  holeParameter = 0;


  for(int i = 0, j = 0 ; i < BLOCK_NUMBER ; i++ , j+=24)
  	blockPosition[i] = j;

    for(int i = 0 , j = 40; i < OBSTACLE_NUMBER ; i++ , j+=40)
    {
    	obstacle[i].x = j;
    	obstacle[i].type = rand()%3;
    	obstacle[i].track = rand()%3-1;
    }
}

void detectColision() {
	if(obstacle[firstObstacle].x - 1 == 3)

      	switch(obstacle[firstObstacle].track)
      	{
      		case 0:
      			if(movementParameter < 1.8 && movementParameter > -1.8)
      			{
	      			cout << "Udario si u: ";
	      			switch(obstacle[firstObstacle].type)
	      			{
		      			case 0:
		      				cout << "X zamku" << endl;
		      				driveAnimation = 0;
		      				trapAnimation = 1;
		      				break;
		      			case 1:
		      				cout << "Rupu" << endl;
		      				activateHole = true;
		      				driveAnimation = 0;
		      				trapAnimation = 1;
		      				break;
		      			case 2:
		      				cout << "Bombu" << endl;
		      				driveAnimation = 0;
		      				trapAnimation = 1;
		      				break;
		      		}		

      			

      			}
      			break;
      		case 1:
      			if(movementParameter < 5.4 && movementParameter > 1.8)
      			{
	      			cout << "Udario si u: ";
	      			switch(obstacle[firstObstacle].type)
	      			{
		      			case 0:
		      				cout << "X zamku" << endl;
		      				driveAnimation = 0;
		      				trapAnimation = 1;
		      				break;
		      			case 1:
		      				cout << "Rupu" << endl;
		      				activateHole = true;
		      				driveAnimation = 0;
		      				trapAnimation = 1;
		      				break;
		      			case 2:
		      				cout << "Bombu" << endl;
		      				driveAnimation = 0;
		      				trapAnimation = 1;
		      				break;
		      		}		

      			

      			}
      			break;
      		case -1:
      			if(movementParameter > -5.4 && movementParameter < -1.8)
      			{
	      			cout << "Udario si u: ";
	      			switch(obstacle[firstObstacle].type)
	      			{
		      			case 0:
		      				cout << "X zamku" << endl;
		      				driveAnimation = 0;
		      				trapAnimation = 1;
		      				break;
		      			case 1:
		      				cout << "Rupu" << endl;
		      				driveAnimation = 0;
		      				trapAnimation = 1;
		      				activateHole = true;
		      				break;
		      			case 2:
		      				cout << "Bombu" << endl;
		      				driveAnimation = 0;
		      				trapAnimation = 1;
		      				break;
		      		}		

      			

      			}
      			break;		



      	}
}
