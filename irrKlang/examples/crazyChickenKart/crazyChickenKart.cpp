#include <GL/glut.h>
#include <irrKlang.h>

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "DrawFunctions.hpp"
#include "image.hpp"

// using namespace std;
using namespace irrklang;

#pragma comment(lib, "irrKlang.lib")

#define FILENAME0 "navigation.bmp"
#define FILENAME1 "speedometer.bmp"
#define FILENAME2 "plate.bmp"
#define FILENAME3 "sky.bmp"
#define FILENAME4 "keyguide.bmp"

/* Identifikatori tekstura. */
static GLuint names[5];

#define TIMER_INTERVAL 20
#define TIMER_ID1 0  // Koristimo za animaciju voznje
#define TIMER_ID2 1  // Koristimo za animaciju kamere
#define TIMER_ID3 2  // Koristimo za animaciju prepreka
#define LEN 100
#define BLOCK_NUMBER 10
#define OBSTACLE_NUMBER 20
#define STAR_NUMBER 10
#define SPACEBAR 32
#define ESC 27
#define STAR_POINTS 100

/* Granice kretanja */
#define MAX_LEFT -3.6
#define MAX_RIGHT 3.6
#define MAX_TURN_LENGTH 3.6

/* Callback funkcije */

static void on_display(void);
static void on_reshape(int width, int height);
static void on_keyboard(unsigned char key, int x, int y);
static void onSpecialKeyPress(int key, int x, int y);
static void onTimer(int id);

static void lightInitialization(void);
static void adjustPositionParameters(void);
static void resetAllParameters(void);
static void detectTrapColision(void);
static void detectStarColision(void);
static void initializeTextures(void);
static void displayStartScreen(void);
static void displayEndScreen(void);
static float matrix[16];

/* Struktura prepreke */

struct OBSTACLE {
  float x;
  int track;
  int type;
};

/* Struktura zvezde */

struct STARS {
  float x;
  float y;
  int track;
  bool goUp;
};

/* Promenljive */

float roofParameter     = 10.25;
float spoilerParameter  = 3.3;
float tiresParameter    = 0;
float movementParameter = 0;
// float turnParameter = 0;
int track                 = 0;  // -1 oznacava levu traku,0 srednju,a 1 desnu
float holeParameter       = 0;
float holeRotation        = 0;
float xTrapHorizontal     = 0;
float xTrapVertical       = 0;
float xTrapRotation       = 0;
float bombParameter       = 0;
float movementSpeed       = 0;
int starRotationParameter = 0;
int score                 = 0;
int starsCollected        = 0;
vector<float> blockPosition(BLOCK_NUMBER);
vector<OBSTACLE> obstacle(OBSTACLE_NUMBER);
vector<STARS> stars(STAR_NUMBER);

/* Pokazivaci na prvi i poslednji blok */
int firstBlock = 0;
int lastBlock  = 9;

/* Pokazivaci na prvu i poslenju prepreku */

int firstObstacle = 0;
int lastObstacle  = 19;

/* Pokazivaci na prvu i poslednju zvezdu */

int firstStar = 0;
int lastStar  = 9;

static float animationOngoing = 0;
static float cameraParameter  = 0;
static int windowWidth;
static int windowHeight;
static bool roofOn          = true;
static bool roofOff         = false;
static bool takeOffRoof     = false;
static bool putOnRoof       = false;
static bool activateSpoiler = false;
static bool thirdPerson     = true;
static bool pressedStart    = false;
static bool goPressed       = false;
static bool keyGuideScreen  = true;
static bool godMode         = false;
bool goLeft                 = false;
bool goRight                = false;
bool activateHole           = false;
bool activateXtrap          = false;
bool activateBomb           = false;

/* Promenljive za odredjivanje animacija */

static float driveAnimation = 0;
int cameraAnimation         = 1;
int trapAnimation           = 0;

ISoundEngine *SoundEngine = createIrrKlangDevice();

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE | GLUT_MULTISAMPLE |
                      GLUT_ALPHA);

  /* Postavljanje prozora */

  glutInitWindowSize(800, 600);
  glutInitWindowPosition(500, 300);
  glutCreateWindow("Crazy Chicken Kart");
  // glutFullScreen();

  /* Inicijalizacija pocetnih pozicija blokova okoline,prepreka i zvezdica */

  for (int i = 0, j = 0; i < BLOCK_NUMBER; i++, j += 24) blockPosition[i] = j;

  srand(time(NULL));
  for (int i = 0, j = 40; i < OBSTACLE_NUMBER; i++, j += 40) {
    obstacle[i].x     = j;
    obstacle[i].type  = rand() % 3;
    obstacle[i].track = rand() % 3 - 1;
  }

  for (int i = 0, j = 250; i < STAR_NUMBER; i++, j += 250) {
    stars[i].x     = j;
    stars[i].track = rand() % 3 - 1;
    stars[i].goUp  = false;
    stars[i].y     = 0;
  }

  /* Inicijalizacija tekstura */

  initializeTextures();

  /* Registrovanje callback funkcija */

  glutDisplayFunc(on_display);
  glutReshapeFunc(on_reshape);
  glutKeyboardFunc(on_keyboard);
  glutSpecialFunc(onSpecialKeyPress);

  /* Ukljucivanje dodatnih opengl opcija */

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);

  /*Postavljanje pozadine na crnu boju */

  glClearColor(0.031, 0.094, 0.227, 0);

  if (!engine) return 0;

  engine->play2D("../../media/getout.ogg", true);

  glutMainLoop();

  return 0;
}

void on_keyboard(unsigned char key, int x, int y) {
  switch (key) {
    case 'r':
      resetAllParameters();
      glutPostRedisplay();
      break;
    case 's':
    case 'S': animationOngoing = 0; break;
    case 'g':
    case 'G':
      if (!pressedStart) {
        keyGuideScreen = false;
        pressedStart   = true;
        if (!driveAnimation && cameraAnimation == 0) {
          driveAnimation = 1;
          glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID1);
        } else if (cameraAnimation)
          glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID2);
      }
      break;
    case 'q':
    case 'Q':
      if (takeOffRoof) {
        putOnRoof   = true;
        takeOffRoof = false;
      } else {
        takeOffRoof = true;
        putOnRoof   = false;
      }
      break;

    case 'e': activateSpoiler = true; break;
    case 'f':
      if (thirdPerson)
        thirdPerson = false;
      else
        thirdPerson = true;
      break;
    case 'd':
    case 'D':
      if (driveAnimation) {
        goRight = true;
        goLeft  = false;
        if (track != 1) track += 1;
        glutPostRedisplay();
      }
      break;
    case 'a':
    case 'A':
      if (driveAnimation) {
        goLeft  = true;
        goRight = false;
        if (track != -1) track -= 1;
        glutPostRedisplay();
      }
      break;
    case SPACEBAR:
      if (!goPressed && driveAnimation) goPressed = true;
      break;
    case 'k':
    case 'K':
      if (!godMode)
        godMode = true;
      else
        godMode = false;
      break;
    case ESC: exit(0); break;
  }
}

void onSpecialKeyPress(int key, int x, int y) {
  switch (key) {
    case GLUT_KEY_RIGHT:
      if (driveAnimation) {
        goRight = true;
        goLeft  = false;
        if (track != 1) track += 1;
        glutPostRedisplay();
      }
      break;
    case GLUT_KEY_LEFT:
      if (driveAnimation) {
        goLeft  = true;
        goRight = false;
        if (track != -1) track -= 1;
        glutPostRedisplay();
      }
      break;
  }
}

void onTimer(int id) {
  if (id == TIMER_ID1) {
    if (goPressed) {
      tiresParameter += 2;
      starRotationParameter += 5;

      /* Uvecavanje brzine kretanja */

      if (movementSpeed < 1) {
        movementSpeed += 0.005;
        score += 1;
      } else if (movementSpeed < 1.5) {
        movementSpeed += 0.0025;
        score += 2;
      } else if (movementSpeed < 3) {
        movementSpeed += 0.001;
        score += 3;
      }

      /* Promena pozicija blokova u zavisnosti od brzine kretanja.
         Kada prvi blok dodje na poziciju manju od -72 on se translira
         na poziciju poslednjeg bloka plus 24 (24 je duzina jednog bloka)
         Ako pokazivac za prvi blok pokazuje na poslednji blok(9),njega
         prebacujemo da pokazuje na prvi blok(0) */

      for (int i = 0; i < BLOCK_NUMBER; i++) blockPosition[i] -= movementSpeed;

      if (blockPosition[firstBlock] <= -72) {
        blockPosition[firstBlock] = blockPosition[lastBlock] + 24;
        lastBlock                 = firstBlock;
        firstBlock++;

        if (firstBlock == BLOCK_NUMBER) firstBlock = 0;
      }

      /* Vrsi se promena pozicija prepreka po istom principu kao sa blokovima */

      for (int i = 0; i < OBSTACLE_NUMBER; i++) obstacle[i].x -= movementSpeed;

      if (obstacle[firstObstacle].x <= -20) {
        obstacle[firstObstacle].x = obstacle[lastObstacle].x + 40;
        lastObstacle              = firstObstacle;
        firstObstacle++;

        if (firstObstacle == OBSTACLE_NUMBER) firstObstacle = 0;
      }

      /* Vrsi se promena pozicija zvezdica po istom principu kao sa blokovima i
       * preprekama */

      for (int i = 0; i < STAR_NUMBER; i++) {
        stars[i].x -= movementSpeed;
        if (stars[i].goUp && stars[i].y < 4) {
          stars[i].y += 1;
        }
      }

      if (stars[firstStar].x <= -20) {
        stars[firstStar].goUp = false;
        stars[firstStar].y    = 0;
        stars[firstStar].x    = stars[lastStar].x + 250;
        lastStar              = firstStar;
        firstStar++;

        if (firstStar == STAR_NUMBER) firstStar = 0;
      }

      /* Detektovanje kolizije sa preprekama se aktivira u
   zavisnosti od bool promenljive godMode(da li je
   aktiviran stit oko buggy-ja) */

      if (!godMode) detectTrapColision();

      /* Detektovanje kolizije sa zvezdicama, naredbom
         if(!stars[firstStar].goUp) izbegavamo ponavljanje detekcije kolizije
         iste zvezdice */

      if (!stars[firstStar].goUp) detectStarColision();

      /* Promene parametara za skidanje krova,aktiviranje spojlera */

      if (roofParameter >= 0 && takeOffRoof) roofParameter -= 0.06;

      if (roofParameter <= 10.25 && putOnRoof) roofParameter += 0.06;

      if (activateSpoiler) spoilerParameter += 0.05;

      /* Promene pozicije buggy-ja */

      adjustPositionParameters();
    }

  } else if (id == TIMER_ID2) {
    cameraParameter += 2.5;
    if (cameraParameter > 1130) {
      cameraAnimation = 0;
      driveAnimation  = 1;
    }
  } else {
    thirdPerson = true;

    if (activateHole) {
      holeParameter += 0.1;

      if (holeParameter > 1.2) {
        holeRotation += 0.2;
        holeParameter += 0.05;
      }

      if (holeParameter > 10) {
        score += starsCollected * STAR_POINTS;
        cout << score << endl;
        resetAllParameters();
      }
    } else if (activateXtrap) {
      if (xTrapHorizontal < 75) {
        xTrapHorizontal += 0.5;
        if (xTrapHorizontal > 25) xTrapRotation += 0.5;
      } else {
        score += starsCollected * STAR_POINTS;
        cout << score << endl;
        resetAllParameters();
      }

      if (xTrapVertical > -2) xTrapVertical -= 0.05;
    } else {
      if (bombParameter < 5.7)
        bombParameter += 0.3;
      else {
        score += starsCollected * STAR_POINTS;
        cout << score << endl;
        resetAllParameters();
      }
    }
  }
  glutPostRedisplay();
  if (driveAnimation)
    glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID1);
  else if (cameraAnimation)
    glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID2);
  else
    glutTimerFunc(TIMER_INTERVAL, onTimer, TIMER_ID3);
}

void on_reshape(int width, int height) {
  windowWidth  = width;
  windowHeight = height;

  /* Viewport */

  glViewport(0, 0, width, height);

  /* Postavljanje projekcije */

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, (float)width / height, 0.3, 150);
}

void on_display() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  lightInitialization();

  /* Postavljanje pogleda */

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  if (driveAnimation || trapAnimation) {
    if (thirdPerson)
      gluLookAt(-5, 3, movementParameter, 120, 0, movementParameter, 0, 1, 0);
    else
      gluLookAt(1, 0.8, -0.3 + movementParameter, 120, 0, movementParameter, 0,
                1, 0);
  } else
    gluLookAt(5 * cos(cameraParameter / 360), 3,
              -2.5 * sin(cameraParameter / 360), 1.5, cameraParameter / 400, 0,
              0, 1, 0);

  /* Aktiviranje multisamplovanja(anti-aliasing) */

  glEnable(GL_MULTISAMPLE);
  glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);

  // draw_axes(50);
  drawFixedParts();

  glPushMatrix();
  drawCompleteScene();
  glPopMatrix();

  if (keyGuideScreen) displayStartScreen();

  glPushMatrix();
  glTranslatef(0, 0.2, movementParameter);

  /* Tekstura neba */

  glBindTexture(GL_TEXTURE_2D, names[3]);
  glBegin(GL_QUADS);
  glNormal3f(0, 0, -1);

  glTexCoord2f(0, 0);
  glVertex3f(140, -25, -200);

  glTexCoord2f(1, 0);
  glVertex3f(140, -25, 200);

  glTexCoord2f(1, 1);
  glVertex3f(140, 90, 200);

  glTexCoord2f(0, 1);
  glVertex3f(140, 90, -200);
  glEnd();
  glPopMatrix();

  if (!trapAnimation) {
    glPushMatrix();
    glTranslatef(0, 0.2, movementParameter);

    /*Tekstura navigacije*/

    glBindTexture(GL_TEXTURE_2D, names[0]);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);

    glTexCoord2f(0, 0);
    glVertex3f(1.8105, 0.23625, -0.0765);

    glTexCoord2f(1, 0);
    glVertex3f(1.8105, 0.23625, 0.0765);

    glTexCoord2f(1, 1);
    glVertex3f(1.932, 0.32625, 0.0765);

    glTexCoord2f(0, 1);
    glVertex3f(1.932, 0.32625, -0.0765);

    glEnd();

    glScalef(0.15, 0.15, 0.15);

    /*Tekstura brzinometra*/

    glBindTexture(GL_TEXTURE_2D, names[1]);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);

    glTexCoord2f(0, 0);
    glVertex3f(12.98, 2.25, -3);

    glTexCoord2f(1, 0);
    glVertex3f(12.98, 2.25, -1.5);

    glTexCoord2f(1, 1);
    glVertex3f(13.73, 2.8125, -1.5);

    glTexCoord2f(0, 1);
    glVertex3f(13.73, 2.8125, -3);
    glEnd();

    /*Tekstura tablice*/

    glBindTexture(GL_TEXTURE_2D, names[2]);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);

    glTexCoord2f(0, 0);
    glVertex3f(-0.51, 2.25, -1.75);

    glTexCoord2f(1, 0);
    glVertex3f(-0.51, 2.25, 1.75);

    glTexCoord2f(1, 1);
    glVertex3f(-0.51, 3.25, 1.75);

    glTexCoord2f(0, 1);
    glVertex3f(-0.51, 3.25, -1.75);
    glEnd();

    glPopMatrix();
  }

  /* Iskljucujemo aktivnu teksturu */

  glBindTexture(GL_TEXTURE_2D, 0);

  if (godMode) {
    glPushMatrix();
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.0f, 1.0f, 0.5f);
    glTranslatef(1.2, 0.2, movementParameter);
    glScalef(1.94, 1.1, 1.2);
    glRotatef(starRotationParameter, -1, 0, 0);
    glutSolidSphere(1.2, 50, 50);
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
    glPopMatrix();
  }

  glutSwapBuffers();
}

void lightInitialization() {
  float lightPosition[] = {5 * cos(cameraParameter / 360), 8,
                           4 * sin(cameraParameter / 360), 0};
  float lightAmbient[]  = {0.1, 0.1, 0.1, 0.1, 1};
  float lightDiffuse[]  = {1, 1, 1, 1};
  float lightSpecular[] = {0.9, 0.9, 0.9, 1};

  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
  glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
}

void adjustPositionParameters() {
  /* Iz srednje u desnu */
  if (goRight && track == 1) {
    movementParameter += 0.2;
    if (movementParameter >= MAX_RIGHT) {
      movementParameter = MAX_RIGHT;
      goRight           = false;
    }
  }

  if (goRight && track == 0) {
    movementParameter += 0.2;
    if (movementParameter >= 0) {
      movementParameter = 0;
      goRight           = false;
    }
  }

  if (goLeft && track == -1) {
    movementParameter -= 0.2;
    if (movementParameter <= MAX_LEFT) {
      movementParameter = MAX_LEFT;
      goLeft            = false;
    }
  }

  if (goLeft && track == 0) {
    movementParameter -= 0.2;
    if (movementParameter <= 0) {
      movementParameter = 0;
      goLeft            = false;
    }
  }
}

void resetAllParameters() {
  cameraParameter   = 0;
  roofParameter     = 10.25;
  takeOffRoof       = false;
  putOnRoof         = false;
  spoilerParameter  = 3.3;
  activateSpoiler   = false;
  movementParameter = 0;
  track             = 0;
  firstBlock        = 0;
  firstObstacle     = 0;
  activateHole      = false;
  activateXtrap     = false;
  activateBomb      = false;
  driveAnimation    = 0;
  cameraAnimation   = 1;
  trapAnimation     = 0;
  goPressed         = false;
  goLeft            = false;
  goRight           = false;
  holeRotation      = 0;
  holeParameter     = 0;
  xTrapHorizontal   = 0;
  xTrapVertical     = 0;
  xTrapRotation     = 0;
  bombParameter     = 0;
  pressedStart      = false;
  lastBlock         = 9;
  lastObstacle      = 19;
  lastStar          = 9;
  firstStar         = 0;
  movementSpeed     = 0;
  score             = 0;
  starsCollected    = 0;
  godMode           = false;

  for (int i = 0, j = 0; i < BLOCK_NUMBER; i++, j += 24) blockPosition[i] = j;

  for (int i = 0, j = 40; i < OBSTACLE_NUMBER; i++, j += 40) {
    obstacle[i].x     = j;
    obstacle[i].type  = rand() % 3;
    obstacle[i].track = rand() % 3 - 1;
  }

  for (int i = 0, j = 250; i < STAR_NUMBER; i++, j += 250) {
    stars[i].x     = j;
    stars[i].track = rand() % 3 - 1;
    stars[i].goUp  = false;
    stars[i].y     = 0;
  }
}

void detectTrapColision() {
  if (obstacle[firstObstacle].x - 1 <= 3 && obstacle[firstObstacle].x + 1 >= 0)

    switch (obstacle[firstObstacle].track) {
      case 0:
        if (movementParameter < 1.8 && movementParameter > -1.8) {
          cout << "Udario si u: ";
          switch (obstacle[firstObstacle].type) {
            case 0:
              cout << "X zamku" << endl;
              driveAnimation = 0;
              trapAnimation  = 1;
              activateXtrap  = true;
              break;
            case 1:
              cout << "Rupu" << endl;
              activateHole   = true;
              driveAnimation = 0;
              trapAnimation  = 1;
              break;
            case 2:
              cout << "Bombu" << endl;
              driveAnimation = 0;
              trapAnimation  = 1;
              activateBomb   = true;
              break;
          }
        }
        break;
      case 1:
        if (movementParameter < 5.4 && movementParameter > 1.8) {
          cout << "Udario si u: ";
          switch (obstacle[firstObstacle].type) {
            case 0:
              cout << "X zamku" << endl;
              driveAnimation = 0;
              trapAnimation  = 1;
              activateXtrap  = true;
              break;
            case 1:
              cout << "Rupu" << endl;
              activateHole   = true;
              driveAnimation = 0;
              trapAnimation  = 1;
              break;
            case 2:
              cout << "Bombu" << endl;
              driveAnimation = 0;
              trapAnimation  = 1;
              activateBomb   = true;
              break;
          }
        }
        break;
      case -1:
        if (movementParameter > -5.4 && movementParameter < -1.8) {
          cout << "Udario si u: ";
          switch (obstacle[firstObstacle].type) {
            case 0:
              cout << "X zamku" << endl;
              driveAnimation = 0;
              trapAnimation  = 1;
              activateXtrap  = true;
              break;
            case 1:
              cout << "Rupu" << endl;
              driveAnimation = 0;
              trapAnimation  = 1;
              activateHole   = true;
              break;
            case 2:
              cout << "Bombu" << endl;
              driveAnimation = 0;
              trapAnimation  = 1;
              activateBomb   = true;
              break;
          }
        }
        break;
    }
}

void detectStarColision() {
  if (stars[firstStar].x <= 3 && stars[firstStar].x >= 0) {
    switch (stars[firstStar].track) {
      case 0:
        if (movementParameter < 1.8 && movementParameter > -1.8) {
          starsCollected += 1;
          stars[firstStar].goUp = true;
          cout << "Uhvatio si zvezdicu u srednjoj traci,poeni: " << score
               << endl;
        }
        break;
      case 1:
        if (movementParameter < 5.4 && movementParameter > 1.8) {
          starsCollected += 1;
          stars[firstStar].goUp = true;
          cout << "Uhvatio si zvezdicu u desnoj traci,poeni: " << score << endl;
        }
        break;
      case -1:
        if (movementParameter > -5.4 && movementParameter < -1.8) {
          starsCollected += 1;
          stars[firstStar].goUp = true;
          cout << "Uhvatio si zvezdicu u levoj traci,poeni: " << score << endl;
        }
        break;
    }
  }
}

static void initializeTextures(void) {
  /* Objekat koji predstavlja teskturu ucitanu iz fajla. */
  Image *image;

  /* Postavlja se boja pozadine. */
  glClearColor(0, 0, 0, 0);

  /* Ukljucuje se testiranje z-koordinate piksela. */
  glEnable(GL_DEPTH_TEST);

  /* Ukljucuju se teksture. */
  glEnable(GL_TEXTURE_2D);

  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

  /*
   * Inicijalizuje se objekat koji ce sadrzati teksture ucitane iz
   * fajla.
   */
  image = image_init(0, 0);

  /* Kreira se prva tekstura. */
  image_read(image, FILENAME0);

  /* Generisu se identifikatori tekstura. */
  glGenTextures(5, names);

  glBindTexture(GL_TEXTURE_2D, names[0]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, image->pixels);

  /* Kreira se druga tekstura. */
  image_read(image, FILENAME1);

  glBindTexture(GL_TEXTURE_2D, names[1]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, image->pixels);

  /* Kreira se treca tekstura. */

  image_read(image, FILENAME2);

  glBindTexture(GL_TEXTURE_2D, names[2]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, image->pixels);

  /* Kreira se cetvrta tekstura. */

  image_read(image, FILENAME3);

  glBindTexture(GL_TEXTURE_2D, names[3]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, image->pixels);

  /* Kreira se peta tekstura. */

  image_read(image, FILENAME4);

  glBindTexture(GL_TEXTURE_2D, names[4]);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, image->pixels);

  /* Iskljucujemo aktivnu teksturu */
  glBindTexture(GL_TEXTURE_2D, 0);

  /* Unistava se objekat za citanje tekstura iz fajla. */
  image_done(image);

  /* Inicijalizujemo matricu rotacije. */
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
}

void displayStartScreen() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, names[4]);
  glMatrixMode(GL_PROJECTION);

  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0, windowWidth, 0, windowHeight);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glBegin(GL_QUADS);
  glTexCoord2f(0, 0);
  glVertex2f(0, 0);

  glTexCoord2f(0, 1);
  glVertex2f(0, windowHeight);

  glTexCoord2f(1, 1);
  glVertex2f(windowWidth, windowHeight);

  glTexCoord2f(1, 0);
  glVertex2f(windowWidth, 0);
  glEnd();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  glMatrixMode(GL_MODELVIEW);
}
