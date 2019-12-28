#include <iostream>
#include <GL/glut.h>
#include "theCamera.h"
#include "theVolumes.cpp"
#include "terrain.cpp"

using namespace std;

// Global variables
float _angle = 30.0;
GLint windowWidth = 800;
GLint windowHeight = 600;

// Define camera
Camera *userCamera;

//Core theCore(windowWidth, windowHeight);

Cube cube[5];

Terrain newterra;

GLint windowMidX = windowWidth / 2;
GLint windowMidY = windowHeight / 2;

void handleResize(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();
  gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
  windowMidX = w / 2.0;
  windowMidY = h / 2.0;
  userCamera->windowResize(w, h);
}

// Handling mouse movement, key presses and releases
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
    case 'f':
      userCamera->addGravity = false;
      break;
    case 'g':
      userCamera->addGravity = true;
      break;
    case 't':
      cube[0].displayPosition();
      userCamera->position.display();
      break;
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
    default:
      // Do nothing
      break;
  }
}

void handleSpecialKeys(int key, int x, int y) {
  switch(key) {
    case GLUT_KEY_F11:
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
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glEnable(GL_BLEND);// you enable blending function
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  // then you will set flags to achieve desired blending effect.
  glClearColor(0.0, 0.0, 0.0, 1.0);
}

// Draw shapes and lights
void drawScene() {
  //Clears info from last draw
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //Adding ambient light
  GLfloat ambientColor[] = {0.2, 0.2, 0.2, 1.0};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

  //Add positioned light
  GLfloat lightColor0[] = {1.0, 1.0, 1.0, 1.0};
  GLfloat lightPos0[] = {30.0, 10.0, -100.0, 1.0};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

  //Add directed lighting
  GLfloat lightColor1[] = {0.2, 0.2, 0.2, 0.0};
  GLfloat lightPos1[] = {0.0, 0.0, -15.0, 0.0};
  glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
  glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

  glMatrixMode(GL_MODELVIEW); // Switches to the drawing perspective
  glLoadIdentity(); // Resets the drawing perspective

  // ########################## CAMERA MOVEMENTS ######################################

  glRotatef(userCamera->getXRot(), 1.0, 0.0, 0.0); //Rotate camera on x-axis
  glRotatef(userCamera->getYRot(), 0.0, 1.0, 0.0); //Rotate camera on y-axis
  // glutWireSphere(1.0, 10.0, 10.0);
  // Translate ModelView matrix to the position of our camera
  glTranslatef(-userCamera->getXPos(), -userCamera->getYPos(), -userCamera->getZPos());
  // ##################################################################################

  // // Guidelines for quadrants
  // glPushMatrix();
  // glBegin(GL_LINES);
  //   glColor3f(1.0, 1.0, 1.0);
  //   for(int i = 0; i <= 200; i++) {
  //     glVertex3f(i, 0.0, 0.0);
  //     glVertex3f(-i, 0.0, 0.0);
  //     glVertex3f(0.0, i, 0.0);
  //     glVertex3f(0.0, -i, 0.0);
  //     glVertex3f(0.0, 0.0, i);
  //     glVertex3f(0.0, 0.0, -i);
  //   }
  // glEnd();
  // glPopMatrix();

  glPushMatrix();
  glTranslatef(50.0, -17.5, 10.0);
  newterra.generateTerrain(55, 75);
  glPopMatrix();

  // Testing new terrain generation here
  // glPushMatrix();
  // newterra.generateTerrain(50, 50);
  // glPopMatrix();

  // DRAWING CUBES HERE
  glTranslatef(17.5, -10.0, -20.0);
  cube[0].updatePosition(17.5, -10.0, -20.0);
  glPushMatrix(); //saves the current translation
    cube[0].drawCube(15.0);
  glPopMatrix();

  glTranslatef(-35.0, 2.5, 0.0);
  cube[1].updatePosition(-17.5, -7.5, -20);
  glPushMatrix(); //saves the current translation
    // glScalef(1.0, 4.0, 1.0);
    cube[1].drawCube(20.0);
  glPopMatrix();

  glTranslatef(0.0, -2.5, -15.0);
  cube[2].updatePosition(-17.5, -10.0, -35);
  glPushMatrix(); //saves the current translation
    cube[2].drawCube(15.0);
  glPopMatrix();

  glTranslatef(35.0, 0.0, -5.0);
  cube[3].updatePosition(17.5, -10.0, -40.0);
  glPushMatrix(); //saves the current translation
    cube[3].drawCube(15.0);
  glPopMatrix();

  glTranslatef(0.0, 0.0, -20.0);
  cube[4].updatePosition(17.5, -10.0, -60.0);
  glPushMatrix(); //saves the current translation
    cube[4].drawCube(15.0);
  glPopMatrix();

  glTranslatef(-35.0, 0.0, 0.0);
  cube[5].updatePosition(-17.5, -10.0, -60.0);
  glPushMatrix(); //saves the current translation
    cube[5].drawCube(15.0);
  glPopMatrix();


  glutSwapBuffers(); //This sends the 3D scene to the screen
}

void collCheck(double x1, double y1, double z1, float width) { // Collision checking method
  // This is the size of the user
  double sizeSum = 1.5 + (width / 2);

  if (abs(userCamera->getXPos() - x1) < sizeSum) {
    double a = userCamera->getXPos();
    if (abs(userCamera->getYPos() - y1) < sizeSum) {
      double b = userCamera->getYPos();
      if (abs(userCamera->getZPos() - z1) < sizeSum) {
        double c = userCamera->getZPos();
        userCamera->lastPos(a, b, c);
        userCamera->collision = true;
      }
    }
  }
}

void update(int value) {
  userCamera->move(0.02); // Passing deltaTime to move function

  // Currently using this as a floor for testing
  if (userCamera->getYPos() < -14.1) { userCamera->position.y = -14.0;}

  // Using Axis Aligned Bound Box (AABB) checking for collision
  for (int i = 0; i < 6; i++) {
    collCheck(cube[i].getXPos(), cube[i].getYPos(), cube[i].getZPos(), cube[i].getSize());
  }

  glutPostRedisplay(); //Tell GLUT the scene had changed

  //Tell glut to call the update again in 16 milliseconds
  glutTimerFunc(16, update, 0);
}

void idleFunc() {
  glutWarpPointer(windowMidX-1, windowMidY-1);
}

int main(int argc, char** argv) {
  //Initializing GLUT
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  userCamera = new Camera(windowWidth, windowHeight);
  glutInitWindowSize(windowWidth, windowHeight);

  // Here is for creating the window
  glutCreateWindow("Lighting and Collision");
  initRendering();

  glutSetCursor(GLUT_CURSOR_NONE);
  //Setting Handler functions
  glutDisplayFunc(drawScene);

  glutPassiveMotionFunc(mouseMove);
  glutKeyboardFunc(handleDownKeys);
  glutKeyboardUpFunc(handleUpKeys);
  glutSpecialFunc(handleSpecialKeys);


  glutReshapeFunc(handleResize);
  glutTimerFunc(16, update, 0);
  glutIdleFunc(idleFunc);

  glutMainLoop(); //Start the main loop
  return 0;

}
// Lighting and collision
