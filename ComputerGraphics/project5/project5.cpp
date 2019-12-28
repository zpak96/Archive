// Zane Paksi Project 5

#include "core.hpp"

using namespace std;

float _bicepX = 0.0;
float _bicepZ = 0.0;
bool bicepIdle = false;

float _forearmRot = 0.0;

float _clawRot;
float clawIncrement = 1.5;

bool onButton = false;

Camera *userCamera;

float dist;
float dx, dy, dz;

// Instantiate a new core with window width and height
Core newCore;

Rectangle bicep[2];
Rectangle forearm[2];
Rectangle digit[5];

Terrain theFloor;
Sphere base;

void handleResize(GLint w, GLint h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
  gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
  newCore.windowResize(w, h);
}

void handleDownKeys(unsigned char key, int x, int y) {
  switch(key) {
    case 27:
      exit(EXIT_SUCCESS);
    case 'w':
      glutIgnoreKeyRepeat('w');
      userCamera->holdForward = true;
      break;
    case 'a':
      glutIgnoreKeyRepeat('a');
      userCamera->holdLeft = true;
      break;
    case 's':
      glutIgnoreKeyRepeat('s');
      userCamera->holdBackward = true;
      break;
    case 'd':
      glutIgnoreKeyRepeat('d');
      userCamera->holdRight = true;
      break;
    case ' ':
      glutIgnoreKeyRepeat(' ');
      userCamera->holdSpace = true;
      break;
    case 'c':
      glutIgnoreKeyRepeat('c');
      userCamera->holdC = true;
      break;
    case 'f':
      userCamera->addGravity = false;
      break;
    case 'g':
      userCamera->addGravity = true;
      break;
    case 't':
      userCamera->camPos.display();
      break;
    case 'o':
      _clawRot = userCamera->getXPos() + userCamera->getZPos() + userCamera->getYPos();
      onButton = true;
      break;
    case 'p':
      onButton = false;
    default:
      // Do nothing
      break;
  }
}

void handleUpKeys(unsigned char key, int x, int y) {
  switch(key) {
    case 'w':
      userCamera->holdForward = false;
      break;
    case 'a':
      userCamera->holdLeft = false;
      break;
    case 's':
      userCamera->holdBackward = false;
      break;
    case 'd':
      userCamera->holdRight = false;
      break;
    case ' ':
      userCamera->holdSpace = false;
      break;
    case 'c':
      userCamera->holdC = false;
      break;
    default:
      // Do nothing
      break;
  }
}

void handleSpecialKeys(int key, int x, int y) {
  switch(key) {
    case GLUT_KEY_F11:
      // glutReshapeWindow(1280, 720);
      glutFullScreen();
      glutReshapeFunc(handleResize);
      break;
    case GLUT_KEY_F12:
      glutReshapeWindow(800, 600);
      glutReshapeFunc(handleResize);
      break;
    default:
      // Do nothing
      break;
  }
}

void mouseMove(int mouseX, int mouseY) {
  userCamera->handleMouseMove(mouseX, mouseY);
}

// Rendering views and enabling lights
void initRendering() {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);

  glShadeModel(GL_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);

  glClearColor(1.0, 0.7, 0.0, 1.0);
}

void drawScene() {
  // Light Variables
  GLfloat ambientColor[] = {0.2, 0.2, 0.2, 1.0};
  GLfloat lightColor0[] = {0.5, 0.5, 0.5, 1.0}; // Directional Lighting
  GLfloat lightPos0[] = {0.0, -1.0, 0.0, 1.0};
  GLfloat lightColor1[] = {0.5, 0.2, 0.2, 0.0}; // Ambient Lighting
  GLfloat lightPos1[] = {-1.0, 0.5, 0.5, 0.0};

  //Clears info from last draw
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //Adding ambient light
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

  //Add directional light
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

  //Add Ambient lighting
  glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
  glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

  // Switches to the drawing perspective
  glMatrixMode(GL_MODELVIEW);
  // Reset the drawing perspective
  glLoadIdentity();

  // ########################## CAMERA MOVEMENTS ######################################

  glRotatef(userCamera->getXRot(), 1.0, 0.0, 0.0); //Rotate camera on x-axis
  glRotatef(userCamera->getYRot(), 0.0, 1.0, 0.0); //Rotate camera on y-axis

  // Translate ModelView matrix to the position of our camera
  glTranslatef(-userCamera->getXPos(), -userCamera->getYPos(), -userCamera->getZPos());

  // ################ DRAW TERRAIN AND SHAPES HERE ####################################

  glPushMatrix();
    glTranslatef(50.0, -6.0, 25.0);
      glTranslatef(-userCamera->getXPos(), -userCamera->getYPos(), 0.0);
    theFloor.genTerrain(100, 400);
  glPopMatrix();

  glTranslatef(0.0, -6.0, -150.0);
  glRotatef(90.0, 0.0, 1.0, 0.0);

  glPushMatrix();
    // glTranslatef(0.0, 0.0, -5.0);
    // glScalef(2.0, 1.0, 2.0);
    glutSolidSphere(5.0, 10.0, 10.0);
  glPopMatrix();

  glPushMatrix();
    // Initial bicep rotation - not being incremented
    // Translate bicep up from base sphere
    glRotatef(_angle, 0.0, 0.0, 1.0);
    glRotatef(_bicepZ, 1.0, 0.0, 1.0);
    glRotatef(-userCamera->getYRot(), 0.0, 1.0, 0.0);
    glTranslatef(0.0, 5.0, 0.0);

    // Build bicep
    bicep[0].genRectangle(4.0);
    glTranslatef(-0.5, 3.4, 0.0);
    glRotatef(15.0, 0.0, 0.0, 1.0);
    bicep[1].genRectangle(4.0);

    // Translate above bicep and generate elbow
    glTranslatef(0.0, 4.0, 0.0);
    glutSolidSphere(3, 10.0, 10.0);

    glRotatef(-userCamera->getXRot(), 1.0, 0.0, 0.0);

    // Adding a slight rotation to forearm and up for beginning pose
    glRotatef(40.0, 0.0, 0.0, 1.0);
    // Translate above elbow and build forearm
    glRotatef(userCamera->getXRot(), 0.0, 0.0, -1.0);
    glTranslatef(0.0, 4.0, 0.0);
    forearm[0].genRectangle(4);

    // Translate above forarm and generate some sort of hand
    glTranslatef(0.0, 4.0, 0.0);
    // glRotatef(_bicepZ*2, 0.0, 0.0, 1.0);
    glutSolidSphere(3.0, 10.0, 10.0);

    // Idle rotation of the claw
    glRotatef(_clawRot, 0.0, 1.0, 0.0);

    glRotatef(_angle, 0.0, 0.0, -1.0);
    glTranslatef(0.0, 3.5, 0.0);
    digit[0].genRectangle(2);
    glTranslatef(0.0, 0.45, 0.0);
    glRotatef(90.0, 0.0, 0.0, 1.0);
    digit[1].genRectangle(1);

    // Weird formatting to get the second claw looking right
    glTranslatef(-7.0, 1.0, 0.0);
    glRotatef(-15.0, 0.0, 0.0, 1.0);
    digit[2].genRectangle(2);
    glTranslatef(0.0, 0.45, 0.0);
    glRotatef(90.0, 0.0, 0.0,-1.0);
    digit[4].genRectangle(1);

  glPopMatrix();

  // ################ END OF DRAWING ################
  glutSwapBuffers(); //This sends the 3D scene to the screen
}

// Handles the screen refresh
void refresh(int value) {
  // _angle += 1.0;
  // if (_angle > 360) {
  //   _angle -= 360;
  // }

  if (onButton) {
    dx = 0.0 - userCamera->getXPos();
    dy = -6 - userCamera->getYPos();
    dz = -150 - userCamera->getZPos();
    dist = sqrt(dx * dx + dy * dy + dz * dz);

    if (dist < 70) {
      clawIncrement = 95;
    } else {
      clawIncrement = 1.5;
    }

    switch (bicepIdle) {
      case false:
        _bicepZ += 0.08;
        _clawRot += clawIncrement;
        _forearmRot -= 0.3;
        if (_bicepZ > 20.0) {
          bicepIdle = true;
        }
        break;
      case true:
        _bicepZ -= 0.08;
        _clawRot -= clawIncrement;
        _forearmRot += 0.3;
        if (_bicepZ < -20.0) {
          bicepIdle = false;
        }
        break;
    }


  }

  userCamera->move(0.02); // Passing deltaTime to move function

  // Currently using this as a floor for testing
  if (userCamera->getYPos() < -2.01) { userCamera->camPos.y = -2.0;}

  glutPostRedisplay(); //Tell GLUT the scene had changed

  //Tell glut to call the update again in 16 milliseconds
  glutTimerFunc(16, refresh, 0);
}

// This method is called after all other method in the main loop
void idleFunc() {
  glutWarpPointer(newCore.getMidX()-1, newCore.getMidY()-1);
}

int main(int argc, char** argv) {
  // Initialize GLUT
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  // Instantiate userCamera
  userCamera = new Camera();

  glutInitWindowSize(800, 600);

  // Here is for creating the window
  glutCreateWindow("Project 5 | Animation");
  initRendering();

  glutSetCursor(GLUT_CURSOR_NONE);

  // ###### HANDLER FUNCTIONS ######
  glutDisplayFunc(drawScene);

  // Input handlers
  glutPassiveMotionFunc(mouseMove);
  glutKeyboardFunc(handleDownKeys);
  glutKeyboardUpFunc(handleUpKeys);
  glutSpecialFunc(handleSpecialKeys);

  glutReshapeFunc(handleResize);
  glutTimerFunc(16, refresh, 0);
  glutIdleFunc(idleFunc);

  glutMainLoop(); //Start the main loop
  return 0;

}
